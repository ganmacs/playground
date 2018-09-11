def _repository_rule_impl(ctxt):
    ctxt.symlink(Label("//thirdparty:BUILD"), "BUILD")
    ctxt.symlink(Label("//thirdparty:build.sh"), "build.sh")
    ctxt.symlink(Label("//thirdparty:Makefile"), "Makefile")
    for r in ctxt.attr.repos:
        ctxt.symlink(Label("//thirdparty:build_scripts/" + r + ".sh"),
                     "build_scripts/" + r + ".sh")
    result = ctxt.execute(["./build.sh"] + ctxt.attr.repos)
    print(result.stdout)
    # print(result.stderr)
    if result.return_code != 0:
        fail("external dep build faield")


vega_repository = repository_rule(
    implementation = _repository_rule_impl,
    environ = [
        "CC",
        "CXX",
        "LD_LIBRARY_PATH",
        "CFLAGS",
        "CXXFLAGS",
        "LD_LIBRARY_PATH"
    ],
    local = True,
    attrs = {
        "repos": attr.string_list(),
    },
)
