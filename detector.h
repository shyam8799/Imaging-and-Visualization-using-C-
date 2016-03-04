#include <Eigen/Dense>
#include <iostream>


#ifndef DETECTOR_H
#define DETECTOR_H

typedef Eigen::Matrix<float, 1, 25> PXLVector;

class Detector {
private:
    Eigen::Vector3f position;
    Eigen::Vector3f normal;
    float angle;
    PXLVector pixels;
public:
    Detector();

    //Returns the pixel Image
    PXLVector getImage();

    void setPosition(Eigen::Vector3f position, Eigen::Vector3f normal, float angle);
    Eigen::Vector3f  getPosition();
    std::vector<Eigen::Vector3f> getPixelPositions();
    void setPixel(int i, float value);
};

#endif // DETECTOR_H
