local directory(recurse=false) =
  local r = (if recurse then { recurse: true} else {});
  if recurse then { directory: r } else {};

{
  app(name, path, namespace="default", recurse=false): {
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
        path: path,
      } + directory(recurse),
      destination: {
        server: "https://kubernetes.default.svc",
        namespace: namespace,
      },
    },
  },
  systemApp(name, namespace="argocd", recurse=false): self.app(name, "k8s/deployment2/system/%s" % name, namespace, recurse),

}
