(ns cpg.yesmad
  (:require [clojure.java.io :as io]
            [clojure.edn :as edn]
            [clojure.java.shell :refer [sh]]
            [clojure.pprint  :refer [pprint]]))

;; util
(defn- deep-merge [& maps]
  (if (every? map? maps)
    (apply merge-with deep-merge maps)
    (last maps)))

(defprotocol ConfigFile
  (slurp* [_]))

(defn- safe-slurp [f default]
  (try
    (slurp f)
    (catch Exception e
      default)))

(extend-protocol ConfigFile
  java.io.File
  (slurp* [file] (safe-slurp file (str {})))

  java.net.URL
  (slurp* [url] (safe-slurp url (str {})))

  java.lang.String
  (slurp* [s] (safe-slurp s))

  nil
  (slurp* [s] (str {})))

(defn- get-hostname []
  (.trim (:out (sh "hostname"))))

(defn- get-environment []
  (or (System/getProperty "yesmad.env")))

(defn- update-private-config [configs src-key dest-key]
  (let [private-file (get-in configs [src-key :config :yesmad/private-file])]
    (pprint private-file)
    (assoc configs
           dest-key (load-edn-file private-file))))

(defn- attach-location [configs]
  (assoc configs
         :location {:yesmad/host (get-hostname)}))

(defn- yesmad-data-reader [snippet-reader]
  {'yesmad/snippet snippet-reader
   'yesmad/file io/file})

(defn- without-snippets-reader []
  (yesmad-data-reader (constantly ::snippet)))

(defn- with-snippets-reader [snippets]
  (yesmad-data-reader
   (fn [ks]
     (or
      (get-in snippets ks)
      (throw (ex-info "No snippet found for keys" {:keys ks}))))))

(defn extract-snippets [config-str]
  (let [edn (edn/read-string {:readers (without-snippets-reader)} config-str)]
    (get edn :yesmad/snippets)))

(defn- load-config-file [file-resource]
  (let [config-str (slurp* file-resource)
        snippets (extract-snippets config-str)]
    ;; expand-reader-macro
    (edn/read-string {:readers (with-snippets-reader snippets)}
                     config-str)))

(defn- attach-attr [config-map new-attr {:keys [pkey subkey]}]
  (let [{new-config :config} (get config-map pkey)]
    (assoc config-map
           new-attr {:config (get-in new-config subkey)})))

(defn- attach-private-attr [config-map new-attr src-key]
  (let [private-file (get-in config-map [src-key :config :yesmad/private-file])]
    (assoc config-map
           new-attr {:config (load-config-file private-file)})))

(get-in {:a {:b {"c" 2}}} [:a :b "c"])

(defn cleanup-config [config-file]
  (-> (deep-merge (or (get-in config-file [:general :config]) {})
                  (or (get-in config-file [:general-private :config]) {})
                  (or (get-in config-file [:host :config]) {})
                  (or (get-in config-file [:host-private :config]) {}))
      (dissoc :yesmad/hosts :yesmad/snippets :yesmad/private-file)))

(defn build-config [file-or-resource]
  (let [config-file (load-config-file file-or-resource)
        config-map {:general {:config-file file-or-resource
                              :config config-file}}]
    (cleanup-config
     (-> config-map
         (attach-attr :host {:pkey :general, :subkey [:yesmad/hosts (get-hostname)]})
         (attach-private-attr :general-private :general)
         (attach-private-attr :host-private :host)))))

(defmacro defconfig [name file-or-resource]
  `(let [cached-config# (atom nil)]
     (defn ~name []
       (swap! cached-config#
              (fn [f#]
                ;; TODO use f#
                (build-config ~file-or-resource))))))

;; -- api
(defconfig my-config (io/resource "file.edn"))
(pprint (my-config))
