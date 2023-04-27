#ifndef AUTOBRIGHTNESSANDCONTRAST_H
#define AUTOBRIGHTNESSANDCONTRAST_H

#include <opencv2/opencv.hpp>


class AutoBrightnessAndContrast
{
public:
    AutoBrightnessAndContrast();

    // Automatic brightness and contrast optimization with optional histogram clipping
    std::tuple<cv::Mat, float, float> automaticBrightnessAndContrast14bit(cv::Mat pGrayImage, float clip_hist_percent = 1);

};

#endif // AUTOBRIGHTNESSANDCONTRAST_H
