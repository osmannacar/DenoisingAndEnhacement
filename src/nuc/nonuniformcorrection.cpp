#include "nonuniformcorrection.h"

#include <QFile>
#include <qtextstream.h>
#include <fstream>

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "src/Common.h"

NonUniformCorrection::NonUniformCorrection(QString pFramesPath)
    : mFramesPath(pFramesPath)
{

}

void NonUniformCorrection::calculte2PointNuc()
{


    Common::fillFrameContainer(g_hot_frame,   mFramesPath + "sicak/", 0, 50);
    Common::fillFrameContainer(g_cold_frame,  mFramesPath + "soguk/", 0, 50);

    calculateMean(g_hot_frame, g_hot_mean);
    calculateMean(g_cold_frame, g_cold_mean);

    calcDiff();

    float tMeanHotMean = 0.0;
    calcMean(g_hot_mean, tMeanHotMean);

    float tMeanColdMean = 0.0;
    calcMean(g_cold_mean, tMeanColdMean);

    calcGain(tMeanHotMean, tMeanColdMean);

    calcOffset(tMeanColdMean);


    std::remove(QString(mFramesPath + "gain_matris.csv" ).toStdString().c_str());
    std::remove(QString(mFramesPath + "ofset_matris.csv").toStdString().c_str());


    std::fstream gain_of(mFramesPath.toStdString() + "gain_matris.csv", std::ios::out | std::ios::app);

    if (gain_of.is_open())
    {
        writemap(gain_of, g_gain);
        gain_of.close();
    }

    std::fstream ofset_of(mFramesPath.toStdString() + "ofset_matris.csv", std::ios::out | std::ios::app);

    if (ofset_of.is_open())
    {
        writemap(ofset_of, g_ofset);
        ofset_of.close();
    }
}

void NonUniformCorrection::fillGainOffsetMatrix()
{
        readGainOffsetMatrix(g_gain, mFramesPath + "gain_matris.csv");
        readGainOffsetMatrix(g_ofset, mFramesPath + "ofset_matris.csv");
}

void NonUniformCorrection::applyNuc(ushort *pFrame){
    for (int col = 0; col < g_frame_cols; ++col) {
        for (int row = 0; row < g_frame_rows; ++row) {
            pFrame[row * g_frame_cols + col] = (ushort)((g_gain[col][row] * pFrame[row * g_frame_cols + col]) + g_ofset[col][row]);
        }
    }

}

void NonUniformCorrection::calculateMean(QVector<cv::Mat> &tContainer, float pMean[][g_frame_rows]){

    for (int col = 0; col < g_frame_cols; ++col) {
        for (int row = 0; row < g_frame_rows; ++row) {
            long long tMeanVal = 0;
            for (int i = 0; i < tContainer.size(); ++i) {
                tMeanVal += reinterpret_cast<ushort*>(tContainer.at(i).data)[row * g_frame_cols + col];
            }
            pMean[col][row] = (float)tMeanVal / tContainer.size();
        }
    }
}

void NonUniformCorrection::calcDiff(){
    for (int col = 0; col < g_frame_cols; ++col) {
        for (int row = 0; row < g_frame_rows; ++row) {
            g_diff_hot_cold[col][row] = g_hot_mean[col][row] - g_cold_mean[col][row] <= 0 ? 0 : g_hot_mean[col][row] - g_cold_mean[col][row];
        }
    }
}

void NonUniformCorrection::calcMean(float pMean[][g_frame_rows], float &pMeanValue){

    long double tTemp = 0.0;
    for (int col = 0; col < g_frame_cols; ++col) {
        for (int row = 0; row < g_frame_rows; ++row) {
            tTemp += pMean[col][row];
        }
    }

    pMeanValue = (float)tTemp / (g_frame_cols * g_frame_rows);
}

void NonUniformCorrection::calcGain(float tMeanHotMean, float tMeanColdMean){
    for (int col = 0; col < g_frame_cols; ++col) {
        for (int row = 0; row < g_frame_rows; ++row) {
            g_gain[col][row] = (tMeanHotMean - tMeanColdMean) / g_diff_hot_cold[col][row];
        }
    }
}

void NonUniformCorrection::calcOffset(float tMeanColdMean){
    for (int col = 0; col < g_frame_cols; ++col) {
        for (int row = 0; row < g_frame_rows; ++row) {
            g_ofset[col][row] = tMeanColdMean - (g_gain[col][row] * g_cold_mean[col][row]);
        }
    }
}

bool NonUniformCorrection::readGainOffsetMatrix(float pMatris[][g_frame_rows], QString pPath){
    QFile file(pPath);
    if(!file.exists()){
        return false;
    }

    if(!file.open(QIODevice::ReadOnly)){
        return false;
    }

    int i = 0;
    int j = 0;
    QTextStream in(&file);
    while(!in.atEnd()) {
        j = 0;
        QString line = in.readLine();
        QStringList  fields = line.split(",");
        for(const auto &tField: fields){
            pMatris[i][j] = tField.toFloat();
            ++j;
        }
        ++i;
    }
    file.close();
    return true;
}
