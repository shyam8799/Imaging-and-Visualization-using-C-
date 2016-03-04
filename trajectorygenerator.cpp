#include "trajectorygenerator.h"

TrajectoryGenerator::TrajectoryGenerator()
{
    //ctor
}

TrajectoryGenerator::~TrajectoryGenerator()
{
    //dtor
}

std::string TrajectoryGenerator::generate(int x_steps, int angle_steps) {

/*
    Eigen::Vector3f sourcePosition(-0.075,0.075,0);
    Eigen::Vector3f sourceNormal(1,0,0);
    float sourceAngle = 0;

    Eigen::Vector3f detectorPosition(0.225,0.075,0);
    Eigen::Vector3f detectorNormal(-1,0,0);
    float detectorAngle = 0;
*/
    float theta = M_PI / angle_steps;
    float height = 0.25 / x_steps;


    int rows = angle_steps * (x_steps+1);
    float values[rows][14];
    int cols = 14;
    for(int j = 0; j <= x_steps; j++) {
        for(int i = 0; i < angle_steps; i++) {

            values[j * angle_steps + i][0] = (-0.15) * cos(theta * i) + (0.075);
            values[j * angle_steps + i][1] = (-0.15) * sin(theta * i) + (0.075);
            values[j * angle_steps + i][2] = height * j;
            values[j * angle_steps + i][3] = cos(theta * i);
            values[j * angle_steps + i][4] = sin(theta * i);
            values[j * angle_steps + i][5] = 0;
            values[j * angle_steps + i][6] = 0;

            values[j * angle_steps + i][7] = (0.15) * cos(theta * i) + (0.075);
            values[j * angle_steps + i][8] = (0.15) * sin(theta * i) + (0.075);
            values[j * angle_steps + i][9] = height * j;
            values[j * angle_steps + i][10] = -cos(theta * i);
            values[j * angle_steps + i][11] = -sin(theta * i);
            values[j * angle_steps + i][12] = 0;
            values[j * angle_steps + i][13] = 0;
        }
    }
    std::string fileName = "trajectory.csv";
    std::ofstream myfile (fileName);
    if (myfile.is_open()) {
        for (int i=0; i<rows;i++) {
            for (int j=0;j<cols;j++) {
                myfile<<values[i][j];
                myfile<<",";
            }
            myfile<<"\n";
        }
        myfile.close();
    }

    return fileName;


}
