#ifndef CPUSTRETCHER_H
#define CPUSTRETCHER_H

#include <QList>

class CpuStretcher
{
public:
    CpuStretcher();

    void stretch14Bit(ushort *pData, int rows = 480, int cols = 640);
};

#endif // CPUSTRETCHER_H
