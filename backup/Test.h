#ifndef TEST_H
#define TEST_H

///////////////////////SHIFT PROCESS///////////////////////////
//for(int row = 0; row < tFrame.rows; ++row){
//    for(int col = 0; col < tFrame.cols; ++col){
//        tFrameData[row * tFrame.cols + col] =( tFrameData[row * tFrame.cols + col] << 2 );
//    }
//}
//cv::imshow("shift", tFrame);
////////////////////////////////////////////////////////////////


///////////////////////////////////////

//unsigned short *tFrameData = reinterpret_cast<unsigned short*>(tFrame.data);

//static int tFrameCount = 0;
//if(tFrameCount == 3){
//    QFile file("/home/oscar/Desktop/beforeShift.txt");
//    file.open(QIODevice::WriteOnly);

//    QList<ushort> tContiner1;
//    for(int row = 0; row < tFrame.rows; ++row){
//        for(int col = 0; col < tFrame.cols; ++col){
//            tContiner1.append(tFrameData[row * tFrame.cols + col]);
//        }
//    }
//    std::sort(tContiner1.begin(), tContiner1.end());
//    QTextStream stream(&file);
//    for(int row = 0; row < tContiner1.size(); ++row){
//        stream << tContiner1[row] << ", ";

//    }
//}
//////////////////////////////////////////////////////////////


//#include <QCoreApplication>
//#include <QDateTime>
//#include <QDebug>

//#include <hazeremove/hazeremove.h>

//#include <defogger/defogger.h>

//#include <badpixelreplacement/badpixelreplacement.h>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    BadPixelReplacement tBadPixelReplacement("/home/oscar/Videos/Thermal_Video_With_BadPixel/bpr20_35_14ms.3.csv", 7);
//    HazeRemove tHazeRemove;
//    Defogger tDefogger;

//    //        cv::Mat tMat = cv::imread("/home/oscar/Pictures/Example/11.jpg");
//    //        cv::Mat tMatOutput, tMatOutput2, tMatOutput3;
//    //        tHazeRemove.process(tMat, tMatOutput);

//    //        tDefogger.defog(tMat, tMatOutput3);

//    //        tMatOutput2 = simplestColorBalance(tMat, 0.005, 0.001, 1);
//    //        cv::imshow("input", tMat);
//    //        cv::imshow("output HazeRemove", tMatOutput);
//    //        cv::imshow("output simplestColorBalance", tMatOutput2);
//    //        cv::imshow("output Defogger", tMatOutput3);
//    //        cv::waitKey(0);

//    cv::VideoCapture vid("/home/oscar/Videos/Termal_Video/recorded_2022_11_30_17_52_07.avi");
//    if(!vid.isOpened())
//        return -1;

//    cv::Mat frame, output, tdefogoutput;

//    while(vid.read(frame))
//    {

//        cv::resize(frame, frame, cv::Size(640, 480));
//        cv::imshow("before", frame);


////        cv::medianBlur(frame, frame, 3);

//        //        ///highlight thermal

//        cv::Mat tBlur;
//        cv::blur(frame, tBlur, cv::Size(30, 30));
//        cv::addWeighted(frame, 4, tBlur, -4, 180, frame);

//        //        ///

//        ///

//        //                double sigma=2, amount=4;
//        //                cv::Mat blurry;
//        //                cv::GaussianBlur(frame, blurry, cv::Size(), sigma);
//        //                cv::addWeighted(frame, 1 + amount, blurry, -amount, 30, frame);

//        ///

//        /////////////HazeRemove/////////////
//        quint64 tTime = QDateTime::currentMSecsSinceEpoch();
//        tHazeRemove.process(frame, output);
//        std::cout << "Each Haze Removing Process Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;
//        //////////////////////////////////

//        /////////////Defogger/////////////
//        tTime = QDateTime::currentMSecsSinceEpoch();
//        tDefogger.defog(frame, tdefogoutput);
//        std::cout << "Each Image Defogger Process Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;
//        ///////////////////////////////////

//        cv::imshow("sharp", frame);
//        cv::imshow("Haze Removing", output);
//        cv::imshow("Image Defogger", tdefogoutput);

//        if(cv::waitKey(1) >= 0)
//            break;
//    }


//    return a.exec();
//}






///////////////////////////////////////////////////////////////////

//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <QCoreApplication>
//#include <QDateTime>
//#include <badpixelreplacement/badpixelreplacement.h>
//#include "device_launch_parameters.h"
//#include <QDebug>
//#include <qfile.h>
//#include "cudaalgorithm/imageprocessor.h"
//#include "cudaalgorithm/dehazeImage.h"

//void testWithoutSort(cv::Mat &pSource){
//    ushort *tData = reinterpret_cast<ushort*>(pSource.data);
//    auto tSize = pSource.cols * pSource.rows;

