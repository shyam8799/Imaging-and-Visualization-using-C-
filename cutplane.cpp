#include "cutplane.h"

CutPlane::CutPlane() {

}

void CutPlane::setVolume(Volume vol) {

    volume = vol;
    Eigen::VectorXf data = vol.getContent();

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
    minIntValue = min;
    maxIntValue = max;

    std::cout << min << "-" <<max<< std::endl;


}

Volume CutPlane::getVolume() {
    return volume;
}

void CutPlane::setup(float theta1, float theta2, float z, int reconMethod) {

    direction1[0] = cos(theta1);
    direction1[2] = sin(theta1);

    direction2[1] = cos(theta2);
    direction2[2] = sin(theta2);

    center[2] = z;
    reconstructionMethod = reconMethod;

    tf.setIntensityInterval(minIntValue, maxIntValue);

    std::cout << direction1.transpose() << "-" << direction2.transpose() << "-" << center.transpose() << std::endl;

}

void CutPlane::computeImages() {

}

QPixmap CutPlane::getImage() {
    QSize size(500, 500);
    QImage image(500, 500, QImage::Format_ARGB32);
    QByteArray data;
    data.resize(2000*2000);

    Eigen::Vector3i dimSize = volume.getDimSize();
    Eigen::Vector3f dimSpacing = volume.getDimSpacing();

    for(int i = 0; i < 500; i=i+5) {
        for(int j = 0; j < 500; j=j+5) {
            Eigen::Vector3f position = (direction1 * 0.0003 * i) + (direction2 * 0.0003 * j) + center;

            if(position[0] <= 0 || position[0] >= dimSize(0)*dimSpacing(0) || position[1] <= 0 || position[1] >= dimSize(1)*dimSpacing(1) || position[2] <= 0 || position[2] >= dimSize(2)*dimSpacing(2)) {
                for(int a = 0; a < 5; a++) {
                    for(int b = 0; b < 5; b++) {
                        image.setPixel(i+a, j+b, QColor(0,0,0,0).rgba());
                    }
                }
                continue;
            }
            float intensity;
            switch(reconstructionMethod) {
                case 0:intensity = volume.getVoxelNearest(position[0], position[1], position[2]);break;
                case 1:intensity = volume.getVoxelLinear(position[0], position[1], position[2]);break;
                default:intensity = volume.getVoxelLinear(position[0], position[1], position[2]);break;
            }

            //float intensity = volume.getVoxelLinear(position[0], position[1], position[2]);
            QColor color = tf.classify(intensity);
            int index = (j*2000)+(i*4);
            data[index] = (char) color.red();
            data[index+1] = (char) color.green();
            data[index+2] = (char) color.blue();
            data[index+3] = (char) color.alpha();
            for(int a = 0; a < 5; a++) {
                for(int b = 0; b < 5; b++) {

                    image.setPixel(i+a, j+b, color.rgba());

                }
            }
        }
    }
    return QPixmap::fromImage(image);
}

void CutPlane::testData() {
    Eigen::Matrix<float, 1, 1000> data;

    for(int i = 0; i<10; i++) {
        //data(i) = rand() % 100;
        for(int j = 0; j<100; j++) {
            data(i*100+j) = i;
        }
    }

    volume.setContent(data);
    volume.setVoxelCoordinates();
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
    minIntValue = min;
    maxIntValue = max;
}

