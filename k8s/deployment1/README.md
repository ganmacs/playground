## 1. Bootstrap

```
$ cd bootstrap
$ kubectl apply -k . && kubectl apply -f application.yaml
```


### 2. update system

```
$ cd system
// eit helmfile
$ helmfile template --output-dir . --output-dir-template .

// update/add application settings under applications

```
