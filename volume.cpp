#include "volume.h"

Volume::Volume(){
    lowerLeft = Eigen::Vector3f(0,0,0);
    upperRight = Eigen::Vector3f(0.15, 0.15, 0.25);
    dimSpacing = Eigen::Vector3f(0.015, 0.015, 0.025);
    dimSize = Eigen::Vector3i(10,10,10);
}
Volume::Volume(Eigen::Vector3f lL,Eigen::Vector3f uR,Eigen::Vector3f dSp, Eigen::Vector3i dSz) {
    lowerLeft = lL;
    upperRight = uR;
    dimSpacing = dSp;
    dimSize = dSz;
}

void Volume::setContent(const Eigen::VectorXf d) {
    data = d;
}


Eigen::Vector3f Volume::getDimSpacing() {
    return dimSpacing;
}

Eigen::VectorXf Volume::getContent() {
    return data;
}

Eigen::Vector3i Volume::getNumVoxels() {
   return dimSize;
}

float Volume::getVoxelValue(int index) {
    return data(index);
}

std::vector< std::vector<Eigen::Vector3f> > Volume::getVoxelCoordinates() {
    return voxelCoordinates;
}

int Volume::getDataSize() {
    return data.size();
}
Eigen::Vector3i Volume::getDimSize() {
    return dimSize;
}

void Volume::setVoxelCoordinates() {
    for(int i = 0; i < data.size(); i++) {
        Eigen::Vector3f min(i%dimSize(0) * dimSpacing(0), ((int)(i/dimSize(0)))%dimSize(1) * dimSpacing(1), ((int)(i/(dimSize(2)*dimSize(1)))) * dimSpacing(2));
        Eigen::Vector3f max = min + dimSpacing;
        std::vector<Eigen::Vector3f> coords;
        coords.push_back(min);
        coords.push_back(max);
        voxelCoordinates.push_back(coords);
    }
}

bool Volume::intersectionRayVoxel(Eigen::ParametrizedLine<float, 3> ray, Eigen::Vector3f min, Eigen::Vector3f max, float t0, float t1) {
    float txmin, txmax, tymin, tymax, tzmin, tzmax;
    Eigen::Vector3f origin = ray.origin();
    Eigen::Vector3f direction = ray.direction();
    if (direction[0] >= 0) {
        txmin = (min[0] - origin[0]) / direction[0];
        txmax = (max[0] - origin[0]) / direction[0];
    }
    else {
        txmin = (max[0] - origin[0]) / direction[0];
        txmax = (min[0] - origin[0]) / direction[0];
    }
    if (direction[1] >= 0) {
        tymin = (min[1] - origin[1]) / direction[1];
        tymax = (max[1] - origin[1]) / direction[1];
    }
    else {
        tymin = (max[1] - origin[1]) / direction[1];
        tymax = (min[1] - origin[1]) / direction[1];
    }
    if ( (txmin > tymax) || (tymin > txmax) ) {
        return false;
    }
    if (tymin > txmin) {
        txmin = tymin;
    }
    if (tymax < txmax) {
        txmax = tymax;
    }
    if (direction[2] >= 0) {
        tzmin = (min[2] - origin[2]) / direction[2];
        tzmax = (max[2] - origin[2]) / direction[2];
    }
    else {
        tzmin = (max[2] - origin[2]) / direction[2];
        tzmax = (min[2] - origin[2]) / direction[2];
    }
    if ( (txmin > tzmax) || (tzmin > txmax) ) {
        return false;
    }
    if (tzmin > txmin) {
        txmin = tzmin;
    }
    if (tzmax < txmax) {
        txmax = tzmax;
    }
    return ( (txmin < t1) && (txmax > t0) );
}


float Volume::getVoxel(int x, int y, int z) {
    if(((x >= 0) && (x < dimSize(0))) && ((y >= 0) && (y < dimSize(1))) && ((z >= 0) && (z < dimSize(2)))) {
        return ((float) data[z*dimSize(0)*dimSize(1) + y*dimSize(0) + x]);
    }
    else {
        return 0.0;
    }
}

