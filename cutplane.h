#ifndef CUTPLANE_H
#define CUTPLANE_H

#include <Eigen/Dense>
#include <QPixmap>
#include <QImage>
#include <QByteArray>
#include <QBuffer>

#include <iostream>
#include <cstdlib>
#include <time.h>

#include "formula.h"
#include "volume.h"
#include "transferfunction.h"

class CutPlane
{
private:
    Eigen::Vector3f center;
    Eigen::Vector3f direction1;
    Eigen::Vector3f direction2;
    Volume volume;
    TransferFunction tf;
    float minIntValue;
    float maxIntValue;
    int reconstructionMethod;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    CutPlane();
    void setVolume(Volume vol);
    Volume getVolume();
    void setup(float theta1, float theta2, float z, int reconMethod);
    void computeImages();
    QPixmap getImage();
    void testData();
    float getMinValue();
    float getMaxValue();

};

#endif // CUTPLANE_H
