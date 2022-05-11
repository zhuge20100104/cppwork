
#include "img_util/img_util.h"

bool ImageUtil::compare_equal(const std::string& src, const std::string& dst) {
    cv::Mat img1 = cv::imread(src);
    cv::Mat img2 = cv::imread(dst);
    cv::Mat imgSrc{};
    cv::Mat imgDst{};

    cv::cvtColor(img1, imgSrc, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img2, imgDst, cv::COLOR_BGR2GRAY);

    if (imgSrc.size() != imgDst.size()) {
        std::cerr << "Image size is not equal.." << std::endl;
        return false;
    }

    cv::Mat result{};
    cv::compare(imgSrc, imgDst, result, cv::CMP_NE);

    int nz = cv::countNonZero(result);
    return nz == 0;
}