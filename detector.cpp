#include "detector.h"

Detector::Detector() {

}

void Detector::setPosition(Eigen::Vector3f position, Eigen::Vector3f normal, float angle) {
    this->position = position;
    this->normal = normal;
    this->angle = angle;
    pixels.setZero();
}

void Detector::setPixel(int i, float value) {
    pixels(i) = value;
}

PXLVector Detector::getImage() {
    return this->pixels;
}


std::vector<Eigen::Vector3f> Detector::getPixelPositions() {
    std::vector<Eigen::Vector3f> list;
    Eigen::Vector3f v1(0,0,1);
    Eigen::Vector3f v2 = v1.cross(normal);
    v2.normalize();

    for(float i = -0.08; i <= 0.08; i+=0.04) {
        for(float j = -0.08; j <= 0.08; j+=0.04) {
            Eigen::Vector3f pixelPosition = position + (i * v2) + (j * v1);
            list.push_back(pixelPosition);
        }
    }
    return list;
}
