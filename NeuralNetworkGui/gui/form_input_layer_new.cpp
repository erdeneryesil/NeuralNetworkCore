#include"form_input_layer_new.h"
#include"gui/defines_gui.h"
#include<thread>

FormInputLayerNew::FormInputLayerNew(){
    this->_mainLayout=new QVBoxLayout();
    this->_layoutHead=new QHBoxLayout();

    this->_labelCountInput=new QLabel();
    this->_spinBoxCountInput=new QSpinBox();
    this->_checkBoxSame=new QCheckBox();
    this->_spacerCountInput=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);

    this->_scrollArea=new QScrollArea();
    this->_layoutRowsScrollArea=new QVector<QHBoxLayout*>();
    this->_layoutScrollArea=new QVBoxLayout();
    this->_widgetScrollArea=new QWidget();

    this->_labelDataType=new QVector<QLabel*>();
    this->_comboBoxDataType=new QVector<QComboBox*>();
    this->_layoutDataType=new QVector<QHBoxLayout*>();
    this->_widgetDataType=new QVector<QWidget*>();
    this->_labelMinimum=new QVector<QLabel*>();
    this->_spinBoxMinimum=new QVector<QSpinBox*>();
    this->_layoutMinimum=new QVector<QHBoxLayout*>();
    this->_widgetMinimum=new QVector<QWidget*>();
    this->_labelMaximum=new QVector<QLabel*>();
    this->_spinBoxMaximum=new QVector<QSpinBox*>();
    this->_layoutMaximum=new QVector<QHBoxLayout*>();
    this->_widgetMaximum=new QVector<QWidget*>();

    this->_pushButtonSubmit=new QPushButton();

    this->_threadWidgetRowOperation=new ThreadWidgetRowOperation();

    this->_labelCountInput->setText("Number of inputs");
    this->_spinBoxCountInput->setMinimum(COUNT_INPUT_MIN);
    this->_spinBoxCountInput->setMaximum(COUNT_INPUT_MAX);
    this->_layoutHead->addWidget(this->_labelCountInput);
    this->_layoutHead->addWidget(this->_spinBoxCountInput);

    this->_checkBoxSame->setLayoutDirection(Qt::RightToLeft);
    this->_checkBoxSame->setText("Same all");
    this->_layoutHead->addWidget(this->_checkBoxSame);

    this->_layoutHead->addSpacerItem(this->_spacerCountInput);
    this->_mainLayout->addLayout(this->_layoutHead);

    this->_scrollArea->setFixedHeight(SCROLL_AREA_HEIGHT);
    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->slotCreateWidgetsInRow();
    this->_widgetScrollArea->setLayout(this->_layoutScrollArea);
    this->_scrollArea->setWidget(this->_widgetScrollArea);
    this->_scrollArea->setFixedWidth(this->_widgetScrollArea->width()+this->_scrollArea->verticalScrollBar()->sizeHint().width());
    this->_scrollArea->setFixedHeight(SCROLL_AREA_HEIGHT);

    this->_mainLayout->addWidget(this->_scrollArea);

    this->_pushButtonSubmit->setText("OK");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->setLayout(this->_mainLayout);

    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);
    this->setWindowTitle("Input Layer");

    connect(this->_spinBoxCountInput,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxCountInputValueChanged(int)));
    connect(this->_checkBoxSame,SIGNAL(clicked(bool)),this,SLOT(slotCheckBoxSameClicked(bool)));
    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
    connect(this->_comboBoxDataType->first(),SIGNAL(currentIndexChanged(int)),this,SLOT(slotFirstComboBoxDataTypeCurrentIndexChanged(int)));
    connect(this->_spinBoxMinimum->first(),SIGNAL(valueChanged(int)),this,SLOT(slotFirstSpinBoxMinimumValueChanged(int)));
    connect(this->_spinBoxMaximum->first(),SIGNAL(valueChanged(int)),this,SLOT(slotFirstSpinBoxMaximumValueChanged(int)));
    connect(this->_threadWidgetRowOperation,SIGNAL(signalCreateWidgetsInRow()),this,SLOT(slotCreateWidgetsInRow()));
    connect(this->_threadWidgetRowOperation,SIGNAL(signalDeleteWidgetsInRow()),this,SLOT(slotDeleteWidgetsInRow()));
    qRegisterMetaType<ThreadWidgetRowOperation::OperationType>("ThreadWidgetRowOperation::OperationType");
    connect(this->_threadWidgetRowOperation,SIGNAL(signalWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType)),this,SLOT(slotWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType)));
    connect(this->_threadWidgetRowOperation,SIGNAL(signalOperationFinished()),this,SLOT(slotThreadOperationFinished()));

    this->_countInput=this->_spinBoxCountInput->value();
}
FormInputLayerNew::~FormInputLayerNew()
{
    delete this->_pushButtonSubmit;
    for(size_t i=0;i<this->_countInput;i++){
        this->slotDeleteWidgetsInRow();
    }
    delete this->_labelDataType;
    delete this->_comboBoxDataType;
    delete this->_layoutDataType;
    delete this->_widgetDataType;
    delete this->_labelMinimum;
    delete this->_spinBoxMinimum;
    delete this->_layoutMinimum;
    delete this->_widgetMinimum;
    delete this->_labelMaximum;
    delete this->_spinBoxMaximum;
    delete this->_layoutMaximum;
    delete this->_widgetMaximum;
    delete this->_layoutRowsScrollArea;

    delete this->_layoutScrollArea;
    delete this->_widgetScrollArea;
    delete this->_scrollArea;

    this->_layoutHead->removeItem(_spacerCountInput);
    delete this->_spacerCountInput;
    delete this->_spinBoxCountInput;
    delete this->_labelCountInput;
    delete this->_checkBoxSame;

    delete this->_layoutHead;
    delete this->_mainLayout;

    delete this->_threadWidgetRowOperation;
}

