#ifndef MPRVISUALIZER_H
#define MPRVISUALIZER_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBoxLayout>
#include <QImage>
#include <QPen>
#include <QLabel>
#include "cutplane.h"

class MPRVisualizer : public QWidget
{
    Q_OBJECT
public:
    explicit MPRVisualizer(QWidget *parent = 0);
    void updateCutPlane(float theta1, float theta2, float position, int reconMethod);
    void initialize();
    Volume getVolume();
    void initializeVolume(Volume vol);
    void testData();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* pE) override;
private:
    CutPlane cutPlane;
    QLabel* label;
    QImage* image;
    QGridLayout* layout;
};

#endif // MPRVISUALIZER_H
