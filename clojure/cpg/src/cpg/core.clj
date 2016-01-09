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


(with-meta 'foo {:doc 1})
(meta 'foo)

(def vv (with-meta [1 2 3] {:doc "fuu"}))
(def vvv [2])

(meta (let [attr (conj (meta vv) {:foo "var"})]
        (with-meta vv attr)))
(atom {})

(defrecord Mode [name])

(defrecord Task [name mode])

(defprotocol Runable
  (run [task]))

(extend-type Task
  Runable
  (run [this]
    (if-let [mode (:mode this)]
      (str
       (:name this)
       " in "
       (:name mode)))))

(run (Task.
      "Create some file"
      (Mode. "dry-run-mode")))


(defrecord Exprs [exprs])
(defrecord Prim [op oprand1 oprand2])
(defrecord Op [v])
(defrecord Int [v])
(defrecord Bool [v])

(defprotocol AST
  (eeval [this]))                     ;maybe it willl be passed env in the furture

(extend-protocol AST
  Exprs
  (eeval [this]
    (map #(eeval %) this))

  Prim
  (eeval [p]
    (let [op (eeval (:op p))
          oprand1 (eeval (:oprand1 p))
          oprand2 (eeval (:oprand2 p))]
      (apply :+ [oprand1 oprand2])))

  Op
  (eeval [o] (:v o))

  Int
  (eeval [o] (:v o))

  Bool
  (eeval [o] (:v o)))


(eeval
 (Prim. (Op. :+) (Int. 10) (Int. 10))
 )

()

(defmacro sends [op & body]
  `(~op ~@body))

(sends + 10 10)

(def a "a")
(def b "a")
(def c "a")

(let [m {:a 1 :b 2 :c 3}]
  (-> m
      keys
      ((partial map (comp symbol name)))
      vec))


(-> [:a :b :c]
    ((fn [xs] (map (comp symbol name) xs)))
    )


(defmacro mapie [n m]
  (let [kewords2symbols (fn [xs] (map (comp symbol name) xs))
        map-keys (-> m keys (kewords2symbols) vec)]
    `(defrecord ~n ~map-keys)))

(mapie Foo {:a 1 :b 2 :c 3})

(:a (Foo. 1 2))
