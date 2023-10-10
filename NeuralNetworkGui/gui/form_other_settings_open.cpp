#include"form_other_settings_open.h"
#include"gui/defines_gui.h"

FormOtherSettingsOpen::FormOtherSettingsOpen(const double&lambda,const double&alfa,const char&separator,const std::string&parametersFile){

    int columnLeftWidth=0;

    this->_mainLayout=new QVBoxLayout();

    this->_groupBoxTraining=new QGroupBox();
    this->_layoutTraining=new QVBoxLayout();
    this->_spacerTraining=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->_layoutRowsTraining=new QVector<QHBoxLayout*>();
    this->_labelLambda=new QLabel();
    this->_spinBoxLambda=new QDoubleSpinBox();
    this->_labelAlfa=new QLabel();
    this->_spinBoxAlfa=new QDoubleSpinBox();

    this->_groupBoxParametersFile=new QGroupBox();
    this->_layoutParametersFile=new QVBoxLayout();
    this->_spacerParametersFile=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->_layoutRowsParametersFile=new QVector<QHBoxLayout*>();
    this->_labelParametersFileName=new QLabel();
    this->_lineEditParametersFileName=new QLineEdit();
    this->_labelSeparator=new QLabel();
    this->_lineEditSeparator=new QLineEdit();

    this->_pushButtonSubmit=new QPushButton();

    this->_layoutRowsTraining->push_back(new QHBoxLayout());
    this->_labelLambda->setText("Lambda");
    this->_spinBoxLambda->setMinimum(LAMBDA_MIN);
    this->_spinBoxLambda->setMaximum(LAMBDA_MAX);
    this->_spinBoxLambda->setDecimals(LAMBDA_DECIMALS);
    this->_spinBoxLambda->setSingleStep(LAMBDA_SINGLE_STEP);
    this->_spinBoxLambda->setValue(lambda);
    this->_spinBoxLambda->setLocale(LOCAL_FOR_DECIMAL_SEPARATOR);
    this->_layoutRowsTraining->back()->addWidget(this->_labelLambda);
    this->_layoutRowsTraining->back()->addWidget(this->_spinBoxLambda);
    this->_layoutRowsTraining->back()->addSpacerItem(this->_spacerTraining);
    this->_layoutTraining->addLayout(this->_layoutRowsTraining->back());
    if(columnLeftWidth<this->_labelLambda->sizeHint().width())columnLeftWidth=this->_labelLambda->sizeHint().width();

    this->_layoutRowsTraining->push_back(new QHBoxLayout());
    this->_labelAlfa->setText("Alfa");
    this->_spinBoxAlfa->setMinimum(ALFA_MIN);
    this->_spinBoxAlfa->setMaximum(ALFA_MAX);
    this->_spinBoxAlfa->setDecimals(ALFA_DECIMALS);
    this->_spinBoxAlfa->setSingleStep(ALFA_SINGLE_STEP);
    this->_spinBoxAlfa->setValue(alfa);
    this->_spinBoxAlfa->setLocale(LOCAL_FOR_DECIMAL_SEPARATOR);
    this->_layoutRowsTraining->back()->addWidget(this->_labelAlfa);
    this->_layoutRowsTraining->back()->addWidget(this->_spinBoxAlfa);
    this->_layoutRowsTraining->back()->addSpacerItem(this->_spacerTraining);
    this->_layoutTraining->addLayout(this->_layoutRowsTraining->back());
    if(columnLeftWidth<this->_labelAlfa->sizeHint().width())columnLeftWidth=this->_labelAlfa->sizeHint().width();

    this->_groupBoxTraining->setTitle("Training Settings");
    this->_groupBoxTraining->setLayout(this->_layoutTraining);
    this->_mainLayout->addWidget(this->_groupBoxTraining);

    this->_layoutRowsParametersFile->push_back(new QHBoxLayout());
    QString separatorDescription;
    for(int i=0;i<COUNT_SEPARATOR;i++){
        if(separator==SEPARATORS[i])
            separatorDescription=SEPARATOR_DESCRIPTIONS[i];
    }
    this->_labelSeparator->setText("Separator character");
    this->_lineEditSeparator->setText(separatorDescription);
    this->_lineEditSeparator->setReadOnly(true);
    this->_lineEditSeparator->setFixedWidth(this->_lineEditSeparator->sizeHint().width());
    this->_layoutRowsParametersFile->back()->addWidget(this->_labelSeparator);
     this->_layoutRowsParametersFile->back()->addWidget(this->_lineEditSeparator);
    this->_layoutRowsParametersFile->back()->addSpacerItem(this->_spacerParametersFile);
    this->_layoutParametersFile->addLayout(this->_layoutRowsParametersFile->back());
    if(columnLeftWidth<this->_labelSeparator->sizeHint().width())columnLeftWidth=this->_labelSeparator->sizeHint().width();

    this->_layoutRowsParametersFile->push_back(new QHBoxLayout());
    this->_labelParametersFileName->setText("File name");
    this->_lineEditParametersFileName->setText(parametersFile.c_str());
    this->_lineEditParametersFileName->setReadOnly(true);
    this->_lineEditParametersFileName->setFixedWidth(PARAMETERS_FILE_NAME_LABEL_WIDTH);
    this->_layoutRowsParametersFile->back()->addWidget(this->_labelParametersFileName);
    this->_layoutRowsParametersFile->back()->addWidget(this->_lineEditParametersFileName);
    this->_layoutParametersFile->addLayout(this->_layoutRowsParametersFile->back());
    if(columnLeftWidth<this->_labelParametersFileName->sizeHint().width())columnLeftWidth=this->_labelParametersFileName->sizeHint().width();

    this->_labelLambda->setFixedWidth(columnLeftWidth);
    this->_labelAlfa->setFixedWidth(columnLeftWidth);
    this->_groupBoxTraining->setFixedWidth(this->_groupBoxTraining->sizeHint().width());
    this->_labelParametersFileName->setFixedWidth(columnLeftWidth);
    this->_labelSeparator->setFixedWidth(columnLeftWidth);

    this->_groupBoxParametersFile->setTitle("File Settings");
    this->_groupBoxParametersFile->setLayout(this->_layoutParametersFile);
    this->_mainLayout->addWidget(this->_groupBoxParametersFile);

    this->_pushButtonSubmit->setText("SAVE");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->setWindowTitle("Training and File Settings");

    this->setLayout(this->_mainLayout);

    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
}

