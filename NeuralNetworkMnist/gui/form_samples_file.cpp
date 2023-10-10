#include"form_samples_file.h"
#include"gui/defines_gui.h"
#include"form_main.h"
FormSamplesFile::FormSamplesFile(FileType fileType):_fileType(fileType){

    int columnLeftWidth=0;

    this->_mainLayout=new QVBoxLayout();

    this->_layoutCountSample=new QHBoxLayout();
    this->_labelCountSample=new QLabel();
    this->_spinBoxCountSample=new QSpinBox();
    this->_spacerCountSample=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->_layoutFileName=new QHBoxLayout();
    this->_pushButtonOpenFile=new QPushButton();
    this->_lineEditSamplesFileName=new QLineEdit();
    this->_pushButtonLoadImages=new QPushButton();

    this->_layoutImage=new QHBoxLayout();
    this->_labelImage=new QLabel();
    this->_comboBoxImage=new QComboBox();
    this->_scrollAreaImage=new QScrollArea();
    this->_sceneImage=new QGraphicsScene();
    this->_graphicsViewImage=new QGraphicsView();
    this->_spacerImage=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);

    this->_pushButtonSubmit=new QPushButton();

    this->_threadSampleImages=new ThreadSampleImages(this);

    this->_isReadySceneImage=false;
    this->_graphicsViewImage->setFixedSize(0,0);

    this->_labelCountSample->setText("Number of samples");
    this->_layoutCountSample->addWidget(this->_labelCountSample);;
    if(columnLeftWidth<this->_labelCountSample->sizeHint().width())columnLeftWidth=this->_labelCountSample->sizeHint().width();

    this->_spinBoxCountSample->setMinimum(COUNT_SAMPLE_MIN);
    this->_spinBoxCountSample->setMaximum(COUNT_SAMPLE_MAX);
    this->_layoutCountSample->addWidget(this->_spinBoxCountSample);
    this->_mainLayout->addLayout(this->_layoutCountSample);

    this->_layoutCountSample->addSpacerItem(this->_spacerCountSample);

    this->_pushButtonOpenFile->setText("Choose location");
    if(columnLeftWidth<this->_pushButtonOpenFile->sizeHint().width())columnLeftWidth=this->_pushButtonOpenFile->sizeHint().width();
    this->_layoutFileName->addWidget(this->_pushButtonOpenFile);

    this->_lineEditSamplesFileName->setReadOnly(true);
    this->_lineEditSamplesFileName->setFixedWidth(PARAMETERS_FILE_NAME_LABEL_WIDTH);
    this->_layoutFileName->addWidget(this->_lineEditSamplesFileName);
    this->_mainLayout->addLayout(this->_layoutFileName);

    this->_pushButtonLoadImages->setText("Load Images");
    this->_mainLayout->addWidget(this->_pushButtonLoadImages);

    this->_labelImage->setText("Images");
    this->_layoutImage->addWidget(this->_labelImage);
    if(columnLeftWidth<this->_labelImage->sizeHint().width())columnLeftWidth=this->_labelImage->sizeHint().width();

    this->_comboBoxImage->addItem("Select");
    for(int i=0;i<COUNT_MNIST_IMAGE;i++)
        this->_comboBoxImage->addItem(QString::number(i));

    this->_scrollAreaImage->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOn);
    this->_scrollAreaImage->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    this->_scrollAreaImage->setWidgetResizable(true);
    this->_scrollAreaImage->setWidget(this->_graphicsViewImage);


    this->_layoutImage->addWidget(this->_comboBoxImage);
    this->_layoutImage->addWidget(this->_scrollAreaImage);
    this->_layoutImage->addSpacerItem(this->_spacerImage);
    this->_mainLayout->addLayout(this->_layoutImage);


    this->_pushButtonSubmit->setText("OK");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->_pushButtonOpenFile->setFixedWidth(columnLeftWidth);
    this->_labelCountSample->setFixedWidth(columnLeftWidth);
    this->_labelImage->setFixedWidth(columnLeftWidth);

    if(this->_fileType==FileType::TestSet)
        this->setWindowTitle("Test File");
    else
        this->setWindowTitle("Training File");

    this->setLayout(this->_mainLayout);
    this->setFixedSize(this->sizeHint().width(),this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    connect(this->_pushButtonLoadImages,SIGNAL(clicked()),this,SLOT(slotPushButtonLoadImagesClicked()));
    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
    connect(this->_pushButtonOpenFile,SIGNAL(clicked()),this,SLOT(slotPushButtonOpenClicked()));
    connect(this->_comboBoxImage,SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboBoxImageCurrentIndexChanged(int)));
    connect(this->_threadSampleImages,SIGNAL(signalFillImagesError()),this,SLOT(slotFillImagesError()));
    connect(this->_threadSampleImages,SIGNAL(signalFillImagesFinished()),this,SLOT(slotFillImagesFinished()));
    connect(this->_threadSampleImages,SIGNAL(signalPrepareImageGUI(int,int)),this,SLOT(slotPrepareImageGUI(int,int)));
    connect(this->_threadSampleImages,SIGNAL(signalDrawImage(QPixmap)),this,SLOT(slotDrawImage(QPixmap)));

    this->_viewBeforeLoadImages();

}
FormSamplesFile::~FormSamplesFile(){
    delete this->_pushButtonSubmit;
    delete this->_pushButtonLoadImages;
    delete this->_lineEditSamplesFileName;
    delete this->_pushButtonOpenFile;
    delete this->_layoutFileName;

    this->_layoutImage->removeItem(this->_spacerImage);
    delete this->_spacerImage;
    delete this->_graphicsViewImage;
    delete this->_scrollAreaImage;
    delete this->_comboBoxImage;
    delete this->_labelImage;
    delete this->_layoutImage;

    delete this->_threadSampleImages;

    delete this->_sceneImage;

    this->_layoutCountSample->removeItem(this->_spacerCountSample);
    delete this->_spacerCountSample;
    delete this->_spinBoxCountSample;
    delete this->_labelCountSample;
    delete this->_layoutCountSample;

    delete this->_mainLayout;
}
void FormSamplesFile::_viewBeforeLoadImages(){
    this->_labelCountSample->setEnabled(true);
    this->_spinBoxCountSample->setEnabled(true);
    this->_pushButtonOpenFile->setEnabled(true);
    this->_lineEditSamplesFileName->setEnabled(true);
    this->_pushButtonLoadImages->setEnabled(true);

    this->_labelImage->setEnabled(false);
    this->_comboBoxImage->setEnabled(false);
    this->_scrollAreaImage->setEnabled(false);
    this->_graphicsViewImage->setEnabled(false);

    this->_pushButtonSubmit->setEnabled(false);
}
void FormSamplesFile::_viewAfterLoadImages(){
    this->_labelCountSample->setEnabled(false);
    this->_spinBoxCountSample->setEnabled(false);
    this->_pushButtonOpenFile->setEnabled(false);
    this->_lineEditSamplesFileName->setEnabled(false);
    this->_pushButtonLoadImages->setEnabled(false);

    this->_labelImage->setEnabled(true);
    this->_comboBoxImage->setEnabled(true);
    this->_scrollAreaImage->setEnabled(true);
    this->_graphicsViewImage->setEnabled(true);

    this->_pushButtonSubmit->setEnabled(true);
}

