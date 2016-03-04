#include "detector.h"
#include "source.h"
#include <iostream>

#ifndef ROBOT_H
#define ROBOT_H

class Robot {
private:
    Detector detector;
    Source source;
public:
    Robot();
    void setSrcDetPositions(std::vector<float> state);
    std::vector<Eigen::ParametrizedLine<float, 3> > getRays();
    Detector* getDetector();
    Source getSource();
    void setImage(Eigen::MatrixXf image);
};

#endif // ROBOT_H
