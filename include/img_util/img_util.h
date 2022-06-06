#ifndef _FREDRIC_IMG_UTIL_H_
#define _FREDRIC_IMG_UTIL_H_

#include <opencv2/opencv.hpp>

#include <string>

struct ImageUtil {
    /**
     * Compare two image is totally equal in pixels,
     * This function may takes a lot of time
     * @param src Source image
     * @param dst Dest image
     * 
     * @return an indicator whether two images have same pixels
     * 
     * */
    static bool compare_equal(const std::string& src, const std::string& dst);
};
#endif