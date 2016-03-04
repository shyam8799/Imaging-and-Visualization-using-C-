#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <math.h>


#ifndef TRAJECTORYGENERATOR_H
#define TRAJECTORYGENERATOR_H


class TrajectoryGenerator
{
    public:
        TrajectoryGenerator();
        virtual ~TrajectoryGenerator();
        static std::string generate(int x_steps, int angle_steps);
    protected:
    private:
};

#endif // TRAJECTORYGENERATOR_H