//    auto tSum = std::accumulate(tData, tData + tSize, 0.0);
//    ushort tAvg = tSum / tSize;

//    ushort tMaxPixel2 = std::numeric_limits<ushort>::min();
//    ushort tMinPixel2 = std::numeric_limits<ushort>::max();

//    std::for_each(tData, tData + tSize, [&] (ushort n) {
//        if((n <= (tAvg * 15/10)) && (n >= (tAvg * 5/10))){
//            if(n > tMaxPixel2){
//                tMaxPixel2 = n;
//            }

//            if(n < tMinPixel2){
//                tMinPixel2 = n;
//            }
//        }
//    });

//    qDebug() << "tAvg:" << tAvg;
//    qDebug() << "tSum:" << tSum;
//    qDebug() << "tMinPixel2:" << tMinPixel2;
//    qDebug() << "tMaxPixel2:" << tMaxPixel2;


//    uint16_t tDiff2 = tMaxPixel2 - tMinPixel2;

//    cv::Mat tOutputCPU2 = cv::Mat::zeros(pSource.rows, pSource.cols, pSource.type());
//    ushort *tOutputCPU2Data = (ushort*)tOutputCPU2.data;
//    ushort *tFrameData = (ushort*)pSource.data;

//    for (ushort y = 0; y < pSource.rows; ++y) {
//        for (ushort x = 0; x < pSource.cols; ++x) {
//            tOutputCPU2Data[y * pSource.cols + x] = std::round((tFrameData[y * pSource.cols + x] - tMinPixel2) * (65535 / tDiff2));
//        }
//    }
//    cv::imshow("tOutputCPU2", tOutputCPU2);

//}

//void findGrayScaleMinMaxPixel(cv::Mat &pSource, ushort &pMinValue, ushort &pMaxValue){
//    pMaxValue = std::numeric_limits<uchar>::min();
//    pMinValue = std::numeric_limits<uchar>::max();

//    std::vector<ushort> tPixels;

//    for (int y = 0; y < pSource.rows; ++y) {
//        for (int x = 0; x < pSource.cols; ++x) {
//            tPixels.push_back(pSource.at<ushort>(y, x));
//        }
//    }

//    std::sort(tPixels.begin(), tPixels.end());

//    pMinValue = tPixels.at(10);
//    pMaxValue = tPixels.at(tPixels.size() - 10);

//}

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    cv::Mat tFrame, tOutput;
//    int tIndex = 0;
//    unsigned long long tGPUDuration = 0;
//    cv::VideoCapture vid("/home/oscar/Videos/haze_foggy/foggy4.mp4");
//    if(!vid.isOpened())
//        return -1;

//    while(vid.read(tFrame))
//    {

//        auto start = std::chrono::high_resolution_clock::now();
//        cudaDehazeImage(tFrame, tOutput);
//        qDebug() << "GPU Duration Of Each Frame MicroSec:" <<  (tGPUDuration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()) /  (tIndex+1);

//        ++tIndex;
//        cv::imshow("Frame", tFrame);
//        cv::imshow("tOutput", tOutput);
//        cv::waitKey(1);
//    }
//    qDebug() << "Average GPU Time:" << (tGPUDuration / (tIndex + 1));

//    //    BadPixelReplacement tBadPixelReplacement("/home/oscar/Videos/Thermal_Video_With_BadPixel/bpr20_35_14ms.3.csv", 7);

//    //    unsigned long long tGPUDuration = 0, tCPUDuration = 0;
//    //    int tIndex = 0;
//    //    for (tIndex = 0; tIndex < 128/*INT32_MAX*/; ++tIndex) {

//    //        QString tPath = "/home/oscar/Pictures/DNTSS/BURCAK_TEST3/LAB1_12ms/2023_03_06_12_00_41/recorded" + QString("000000%1").arg(QString::number(tIndex %128)).right(6) + ".tif";
//    //        cv::Mat tFrame = cv::imread(tPath.toStdString().c_str(), cv::IMREAD_ANYDEPTH | cv::IMREAD_ANYCOLOR);
//    //        cv::Mat tOutput, tOutputBPR;

//    //        auto start = std::chrono::high_resolution_clock::now();
//    //        tBadPixelReplacement.process16Bit(tFrame, tOutputBPR);
//    //        qDebug() << "CPU Duration Of Each Frame BPR MicroSec:" <<  (tCPUDuration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()) /  (tIndex+1);

//    //        cv::imshow("OutputBPR", tOutputBPR);

//    //        testWithoutSort(tOutputBPR);

//    //        cv::imshow("Frame", tFrame);

