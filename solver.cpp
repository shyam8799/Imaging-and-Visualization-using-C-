#include "solver.h"

Eigen::VectorXf Solver::sirt(Eigen::MatrixXf matrix, Eigen::VectorXf projection, Eigen::VectorXf volume, int steps) {
    Eigen::VectorXf before(1000);

    for(int i = 0; i < 1000; i++) {
        before[i] = volume[i];
    }
    Eigen::VectorXf after(1000);
    after.setZero();


    float alpha = 1.0 / (25.0*steps);

    for(int i = 0; i < steps; i++) {
        //std::cout << before << std::endl;
        after = before + ( alpha * (matrix.transpose() * (projection - (matrix * before))));
        before = after;

    }
    return after;

}
//static Eigen::VectorXf Solver::cg(Eigen::MatrixXf matrix, Eigen::VectorXf projection, int steps) {}
