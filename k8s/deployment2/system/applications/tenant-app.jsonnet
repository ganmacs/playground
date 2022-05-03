local base = import 'base.libsonnet';
local name = "tenant-apps";
base.app(name, "k8s/deployment2/tenant/applications", "default", false)
