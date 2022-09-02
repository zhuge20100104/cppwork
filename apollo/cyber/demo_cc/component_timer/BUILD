# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "timer_cpt_lib",
    srcs = ["timer_cpt.cc"],
    hdrs = ["timer_cpt.h"],
    deps = ["//cyber"],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "libtimer_cpt.so",
    linkshared = True,
    linkstatic = False,
    deps = [":timer_cpt_lib"],
)