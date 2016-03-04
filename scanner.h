#include "robot.h"
#include "mhdhandler.h"
#include "ontheflymatrix.h"
#include "solver.h"
#include "csvfilereader.h"
#include <iostream>
#include <time.h>
#include <pthread.h>

#include <QProgressBar>

#ifndef SCANNER_H
#define SCANNER_H

class Scanner {
private:
    Robot robot;
    Volume volume;
    Eigen::VectorXf rvolume;
    OnTheFlyMatrix onTheFlyMatrix;
    std::vector < std::vector <float> > trajectory;
public:
    Scanner();
    Eigen::VectorXf getData();
    void setTrajectory(std::string fileName);
    OnTheFlyMatrix getOnTheFlyMatrix();
    Eigen::VectorXf getImage();
    Volume scanVolume(std::string trajectoryFileName, std::string mhdFileName, int numberOfIterations);
    void scan(int state);
    float computeForwardProjection(Eigen::ParametrizedLine<float, 3> ray, int step);
    void setupTestEnvironment();
    void testSolve();
    std::vector < std::vector <float> > getTrajectory();
};

#endif // SCANNER_H
