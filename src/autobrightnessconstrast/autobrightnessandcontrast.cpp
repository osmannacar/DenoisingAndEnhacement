#include "autobrightnessandcontrast.h"

AutoBrightnessAndContrast::AutoBrightnessAndContrast()
{

}

std::tuple<cv::Mat, float, float> AutoBrightnessAndContrast::automaticBrightnessAndContrast14bit(cv::Mat pGrayImage, float clip_hist_percent) {

    // Calculate grayscale histogram
    cv::Mat hist;
    int histSize = 16383;
    float range[] = { 0, 16383 };
    const float* histRange = { range };
    cv::calcHist(&pGrayImage, 1, nullptr, cv::Mat(), hist, 1, &histSize, &histRange);

    // Calculate cumulative distribution from the histogram
    std::vector<float> accumulator(histSize);
    accumulator[0] = hist.at<float>(0);
    for (int index = 1; index < histSize; ++index) {
        accumulator[index] = accumulator[index - 1] + hist.at<float>(index);
    }

    // Locate points to clip
    float maximum = accumulator.back();
    clip_hist_percent *= maximum / 16383.0;
    clip_hist_percent /= 2.0;

    // Locate left cut
    int minimum_gray = 0;
    while (accumulator[minimum_gray] < clip_hist_percent) {
        ++minimum_gray;
    }

    // Locate right cut
    int maximum_gray = histSize - 1;
    while (accumulator[maximum_gray] >= maximum - clip_hist_percent) {
        --maximum_gray;
    }

    // Calculate alpha and beta values
    float alpha = 16383.0f / (maximum_gray - minimum_gray);
    float beta = -minimum_gray * alpha;

    cv::Mat auto_result;
    cv::convertScaleAbs(pGrayImage, auto_result, alpha, beta);

    return std::make_tuple(auto_result, alpha, beta);
}
