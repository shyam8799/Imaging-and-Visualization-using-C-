#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

}

void MainWindow::initialize() {

    mainWidget = new QWidget(this);
    gridLayout = new QGridLayout(mainWidget);
    this->setCentralWidget(mainWidget);

    mprVisualizerWidget = new MPRVisualizer(mainWidget);
    directVolumeWidget = new DirectVolume(mainWidget);

    gridLayout->addWidget(createGlobalSetupGroupBox(), 0,0);
    gridLayout->addWidget(createMPRSetupGroupBox(), 1,0);
    gridLayout->addWidget(createMIPSetupGroupBox(), 2,0);
    gridLayout->addWidget(mprVisualizerWidget, 0, 1);
    gridLayout->addWidget(directVolumeWidget, 0, 2);

    mprVisualizerWidget->initialize();
    //directVolumeWidget->initialize();

    connectAll();

    mprVisualizerWidget->testData();



    /*
    float theta1 = (M_PI / 180) * mprVisualizerWidgetTheta1SpinBox->value();
    float theta2 = (M_PI / 180) * mprVisualizerWidgetTheta2SpinBox->value();
    float pos = (0.25 / 100) * mprVisualizerWidgetPositionSpinBox->value();

    mprVisualizerWidget->updateCutPlane(theta1, theta2, pos);
    mprVisualizerWidget->update();

    Formula::testInterpolation();
    */

}

QGroupBox* MainWindow::createGlobalSetupGroupBox() {
    setupGroupBox = new QGroupBox("Global Setup", mainWidget);
    setupGroupBoxLayout = new QGridLayout(mainWidget);

    loadDataButton = new QPushButton("Load Data", setupGroupBox);

    reconstructButton = new QPushButton("Reconstruct", setupGroupBox);



    setupGroupBoxLayout->addWidget(loadDataButton,0, 0);
    setupGroupBoxLayout->addWidget(reconstructButton, 2, 0);

    reconstructButton->setDisabled(true);

    setupGroupBox->setLayout(setupGroupBoxLayout);

    return setupGroupBox;
}

QGroupBox* MainWindow::createMPRSetupGroupBox() {
    mprSettingsGroupBox = new QGroupBox("MPR Visualization", mainWidget);
    mprSettingGroupBoxLayout = new QGridLayout(mainWidget);

    mprVisualizerWidgetPositionSlider = new QSlider(Qt::Horizontal, mainWidget);
        mprVisualizerWidgetPositionSlider->setMinimum(-100);
        mprVisualizerWidgetPositionSlider->setMaximum(100);
        mprVisualizerWidgetPositionSlider->setTickInterval(1);

    mprVisualizerWidgetPositionSpinBox = new QSpinBox(mainWidget);
        mprVisualizerWidgetPositionSpinBox->setMinimum(-100);
        mprVisualizerWidgetPositionSpinBox->setMaximum(100);
        mprVisualizerWidgetPositionSpinBox->setSingleStep(1);

    mprVisualizerWidgetTheta1Slider = new QSlider(Qt::Horizontal, mainWidget);
        mprVisualizerWidgetTheta1Slider->setMinimum(-100);
        mprVisualizerWidgetTheta1Slider->setMaximum(100);
        mprVisualizerWidgetTheta1Slider->setTickInterval(1);

    mprVisualizerWidgetTheta1SpinBox = new QSpinBox(mainWidget);
        mprVisualizerWidgetTheta1SpinBox->setMinimum(-100);
        mprVisualizerWidgetTheta1SpinBox->setMaximum(100);
        mprVisualizerWidgetTheta1SpinBox->setSingleStep(1);

    mprVisualizerWidgetTheta2Slider = new QSlider(Qt::Horizontal, mainWidget);
        mprVisualizerWidgetTheta2Slider->setMinimum(-100);
        mprVisualizerWidgetTheta2Slider->setMaximum(100);
        mprVisualizerWidgetTheta2Slider->setTickInterval(1);

    mprVisualizerWidgetTheta2SpinBox = new QSpinBox(mainWidget);
        mprVisualizerWidgetTheta2SpinBox->setMinimum(-100);
        mprVisualizerWidgetTheta2SpinBox->setMaximum(100);
        mprVisualizerWidgetTheta2SpinBox->setSingleStep(1);

    mprReconstructionMethodComboBox = new QComboBox(mainWidget);
        mprReconstructionMethodComboBox->addItem("Nearest Neighbor");
        mprReconstructionMethodComboBox->addItem("Linear Interpolation");


    positionOfCutPlaneLabel = new QLabel("Position", mainWidget);
    xzAngleLabel = new QLabel("x-z Angle", mainWidget);
    yzAngleLabel = new QLabel("y-z Angle", mainWidget);
    algorithmLabel = new QLabel("Algorithm", mainWidget);

    mprSettingGroupBoxLayout->addWidget(positionOfCutPlaneLabel, 0, 0);
    mprSettingGroupBoxLayout->addWidget(xzAngleLabel, 1, 0);
    mprSettingGroupBoxLayout->addWidget(yzAngleLabel, 2, 0);
    mprSettingGroupBoxLayout->addWidget(algorithmLabel, 3, 0);

    mprSettingGroupBoxLayout->addWidget(mprVisualizerWidgetPositionSlider, 0, 1);
    mprSettingGroupBoxLayout->addWidget(mprVisualizerWidgetTheta1Slider, 1, 1);
    mprSettingGroupBoxLayout->addWidget(mprVisualizerWidgetTheta2Slider, 2, 1);

    mprSettingGroupBoxLayout->addWidget(mprVisualizerWidgetPositionSpinBox, 0, 2);
    mprSettingGroupBoxLayout->addWidget(mprVisualizerWidgetTheta1SpinBox, 1, 2);
    mprSettingGroupBoxLayout->addWidget(mprVisualizerWidgetTheta2SpinBox, 2, 2);

    mprSettingGroupBoxLayout->addWidget(mprReconstructionMethodComboBox, 3, 1);

    mprSettingsGroupBox->setLayout(mprSettingGroupBoxLayout);

    mprSettingsGroupBox->setDisabled(true);

    return mprSettingsGroupBox;
}

