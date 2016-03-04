#include <Eigen/Dense>
#include <iostream>

#ifndef SOLVER_H
#define SOLVER_H


class Solver
{
public:
    static Eigen::VectorXf sirt(Eigen::MatrixXf matrix, Eigen::VectorXf projection, Eigen::VectorXf volume, int steps);
    static Eigen::VectorXf cg(Eigen::MatrixXf matrix, Eigen::VectorXf projection, int steps);
};

#endif // SOLVER_H
