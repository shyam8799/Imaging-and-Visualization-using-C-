#include <Eigen/Dense>

#ifndef SOURCE_H
#define SOURCE_H

class Source {
private:
    Eigen::Vector3f position;
    Eigen::Vector3f normal;
public:
    Source();
    void setPosition(Eigen::Vector3f position, Eigen::Vector3f normal, float angle);
    Eigen::Vector3f getPosition();
    Eigen::Vector3f getNormal();
};


#endif // SOURCE_H
