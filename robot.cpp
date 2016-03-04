

#include "robot.h"

Robot::Robot()
{
    //ctor
}

/*
        arguments:
            arg0: one single line from the CSV file containing the positions
        functionality:
            - sets the positions of the detector and the source, ensuring that
                they are facing each other, at every step of of the scanning
                process

*/

void Robot::setSrcDetPositions(std::vector<float> state) {

    Eigen::Vector3f sourcePosition(state.at(0), state.at(1), state.at(2));
    Eigen::Vector3f sourceNormal(state.at(3), state.at(4), state.at(5));
    float sourceAngle = state.at(6);
    Eigen::Vector3f detectorPosition(state.at(7), state.at(8), state.at(9));
    Eigen::Vector3f detectorNormal(state.at(10), state.at(11), state.at(12));
    float detectorAngle = state.at(13);
    source.setPosition(sourcePosition, sourceNormal, sourceAngle);
    detector.setPosition(detectorPosition, detectorNormal, detectorAngle);

    //std::cout << "Check facing: " << sourceNormal.dot(detectorNormal) / (sourceNormal.norm() * detectorNormal.norm()) << std::endl;
}

/*
        functionality:
            - calculates the equations of the rays
        return:
            list of parametrized lines which describe the rays through origin
                and direction
*/

std::vector<Eigen::ParametrizedLine<float, 3> > Robot::getRays() {

    std::vector<Eigen::Vector3f> pixelPositions = detector.getPixelPositions();
    std::vector<Eigen::ParametrizedLine<float, 3> > rays;
    for(Eigen::Vector3f pos : pixelPositions) {
        Eigen::Vector3f origin = source.getPosition();
        Eigen::Vector3f direction(pos - origin);
        Eigen::ParametrizedLine<float, 3> ray(origin, direction);
        rays.push_back(ray);
    }

    return rays;

}

Detector* Robot::getDetector() {
    return &detector;
}

Source Robot::getSource() {
    return source;
}
