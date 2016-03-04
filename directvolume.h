#ifndef DIRECTVOLUME_H
#define DIRECTVOLUME_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QGridLayout>
#include <time.h>
#include <Eigen/Geometry>
#include <vector>

#include "transferfunction.h"
#include "volume.h"

class DirectVolume : public QWidget
{
    Q_OBJECT
public:
    explicit DirectVolume(QWidget *parent = 0);
    void initialize(Eigen::Vector3f position, int intMin, int intMax);
    std::vector<Eigen::Vector3f> getPixelPositions(Eigen::Vector3f normal);
    std::vector<Eigen::ParametrizedLine<float, 3> > setupRays();
    void setVolume(Volume vol);

signals:

public slots:

private:
    QGridLayout* layout;
    QLabel* label;
    QImage* image;
    Volume volume;
    Eigen::Vector3f position;
    TransferFunction tf;
    float minIntValue;
    float maxIntValue;
};

#endif // DIRECTVOLUME_H
