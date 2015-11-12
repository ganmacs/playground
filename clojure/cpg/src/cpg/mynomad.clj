(ns cgp.mynomad
  (:require [clojure.java.io :as io]))

(def a (io/file (io/resource ".gitignore")))

(def v (atom []))
(swap! v conj 1)

(def foo (ref []))
(deref foo)
@foo

(def current-state (ref "running"))
@current-state

(dosync (ref-set current-state "stoping"))

(def current-song (atom "rainbow"))

(reset! current-song "hoeg")


(defmacro speed-set [name]
  `(let [speed# (atom 1)]
     (defn ~name []
       (swap! speed# (fn [x#]
                       (println x#)
                       (+ 1 x#))))))

(defmacro speed-set2 [name f]
  `(let [speed# (atom 1)]
     (defn ~name []
       (swap! speed# ~f))))

(speed-set add)
(speed-set2 sub #(dec %))
(speed-set2 add #(inc %))

(sub)
(add)

(def speed (atom 0))

(defmacro speed-set3 [name f]
  `(defn ~name []
     (swap! speed ~f)))

(speed-set3 add #(inc %))
(speed-set3 sub #(dec %))
(speed-set3 reset (fn [_] 0))

(add)
(sub)
(reset)

(def user {:name "ganmacs", :age 20 })
(update-in user [:age] + 1)


(let [ v (-> user (update-in [:age] + 11))]
  (vector (get-in v [:age])
       (get-in v [:name])))


((fn [{f :name}] f) user)
(let [{f :v} user] f)