QGroupBox* MainWindow::createMIPSetupGroupBox() {
    mipSettingsGroupBox = new QGroupBox("MIP Visualization", mainWidget);
    mipSettingGroupBoxLayout = new QGridLayout(mainWidget);

    mipVisualizerWidgetIntensity1Slider = new QSlider(Qt::Horizontal, mainWidget);
        mipVisualizerWidgetIntensity1Slider->setMinimum(0);
        mipVisualizerWidgetIntensity1Slider->setMaximum(255);
        mipVisualizerWidgetIntensity1Slider->setTickInterval(1);
    mipVisualizerWidgetIntensity2Slider = new QSlider(Qt::Horizontal, mainWidget);
        mipVisualizerWidgetIntensity2Slider->setMinimum(0);
        mipVisualizerWidgetIntensity2Slider->setMaximum(255);
        mipVisualizerWidgetIntensity2Slider->setTickInterval(1);

    mipVisualizerWidgetIntensity1SpinBox = new QSpinBox(mainWidget);
        mipVisualizerWidgetIntensity1SpinBox->setMinimum(0);
        mipVisualizerWidgetIntensity1SpinBox->setMaximum(255);
        mipVisualizerWidgetIntensity1SpinBox->setSingleStep(1);

    mipVisualizerWidgetIntensity2SpinBox = new QSpinBox(mainWidget);
        mipVisualizerWidgetIntensity2SpinBox->setMinimum(0);
        mipVisualizerWidgetIntensity2SpinBox->setMaximum(255);
        mipVisualizerWidgetIntensity2SpinBox->setSingleStep(1);

    mipSettingGroupBoxLayout->addWidget(mipVisualizerWidgetIntensity1Slider, 0, 0);
    mipSettingGroupBoxLayout->addWidget(mipVisualizerWidgetIntensity2Slider, 1, 0);
    mipSettingGroupBoxLayout->addWidget(mipVisualizerWidgetIntensity1SpinBox, 0, 1);
    mipSettingGroupBoxLayout->addWidget(mipVisualizerWidgetIntensity2SpinBox, 1, 1);

    mipSettingsGroupBox->setLayout(mipSettingGroupBoxLayout);

    mipSettingsGroupBox->setDisabled(true);

    return mipSettingsGroupBox;
}

void MainWindow::onLoadDataButtonClicked() {


    QString fileName = QFileDialog::getOpenFileName(this, tr("Open MHD File..."), QString(), tr("MHD-Files (*.mhd);;All Files (*)"));

    if(fileName != 0) {
        fN = fileName;
        mprSettingsGroupBox->setEnabled(true);
        mipSettingsGroupBox->setEnabled(true);
        reconstructButton->setEnabled(true);
        Volume volume = MHDHandler::read(fileName.toStdString());
        mprVisualizerWidget->initializeVolume(volume);
        directVolumeWidget->setVolume(volume);

        updateMPRVisualizerView();
        updateMIPVisualizerView();

    }
}

void MainWindow::onLoadTrajectoryButtonClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open CSV File..."), QString(), tr("CSV-Files (*.csv);;All Files (*)"));   
}

