#include"form_nn_file.h"
#include"gui/defines_gui.h"

FormNNFile::FormNNFile(){

    int columnLeftWidth=0;

    this->_mainLayout=new QVBoxLayout();

    this->_layoutTop=new QHBoxLayout();
    this->_labelSeparator=new QLabel();
    this->_comboBoxSeparator=new QComboBox();
    this->_spacerSeparator=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->_layoutBottom=new QHBoxLayout();
    this->_pushButtonOpen=new QPushButton();
    this->_lineEditParametersFileName=new QLineEdit();
    this->_pushButtonSubmit=new QPushButton();

    this->_labelSeparator->setText("Separator character");
    this->_layoutTop->addWidget(this->_labelSeparator);
    if(columnLeftWidth<this->_labelSeparator->sizeHint().width())columnLeftWidth=this->_labelSeparator->sizeHint().width();

    for(int i=0;i<COUNT_SEPARATOR;i++)
        this->_comboBoxSeparator->addItem(SEPARATOR_DESCRIPTIONS[i]);
    this->_layoutTop->addWidget(this->_comboBoxSeparator);
    this->_mainLayout->addLayout(this->_layoutTop);
    this->_layoutTop->addSpacerItem(this->_spacerSeparator);

    this->_pushButtonOpen->setText("Choose location");
    if(columnLeftWidth<this->_pushButtonOpen->sizeHint().width())columnLeftWidth=this->_pushButtonOpen->sizeHint().width();
    this->_layoutBottom->addWidget(this->_pushButtonOpen);

    this->_pushButtonOpen->setFixedWidth(columnLeftWidth);
    this->_labelSeparator->setFixedWidth(columnLeftWidth);

    this->_lineEditParametersFileName->setReadOnly(true);
    this->_lineEditParametersFileName->setFixedWidth(PARAMETERS_FILE_NAME_LABEL_WIDTH);
    this->_layoutBottom->addWidget(this->_lineEditParametersFileName);
    this->_mainLayout->addLayout(this->_layoutBottom);

    this->_pushButtonSubmit->setText("OK");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->setWindowTitle("Neural Network File");

    this->setLayout(this->_mainLayout);
    this->setFixedSize(this->sizeHint().width(),this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
    connect(this->_pushButtonOpen,SIGNAL(clicked()),this,SLOT(slotPushButtonOpenClicked()));

}
FormNNFile::~FormNNFile(){
    delete this->_pushButtonSubmit;
    delete this->_lineEditParametersFileName;
    delete this->_pushButtonOpen;
    delete this->_layoutBottom;

    this->_layoutTop->removeItem(this->_spacerSeparator);
    delete this->_spacerSeparator;
    delete this->_comboBoxSeparator;
    delete this->_labelSeparator;
    delete this->_layoutTop;

    delete this->_mainLayout;
}
void FormNNFile::slotPushButtonSubmitClicked(){
    if(this->_lineEditParametersFileName->text()==""){
        QMessageBox::warning(this,"Error","The location of the file is incorrect. ",QMessageBox::Ok);
        return;
    }

    std::string parametersFileName=this->_lineEditParametersFileName->text().toStdString();
    char separator=SEPARATORS[this->_comboBoxSeparator->currentIndex()];

    emit signalNNFileParameters(separator,parametersFileName);

    this->close();
}
void FormNNFile::slotPushButtonOpenClicked(){
    QString parametersFile=QFileDialog::getOpenFileName(this,"Open a Neural Network");
    this->_lineEditParametersFileName->setText(parametersFile);
}
