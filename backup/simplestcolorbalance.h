/* Simplest Color Balance algorithm has been taken from https://web.stanford.edu/~sujason/ColorBalancing/simplestcb.html
 * and it has been implemented in OpenCV/C++ as in the MATLAB code.
 */

#ifndef SIMPLESTCOLORBALANCE_H
#define SIMPLESTCOLORBALANCE_H

#include <opencv2/core.hpp>

#include <algorithm>
#include <cmath>
#include <vector>

template<typename T>
static inline double Lerp(T v0, T v1, T t)
{
    return (1 - t)*v0 + t*v1;
}

template<typename T>
static inline std::vector<T> Quantile(const std::vector<T>& inData, const std::vector<T>& probs)
{
    if (inData.empty())
    {
        return std::vector<T>();
    }

    if (1 == inData.size())
    {
        return std::vector<T>(1, inData[0]);
    }

    std::vector<T> data = inData;
    std::sort(data.begin(), data.end());
    std::vector<T> quantiles;

    for (size_t i = 0; i < probs.size(); ++i)
    {
        T poi = Lerp<T>(-0.5, data.size() - 0.5, probs[i]);

        size_t left = std::max(int64_t(std::floor(poi)), int64_t(0));
        size_t right = std::min(int64_t(std::ceil(poi)), int64_t(data.size() - 1));

        T datLeft = data.at(left);
        T datRight = data.at(right);

        T quantile = Lerp<T>(datLeft, datRight, poi - left);

        quantiles.push_back(quantile);
    }

    return quantiles;
}

cv::Mat simplestColorBalanceSingleChannel(cv::Mat& img, double sat_level1 = 0.005, double sat_level2 = 0.001, double num = 1.0)
{
    cv::Mat imgdouble = img.reshape(1,1);

    imgdouble.convertTo(imgdouble, CV_64FC1);

    std::vector<double> array;
    if (imgdouble.isContinuous())
    {
        array.assign(imgdouble.data, imgdouble.data + imgdouble.total());
    }
    else
    { //painful method
        for (int i = 0; i < imgdouble.rows; ++i)
        {
            array.insert(array.end(), imgdouble.ptr<double>(i), imgdouble.ptr<double>(i) + imgdouble.cols);
        }
    }

    std::vector<double> q = {sat_level1, 1 - sat_level2};

    std::vector<double> quantile_result = Quantile(array, q);

    double* imgdoublei = imgdouble.ptr<double>(0);
    for (int i = 0; i < imgdouble.cols; ++i)
    {
        imgdoublei[i] = imgdoublei[i] < quantile_result[0]  ?  quantile_result[0]  :  imgdoublei[i];
        imgdoublei[i] = imgdoublei[i] > quantile_result[1]  ?  quantile_result[1]  :  imgdoublei[i];
    }

    double min, max;
    cv::minMaxLoc(imgdouble, &min, &max);

    imgdouble = (imgdouble - min) * num / (max - min) * 255;

    imgdouble = imgdouble.reshape(1, img.rows);

    imgdouble.convertTo(imgdouble, CV_8UC1);

    return imgdouble;
}

cv::Mat simplestColorBalance(cv::Mat& img, double sat_level1 = 0.005, double sat_level2 = 0.001, double num = 1.0)
{
    std::vector<cv::Mat> channels;
    cv::split(img, channels);

    for (int i = 0; i < 3; ++i)
    {

    channels[i] = channels[i].reshape(1,1);

    channels[i].convertTo(channels[i], CV_64FC1);

    std::vector<double> array;
    if (channels[i].isContinuous())
    {
        array.assign(channels[i].data, channels[i].data + channels[i].total());
    }
    else
    { //painful method
        for (int i = 0; i < channels[i].rows; ++i)
        {
            array.insert(array.end(), channels[i].ptr<double>(i), channels[i].ptr<double>(i) + channels[i].cols);
        }
    }

    std::vector<double> q = {sat_level1, 1 - sat_level2};

    std::vector<double> quantile_result = Quantile(array, q);

    double* channelsii = channels[i].ptr<double>(0);
    for (int j = 0; j < channels[i].cols; ++j)
    {
        channelsii[j] = channelsii[j] < quantile_result[0]  ?  quantile_result[0]  :  channelsii[j];
        channelsii[j] = channelsii[j] > quantile_result[1]  ?  quantile_result[1]  :  channelsii[j];
    }

    double min, max;
    cv::minMaxLoc(channels[i], &min, &max);

    channels[i] = (channels[i] - min) * num / (max - min) * 255;

    channels[i] = channels[i].reshape(1, img.rows);

    channels[i].convertTo(channels[i], CV_8UC1);
    }

    cv::Mat result;
    cv::merge(channels, result);

    return result;
}

#endif // SIMPLESTCOLORBALANCE_H
