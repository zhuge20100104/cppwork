cc_binary(
    name="front_laser",
    srcs=["front_laser.cc"],
    deps=[
        "//cyber",
        "//cyber/demo_base_proto:lasers_proto_cc"],
)

cc_binary(
    name="back_laser",
    srcs=["back_laser.cc"],
    deps=[
        "//cyber",
        "//cyber/demo_base_proto:lasers_proto_cc"],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "laser_cpt_lib",
    srcs = ["lasers_cpt.cc"],
    hdrs = ["lasers_cpt.h"],
    deps = [
        "//cyber",
        "//cyber/demo_base_proto:lasers_proto_cc"],
)

cc_binary(
    name = "liblaser_cpt.so",
    linkshared = True,
    linkstatic = False,
    deps = [":laser_cpt_lib"],
)