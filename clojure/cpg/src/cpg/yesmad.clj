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
  (slurp* [s] (safe-slurp s)))

(defn- get-hostname []
  (.trim (:out (sh "hostname"))))

(defn- get-environment []
  (or (System/getProperty "nomad.env")))

(defn- read-config-file [file-or-resource]
  (slurp* file-or-resource))

(defn- update-config [current-config target-key from-key selector value]
  (let [{new-upstream-config :config} (get current-config from-key)]
    (assoc current-config
           target-key
           {:config (get-in new-upstream-config [selector value])})))

(defn- yesmad-data-reader [snippet-reader]
  {'yesmad/snippet snippet-reader})

(defn- without-snippets-reader []
  (yesmad-data-reader (constantly ::snippet)))

(defn- with-snippets-reader [snippets]
  (yesmad-data-reader
   (fn [ks]
     (or
      (get-in snippets ks)
      (pprint ks)
      (pprint snippets)
      (throw (ex-info "No snippet found for keys" {:keys ks}))))))

(defn- load-edn-file [file-or-resource]
  (let [config-file-string (read-config-file file-or-resource)
        without-map (edn/read-string {:readers (without-snippets-reader)} config-file-string)
        snippets (get without-map :yesmad/snippets)]
    (edn/read-string {:readers (with-snippets-reader snippets)} config-file-string)))

(defn- attach-location [configs]
  (assoc configs
         :location {:yesmad/host (get-hostname)}))

(defn- attach-config [config-map config-file]
  (assoc config-map
         :config (load-edn-file config-file)))

(defn build-config [config-file]
  (-> (deep-merge (or (get-in config-file [:general :config]) {})
                  (or (get-in config-file [:host :config] {})) {})
      (dissoc :yesmad/hosts :yesmad/snippets)))

(defn load-config [file-or-resource]
  (let [config-map {:general {:config-file file-or-resource}}]
    (build-config
     (-> config-map
         (update-in [:general] attach-config (get-in config-map [:general :config-file]))
         (update-config :host :general :yesmad/hosts (get-hostname))
         attach-location))))

(defmacro defconfig [name file-or-resource]
  `(let [cached-config# (atom nil)]
     (defn ~name []
       (swap! cached-config#
              (fn [f#]
                ;; TODO use f#
                (load-config ~file-or-resource))))))

;; -- api
(defconfig my-config (io/resource "server.edn"))
(pprint (my-config))