//    //         start = std::chrono::high_resolution_clock::now();
//    //        cudaImageProcess(tFrame, tOutput);
//    //        qDebug() << "GPU Duration Of Each Frame MicroSec:" <<  (tGPUDuration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()) /  (tIndex+1);


//    //        //        start = std::chrono::high_resolution_clock::now();
//    //        //        ushort tMinPixel, tMaxPixel;
//    //        //        findGrayScaleMinMaxPixel(tFrame, tMinPixel, tMaxPixel);

//    //        //        qDebug() << "tMinPixel:" << tMinPixel;
//    //        //        qDebug() << "tMaxPixel:" << tMaxPixel;

//    //        //        testWithoutSort(tFrame);


//    //        //        uint16_t tDiff = tMaxPixel - tMinPixel;
//    //        //        cv::Mat tOutputCPU = cv::Mat::zeros(tFrame.rows, tFrame.cols, tFrame.type());

//    //        //        ushort *tOutputCPUData = (ushort*)tOutputCPU.data;
//    //        //        ushort *tFrameData = (ushort*)tFrame.data;

//    //        //        for (ushort y = 0; y < tFrame.rows; ++y) {
//    //        //            for (ushort x = 0; x < tFrame.cols; ++x) {
//    //        //                tOutputCPUData[y * tFrame.cols + x] = std::round((tFrameData[y * tFrame.cols + x] - tMinPixel) * (65535 / tDiff));
//    //        //            }
//    //        //        }
//    //        //        qDebug() << "CPU Duration Of Each Frame MicroSec:" <<  (tCPUDuration += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count()) /  (tIndex+1);

//    //        cv::imshow("OutputGPU", tOutput);
//    //        //        cv::imshow("tOutputCPU", tOutputCPU);
//    //        //        cv::imshow("Frame", tFrame);
//    //        cv::waitKey(1);
//    //    }

//    //    qDebug() << "Average GPU Time:" << (tGPUDuration / (tIndex + 1));
//    //    qDebug() << "Average CPU Time:" << (tCPUDuration / (tIndex + 1));

//    return a.exec();
//}







///////////////////////////////////////////////////////////////////



//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <iostream>
//#include <hazeremove/hazeremove.h>
//#include "simplestcolorbalance.h"
//#include <opencv2/photo.hpp>
//#include <QDateTime>
//#include <defogger/defogger.h>
//#include <badpixelreplacement/badpixelreplacement.h>
//#include "logwriter/staticconsolelogwriter.h"
//#include<QCoreApplication>
//#include <QDebug>

//void findGrayScaleMinMaxPixel(cv::Mat &pSource, ushort &pMinValue, ushort &pMaxValue){
//    pMaxValue = std::numeric_limits<uchar>::min();
//    pMinValue = std::numeric_limits<uchar>::max();

//    std::vector<ushort> tPixels;

//    for (int y = 0; y < pSource.rows; ++y) {
//        for (int x = 0; x < pSource.cols; ++x) {
//            //            ushort tPixelValue = pSource.at<ushort>(y, x);

//            //            if (tPixelValue > pMaxValue) {
//            //                pMaxValue = tPixelValue;
//            //            }else if(tPixelValue < pMinValue){
//            //                pMinValue = tPixelValue;
//            //            }
//            tPixels.push_back(pSource.at<ushort>(y, x));
//        }
//    }

//    std::sort(tPixels.begin(), tPixels.end());

//    pMinValue = tPixels.at(10);
//    pMaxValue = tPixels.at(tPixels.size() - 10);

//}

//int main(int argc, char *argv[])
//{
//    qInstallMessageHandler(StaticConsoleLogWriter::consoleMessageOutput);
//    QCoreApplication a(argc, argv);

//    BadPixelReplacement tBadPixelReplacement("/home/oscar/Videos/Thermal_Video_With_BadPixel/bpr20_35_14ms.3.csv", 7);



//    uint16_t tMinPixel = 123, tMaxPixel = 153;

//    for (int tIndex = 0; tIndex < 128; ++tIndex) {

//        QString tPath = "/home/oscar/Pictures/DNTSS/BURCAK TEST2/NUC+ham/2023_02_28_08_50_51/recorded" + QString("000000%1").arg(QString::number(tIndex)).right(6) + ".tif";


//        cv::Mat tFrame = cv::imread(tPath.toStdString().c_str(), cv::IMREAD_ANYDEPTH | cv::IMREAD_ANYCOLOR);


//        qDebug() << tFrame.size().width << " " << tFrame.size().height<<", d:"<<tFrame.depth()<<", c:"<<tFrame.channels();

//        quint64 tTime = QDateTime::currentMSecsSinceEpoch();
//        tBadPixelReplacement.process16Bit(tFrame, tFrame);
//        cv::Mat tOutput = cv::Mat::zeros(tFrame.rows, tFrame.cols, tFrame.type());