FormOtherSettingsOpen::~FormOtherSettingsOpen(){
    delete this->_pushButtonSubmit;
    delete this->_labelSeparator;
    delete this->_lineEditSeparator;
    delete this->_labelParametersFileName;
    delete this->_lineEditParametersFileName;

    for(int i=0;i<this->_layoutRowsParametersFile->size();i++)
        this->_layoutRowsParametersFile->at(i)->removeItem(this->_spacerParametersFile);
    delete this->_spacerParametersFile;

    for(int i=0;i<this->_layoutRowsParametersFile->size();i++){
        delete this->_layoutRowsParametersFile->back();
        this->_layoutRowsParametersFile->pop_back();
    }
    delete this->_layoutRowsParametersFile;
    delete this->_layoutParametersFile;
    delete this->_groupBoxParametersFile;

    delete this->_spinBoxAlfa;
    delete this->_labelAlfa;
    delete this->_spinBoxLambda;
    delete this->_labelLambda;

    for(int i=0;i<this->_layoutRowsTraining->size();i++)
        this->_layoutRowsTraining->at(i)->removeItem(this->_spacerTraining);
    delete this->_spacerTraining;

    for(int i=0;i<this->_layoutRowsTraining->size();i++){
        delete this->_layoutRowsTraining->back();
        this->_layoutRowsTraining->pop_back();
    }
    delete this->_layoutRowsTraining;
    delete this->_layoutTraining;
    delete this->_groupBoxTraining;

    delete this->_mainLayout;

}
void FormOtherSettingsOpen::slotPushButtonSubmitClicked(){
    double lambda=this->_spinBoxLambda->value();
    double alfa=this->_spinBoxAlfa->value();

    emit signalOtherSettingsOpenParameters(lambda,alfa);

    this->close();
}
