{
  app(name, recurse=false): {
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
        path: "k8s/deployment2/tenant/%s" % name,
        directory: {
          recurse: recurse,
        },
      },
      destination: {
        server: "https://kubernetes.default.svc",
        namespace: "default",
      },
    },
  },
}
