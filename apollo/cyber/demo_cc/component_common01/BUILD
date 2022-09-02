package(default_visibility = ["//visibility:public"])

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "common_cpt_lib",
    srcs = ["common_cpt.cc"],
    hdrs = ["common_cpt.h"],
    deps = [
        "//cyber",
        "//cyber/demo_base_proto:student_cc"
    ],
)

cc_binary(
    name = "lib_common_cpt.so",
    linkshared = True,
    linkstatic = False,
    deps = [":common_cpt_lib"],
)