void MainWindow::onReconstructButtonClicked() {

    std::string trjFile = TrajectoryGenerator::generate(3, 50);
    Scanner scan;
    QProgressBar bar(mainWidget);
    bar.setRange(0,0);
    bar.show();
    Volume volume = scan.scanVolume(trjFile, fN.toStdString(), 25);
    mprVisualizerWidget->initializeVolume(volume);
    directVolumeWidget->setVolume(volume);
    bar.hide();



}

void MainWindow::connectAll() {

    QObject::connect(loadDataButton, SIGNAL(clicked()), this, SLOT(onLoadDataButtonClicked()));
    //QObject::connect(loadTrajectoryButton, SIGNAL(clicked()), this, SLOT(onLoadTrajectoryButtonClicked()));
    QObject::connect(reconstructButton, SIGNAL(clicked()), this, SLOT(onReconstructButtonClicked()));

    QObject::connect(mprVisualizerWidgetPositionSlider, SIGNAL(valueChanged(int)), mprVisualizerWidgetPositionSpinBox, SLOT(setValue(int)));
    QObject::connect(mprVisualizerWidgetTheta1Slider, SIGNAL(valueChanged(int)), mprVisualizerWidgetTheta1SpinBox, SLOT(setValue(int)));
    QObject::connect(mprVisualizerWidgetTheta2Slider, SIGNAL(valueChanged(int)), mprVisualizerWidgetTheta2SpinBox, SLOT(setValue(int)));
    QObject::connect(mipVisualizerWidgetIntensity1Slider, SIGNAL(valueChanged(int)), mipVisualizerWidgetIntensity1SpinBox, SLOT(setValue(int)));
    QObject::connect(mipVisualizerWidgetIntensity2Slider, SIGNAL(valueChanged(int)), mipVisualizerWidgetIntensity2SpinBox, SLOT(setValue(int)));

    QObject::connect(mprVisualizerWidgetPositionSpinBox, SIGNAL(valueChanged(int)), mprVisualizerWidgetPositionSlider, SLOT(setValue(int)));
    QObject::connect(mprVisualizerWidgetTheta1SpinBox, SIGNAL(valueChanged(int)), mprVisualizerWidgetTheta1Slider, SLOT(setValue(int)));
    QObject::connect(mprVisualizerWidgetTheta2SpinBox, SIGNAL(valueChanged(int)), mprVisualizerWidgetTheta2Slider, SLOT(setValue(int)));
    QObject::connect(mipVisualizerWidgetIntensity1SpinBox, SIGNAL(valueChanged(int)), mipVisualizerWidgetIntensity1Slider, SLOT(setValue(int)));
    QObject::connect(mipVisualizerWidgetIntensity2SpinBox, SIGNAL(valueChanged(int)), mipVisualizerWidgetIntensity2Slider, SLOT(setValue(int)));

    QObject::connect(mprVisualizerWidgetPositionSlider, SIGNAL(valueChanged(int)), this, SLOT(updateMPRVisualizerView()));
    QObject::connect(mprVisualizerWidgetTheta1Slider, SIGNAL(valueChanged(int)), this, SLOT(updateMPRVisualizerView()));
    QObject::connect(mprVisualizerWidgetTheta2Slider, SIGNAL(valueChanged(int)), this, SLOT(updateMPRVisualizerView()));

    QObject::connect(mprReconstructionMethodComboBox, SIGNAL(activated()), this, SLOT(updateMPRVisualizerView()));

    QObject::connect(mipVisualizerWidgetIntensity1Slider, SIGNAL(valueChanged(int)), this, SLOT(updateMIPVisualizerView()));
    QObject::connect(mipVisualizerWidgetIntensity2Slider, SIGNAL(valueChanged(int)), this, SLOT(updateMIPVisualizerView()));




}

void MainWindow::updateMPRVisualizerView() {
    float theta1 = (M_PI / 200) * mprVisualizerWidgetTheta1SpinBox->value();
    float theta2 = (M_PI / 200) * mprVisualizerWidgetTheta2SpinBox->value();
    float pos = (0.25 / 100) * mprVisualizerWidgetPositionSpinBox->value();
    int reconstructionMethod = mprReconstructionMethodComboBox->currentIndex();


    mprVisualizerWidget->updateCutPlane(theta1, theta2, pos, reconstructionMethod);

    mprVisualizerWidget->update();
}

void MainWindow::updateMIPVisualizerView() {
    //prVisualizerWidget->updateCutPlane(theta1, theta2, pos, reconstructionMethod);

    float intensity1 = mipVisualizerWidgetIntensity1Slider->value();
    float intensity2 = mipVisualizerWidgetIntensity2Slider->value();
    directVolumeWidget->initialize(Eigen::Vector3f(0,-0.5,0), intensity1, intensity2);
    //directVolumeWidget->update();
}

MainWindow::~MainWindow()
{

}
