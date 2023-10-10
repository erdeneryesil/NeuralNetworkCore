#include"form_other_settings_new.h"
#include"gui/defines_gui.h"
#include<experimental/filesystem>

FormOtherSettingsNew::FormOtherSettingsNew(){

    int columnLeftWidth=0;
    int columnRightWidth=0;

    this->_mainLayout=new QVBoxLayout();

    this->_groupBoxTraining=new QGroupBox();
    this->_layoutTraining=new QVBoxLayout();
    this->_spacerTraining=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->_layoutRowsTraining=new QVector<QHBoxLayout*>();
    this->_labelLambda=new QLabel();
    this->_spinBoxLambda=new QDoubleSpinBox();
    this->_labelAlfa=new QLabel();
    this->_spinBoxAlfa=new QDoubleSpinBox();
    this->_labelRandomWeightMin=new QLabel();
    this->_spinBoxRandomWeightMin=new QDoubleSpinBox();
    this->_labelRandomWeightMax=new QLabel();
    this->_spinBoxRandomWeightMax=new QDoubleSpinBox();

    this->_groupBoxParametersFile=new QGroupBox();
    this->_layoutParametersFile=new QVBoxLayout();
    this->_spacerParametersFile=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->_layoutRowsParametersFile=new QVector<QHBoxLayout*>();

    this->_labelSeparator=new QLabel();
    this->_comboBoxSeparator=new QComboBox();

    this->_pushButtonParametersFileLocation=new QPushButton();
    this->_lineEditParametersFileLocation=new QLineEdit();


    this->_labelParametersFileName=new QLabel();
    this->_lineEditParametersFileName=new QLineEdit();

    this->_pushButtonSubmit=new QPushButton();

    this->_layoutRowsTraining->push_back(new QHBoxLayout());
    this->_labelLambda->setText("Lambda");
    this->_spinBoxLambda->setMinimum(LAMBDA_MIN);
    this->_spinBoxLambda->setMaximum(LAMBDA_MAX);
    this->_spinBoxLambda->setDecimals(LAMBDA_DECIMALS);
    this->_spinBoxLambda->setSingleStep(LAMBDA_SINGLE_STEP);
    this->_spinBoxLambda->setLocale(LOCAL_FOR_DECIMAL_SEPARATOR);
    this->_layoutRowsTraining->back()->addWidget(this->_labelLambda);
    this->_layoutRowsTraining->back()->addWidget(this->_spinBoxLambda);
    this->_layoutRowsTraining->back()->addSpacerItem(this->_spacerTraining);
    this->_layoutTraining->addLayout(this->_layoutRowsTraining->back());
    if(columnLeftWidth<this->_labelLambda->sizeHint().width())columnLeftWidth=this->_labelLambda->sizeHint().width();
    if(columnRightWidth<this->_spinBoxLambda->sizeHint().width())columnRightWidth=this->_spinBoxLambda->sizeHint().width();

    this->_layoutRowsTraining->push_back(new QHBoxLayout());
    this->_labelAlfa->setText("Alfa");
    this->_spinBoxAlfa->setMinimum(ALFA_MIN);
    this->_spinBoxAlfa->setMaximum(ALFA_MAX);
    this->_spinBoxAlfa->setDecimals(ALFA_DECIMALS);
    this->_spinBoxAlfa->setSingleStep(ALFA_SINGLE_STEP);
    this->_spinBoxAlfa->setLocale(LOCAL_FOR_DECIMAL_SEPARATOR);
    this->_layoutRowsTraining->back()->addWidget(this->_labelAlfa);
    this->_layoutRowsTraining->back()->addWidget(this->_spinBoxAlfa);
    this->_layoutRowsTraining->back()->addSpacerItem(this->_spacerTraining);
    this->_layoutTraining->addLayout(this->_layoutRowsTraining->back());
    if(columnLeftWidth<this->_labelAlfa->sizeHint().width())columnLeftWidth=this->_labelAlfa->sizeHint().width();
    if(columnRightWidth<this->_spinBoxAlfa->sizeHint().width())columnRightWidth=this->_spinBoxAlfa->sizeHint().width();

    this->_layoutRowsTraining->push_back(new QHBoxLayout());
    this->_labelRandomWeightMin->setText("Random weight min");
    this->_spinBoxRandomWeightMin->setMinimum(RANDOM_WEIGHT_MIN);
    this->_spinBoxRandomWeightMin->setMaximum(RANDOM_WEIGHT_MAX);
    this->_spinBoxRandomWeightMin->setDecimals(RANDOM_WEIGHT_DECIMALS);
    this->_spinBoxRandomWeightMin->setSingleStep(RANDOM_WEIGHT_SINGLE_STEP);
    this->_spinBoxRandomWeightMin->setLocale(LOCAL_FOR_DECIMAL_SEPARATOR);
    this->_layoutRowsTraining->back()->addWidget(this->_labelRandomWeightMin);
    this->_layoutRowsTraining->back()->addSpacerItem(this->_spacerTraining);
    this->_layoutRowsTraining->back()->addWidget(this->_spinBoxRandomWeightMin);
    this->_layoutTraining->addLayout(this->_layoutRowsTraining->back());
    if(columnLeftWidth<this->_labelRandomWeightMin->sizeHint().width())columnLeftWidth=this->_labelRandomWeightMin->sizeHint().width();
    if(columnRightWidth<this->_spinBoxRandomWeightMin->sizeHint().width())columnRightWidth=this->_spinBoxRandomWeightMin->sizeHint().width();

    this->_layoutRowsTraining->push_back(new QHBoxLayout());
    this->_labelRandomWeightMax->setText("Random weight max");
    this->_spinBoxRandomWeightMax->setMinimum(RANDOM_WEIGHT_MIN);
    this->_spinBoxRandomWeightMax->setMaximum(RANDOM_WEIGHT_MAX);
    this->_spinBoxRandomWeightMax->setDecimals(RANDOM_WEIGHT_DECIMALS);
    this->_spinBoxRandomWeightMax->setSingleStep(RANDOM_WEIGHT_SINGLE_STEP);
    this->_spinBoxRandomWeightMax->setLocale(LOCAL_FOR_DECIMAL_SEPARATOR);
    this->_layoutRowsTraining->back()->addWidget(this->_labelRandomWeightMax);
    this->_layoutRowsTraining->back()->addSpacerItem(this->_spacerTraining);
    this->_layoutRowsTraining->back()->addWidget(this->_spinBoxRandomWeightMax);
    this->_layoutTraining->addLayout(this->_layoutRowsTraining->back());
    if(columnLeftWidth<this->_labelRandomWeightMax->sizeHint().width())columnLeftWidth=this->_labelRandomWeightMax->sizeHint().width();
    if(columnRightWidth<this->_spinBoxRandomWeightMax->sizeHint().width())columnRightWidth=this->_spinBoxRandomWeightMax->sizeHint().width();

    this->_groupBoxTraining->setTitle("Training Settings");
    this->_groupBoxTraining->setLayout(this->_layoutTraining);
    this->_groupBoxTraining->setFixedWidth(this->_groupBoxTraining->sizeHint().width());
    this->_mainLayout->addWidget(this->_groupBoxTraining);

    this->_layoutRowsParametersFile->push_back(new QHBoxLayout());
    this->_labelSeparator->setText("Separator character");
    this->_layoutRowsParametersFile->back()->addWidget(this->_labelSeparator);
    this->_layoutRowsParametersFile->back()->addWidget(this->_comboBoxSeparator);
    this->_layoutRowsParametersFile->back()->addItem(this->_spacerParametersFile);
    this->_layoutParametersFile->addLayout(this->_layoutRowsParametersFile->back());
    if(columnLeftWidth<this->_labelSeparator->sizeHint().width())columnLeftWidth=this->_labelSeparator->sizeHint().width();


    this->_layoutRowsParametersFile->push_back(new QHBoxLayout());
    this->_pushButtonParametersFileLocation->setText("Choose location");
    this->_lineEditParametersFileLocation->setReadOnly(true);
    this->_lineEditParametersFileLocation->setFixedWidth(PARAMETERS_FILE_NAME_LABEL_WIDTH);
    this->_layoutRowsParametersFile->back()->addWidget(this->_pushButtonParametersFileLocation);
    this->_layoutRowsParametersFile->back()->addWidget(this->_lineEditParametersFileLocation);
    this->_layoutParametersFile->addLayout(this->_layoutRowsParametersFile->back());
    if(columnLeftWidth<this->_pushButtonParametersFileLocation->sizeHint().width())columnLeftWidth=this->_pushButtonParametersFileLocation->sizeHint().width();


    this->_layoutRowsParametersFile->push_back(new QHBoxLayout());
    this->_labelParametersFileName->setText("File name");
    this->_layoutRowsParametersFile->back()->addWidget(this->_labelParametersFileName);
    this->_layoutRowsParametersFile->back()->addWidget(this->_lineEditParametersFileName);
    this->_layoutRowsParametersFile->back()->addItem(this->_spacerParametersFile);
    this->_layoutParametersFile->addLayout(this->_layoutRowsParametersFile->back());
    if(columnLeftWidth<this->_labelParametersFileName->sizeHint().width())columnLeftWidth=this->_labelParametersFileName->sizeHint().width();


    this->_labelLambda->setFixedWidth(columnLeftWidth);
    this->_labelAlfa->setFixedWidth(columnLeftWidth);
    this->_labelRandomWeightMin->setFixedWidth(columnLeftWidth);
    this->_labelRandomWeightMax->setFixedWidth(columnLeftWidth);
    this->_labelSeparator->setFixedWidth(columnLeftWidth);
    this->_pushButtonParametersFileLocation->setFixedWidth(columnLeftWidth);
    this->_labelParametersFileName->setFixedWidth(columnLeftWidth);

    QRegExp regexParametersFileName(REGEX_PARAMETERS_FILE_NAME);
    QRegExpValidator* validatorParametersFileName=new QRegExpValidator(regexParametersFileName,this);
    this->_lineEditParametersFileName->setValidator(validatorParametersFileName);
    this->_lineEditParametersFileName->setMaxLength(LENGTH_PARAMETERS_FILE_NAME);
    this->_lineEditParametersFileName->setFixedWidth(columnLeftWidth+columnRightWidth-this->_labelParametersFileName->sizeHint().width());

    for(int i=0;i<COUNT_SEPARATOR;i++)
        this->_comboBoxSeparator->addItem(SEPARATOR_DESCRIPTIONS[i]);
    if(columnRightWidth<this->_comboBoxSeparator->sizeHint().width())columnRightWidth=this->_comboBoxSeparator->sizeHint().width();

    this->_comboBoxSeparator->setFixedWidth(columnLeftWidth+columnRightWidth-this->_labelSeparator->sizeHint().width());
    this->_groupBoxParametersFile->setTitle("File Settings");
    this->_groupBoxParametersFile->setLayout(this->_layoutParametersFile);
    this->_mainLayout->addWidget(this->_groupBoxParametersFile);

    this->_pushButtonSubmit->setText("OK");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->setLayout(this->_mainLayout);

    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);
    this->setWindowTitle("Training and File Settings");

    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
    connect(this->_pushButtonParametersFileLocation,SIGNAL(clicked()),this,SLOT(slotPushButtonParametersFileLocationClicked()));
}
FormOtherSettingsNew::~FormOtherSettingsNew(){
    delete this->_pushButtonSubmit;
    delete this->_pushButtonParametersFileLocation;
    delete this->_lineEditParametersFileLocation;
    delete this->_comboBoxSeparator;
    delete this->_labelSeparator;
    delete this->_lineEditParametersFileName->validator();
    delete this->_lineEditParametersFileName;
    delete this->_labelParametersFileName;

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

    delete this->_spinBoxRandomWeightMax;
    delete this->_labelRandomWeightMax;
    delete this->_spinBoxRandomWeightMin;
    delete this->_labelRandomWeightMin;
    delete this->_spinBoxAlfa;
    delete this->_labelAlfa;
    delete  this->_spinBoxLambda;
    delete this->_labelLambda;

    for(int i=0;i<this->_layoutRowsTraining->size();i++)
        this->_layoutRowsTraining->at(i)->removeItem(this->_spacerTraining);
    delete this->_spacerTraining;


    for(int i=0;i<this->_layoutRowsTraining->size();i++){
        delete  this->_layoutRowsTraining->back();
        this->_layoutRowsTraining->pop_back();
    }

    delete this->_layoutRowsTraining;
    delete this->_layoutTraining;
    delete  this->_groupBoxTraining;

    delete this->_mainLayout;
}
void FormOtherSettingsNew::slotPushButtonParametersFileLocationClicked(){
    QFileDialog dialogParametersFileLocation;
    dialogParametersFileLocation.setFileMode(QFileDialog::DirectoryOnly);
    dialogParametersFileLocation.setOption(QFileDialog::ShowDirsOnly, false);
    dialogParametersFileLocation.exec();
    this->_lineEditParametersFileLocation->setText(dialogParametersFileLocation.directory().toNativeSeparators(dialogParametersFileLocation.directory().path()));
}
void FormOtherSettingsNew::slotPushButtonSubmitClicked(){
    if(this->_lineEditParametersFileLocation->text()=="" || this->_lineEditParametersFileName->text()==""){
        QMessageBox::warning(this,"Error","Either the name or location of the file is incorrect. ",QMessageBox::Ok);
        return;
    }

    double lambda=this->_spinBoxLambda->value();
    double alfa=this->_spinBoxAlfa->value();
    double randomWeightMin=this->_spinBoxRandomWeightMin->value();
    double randomWeightMax=this->_spinBoxRandomWeightMax->value();
    std::string fileName=this->_lineEditParametersFileLocation->text().toStdString();
    fileName.insert(fileName.end(),std::experimental::filesystem::path::preferred_separator);
    fileName.append(this->_lineEditParametersFileName->text().toStdString());
    char separator=SEPARATORS[this->_comboBoxSeparator->currentIndex()];

    emit signalOtherSettingsNewParameters(lambda,alfa,randomWeightMin,randomWeightMax,fileName,separator);

    this->close();
}
