{
  systemApp: function(name, recurse=true) {
    apiVersion: "argoproj.io/v1alpha1",
    kind: "Application",
    metadata: {
      name: name,
      namespace: "argocd",
      // finalizers: [
      //   "resources-finalizer.argocd.argoproj.io",
      // ]
    },
    spec: {
      project: "default",
      source: {
        repoURL: "https://github.com/ganmacs/playground.git",
        targetRevision: "HEAD",
        path: "k8s/deployment2/system/%s" % name,
        directory: {
          recurse: recurse,
        },
      },
      destination: {
        server: "https://kubernetes.default.svc",
        namespace: "argocd",
      },
    },
  },
}
