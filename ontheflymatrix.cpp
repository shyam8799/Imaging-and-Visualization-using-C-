#include "ontheflymatrix.h"

OnTheFlyMatrix::OnTheFlyMatrix() {
}
OTFMatrix OnTheFlyMatrix::getSystemMatrix() {
    return this->systemMatrix;
}
void OnTheFlyMatrix::setElement(int x, int y, float value) {
    systemMatrix(x,y) = value;
}
Eigen::VectorXf OnTheFlyMatrix::forwardProjection(Eigen::VectorXf image) {
    return systemMatrix * image;
}
Eigen::VectorXf OnTheFlyMatrix::backProjection(Eigen::VectorXf projection) {
    return systemMatrix.transpose() * projection;
}
void OnTheFlyMatrix::setZero() {
    systemMatrix.setZero();
}

