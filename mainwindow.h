#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QProgressBar>
#include <math.h>

#include "mprvisualizer.h"
#include "mhdhandler.h"
#include "trajectorygenerator.h"
#include "scanner.h"
#include "directvolume.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadData(std::string fileName);
    void initialize();
    void setVolume();
    void reconstruct();

    void mhdFileLoad();
    void csvFileLoad();

    void connectAll();



    QGroupBox* createGlobalSetupGroupBox();
    QGroupBox* createMPRSetupGroupBox();
    QGroupBox* createMIPSetupGroupBox();
    QGroupBox* createMPRVisualizerWidget();
    QGroupBox* createMIPVisualizerWidget();


private:
    QWidget* mainWidget;
    QGridLayout* gridLayout;
    QString fN;

    //Visualizers
        MPRVisualizer* mprVisualizerWidget;
        DirectVolume* directVolumeWidget;

    //Buttons
        QPushButton* loadDataButton;
        QPushButton* loadTrajectoryButton;
        QPushButton* reconstructButton;

    //Sliders
        QSlider* mprVisualizerWidgetPositionSlider;
        QSlider* mprVisualizerWidgetTheta1Slider;
        QSlider* mprVisualizerWidgetTheta2Slider;

        QSlider* mipVisualizerWidgetIntensity1Slider;
        QSlider* mipVisualizerWidgetIntensity2Slider;

    //SpinBoxes
        QSpinBox* mprVisualizerWidgetPositionSpinBox;
        QSpinBox* mprVisualizerWidgetTheta1SpinBox;
        QSpinBox* mprVisualizerWidgetTheta2SpinBox;

        QSpinBox* mipVisualizerWidgetIntensity1SpinBox;
        QSpinBox* mipVisualizerWidgetIntensity2SpinBox;

    //ComboBoxes
        QComboBox* mprReconstructionMethodComboBox;

    //ProgressBar
        QProgressBar* reconstructProgress;

    //Labels
        QLabel* positionOfCutPlaneLabel;
        QLabel* xzAngleLabel;
        QLabel* yzAngleLabel;
        QLabel* algorithmLabel;
        QLabel* minIntensityLabel;
        QLabel* maxIntensityLabel;


    //GroupBoxes
        QGroupBox* setupGroupBox;
        QGridLayout* setupGroupBoxLayout;

        QGroupBox* mprSettingsGroupBox;
        QGridLayout* mprSettingGroupBoxLayout;

        QGroupBox* mipSettingsGroupBox;
        QGridLayout* mipSettingGroupBoxLayout;

        QGroupBox* actionsGroupBox;
        QVBoxLayout* layout;


signals:
        /*
        void changeMPRVisualizerWidgetPositionSpinBoxValue(int value);
        void changeMPRVisualizerWidgetTheta1SpinBoxValue(int value);
        void changeMPRVisualizerWidgetTheta2SpinBoxValue(int value);
        void changeMIPVisualizerWidgetIntensity1SpinBoxValue(int value);
        void changeMIPVisualizerWidgetIntensity2SpinBoxValue(int value);
        */




private slots:
        void onLoadDataButtonClicked();
        void onLoadTrajectoryButtonClicked();
        void onReconstructButtonClicked();

        void updateMPRVisualizerView();
        void updateMIPVisualizerView();
        /*
        void onChangeMPRVisualizerWidgetPositionSlider();
        void onChangeMPRVisualizerWidgetTheta1Slider();
        void onChangeMPRVisualizerWidgetTheta2Slider();
        void onChangeMIPVisualizerWidgetIntensity1Slider();
        void onChangeMIPVisualizerWidgetIntensity2Slider();
        */


};

#endif // MAINWINDOW_H
