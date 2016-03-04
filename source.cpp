#include "source.h"

Source::Source()
{
    //ctor
}

void Source::setPosition(Eigen::Vector3f position, Eigen::Vector3f normal, float angle) {
    this->position = position;
    this->normal = normal;
}

Eigen::Vector3f Source::getPosition() {
    return this->position;
}
Eigen::Vector3f Source::getNormal() {
    return this->normal;
}