void FormInputLayerNew::slotCreateWidgetsInRow(){
    this->_layoutRowsScrollArea->push_back(new QHBoxLayout());

    this->_layoutDataType->push_back(new QHBoxLayout());
    this->_widgetDataType->push_back(new QWidget());
    this->_labelDataType->push_back(new QLabel());
    this->_labelDataType->back()->setText("Convert to ");
    this->_comboBoxDataType->push_back(new QComboBox());
    for(int i=0;i<COUNT_DATA_TYPES;i++)
        this->_comboBoxDataType->back()->addItem(DATA_TYPES[i]);
    this->_comboBoxDataType->back()->setProperty(PROPERTY_INDEX,this->_comboBoxDataType->size()-1);

    connect(this->_comboBoxDataType->back(),SIGNAL(currentIndexChanged(int)),this,SLOT(slotComboBoxDataTypeCurrentIndexChanged(int)));
    this->_layoutDataType->back()->addWidget(this->_labelDataType->back());
    this->_layoutDataType->back()->addWidget(this->_comboBoxDataType->back());
    this->_widgetDataType->back()->setStyleSheet(WIDGET_STYLESHEET_LIGHT);
    this->_widgetDataType->back()->setLayout(this->_layoutDataType->back());
    this->_layoutRowsScrollArea->back()->addWidget(this->_widgetDataType->back());

    this->_layoutMinimum->push_back(new QHBoxLayout());
    this->_widgetMinimum->push_back(new QWidget());
    this->_labelMinimum->push_back(new QLabel());
    this->_labelMinimum->back()->setText("Minimum");
    this->_spinBoxMinimum->push_back(new QSpinBox());
    this->_spinBoxMinimum->back()->setMinimum(LIMIT_MIN);
    this->_spinBoxMinimum->back()->setMaximum(LIMIT_MAX);
    this->_layoutMinimum->back()->addWidget(this->_labelMinimum->back());
    this->_layoutMinimum->back()->addWidget(this->_spinBoxMinimum->back());
    this->_widgetMinimum->back()->setStyleSheet(WIDGET_STYLESHEET_DARK);
    this->_widgetMinimum->back()->setLayout(this->_layoutMinimum->back());
    this->_layoutRowsScrollArea->back()->addWidget(this->_widgetMinimum->back());

    this->_layoutMaximum->push_back(new QHBoxLayout());
    this->_widgetMaximum->push_back(new QWidget());
    this->_labelMaximum->push_back(new QLabel());
    this->_labelMaximum->back()->setText("Maximum");
    this->_spinBoxMaximum->push_back(new QSpinBox());
    this->_spinBoxMaximum->back()->setMinimum(LIMIT_MIN);
    this->_spinBoxMaximum->back()->setMaximum(LIMIT_MAX);
    this->_layoutMaximum->back()->addWidget(this->_labelMaximum->back());
    this->_layoutMaximum->back()->addWidget(this->_spinBoxMaximum->back());
    this->_widgetMaximum->back()->setStyleSheet(WIDGET_STYLESHEET_LIGHT);
    this->_widgetMaximum->back()->setLayout(this->_layoutMaximum->back());
    this->_layoutRowsScrollArea->back()->addWidget(this->_widgetMaximum->back());

    if(this->_checkBoxSame->checkState()){
        this->_comboBoxDataType->back()->setCurrentIndex(this->_comboBoxDataType->first()->currentIndex());
        this->_comboBoxDataType->back()->setEnabled(false);

        this->_spinBoxMinimum->back()->setValue(this->_spinBoxMinimum->first()->value());
        this->_spinBoxMinimum->back()->setEnabled(false);

        this->_spinBoxMaximum->back()->setValue(this->_spinBoxMaximum->first()->value());
        this->_spinBoxMaximum->back()->setEnabled(false);
    }

    this->_layoutScrollArea->addLayout(this->_layoutRowsScrollArea->back());
}
void FormInputLayerNew::slotDeleteWidgetsInRow(){
    delete this->_labelDataType->back();
    this->_labelDataType->pop_back();
    delete this->_comboBoxDataType->back();
    this->_comboBoxDataType->pop_back();
    delete this->_layoutDataType->back();
    this->_layoutDataType->pop_back();
    delete this->_widgetDataType->back();
    this->_widgetDataType->pop_back();

    delete this->_labelMinimum->back();
    this->_labelMinimum->pop_back();
    delete this->_spinBoxMinimum->back();
    this->_spinBoxMinimum->pop_back();
    delete this->_layoutMinimum->back();
    this->_layoutMinimum->pop_back();
    delete this->_widgetMinimum->back();
    this->_widgetMinimum->pop_back();

    delete this->_labelMaximum->back();
    this->_labelMaximum->pop_back();
    delete this->_spinBoxMaximum->back();
    this->_spinBoxMaximum->pop_back();
    delete this->_layoutMaximum->back();
    this->_layoutMaximum->pop_back();
    delete  this->_widgetMaximum->back();
    this->_widgetMaximum->pop_back();

    delete this->_layoutRowsScrollArea->back();
    this->_layoutRowsScrollArea->pop_back();
}
void FormInputLayerNew::slotWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType operationType){
    int heightRow=this->_layoutRowsScrollArea->first()->sizeHint().height()+this->_layoutRowsScrollArea->first()->layout()->spacing();

    if(operationType==ThreadWidgetRowOperation::OperationType::AddRow){
        this->_widgetScrollArea->setFixedHeight(this->_widgetScrollArea->geometry().height()+heightRow);
    }else if(operationType==ThreadWidgetRowOperation::OperationType::RemoveRow){
        this->_widgetScrollArea->setFixedHeight(this->_widgetScrollArea->geometry().height()-heightRow);
    }
}
void FormInputLayerNew::_threadOperationStarted(){
    this->setEnabled(false);
    this->setWindowOpacity(FORM_TRANSPARENT);
}
void FormInputLayerNew::slotThreadOperationFinished(){
    this->setEnabled(true);
    this->setWindowOpacity(FORM_OPAQUE);
    this->_spinBoxCountInput->setFocus();
}
void FormInputLayerNew::slotSpinBoxCountInputValueChanged(int value){
    while(this->_threadWidgetRowOperation->isRunning())
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    int diff=std::abs(value-(int)this->_countInput);

    this->_threadOperationStarted();
    if((size_t)value>this->_countInput){
        this->_threadWidgetRowOperation->setOperationType(ThreadWidgetRowOperation::OperationType::AddRow,diff);
    }
    else{
        this->_threadWidgetRowOperation->setOperationType(ThreadWidgetRowOperation::OperationType::RemoveRow,diff);
    }
    this->_threadWidgetRowOperation->start();

    this->_countInput=value;
}
void FormInputLayerNew::slotComboBoxDataTypeCurrentIndexChanged(int currentIndex){
    int objectIndex=sender()->property(PROPERTY_INDEX).value<int>();

    if(currentIndex==TYPE_NATIVE_INDEX){
        this->_spinBoxMinimum->at(objectIndex)->setValue(0);
        this->_spinBoxMinimum->at(objectIndex)->setEnabled(false);
        this->_spinBoxMaximum->at(objectIndex)->setValue(1);
        this->_spinBoxMaximum->at(objectIndex)->setEnabled(false);
    }else{
        this->_spinBoxMinimum->at(objectIndex)->setValue(0);
        this->_spinBoxMinimum->at(objectIndex)->setEnabled(true);
        this->_spinBoxMaximum->at(objectIndex)->setValue(0);
        this->_spinBoxMaximum->at(objectIndex)->setEnabled(true);
    }
}
void FormInputLayerNew::slotCheckBoxSameClicked(bool state){
    if(state){
        for(size_t i=1;i<this->_countInput;i++){
            this->_comboBoxDataType->at(i)->setCurrentIndex(this->_comboBoxDataType->first()->currentIndex());
            this->_comboBoxDataType->at(i)->setEnabled(false);
            this->_spinBoxMinimum->at(i)->setValue(this->_spinBoxMinimum->first()->value());
            this->_spinBoxMinimum->at(i)->setEnabled(false);
            this->_spinBoxMaximum->at(i)->setValue(this->_spinBoxMaximum->first()->value());
            this->_spinBoxMaximum->at(i)->setEnabled(false);
        }
    }else{
        for(size_t i=1;i<this->_countInput;i++){
            this->_comboBoxDataType->at(i)->setCurrentIndex(0);
            this->_comboBoxDataType->at(i)->setEnabled(true);
            this->_spinBoxMinimum->at(i)->setValue(0);
            this->_spinBoxMinimum->at(i)->setEnabled(true);
            this->_spinBoxMaximum->at(i)->setValue(0);
            this->_spinBoxMaximum->at(i)->setEnabled(true);
        }
    }
}
void FormInputLayerNew::slotPushButtonSubmitClicked(){
    int inputTypes[this->_countInput];
    int minimums[this->_countInput];
    int maximums[this->_countInput];

    for(size_t i=0;i<this->_countInput;i++){
        inputTypes[i]=this->_comboBoxDataType->at(i)->currentIndex();
        minimums[i]=this->_spinBoxMinimum->at(i)->value();
        maximums[i]=this->_spinBoxMaximum->at(i)->value();
    }
    emit signalInputLayerNewParameters(this->_countInput,inputTypes,minimums,maximums);

    this->close();
}
void FormInputLayerNew::slotFirstComboBoxDataTypeCurrentIndexChanged(int index){
    if(this->_checkBoxSame->checkState()){
        for(size_t i=1;i<this->_countInput;i++){
            this->_comboBoxDataType->at(i)->setCurrentIndex(index);
            this->_spinBoxMinimum->at(i)->setEnabled(false);
            this->_spinBoxMaximum->at(i)->setEnabled(false);
        }
    }

}
void FormInputLayerNew::slotFirstSpinBoxMinimumValueChanged(int value){
    if(this->_checkBoxSame->checkState()){
        for(size_t i=1;i<this->_countInput;i++){
            this->_spinBoxMinimum->at(i)->setValue(value);
        }
    }
}
void FormInputLayerNew::slotFirstSpinBoxMaximumValueChanged(int value){
    if(this->_checkBoxSame->checkState()){
        for(size_t i=1;i<this->_countInput;i++){
            this->_spinBoxMaximum->at(i)->setValue(value);
        }
    }
}
