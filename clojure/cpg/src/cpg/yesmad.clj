(ns cpg.yesmad
  (:require [clojure.java.io :as io]))

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
  (slurp* [url] (safe-slurp url (str {}))))

(defn read-config [file-or-resource]
  (let [config-map {:general {:config-file file-or-resource}}]
    (slurp* file-or-resource)))

(defmacro defconfig [name file-or-resource]
  `(defn ~name []
     (read-config ~file-or-resource)))

(defconfig my-config (io/resource "server.edn"))

(def -main []
  (println "does not work!!"))