float Volume::getVoxelLinear(float x, float y, float z) {
    int index_x = floor(x / dimSpacing(0));
    int index_y = floor(y / dimSpacing(1));
    int index_z = floor(z / dimSpacing(2));
    if( x > (index_x * dimSpacing(0) + dimSpacing(0)/2) ) {
        index_x++;
    }
    if( y > (index_y * dimSpacing(1) + dimSpacing(1)/2) ) {
        index_y++;
    }
    if( z > (index_z * dimSpacing(2) + dimSpacing(2)/2) ) {
        index_z++;
    }
    float min_x = index_x * dimSpacing(0) - dimSpacing(0)/2;
    float max_x = index_x * dimSpacing(0) + dimSpacing(0)/2;
    float min_y = index_y * dimSpacing(1) - dimSpacing(1)/2;
    float max_y = index_y * dimSpacing(1) + dimSpacing(1)/2;
    float min_z = index_z * dimSpacing(2) - dimSpacing(2)/2;
    float max_z = index_z * dimSpacing(2) + dimSpacing(2)/2;
    float neighbors[8];



    neighbors[0] = (float) getVoxel((index_x-1), (index_y-1), (index_z-1));
    neighbors[1] = (float) getVoxel((index_x), (index_y-1), (index_z-1));
    neighbors[2] = (float) getVoxel((index_x-1), (index_y), (index_z-1));
    neighbors[3] = (float) getVoxel((index_x), (index_y), (index_z-1));
    neighbors[4] = (float) getVoxel((index_x-1), (index_y-1), (index_z));
    neighbors[5] = (float) getVoxel((index_x), (index_y-1), (index_z));
    neighbors[6] = (float) getVoxel((index_x-1), (index_y), (index_z));
    neighbors[7] = (float) getVoxel((index_x), (index_y), (index_z));


/*
    neighbors[0] = (float) data[(index_x-1) + (index_y-1)*dimSize(0) + (index_z-1)*dimSize(0)*dimSize(1)];
    neighbors[1] = (float) data[(index_x) + (index_y-1)*dimSize(0) + (index_z-1)*dimSize(0)*dimSize(1)];
    neighbors[2] = (float) data[(index_x-1) + (index_y)*dimSize(0) + (index_z-1)*dimSize(0)*dimSize(1)];
    neighbors[3] = (float) data[(index_x) + (index_y)*dimSize(0) + (index_z-1)*dimSize(0)*dimSize(1)];
    neighbors[4] = (float) data[(index_x-1) + (index_y-1)*dimSize(0) + (index_z)*dimSize(0)*dimSize(1)];
    neighbors[5] = (float) data[(index_x) + (index_y-1)*dimSize(0) + (index_z)*dimSize(0)*dimSize(1)];
    neighbors[6] = (float) data[(index_x-1) + (index_y)*dimSize(0) + (index_z)*dimSize(0)*dimSize(1)];
    neighbors[7] = (float) data[(index_x) + (index_y)*dimSize(0) + (index_z)*dimSize(0)*dimSize(1)];
*/
    float x_coords[2], y_coords[2], z_coords[2];
    x_coords[0] = min_x;
    x_coords[1] = max_x;
    y_coords[0] = min_y;
    y_coords[1] = max_y;
    z_coords[0] = min_z;
    z_coords[1] = max_z;
    return Formula::interpolation3D(x, y, z, x_coords, y_coords, z_coords, neighbors);
}

float Volume::getVoxelNearest(float x, float y, float z) {

    if(x<=0 || x>=dimSize(0)*dimSpacing(0) || y<=0 || y>=dimSize(1)*dimSpacing(1) ||z<=0 || z>=dimSize(2)*dimSpacing(2)) {

        return 0.0;
    }
    int index_x = floor(x / dimSpacing(0));
    int index_y = floor(y / dimSpacing(1));
    int index_z = floor(z / dimSpacing(2));
    return ((float) data[index_z*dimSize(0)*dimSize(1) + index_y*dimSize(0) + index_x]);
}

Eigen::AlignedBox3f getBoundingBox() {
    return Eigen::AlignedBox3f(Eigen::Vector3f(0,0,0), Eigen::Vector3f(0.15,0.15,0.25));
}

Volume Volume::createCopy(Eigen::VectorXf data)  {
    Volume vol;
    vol.dimSpacing = this->dimSpacing;
    vol.lowerLeft = this->lowerLeft;
    vol.upperRight = this->upperRight;
    vol.voxelCoordinates = this->voxelCoordinates;
    vol.data = data;
    return vol;
}