//        ushort *tOutputData = (ushort*)tOutput.data;
//        ushort *tFrameData = (ushort*)tFrame.data;

//        findGrayScaleMinMaxPixel(tFrame, tMinPixel, tMaxPixel);

//        uint16_t tDiff = tMaxPixel - tMinPixel;

//        for (ushort y = 0; y < tFrame.rows; ++y) {
//            for (ushort x = 0; x < tFrame.cols; ++x) {
//                tOutputData[y * tFrame.cols + x] = std::round((tFrameData[y * tFrame.cols + x] - tMinPixel) * (65535 / tDiff));
//            }
//        }
//        std::cout << "Each Image Process Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;
//        cv::imshow("Frame", tFrame);
//        cv::imshow("tOutput", tOutput);

//        cv::waitKey(0);
//    }


//    return a.exec();
//}





/////////////////////////////////////////////////////////////////////////


//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <iostream>
//#include <hazeremove/hazeremove.h>
//#include "simplestcolorbalance.h"
//#include <opencv2/photo.hpp>
//#include <QDateTime>
//#include <defogger/defogger.h>
//#include <badpixelreplacement/badpixelreplacement.h>
//#include "logwriter/staticconsolelogwriter.h"
//#include<QCoreApplication>
//#include <QDebug>

//void findGrayScaleMinMaxPixel(cv::Mat &pSource, uint8_t &pMinValue, uint8_t &pMaxValue){
//    pMaxValue = std::numeric_limits<uchar>::min();
//    pMinValue = std::numeric_limits<uchar>::max();

//    uchar *tSourceData = pSource.data;
//    QVector<int> tPixels;

//    for (int y = 0; y < pSource.rows; ++y) {
//        for (int x = 0; x < pSource.cols; ++x) {
//            uchar tPixelValue = tSourceData[y * pSource.cols + x];
//            if((tPixelValue == 255) || (tPixelValue == 0)){
//                continue;
//            }

//            if (tPixelValue > pMaxValue) {
//                pMaxValue = tPixelValue;
//            }else if(tPixelValue < pMinValue){
//                pMinValue = tPixelValue;
//            }
//            tPixels.append(tPixelValue);
//        }
//    }

//    std::sort(tPixels.begin(), tPixels.end());
//    //    qDebug() << "Pixels:" << tPixels;

//}

//int main(int argc, char *argv[])
//{
//    qInstallMessageHandler(StaticConsoleLogWriter::consoleMessageOutput);
//    QCoreApplication a(argc, argv);

//    cv::VideoCapture vid("/home/oscar/Videos/Thermal_Video_With_BadPixel/avg34k/min0-max100.avi");

//    if(!vid.isOpened())
//        return -1;

//    cv::Mat tFrame, tImage1, tImage2, tOutput, tDefogoutput;

//    HazeRemove tHazeRemove;
//    Defogger tDefogger;
//    BadPixelReplacement tBadPixelReplacement("/home/oscar/Videos/Thermal_Video_With_BadPixel/bpr20_35_14ms.3.csv", 7);
//    while(vid.read(tFrame)){
//        //        cv::cvtColor(tFrame, tFrame, cv::COLOR_BGR2GRAY);

//        //        quint64 tTime = QDateTime::currentMSecsSinceEpoch();
//        //        tBadPixelReplacement.process(tFrame, tImage1);
//        //        std::cout << "Bad pixel replacement process Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;

//        //        tTime = QDateTime::currentMSecsSinceEpoch();
//        //        tBadPixelReplacement.processVec(tFrame, tImage2);
//        //        std::cout << "Bad pixel replacement processVec Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;


//        //        /////////////HazeRemove/////////////
//        //        cv::cvtColor(tImage1, tImage1, cv::COLOR_GRAY2BGR);
//        //        tTime = QDateTime::currentMSecsSinceEpoch();
//        //        tHazeRemove.process(tImage1, tOutput);
//        //        std::cout << "Each Haze Removing Process Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;
//        //        //////////////////////////////////

//        //        /////////////Defogger/////////////
//        //        tTime = QDateTime::currentMSecsSinceEpoch();
//        //        tDefogger.defog(tImage1, tDefogoutput);
//        //        std::cout << "Each Image Defogger Process Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;
//        //        ///////////////////////////////////

//        //        cv::imshow("Frame", tFrame);
//        //        cv::imshow("process", tImage1);
//        //        cv::imshow("processVec", tImage2);


//        //        cv::imshow("Haze Removing", tOutput);
//        //        cv::imshow("Defogger", tDefogoutput);

//        //                if(cv::waitKey(1) >= 0)
//        //                    break;

//        /////////////////////////////////////////////////////

