#ifndef NONUNIFORMCORRECTION_H
#define NONUNIFORMCORRECTION_H

#include <QString>
#include <QVector>
#include <opencv2/opencv.hpp>

class NonUniformCorrection
{
public:
    NonUniformCorrection(QString pFramesPath);


public:
    void calculte2PointNuc();
    void fillGainOffsetMatrix();

    void applyNuc(ushort *pFrame);

    static const int g_frame_cols = 640;
    static const int g_frame_rows = 480;

private:

    void calculateMean(QVector<cv::Mat> &tContainer, float pMean[][g_frame_rows]);

    void calcDiff();

    void calcMean(float pMean[][g_frame_rows], float &pMeanValue);

    void calcGain(float tMeanHotMean, float tMeanColdMean);

    void calcOffset(float tMeanColdMean);


    template<typename T, int cols, int rows>
    std::ostream &writemap(std::ostream& os, T (&map)[cols][rows])
    {
        for (int col = 0; col < cols; ++col) {
            for (int row = 0; row < rows; ++row) {
                os << map[col][row]<<",";
            }
            os<<"\n";
        }
        return os;
    }

    bool readGainOffsetMatrix(float pMatris[][g_frame_rows], QString pPath);


private:
    QString mFramesPath;


    QVector<cv::Mat> g_cold_frame;
    QVector<cv::Mat> g_hot_frame;

    float g_hot_mean        [g_frame_cols][g_frame_rows] = {0.0};
    float g_cold_mean       [g_frame_cols][g_frame_rows] = {0.0};
    float g_diff_hot_cold   [g_frame_cols][g_frame_rows] = {0.0};


    float g_gain            [g_frame_cols][g_frame_rows] = {0.0};
    float g_ofset           [g_frame_cols][g_frame_rows] = {0.0};
};

#endif // NONUNIFORMCORRECTION_H
