#include <Eigen/Dense>


#ifndef ONTHEFLYMATRIX_H
#define ONTHEFLYMATRIX_H

typedef Eigen::Matrix<float, 25, 1000> OTFMatrix;


class OnTheFlyMatrix
{
private:
    OTFMatrix systemMatrix;
public:
    OnTheFlyMatrix();
    OTFMatrix getSystemMatrix();
    void setElement(int x, int y, float value);
    Eigen::VectorXf forwardProjection(Eigen::VectorXf image);
    Eigen::VectorXf backProjection(Eigen::VectorXf projection);
    void setZero();
};

#endif // ONTHEFLYMATRIX_H
