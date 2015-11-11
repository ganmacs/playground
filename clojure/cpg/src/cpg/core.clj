(ns cpg.core
  (:require [clojure.string :as str]))

(defrecord User [^String name ^Integer age gender])

(defprotocol Jsonable
  (to-json [this]))

(extend-protocol Jsonable
  Integer
  (to-json [this] this)

  java.lang.Long
  (to-json [this] this)

  String
  (to-json [this] (format "\"%s\"" this))

  clojure.lang.MapEntry
  (to-json [this]
    (format "\"%s\": %s"
            (name (key this))
            (to-json (val this))))

  User
  (to-json [this]
    (format "{\n  %s\n}"
            (str/join ",\n  " (map #(to-json %) this)))))

(println (to-json (User. "ganmacs" 24 "man")))
