#include "directvolume.h"

DirectVolume::DirectVolume(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout(this);
    label = new QLabel();
    layout->addWidget(label,0, 0);
}

void DirectVolume::setVolume(Volume vol) {
    this->volume = vol;


    QSize size(200, 200);
    image = new QImage(size, QImage::Format_ARGB32);

}

void DirectVolume::initialize(Eigen::Vector3f pos, int intMin, int intMax) {
    if(intMin >= intMax) {
        return;
    }
    srand(time(NULL));
    position = pos;
    Eigen::VectorXf data = volume.getContent();
    float min = data(0);
    float max = data(0);
    for(int i = 0; i<1000; i++) {
        if(min>data(i)) {
            min = data(i);
        }
        if(max<data(i)) {
            max = data(i);
        }
    }
    minIntValue = intMin;
    maxIntValue = intMax;
    tf.setIntensityInterval(minIntValue, maxIntValue);
    float maxIntensity;
    QColor color;
    int i = -10, j = 0;
    std::vector<Eigen::ParametrizedLine<float, 3> > rays = setupRays();
    for(Eigen::ParametrizedLine<float, 3> ray : rays) {
        maxIntensity = 0;
        if(!volume.intersectionRayVoxel(ray, Eigen::Vector3f(0,0,0), Eigen::Vector3f((float)volume.getDimSize()[0],(float)volume.getDimSize()[1],(float)volume.getDimSize()[2]), 0, INFINITY)) {
            i= i+10;
            if(i==200) {
                i = 0;
                j=j+10;
            }
            if(j==200) {
                j = 0;
            }
            continue;
        }
        for(int i = 0; i < 50; i++) {
            Eigen::Vector3f step = ray.pointAt((float) i/50.0);
            float value = volume.getVoxelNearest(step(0), step(1), step(2));
            color = tf.classify(value);
            if(maxIntensity < color.alpha()) {
                maxIntensity = color.alpha();
            }
        }
        color.setAlpha(maxIntensity);


//        i=i+1;
//        if(i==200) {
//            i = 0;
//            j = j+1;
//        }
//        if(j==200) {
//            j = 0;
//        }

//        image->setPixel(i, j, color.rgba());

        i=i+10;
        if(i==200) {
            i = 0;
            j = j+10;
        }
        if(j==200) {
            j = 0;
        }
        for(int a = 0; a < 10; a++) {
            for(int b = 0; b < 10; b++) {
                image->setPixel(j+a, i+b, color.rgba());
            }
        }

    }

    label->setPixmap(QPixmap::fromImage(*image));

}

std::vector<Eigen::ParametrizedLine<float, 3> > DirectVolume::setupRays() {
    std::vector<Eigen::ParametrizedLine<float, 3> > rays;
    Eigen::Vector3f direction(0,1,0);
    std::vector<Eigen::Vector3f> positions = getPixelPositions(direction);
    for(Eigen::Vector3f origin : positions) {
        Eigen::ParametrizedLine<float, 3> ray(origin, direction);
        rays.push_back(ray);
    }
    return rays;
}

std::vector<Eigen::Vector3f> DirectVolume::getPixelPositions(Eigen::Vector3f normal) {
    std::vector<Eigen::Vector3f> list;
    Eigen::Vector3f v1(0,0,1);
    Eigen::Vector3f v2 = (-1) * v1.cross(normal);
    v2.normalize();
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) {
            Eigen::Vector3f pixelPosition = position + (i * v2 * (volume.getDimSize()[0] * volume.getDimSpacing()[0]) / 20) + (j * v1 * (volume.getDimSize()[2] * volume.getDimSpacing()[2]) / 20);
            list.push_back(pixelPosition);
        }
    }
    return list;
}

