(ns cgp.jure
  (:require [clojure.tools.macro :as macro]))

(defmacro defn10
  "A clone of `defn`."
  [symb & defn-args]
  (let [[symb body] (macro/name-with-attributes symb defn-args)]
    `(defn ~symb ~@body)))

(defn10 add
  "ooooooooooooooooo"
  ([] 1))

(meta #'add)

(add)

(defroutes app
  (GET "/" [] "<h1>Hello World</h1>")
  (route/not-found "<h1>Page not found</h1>"))