//        //        cv::equalizeHist(tFrame, tOutput);
//        //        cv::addWeighted(tFrame, 0.0001, tOutput, 0.35, 0.05, tOutput);

//        //        cv::cvtColor(tFrame, tFrame, cv::COLOR_BGR2GRAY);
//        //        cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
//        //        clahe->setClipLimit(6);
//        ////        clahe->setTilesGridSize(cv::Size(20,20));
//        //        clahe->apply(tFrame, tOutput);
//        //        //        cv::equalizeHist(tOutput, tOutput);

//        //        cv::imshow("Frame", tFrame);
//        //        cv::imshow("tOutput", tOutput);


//        //////////////////////////////////////////////////////


//        cv::cvtColor(tFrame, tFrame, cv::COLOR_BGR2GRAY);

//        tBadPixelReplacement.process(tFrame, tFrame);

//        uchar tMinPixel = 123, tMaxPixel = 153;
//        tOutput = cv::Mat::zeros(tFrame.rows, tFrame.cols, tFrame.type());

//        uchar *tOutputData = tOutput.data;

//        findGrayScaleMinMaxPixel(tFrame, tMinPixel, tMaxPixel);

////        uchar tDiff = tMaxPixel - tMinPixel;

//        QString tPixels;
//        for (int y = 0; y < tFrame.rows; ++y) {
//            for (int x = 0; x < tFrame.cols; ++x) {
//                tOutputData[y * tFrame.cols + x] = 2.55 * (uchar)(tFrame.at<uchar>(y, x) - 100);
//            }
//        }

//        //        QString tPixels;
//        //        for (int y = 0; y < tFrame.rows; ++y) {
//        //            for (int x = 0; x < tFrame.cols; ++x) {
//        //                tPixels += "(b:" + QString::number((int)tFrame.at<uchar>(y, x));
//        //                tOutputData[y * tFrame.cols + x] = std::round((tFrame.at<uchar>(y, x) - tMinPixel) * (255 / tDiff));
//        //                tPixels +=  "a:" + QString::number((int)tOutputData[y * tFrame.cols + x]) + ")" ;
//        //            }
//        //        }
//        //        qDebug() << "Frame:" << tPixels;
//        //        qDebug()  << "tMinPixel:" << (int)tMinPixel << " tMaxPixel:" << (int)tMaxPixel;



//        cv::imshow("Frame", tFrame);
////        cv::cvtColor(tFrame, tFrame, cv::COLOR_GRAY2BGR);
////        tHazeRemove.process(tFrame, tOutput);
//        cv::imshow("tOutput", tOutput);

//        cv::waitKey(10);

//    }
//    return a.exec();
//}







///////////////////////main/////////////////////////////////////////////


//    HazeRemove tHazeRemove;
//    Defogger tDefogger;

//    //        cv::Mat tMat = cv::imread("/home/oscar/Pictures/Example/11.jpg");
//    //        cv::Mat tMatOutput, tMatOutput2, tMatOutput3;
//    //        tHazeRemove.process(tMat, tMatOutput);

//    //        tDefogger.defog(tMat, tMatOutput3);

//    //        tMatOutput2 = simplestColorBalance(tMat, 0.005, 0.001, 1);
//    //        cv::imshow("input", tMat);
//    //        cv::imshow("output HazeRemove", tMatOutput);
//    //        cv::imshow("output simplestColorBalance", tMatOutput2);
//    //        cv::imshow("output Defogger", tMatOutput3);
//    //        cv::waitKey(0);

//    cv::VideoCapture vid("/home/oscar/Videos/Termal_Video/recorded_2022_11_30_17_52_07.avi");
//    if(!vid.isOpened())
//        return -1;

//    cv::Mat frame, output, tdefogoutput;

//    while(vid.read(frame))
//    {

//        cv::resize(frame, frame, cv::Size(640, 480));
//        cv::imshow("before", frame);

//        //        ///highlight thermal

//        cv::Mat tBlur;
//        cv::blur(frame, tBlur, cv::Size(30, 30));
//        cv::addWeighted(frame, 4, tBlur, -4, 180, frame);

//        //        ///

//        ///

//        //                double sigma=2, amount=4;
//        //                cv::Mat blurry;
//        //                cv::GaussianBlur(frame, blurry, cv::Size(), sigma);
//        //                cv::addWeighted(frame, 1 + amount, blurry, -amount, 30, frame);

//        ///

//        /////////////HazeRemove/////////////
//        quint64 tTime = QDateTime::currentMSecsSinceEpoch();
//        tHazeRemove.process(frame, output);
//        std::cout << "Each Haze Removing Process Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;
//        //////////////////////////////////

