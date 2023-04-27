#include "cpustretcher.h"
#include "iostream"

CpuStretcher::CpuStretcher()
{

}

void CpuStretcher::stretch14Bit(ushort *pData, int rows, int cols){

    QList<ushort> tContiner;
    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < cols; ++col){
            ushort tData = pData[row * cols + col];
            if(tData != 0 && tData != 16383){
                tContiner.append(tData);
            }
        }
    }

    //    quint64 tSum =  std::accumulate(tContiner.begin(), tContiner.end(), 0);
    //    ushort tMean = tSum / tContiner.size();
    //    qDebug() << "mean:" << tMean;

    std::sort(tContiner.begin(), tContiner.end());

    ushort min = tContiner[tContiner.size()/2] * 0.25, max = tContiner[tContiner.size()/2] * 0.35;
    //    ushort min = tContiner[10], max = tContiner[tContiner.size() - 10];
    //    ushort min = tMean * 0.9, max = tMean * 1.1;

    std::cout << "min:" << min << " max:" << max <<  std::endl;
    std::cout << "mid:" << tContiner[tContiner.size()/2] <<  std::endl;

    float diff = 16383.0f / (float)(max - min);
    for(int row = 0; row < rows; ++row){
        for(int col = 0; col < cols; ++col){
            pData[row * cols + col] = (pData[row * cols + col] - min) * diff;
        }
    }
}
