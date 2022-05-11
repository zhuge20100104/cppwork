#include "images_timeline/images_.h"

#include <gtest/gtest.h>

GTEST_TEST(ImagesTests, GetScreenshotsFromDB) {
    auto screenshots = get_screenshots_from_db();
    ASSERT_EQ(10, screenshots.size());
}

GTEST_TEST(ImagesTests, AllImagesCanBeAccessed) {
    bool ret = test_all_images_can_be_accessed();
    ASSERT_TRUE(ret);
}

GTEST_TEST(ImagesTests, MetaIsCorrect) {
    bool ret = test_meta_is_correct();
    ASSERT_TRUE(ret);
}


GTEST_TEST(ImagesTests, GetIconUrlFromDb) {
    auto res = get_icon_url_from_db();
    ASSERT_EQ(100, res.size());
}

GTEST_TEST(ImagesTests, TestAllIconsCanBeAccessed) {
    auto res = test_all_icons_can_be_accessed();
    ASSERT_TRUE(res);
}

GTEST_TEST(ImagesTests, TestIconsAreCorrect) {
    auto res = test_icons_are_correct();
    ASSERT_TRUE(res);
}