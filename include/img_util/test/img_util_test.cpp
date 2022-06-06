#include <img_util/img_util.h>

#include <gtest/gtest.h>


GTEST_TEST(ImageUtilTests, CompareEqual) {
    const std::string src_img = "../images/src.png";
    const std::string dst_img = "../images/dst.png";
    bool is_equal = ImageUtil::compare_equal(src_img, dst_img);
    ASSERT_TRUE(is_equal);
}

GTEST_TEST(ImageUtilTests, CompareNotEqual) {
    const std::string src_img = "../images/src.png";
    const std::string dst_img = "../images/dst2.png";
    bool is_equal = ImageUtil::compare_equal(src_img, dst_img);
    ASSERT_FALSE(is_equal);
}

GTEST_TEST(ImageUtilTests, CompareSizeNotEqual) {
    const std::string src_img = "../images/src.png";
    const std::string dst_img = "../images/dst3.png";
    bool is_equal = ImageUtil::compare_equal(src_img, dst_img);
    ASSERT_FALSE(is_equal);
}