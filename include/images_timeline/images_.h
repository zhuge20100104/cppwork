#ifndef _FREDRIC_IMAGES_H_
#define _FREDRIC_IMAGES_H_

#include "images_timeline/screenshots.h"

std::vector<screenshots> get_screenshots_from_db();

bool test_all_images_can_be_accessed();

bool test_meta_is_correct();

std::vector<icon_url> get_icon_url_from_db();

bool test_all_icons_can_be_accessed();

bool test_icons_are_correct();

#endif