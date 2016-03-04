#ifndef VOLUME_H
#define VOLUME_H

#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <math.h>

#include "formula.h"


class Volume {
private:
    Eigen::VectorXf data;
    Eigen::VectorXf interpolationData;
    Eigen::Vector3f lowerLeft;
    Eigen::Vector3f upperRight;
    Eigen::Vector3f dimSpacing;
    Eigen::Vector3i dimSize;
    std::vector< std::vector<Eigen::Vector3f> > voxelCoordinates;

public:
    Volume();
    Volume(Eigen::Vector3f lowerLeft, Eigen::Vector3f upperRight,Eigen::Vector3f dSp, Eigen::Vector3i dSz);
    void setContent(Eigen::VectorXf d);
    Eigen::Vector3f getDimSpacing();
    Eigen::VectorXf getContent();
    Eigen::Vector3i getNumVoxels();
    Eigen::Vector3i getDimSize();
    std::vector< std::vector<Eigen::Vector3f> > getVoxelCoordinates();
    void setVoxelCoordinates();
    float getVoxelValue(int index);
    float getVoxel(int x, int y, int z);
    float getVoxelLinear(float x, float y, float z);
    float getVoxelNearest(float x, float y, float z);
    bool intersectionRayVoxel(Eigen::ParametrizedLine<float, 3> line, Eigen::Vector3f min, Eigen::Vector3f max, float t0, float t1);
    int getDataSize();
    Eigen::AlignedBox3f getBoundingBox();
    Volume createCopy(Eigen::VectorXf data);
};

#endif // VOLUME_H
