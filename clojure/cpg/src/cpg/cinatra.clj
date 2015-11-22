(ns cpg.cinatra)

(defprotocol Routes
  (routes-match [route request]))

(defprotocol Render
  (render [render body]))

(defprotocol Handler
  (handle [handler body]))

(defrecord Foo [f]
  Routes
  (routes-match [_ request]
    request))

(extend-protocol Render
  Foo
  (render [_ body] (str body)))

(render (routes-match (Foo. "a") "k"))
(some-> {:a 1} :b inc)

(defn response [body]
  {:status 200
   :header {}
   :body body})

(defn header [response name value]
  (assoc-in response [:header name] value))

(defn status [response status]
  (assoc response :status status))

(defn content-type [response value]
  (header response "Content-type" value))

(-> (response "foo=bar")
    (content-type "text/json;char-set=utf8")
    (status 410))

(defmulti fact pos?)

(defmethod fact true [x]
  (* x (fact (dec x))))

(defmethod fact false [x] 1)

(defn foo [request]
  (if-let [body (:body request)] body "non"))

(defmulti greeting2
  (fn [x] (:language x)))

(defmethod greeting2 :japanese [p]
  "foo2")

(defmethod greeting2 :english [p]
  "bar")

(defmethod greeting2 :nil [p]
  "hoge")

(let [j {:language :japanese}
      e {:language :english}]
  (greeting2 j))

(:foo {:foo2 (fn [x] (inc x))} 1)


(defn ll [x]
  (if (pos? x)
    (* x (ll (dec x)))
    1))

(defn x [y] (memoize (ll y)))

(time (x 20))