//        /////////////Defogger/////////////
//        tTime = QDateTime::currentMSecsSinceEpoch();
//        tDefogger.defog(frame, tdefogoutput);
//        std::cout << "Each Image Defogger Process Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;
//        ///////////////////////////////////

//        cv::imshow("sharp", frame);
//        cv::imshow("Haze Removing", output);
//        cv::imshow("Image Defogger", tdefogoutput);

//        if(cv::waitKey(1) >= 0)
//            break;
//    }


//////////////////////////////////////////////////////////////////////////////////////////////////

//#include <QCoreApplication>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include "iostream"
//#include "simplestcolorbalance.h"
//#include <QDateTime>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    cv::Mat im = cv::imread("/home/oscar/Pictures/Image-Enhancment-In-Foggy-Images.jpg");
//    cv::imshow("orig", im);
//    cv::Mat result = simplestColorBalance(im, 0.05 , 0.01, 1);
//    cv::imshow("balanced", result);

//    cv::waitKey(0);

//    /* mean value
//     *  frame = (frame + tPrevious) * 0.5;
//     *  tPrevious = frame;
//      */

////    cv::VideoCapture cap("/home/oscar/Videos/foggy2.mp4");

////    // Check if camera opened successfully
////    if(!cap.isOpened()){
////        std::cout << "Error opening video stream or file" << std::endl;
////        return -1;
////    }

////    cv::Mat frame;
////    while(cap.read(frame)){

////        quint64 tTime = QDateTime::currentMSecsSinceEpoch();
////        cv::Mat result = simplestColorBalance(frame, 0.05 , 0.01, 1);
////        std::cout << "Each Frame Process Time:" <<  (QDateTime::currentMSecsSinceEpoch() - tTime) <<  std::endl;

////        cv::imshow( "Frame", frame );
////        cv::imshow( "result", result );

////        // Press  ESC on keyboard to exit
////        if(cv::waitKey(1) == 27)
////            break;
////    }

////    // When everything done, release the video capture object
////    cap.release();

////    // Closes all the frames
////    cv::destroyAllWindows();



//    return a.exec();
//}



/////////////////////////////////////////////////////////////

//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>

//#include "opencv2/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include <stdio.h>
//#include <iostream>

//using namespace cv;
//using namespace std;


////median filtered dark channel
//Mat getMedianDarkChannel(Mat src, int patch)
//{
//    Mat rgbmin = Mat::zeros(src.rows, src.cols, CV_8UC1);
//    Mat MDCP;
//    Vec3b intensity;

//    for(int m=0; m<src.rows; m++)
//    {
//        for(int n=0; n<src.cols; n++)
//        {
//            intensity = src.at<Vec3b>(m,n);
//            rgbmin.at<uchar>(m,n) = min(min(intensity.val[0], intensity.val[1]), intensity.val[2]);
//        }
//    }
//    cv::medianBlur(rgbmin, MDCP, patch);
//    return MDCP;

//}


////estimate airlight by the brightest pixel in dark channel (proposed by He et al.)
//int estimateA(Mat DC)
//{
//    double minDC, maxDC;
//    minMaxLoc(DC, &minDC, &maxDC);
//    cout<<"estimated airlight is:"<<maxDC<<endl;
//    return maxDC;
//}


////estimate transmission map
//Mat estimateTransmission(Mat DCP, int ac)
//{
//    double w = 0.75;
//    Mat transmission = Mat::zeros(DCP.rows, DCP.cols, CV_8UC1);
//    Scalar intensity;

//    for (int m=0; m<DCP.rows; m++)
//    {
//        for (int n=0; n<DCP.cols; n++)
//        {
//            intensity = DCP.at<uchar>(m,n);
//            transmission.at<uchar>(m,n) = (1 - w * intensity.val[0] / ac) * 255;
//        }
//    }
//    return transmission;
//}


////dehazing foggy image
//Mat getDehazed(Mat source, Mat t, int al)
//{
//    double tmin = 0.1;
//    double tmax;

//    Scalar inttran;
//    Vec3b intsrc;
//    Mat dehazed = Mat::zeros(source.rows, source.cols, CV_8UC3);

//    for(int i=0; i<source.rows; i++)
//    {
//        for(int j=0; j<source.cols; j++)
//        {
//            inttran = t.at<uchar>(i,j);
//            intsrc = source.at<Vec3b>(i,j);
//            tmax = (inttran.val[0]/255) < tmin ? tmin : (inttran.val[0]/255);
//            for(int k=0; k<3; k++)
//            {
//                dehazed.at<Vec3b>(i,j)[k] = abs((intsrc.val[k] - al) / tmax + al) > 255 ? 255 : abs((intsrc.val[k] - al) / tmax + al);
//            }
//        }
//    }
//    return dehazed;
//}




