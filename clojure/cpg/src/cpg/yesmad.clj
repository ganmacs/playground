(ns cpg.yesmad
  (:require [clojure.java.io :as io]
            [clojure.edn :as edn]
            [clojure.java.shell :refer [sh]]))

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

(defn- read-config-file [file-or-resource]
  (slurp* file-or-resource))

(defn- update-config [current-config target-key from-key selector value]
  (let [{new-upstream-config :config} (get current-config from-key)]
    (assoc current-config
           target-key
           {:config (get-in new-upstream-config [selector value])})))

(defn- load-edn-file [file-or-resource]
  (edn/read-string (read-config-file file-or-resource)))

(defn- attach-location [configs]
  (assoc configs
         :location {:yesmad/hostname (get-hostname)}))

(defn- attach-config [config-map config-file]
  (assoc config-map
         :config (load-edn-file config-file)))

(defn load-config [file-or-resource]
  (let [config-map {:general {:config-file file-or-resource}}]
    (do
      (println (-> config-map
                   (update-in [:general] attach-config (get-in config-map [:general :config-file]))
                   (update-config :host :general :nomad/hosts (get-hostname))
                   attach-location
                   ;; (expand-host-variable)
                   ))
      (read-config-file (get-in config-map [:general :config-file])))))

(defmacro defconfig [name file-or-resource]
  `(let [cached-config# (atom nil)]
     (defn ~name []
       (swap! cached-config#
              (fn [f#]
                ;; TODO use f#
                (load-config ~file-or-resource))))))
;; -- api
(defconfig my-config (io/resource "server.edn"))
(my-config)
