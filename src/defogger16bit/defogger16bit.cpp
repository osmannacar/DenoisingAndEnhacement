#include "defogger16bit.h".h"
#include <opencv2/highgui.hpp>
#include <opencv2/photo.hpp>

Defogger16bit::Defogger16bit()
{

}

void Defogger16bit::defog(cv::Mat pSource, cv::Mat &pOutput, int pRectSize, double pOmega, double pNumt)
{
    cv::Mat tI;
    pSource.convertTo(tI, CV_32F);
    tI /= 65535;

    float tA[3] = { 0 };
    cv::Mat tDark = darkChannel(tI, pRectSize);
    atmLight(tI, tDark, tA);

    cv::Mat tTransmissionEstimated = transmissionEstimate(tI, tA, pRectSize, pOmega);
    cv::Mat tTransmissionRefined = transmissionRefine(pSource, tTransmissionEstimated);
    pOutput = recover(tI, tTransmissionRefined, tA, pNumt);
}

cv::Mat Defogger16bit::darkChannel(cv::Mat pSource, int pSize)
{
    std::vector<cv::Mat> tChanels;
    cv::split(pSource, tChanels);

    cv::Mat tMinChannel = (cv::min)((cv::min)(tChanels[0], tChanels[1]), tChanels[2]);
    cv::Mat tKernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(pSize, pSize));

    cv::Mat tDark(tMinChannel.rows, tMinChannel.cols, CV_32FC1);
    cv::erode(tMinChannel, tDark, tKernel);
    return tDark;
}

void Defogger16bit::atmLight(cv::Mat pSource, cv::Mat pDark, float pOutA[])
{
    int row = pSource.rows;
    int col = pSource.cols;
    int imgSize = row*col;

    std::vector<int> tDarkVector = pDark.reshape(1, imgSize);
    cv::Mat tSrcVector = pSource.reshape(3, imgSize);

    int tNumpx = int(cv::max(floor(imgSize / 1000), 1.0));
    std::vector<int> tIndices = argsort(tDarkVector);
    std::vector<int> tDstIndices(tIndices.begin() + (imgSize - tNumpx), tIndices.end());

    for (int i = 0; i < tNumpx; ++i)
    {
        pOutA[0] += tSrcVector.at<cv::Vec3f>(tDstIndices[i], 0)[0];
        pOutA[1] += tSrcVector.at<cv::Vec3f>(tDstIndices[i], 0)[1];
        pOutA[2] += tSrcVector.at<cv::Vec3f>(tDstIndices[i], 0)[2];
    }
    pOutA[0] /= tNumpx;
    pOutA[1] /= tNumpx;
    pOutA[2] /= tNumpx;
}

cv::Mat Defogger16bit::transmissionEstimate(cv::Mat pSource, float pOutA[], int pSize, float pOmega)
{
    cv::Mat tImgA = cv::Mat::zeros(pSource.rows, pSource.cols, CV_32FC3);

    std::vector<cv::Mat> tChanels;
    split(pSource, tChanels);
    for (int i = 0; i < 3; ++i)
    {
        tChanels[i] = tChanels[i] / pOutA[i];
    }

    merge(tChanels, tImgA);
    cv::Mat tTransmission = 1 - pOmega*darkChannel(tImgA, pSize);
    return tTransmission;
}

cv::Mat Defogger16bit::guidedfilter(cv::Mat pSource, cv::Mat pTransmissionEstimated, int pR, float pEps)
{
    cv::Mat tMeanI, tMeanT, tMeanIT, tMeanII, tMeanA, tMeanB;
    cv::boxFilter(pSource, tMeanI, CV_32F, cv::Size(pR, pR));
    cv::boxFilter(pTransmissionEstimated, tMeanT, CV_32F, cv::Size(pR, pR));
    cv::boxFilter(pSource.mul(pTransmissionEstimated), tMeanIT, CV_32F, cv::Size(pR, pR));
    cv::Mat tCovIT = tMeanIT - tMeanI.mul(tMeanT);

    cv::boxFilter(pSource.mul(pSource), tMeanII, CV_32F, cv::Size(pR, pR));
    cv::Mat tVarI = tMeanII - tMeanI.mul(tMeanI);

    cv::Mat a = tCovIT / (tVarI + pEps);
    cv::Mat b = tMeanT - a.mul(tMeanI);
    cv::boxFilter(a, tMeanA, CV_32F, cv::Size(pR, pR));
    cv::boxFilter(b, tMeanB, CV_32F, cv::Size(pR, pR));

    cv::Mat tGuidedFiltered = tMeanA.mul(pSource) + tMeanB;

    return tGuidedFiltered;
}

cv::Mat Defogger16bit::transmissionRefine(cv::Mat pSource, cv::Mat pTransmissionEstimated)
{
    cv::Mat tGray;
    cvtColor(pSource, tGray, cv::COLOR_BGR2GRAY);
    tGray.convertTo(tGray, CV_32F);
    tGray /= 65535;

    int tR = 60;
    float tEps = 0.0001;
    cv::Mat tTransmissionRefined = guidedfilter(tGray, pTransmissionEstimated, tR, tEps);
    return tTransmissionRefined;
}

cv::Mat Defogger16bit::recover(cv::Mat pSource, cv::Mat pTransmissionRefined, float pOutA[], float pTx)
{
    cv::Mat tDst = cv::Mat::zeros(pSource.rows, pSource.cols, CV_32FC3);
    pTransmissionRefined = (cv::max)(pTransmissionRefined, pTx);

    std::vector<cv::Mat> tChanels;
    cv::split(pSource, tChanels);
    for (int i = 0; i < 3; ++i)
    {
        tChanels[i] = (tChanels[i] - pOutA[i]) / pTransmissionRefined + pOutA[i];
    }
    cv::merge(tChanels, tDst);
    return tDst;
}
