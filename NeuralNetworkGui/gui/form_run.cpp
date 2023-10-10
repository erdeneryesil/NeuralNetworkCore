#include"form_run.h"
#include"gui/defines_gui.h"
#include"form_main.h"

FormRun::FormRun(){

    int columnLeftWidth=0;

    this->_mainLayout=new QVBoxLayout();

    this->_layoutTop=new QHBoxLayout();
    this->_labelSeparator=new QLabel();
    this->_lineEditSeparator=new QLineEdit();
    this->_spacerSeparator=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);
    this->_layoutBottom=new QHBoxLayout();
    this->_labelInputs=new QLabel();
    this->_lineEditInputs=new QLineEdit();
    this->_pushButtonSubmit=new QPushButton();

    this->_labelSeparator->setText("Separator Character ");
    this->_layoutTop->addWidget(this->_labelSeparator);
    if(columnLeftWidth<this->_labelSeparator->sizeHint().width())columnLeftWidth=this->_labelSeparator->sizeHint().width();

    this->_lineEditSeparator->setReadOnly(true);
    QChar separatorCharacter;
    for(int i=0;i<COUNT_SEPARATOR;i++){
        if(FormMain::NeuralNetworkObject()->getSeparator()==SEPARATORS[i]){
            this->_lineEditSeparator->setText(SEPARATOR_DESCRIPTIONS[i]);
            separatorCharacter=SEPARATORS[i];
            break;
        }
    }
    this->_lineEditSeparator->setFixedWidth(this->_lineEditSeparator->sizeHint().width());
    this->_layoutTop->addWidget(this->_lineEditSeparator);
    this->_mainLayout->addLayout(this->_layoutTop);
    this->_layoutTop->addSpacerItem(this->_spacerSeparator);

    QString lineEditInputsText="input0"+(QString)separatorCharacter+"input1"+separatorCharacter+"input2"+separatorCharacter+"..."+separatorCharacter+"inputN";
    this->_labelInputs->setText("Inputs ");
    if(columnLeftWidth<this->_labelInputs->sizeHint().width())columnLeftWidth=this->_labelInputs->sizeHint().width();
    this->_layoutBottom->addWidget(this->_labelInputs);

    this->_labelInputs->setFixedWidth(columnLeftWidth);
    this->_labelSeparator->setFixedWidth(columnLeftWidth);

    QRegExp regexParametersFileName(REGEX_PARAMETERS_INPUTS);
    QRegExpValidator* validatorParametersInputs=new QRegExpValidator(regexParametersFileName,this);
    this->_lineEditInputs->setValidator(validatorParametersInputs);

    this->_lineEditInputs->setFixedWidth(INPUTS_LINE_EDIT_WIDTH);
    this->_layoutBottom->addWidget(this->_lineEditInputs);
    this->_mainLayout->addLayout(this->_layoutBottom);

    this->_pushButtonSubmit->setText("OK");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->setWindowTitle("Run");

    this->setLayout(this->_mainLayout);
    this->setFixedSize(this->sizeHint().width(),this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));

    this->_lineEditInputs->setPlaceholderText(lineEditInputsText);
}
FormRun::~FormRun(){
    delete this->_pushButtonSubmit;
    delete this->_lineEditInputs;
    delete this->_labelInputs;
    delete this->_layoutBottom;

    this->_layoutTop->removeItem(this->_spacerSeparator);
    delete this->_spacerSeparator;
    delete this->_lineEditSeparator;
    delete this->_labelSeparator;
    delete this->_layoutTop;

    delete this->_mainLayout;
}

void FormRun::slotPushButtonSubmitClicked(){
    if(this->_lineEditInputs->text()==""){
        QMessageBox::warning(this,"Error","Inputs are empty. ",QMessageBox::Ok);
        this->close();
        return;
    }
    QStringList rawInputs=this->_lineEditInputs->text().split(FormMain::NeuralNetworkObject()->getSeparator());
    if((size_t)(rawInputs.size())!=FormMain::NeuralNetworkObject()->getInputLayerPattern()->getCountOriginal()){
        QMessageBox::warning(this,"Error","The inputs are incorrect. ",QMessageBox::Ok);
        this->close();
        return;
    }

    int inputs[FormMain::NeuralNetworkObject()->getInputLayerPattern()->getCountOriginal()];

    for(int i=0;i<rawInputs.size();i++){
        inputs[i]=rawInputs.at(i).toInt();
    }

    emit signalRunParameters(inputs);

    this->close();
}
