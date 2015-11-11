(ns cpg.core
  (:require [clojure.string :as str]))

(defprotocol Jsonable
  (to-json [this]))

(defrecord User [name age gender])

(extend-protocol Jsonable
  Integer
  (to-json [this] this)

  java.lang.Long
  (to-json [this] this)

  String
  (to-json [this] (str "\"" this "\""))

  clojure.lang.MapEntry
  (to-json [this]
    (let [k (key this)
          value (to-json (val this))]
      (str "\"" (name k) "\" : " value)))

  User
  (to-json [this]
    (let [obj (str/join ",\n  " (map #(to-json %) this))]
      (str "{ \n" obj "\n }"))))


(to-json (User. "ganmacs" 24 "man"))
