#include "mprvisualizer.h"



MPRVisualizer::MPRVisualizer(QWidget *parent) : QWidget(parent)
{

}

void MPRVisualizer::paintEvent(QPaintEvent* paintEvent) {

}

void MPRVisualizer::initializeVolume(Volume vol) {
    cutPlane.setVolume(vol);
}

void MPRVisualizer::initialize() {
    QSize size(500, 500);
    layout = new QGridLayout(this);
    label = new QLabel();
    image = new QImage(size, QImage::Format_ARGB32);

    layout->addWidget(label,0, 0);
    label->setPixmap(cutPlane.getImage());
}

Volume MPRVisualizer::getVolume() {
    return cutPlane.getVolume();
}

void MPRVisualizer::updateCutPlane(float theta1, float theta2, float position, int reconMethod) {
    cutPlane.setup(theta1, theta2, position, reconMethod);
    label->setPixmap(cutPlane.getImage());
}

void MPRVisualizer::testData() {
    cutPlane.testData();
}