FormSamplesFile::FileType FormSamplesFile::getFileType()const{
    return this->_fileType;
}
int FormSamplesFile::getCountImage()const{
    return this->_countImage;
}
std::string FormSamplesFile::getSamplesFile()const{
    return this->_samplesFile;
}
int FormSamplesFile::getImageDigitValue()const{
    return this->_imageDigitValue;
}
qreal FormSamplesFile::getSceneImageWidth()const{
    return this->_sceneImage->width();
}
qreal FormSamplesFile::getSceneImageHeight()const{
    return this->_sceneImage->height();
}
bool FormSamplesFile::isSceneImageReady()const{
    return this->_isReadySceneImage;
}
void FormSamplesFile::slotFillImagesError(){
    QMessageBox::warning(this,"Error","The location of the file is incorrect. ",QMessageBox::Ok);
    this->close();
}
void FormSamplesFile::slotFillImagesFinished(){
    this->setWindowOpacity(FORM_OPAQUE);
    this->setEnabled(true);
    this->_viewAfterLoadImages();
}

void FormSamplesFile::slotPrepareImageGUI(int rowCount, int columnCount){
    this->_graphicsViewImage->setFixedWidth(2*this->_graphicsViewImage->frameWidth()+columnCount*IMAGE_WIDTH);
    this->_graphicsViewImage->setFixedHeight(2*this->_graphicsViewImage->frameWidth()+rowCount*IMAGE_HEIGHT);

    this->_sceneImage->clear();
    this->_sceneImage->setSceneRect(0,0,this->_graphicsViewImage->width()-2*this->_graphicsViewImage->frameWidth(),this->_graphicsViewImage->height()-2*this->_graphicsViewImage->frameWidth());

    this->_isReadySceneImage=true;
}
void FormSamplesFile::slotDrawImage(QPixmap pixmap){
    this->_sceneImage->addPixmap(pixmap);
    this->_graphicsViewImage->setScene(this->_sceneImage);
    this->_isReadySceneImage=false;
    this->_comboBoxImage->setEnabled(true);
}
void FormSamplesFile::slotPushButtonLoadImagesClicked(){
    this->setEnabled(false);
    this->setWindowOpacity(FORM_TRANSPARENT);

    if(this->_lineEditSamplesFileName->text()==""){
        QMessageBox::warning(this,"Error","The location of the file is incorrect. ",QMessageBox::Ok);
        this->setWindowOpacity(FORM_OPAQUE);
        this->setEnabled(true);
        return;
    }

    this->_samplesFile=this->_lineEditSamplesFileName->text().toStdString();

    int countLinesOfFile=FormMain::NeuralNetworkObject()->getCountLinesOfFile(this->_samplesFile);
    this->_countImage=this->_spinBoxCountSample->value();
    if(countLinesOfFile<this->_countImage){
        this->_countImage=countLinesOfFile;
        QMessageBox::information(this,"Correction","Corrected the number of images. ",QMessageBox::Ok);
    }

    this->_spinBoxCountSample->setValue(this->_countImage);

    this->_threadSampleImages->setOperationType(ThreadSampleImages::OperationType::Fill);
    this->_threadSampleImages->start();
}
void FormSamplesFile::slotComboBoxImageCurrentIndexChanged(int index){
    this->_comboBoxImage->setEnabled(false);

    if(index==0){
        this->_graphicsViewImage->setFixedSize(0,0);
        this->_comboBoxImage->setEnabled(true);
        return;
    }

    this->_imageDigitValue=index-1;

    this->_threadSampleImages->setOperationType(ThreadSampleImages::OperationType::Draw);
    this->_threadSampleImages->start();

}
void FormSamplesFile::slotPushButtonOpenClicked(){
    QString title;
    if(this->_fileType==FileType::TestSet)
        title="Open the test file";
    else if(this->_fileType==FileType::TrainingSet)
        title="Open the training file";

    QString samplesFile=QFileDialog::getOpenFileName(this,title);

    this->_lineEditSamplesFileName->setText(samplesFile);
}
void FormSamplesFile::slotPushButtonSubmitClicked(){
    this->setWindowOpacity(FORM_TRANSPARENT);
    this->setEnabled(false);

    emit signalSamplesFileParameters(this->_countImage,this->_samplesFile);

    this->close();
}


