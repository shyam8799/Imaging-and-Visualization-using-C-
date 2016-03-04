

#include "scanner.h"


struct pargs {
    int arg1;
    Eigen::ParametrizedLine<float, 3> arg2;
};

Scanner::Scanner() {

}

Eigen::VectorXf Scanner::getImage() {
    return robot.getDetector()->getImage();
}

Eigen::VectorXf Scanner::getData() {
    return volume.getContent();
}

std::vector < std::vector <float> > Scanner::getTrajectory() {
    return trajectory;
}

OnTheFlyMatrix Scanner::getOnTheFlyMatrix() {
    return this->onTheFlyMatrix;
}


void Scanner::setTrajectory(std::string fileName) {
    trajectory = CSVFileReader::parseCSV(fileName);
    rvolume.resize(volume.getDataSize());
    rvolume.setZero();
    onTheFlyMatrix.setZero();
}

Volume Scanner::scanVolume(std::string trajectoryFileName, std::string mhdFileName, int numberOfIterations) {
    volume = MHDHandler::read(mhdFileName);
    setTrajectory(trajectoryFileName);
    volume.setVoxelCoordinates();
    int step = 0;
    for(std::vector<float> state : trajectory) {
        robot.setSrcDetPositions(state);
        scan(step);
        rvolume = Solver::sirt(onTheFlyMatrix.getSystemMatrix(), robot.getDetector()->getImage(), rvolume, numberOfIterations);
        step++;
    }
    Volume copy = volume.createCopy(rvolume);
    MHDHandler::write("reconstruction",copy);
    return copy;
}

void Scanner::scan(int step) {
    std::vector<Eigen::ParametrizedLine<float, 3> > rays = robot.getRays();
    for(int i = 0; i < rays.size(); i++) {
        Eigen::ParametrizedLine<float, 3> ray = rays.at(i);
        if(this->volume.intersectionRayVoxel(ray, Eigen::Vector3f(0,0,0), Eigen::Vector3f(0.15, 0.15, 0.25), 0, INFINITY)) {
            float value = computeForwardProjection(ray, i);
            robot.getDetector()->setPixel(i, value);
        }
    }
}

float Scanner::computeForwardProjection(Eigen::ParametrizedLine<float, 3> ray, int step) {
    float value = 0.0;
    std::vector< std::vector<Eigen::Vector3f> > voxels = volume.getVoxelCoordinates();
    for(int i = 0; i < voxels.size(); i++) {
        std::vector <Eigen::Vector3f> vec = voxels.at(i);
        Eigen::Vector3f min = vec.at(0);
        Eigen::Vector3f max = vec.at(1);
        if(this-> volume.intersectionRayVoxel(ray, min, max, 0, INFINITY)) {
            onTheFlyMatrix.setElement(step, i, 1);
            value += volume.getVoxelValue(i);
            continue;
        }
        onTheFlyMatrix.setElement(step, i, 0);
    }
    return value;
}

void Scanner::testSolve() {
    for(int i = 0; i < 1000; i++) {
        if(i % 10 == 0) {
            std::cout << std::endl;
        }
        if(i % 100 == 0) {
            std::cout << std::endl;
        }
        std::cout << rvolume[i] << " ";

    }
    //std::cout << rvolume << std::endl;
}




void Scanner::setupTestEnvironment() {
    //volume = MHDHandler::read("box.mhd");


    Eigen::Matrix<float, 1, 1000> data;

    for(int i = 0; i<1000; i++) {
        data(i) = 1;
    }

    volume.setContent(data);
    volume.setVoxelCoordinates();


    //std::cout << volume.getContent();
    std::vector<float> positions;
    positions.push_back(-0.075);
    positions.push_back(0.075);
    positions.push_back(0.125);
    positions.push_back(1);
    positions.push_back(0);
    positions.push_back(0);
    positions.push_back(0);
    positions.push_back(0.225);
    positions.push_back(0.075);
    positions.push_back(0.125);
    positions.push_back(-1);
    positions.push_back(0);
    positions.push_back(0);
    positions.push_back(0);



    robot.setSrcDetPositions(positions);

    scan(0);

}