//int main(int argc, char** argv)
//{
//    //for video defogging

//    VideoCapture vid("/home/oscar/Videos/foggy4.mp4");
//    if(!vid.isOpened())
//        return -1;
//    double rate = vid.get(cv::CAP_PROP_FPS);
//    int delay = 1000/rate;
//    bool stop(false);

//    Mat frame;
//    Mat darkChannel;
//    Mat T;
//    Mat fogfree;
//    double alpha = 0.05;    //alpha smoothing
//    int Airlightp;          //airlight value of previous frame
//    int Airlight;           //airlight value of current frame
//    int FrameCount = 0;     //frame number
//    int ad;                 //temp airlight value
//    namedWindow("before and after", cv::WINDOW_AUTOSIZE);

//    for(;;)
//    {
//        vid >> frame;
//        FrameCount++;
//        if(vid.get(cv::CAP_PROP_POS_AVI_RATIO)==1)
//            break;

//        //create mat for showing the frame before and after processing
//        Mat beforeafter = Mat::zeros(frame.rows, 2 * frame.cols, CV_8UC3);
//        Rect roil (0, 0, frame.cols, frame.rows);
//        Rect roir (frame.cols, 0, frame.cols, frame.rows);

//        //first frame, without airlight smoothing
//        if (FrameCount == 1)
//        {
//            darkChannel = getMedianDarkChannel(frame, 5);
//            Airlight = estimateA(darkChannel);
//            T = estimateTransmission(darkChannel, Airlight);
//            ad = Airlight;
//            fogfree = getDehazed(frame, T, Airlight);
//        }

//        //other frames, with airlight smoothing
//        else
//        {
//            double t = (double)getTickCount();

//            Airlightp = ad;
//            darkChannel = getMedianDarkChannel(frame, 5);
//            Airlight = estimateA(darkChannel);
//            T = estimateTransmission(darkChannel, Airlight);
//            cout<<"previous:"<<Airlightp<<"--current:"<<Airlight<<endl;
//            ad = int(alpha * double(Airlight) + (1 - alpha) * double(Airlightp));//airlight smoothing
//            cout<<"smoothed airlight is:"<<ad<<endl;
//            fogfree = getDehazed(frame, T, ad);

//            t = (double)cv::getTickCount() - t;
//            printf( "=============Execution time per frame = %gms\n", t/((double)cv::getTickFrequency()*1000.) );
//        }
//        frame.copyTo(beforeafter(roil));
//        fogfree.copyTo(beforeafter(roir));
//        imshow("before and after", beforeafter);

//        if(waitKey(delay) >= 0)
//            stop = true;
//    }

//    return 0;
//}


////////////////////////////////////////////////////////////////////////////////////////////////////

//#include"ImageDefogging.h"


//int main()
//{
////效果参数
//double omega = 0.95;
//double numt = 0.3;
//int rectSize = 15;

//clock_t startTime, endTime;
//startTime = clock();//计时开始

//Mat src = imread("1.png");
//Mat dst;//(src.rows, src.cols, CV_32FC3)
//Mat dst1(src.rows, src.cols, CV_32FC3);
//ImageDefogging(src, dst, rectSize, omega, numt);

//endTime = clock();				//计时结束
//cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;

//imwrite("dst.jpg", dst);
//imwrite("dst1.jpg", dst1);

///*float scale = 0.15;
//resize(src, src, Size(src.cols*scale, src.rows*scale));
//resize(dst, dst, Size(dst.cols*scale, dst.rows*scale));
//resize(dst1, dst1, Size(dst1.cols*scale, dst1.rows*scale));*/

//dst /= 255;
//dst1 /= 255;
//imshow("src", src);
//imshow("dst", dst);
//imshow("dst1", dst1);

//waitKey();
//return 0;
//}

//void ImageDefogging(Mat src, Mat& dst, int rectSize, double omega, double numt)
//{
////对原图进行归一化
//Mat I;
//src.convertTo(I, CV_32F);
//I /= 255;

//float A[3] = { 0 };
//Mat dark = DarkChannel(I, rectSize);
//AtmLight(I, dark, A);

//Mat te = TransmissionEstimate(I, A, rectSize, omega);
//Mat t = TransmissionRefine(src, te);
//dst = Defogging(I, t, A, numt);
//}

//Mat DarkChannel(Mat srcImg, int size)
//{
//vector<Mat> chanels;
//split(srcImg, chanels);

////求RGB三通道中的最小像像素值
//Mat minChannel = (cv::min)((cv::min)(chanels[0], chanels[1]), chanels[2]);
//Mat kernel = getStructuringElement(MORPH_RECT, Size(size, size));

//Mat dark(minChannel.rows, minChannel.cols, CV_32FC1);
//erode(minChannel, dark, kernel);	//图像腐蚀
//return dark;
//}

