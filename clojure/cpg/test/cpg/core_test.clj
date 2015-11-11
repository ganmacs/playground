(ns cpg.core-test
  (:require [clojure.test :refer :all]
            [cpg.core :refer :all]))

(deftest integer-jsonable-test
  (testing "integer jsonable"
    (is (= 1 (to-json 1)))))

(deftest string-jsonable-test
  (testing "string jsonable"
    (is (= "\"a\"" (to-json "a")))))

(deftest user-jsonable-test
  (testing "user jsonable"
    (is (= "\"a\"" (to-json (User. "name" 1 1))))))
