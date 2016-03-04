#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H

#include <QColor>

#include "formula.h"

class TransferFunction
{
private:
    float minimalIntensity;
    float maximalIntensity;

public:


    TransferFunction();
    void setIntensityInterval(float min, float max);
    QColor classify(float intensity);
;

};

#endif // TRANSFERFUNCTION_H