//template<typename T> vector<int> argsort(const vector<T>& array)
//{
//const int array_len(array.size());
//vector<int> array_index(array_len, 0);
//for (int i = 0; i < array_len; ++i)
//  array_index[i] = i;

//sort(array_index.begin(), array_index.end(),
//  [&array](int pos1, int pos2) {return (array[pos1] < array[pos2]); });

//return array_index;
//}

//void AtmLight(Mat src, Mat dark, float outA[3])
//{
//int row = src.rows;
//int col = src.cols;
//int imgSize = row*col;

////将暗图像和原图转为列向量
//vector<int> darkVector = dark.reshape(1, imgSize);
//Mat srcVector = src.reshape(3, imgSize);

////按照亮度的大小取前0.1%的像素（亮度高）
//int numpx = int(max(floor(imgSize / 1000), 1.0));
//vector<int> indices = argsort(darkVector);
//vector<int> dstIndices(indices.begin() + (imgSize - numpx), indices.end());

//for (int i = 0; i < numpx; ++i)
//{
//  outA[0] += srcVector.at<Vec3f>(dstIndices[i], 0)[0];
//  outA[1] += srcVector.at<Vec3f>(dstIndices[i], 0)[1];
//  outA[2] += srcVector.at<Vec3f>(dstIndices[i], 0)[2];
//}
//outA[0] /= numpx;
//outA[1] /= numpx;
//outA[2] /= numpx;
//}

//Mat TransmissionEstimate(Mat src, float outA[3], int size, float omega)
//{
//Mat imgA = Mat::zeros(src.rows, src.cols, CV_32FC3);

//vector<Mat> chanels;
//split(src, chanels);
//for (int i = 0; i < 3; ++i)
//{
//  chanels[i] = chanels[i] / outA[i];
//}

//merge(chanels, imgA);
//Mat transmission = 1 - omega*DarkChannel(imgA, size);	//计算透射率预估值
//return transmission;
//}

//Mat Guidedfilter(Mat src, Mat te, int r, float eps)
//{
//Mat meanI, meanT, meanIT, meanII, meanA, meanB;
//boxFilter(src, meanI, CV_32F, Size(r, r));
//boxFilter(te, meanT, CV_32F, Size(r, r));
//boxFilter(src.mul(te), meanIT, CV_32F, Size(r, r));
//Mat covIT = meanIT - meanI.mul(meanT);

//boxFilter(src.mul(src), meanII, CV_32F, Size(r, r));
//Mat varI = meanII - meanI.mul(meanI);

//Mat a = covIT / (varI + eps);
//Mat b = meanT - a.mul(meanI);
//boxFilter(a, meanA, CV_32F, Size(r, r));
//boxFilter(b, meanB, CV_32F, Size(r, r));

//Mat t = meanA.mul(src) + meanB;

//return t;
//}

//Mat TransmissionRefine(Mat src, Mat te)
//{
//Mat gray;
//cvtColor(src, gray, CV_BGR2GRAY);
//gray.convertTo(gray, CV_32F);
//gray /= 255;

//int r = 60;
//float eps = 0.0001;
//Mat t = Guidedfilter(gray, te, r, eps);
//return t;
//}

//Mat Defogging(Mat src, Mat t, float outA[3], float tx)
//{
//Mat dst = Mat::zeros(src.rows, src.cols, CV_32FC3);
//t = (cv::max)(t, tx);				//设置阈值当投射图t 的值很小时，会导致图像整体向白场过度

//vector<Mat> chanels;
//split(src, chanels);
//for (int i = 0; i < 3; ++i)
//{
//  chanels[i] = (chanels[i] - outA[i]) / t + outA[i];
//}
//merge(chanels, dst);

//dst *= 255;				//归一化还原
//return dst;
//}

//void GetFiles(string path, vector<string>& files, string fileType)
//{
//intptr_t   hFile = 0;
//struct _finddata_t fileinfo;
//string p;
//if ((hFile = _findfirst(p.assign(path).append("\\" + fileType).c_str(), &fileinfo)) != -1)
//{
//  do
//  {
//      if ((fileinfo.attrib &  _A_SUBDIR))
//      {
//          if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//              GetFiles(p.assign(path).append("\\").append(fileinfo.name), files);
//      }
//      else
//      {
//          files.push_back(p.assign(path).append("\\").append(fileinfo.name));
//      }
//  } while (_findnext(hFile, &fileinfo) == 0);
//  _findclose(hFile);

//  //文件排序
//  sort(files.begin(), files.end(),
//      [](const string &a, const string &b){
//      return a.length() < b.length() || a.length() == b.length() && a < b;
//  });
//}
//}





#endif // TEST_H
