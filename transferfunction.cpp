#include "transferfunction.h"

TransferFunction::TransferFunction()
{

}

QColor TransferFunction::classify(float intensity) {
    if(intensity < minimalIntensity || intensity > maximalIntensity) {

        return QColor(0,0,0,1);
    }
    else {
//        float a = 255.0 / (maximalIntensity - minimalIntensity);
//        float b = a * minimalIntensity;
//        int inten = (int) a * intensity + b;
        int inten = Formula::interpolation1D(intensity, minimalIntensity, maximalIntensity, 0.0, 255.0);
        if(inten >= minimalIntensity || inten<=maximalIntensity) {
            return QColor(0,0,0,inten);
        }

        return QColor(0,0,0,0);
    }
    return QColor(0,0,0,255);
}


void TransferFunction::setIntensityInterval(float min, float max) {
    minimalIntensity = min;
    maximalIntensity = max;
}
