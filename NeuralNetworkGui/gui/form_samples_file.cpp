#include"form_samples_file.h"
#include"gui/defines_gui.h"

FormSamplesFile::FormSamplesFile(FileType fileType):_fileType(fileType){

    int columnLeftWidth=0;

    this->_mainLayout=new QVBoxLayout();

    this->_layoutCountSample=new QHBoxLayout();
    this->_labelCountSample=new QLabel();
    this->_spinBoxCountSample=new QSpinBox();
    this->_spacerCountSample=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->_layoutFileName=new QHBoxLayout();
    this->_pushButtonOpen=new QPushButton();
    this->_lineEditSamplesFileName=new QLineEdit();
    this->_pushButtonSubmit=new QPushButton();

    this->_labelCountSample->setText("Number of samples");
    this->_layoutCountSample->addWidget(this->_labelCountSample);
    if(columnLeftWidth<this->_labelCountSample->sizeHint().width())columnLeftWidth=this->_labelCountSample->sizeHint().width();

    this->_spinBoxCountSample->setMinimum(COUNT_SAMPLE_MIN);
    this->_spinBoxCountSample->setMaximum(COUNT_SAMPLE_MAX);
    this->_layoutCountSample->addWidget(this->_spinBoxCountSample);
    this->_mainLayout->addLayout(this->_layoutCountSample);
    this->_layoutCountSample->addSpacerItem(this->_spacerCountSample);

    this->_pushButtonOpen->setText("Choose location");
    if(columnLeftWidth<this->_pushButtonOpen->sizeHint().width())columnLeftWidth=this->_pushButtonOpen->sizeHint().width();
    this->_layoutFileName->addWidget(this->_pushButtonOpen);

    this->_pushButtonOpen->setFixedWidth(columnLeftWidth);
    this->_labelCountSample->setFixedWidth(columnLeftWidth);

    this->_lineEditSamplesFileName->setReadOnly(true);
    this->_lineEditSamplesFileName->setFixedWidth(PARAMETERS_FILE_NAME_LABEL_WIDTH);
    this->_layoutFileName->addWidget(this->_lineEditSamplesFileName);
    this->_mainLayout->addLayout(this->_layoutFileName);

    this->_pushButtonSubmit->setText("OK");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    if(this->_fileType==FileType::TestSet)
        this->setWindowTitle("Test File");
    else
        this->setWindowTitle("Training File");

    this->setLayout(this->_mainLayout);
    this->setFixedSize(this->sizeHint().width(),this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
    connect(this->_pushButtonOpen,SIGNAL(clicked()),this,SLOT(slotPushButtonOpenClicked()));
}
FormSamplesFile::~FormSamplesFile(){
    delete this->_pushButtonSubmit;
    delete this->_lineEditSamplesFileName;
    delete this->_pushButtonOpen;
    delete this->_layoutFileName;

    this->_layoutCountSample->removeItem(this->_spacerCountSample);
    delete this->_spacerCountSample;
    delete this->_spinBoxCountSample;
    delete this->_labelCountSample;
    delete this->_layoutCountSample;

    delete this->_mainLayout;
}

void FormSamplesFile::slotPushButtonSubmitClicked(){
    if(this->_lineEditSamplesFileName->text()==""){
        QMessageBox::warning(this,"Error","The location of the file is incorrect. ",QMessageBox::Ok);
        return;
    }

    std::string samplesFileName=this->_lineEditSamplesFileName->text().toStdString();
    int countSample=this->_spinBoxCountSample->value();

    this->setWindowOpacity(FORM_TRANSPARENT);
    this->setEnabled(false);

    emit signalSamplesFileParameters(countSample,samplesFileName);

    this->close();
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
FormSamplesFile::FileType FormSamplesFile::getFileType()const{
    return this->_fileType;
}
