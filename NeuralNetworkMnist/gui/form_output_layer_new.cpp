#include"form_output_layer_new.h"
#include"gui/defines_gui.h"
#include<thread>

FormOutputLayerNew::FormOutputLayerNew(){
    this->_mainLayout=new QVBoxLayout();
    this->_layoutHead=new QHBoxLayout();

    this->_labelCountOutput=new QLabel();
    this->_spinBoxCountOutput=new QSpinBox();
    this->_checkBoxSame=new QCheckBox();
    this->_labelSumFunction=new QLabel();
    this->_comboBoxSumFunction=new QComboBox();
    this->_labelActFunction=new QLabel();
    this->_comboBoxActFunction=new QComboBox();

    this->_scrollArea=new QScrollArea();
    this->_layoutRowsScrollArea=new QVector<QHBoxLayout*>();
    this->_layoutScrollArea=new QVBoxLayout();
    this->_widgetScrollArea=new QWidget();
    this->_layoutBunch=new QHBoxLayout();

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
    this->_labelTolerance=new QVector<QLabel*>();
    this->_spinBoxTolerance=new QVector<QDoubleSpinBox*>();
    this->_layoutTolerance=new QVector<QHBoxLayout*>();
    this->_widgetTolerance=new QVector<QWidget*>();

    this->_pushButtonSubmit=new QPushButton();

    this->_threadWidgetRowOperation=new ThreadWidgetRowOperation();

    this->_labelCountOutput->setText("Number of outputs");
    this->_spinBoxCountOutput->setMinimum(COUNT_OUTPUT_MIN);
    this->_spinBoxCountOutput->setMaximum(COUNT_OUTPUT_MAX);
    this->_layoutHead->addWidget(this->_labelCountOutput);
    this->_layoutHead->addWidget(this->_spinBoxCountOutput);

    this->_checkBoxSame->setLayoutDirection(Qt::RightToLeft);
    this->_checkBoxSame->setText("Same all");
    this->_layoutHead->addWidget(this->_checkBoxSame);

    this->_labelSumFunction->setText("Summation function");
    for(int i=0;i<COUNT_SUM_FUNCTIONS;i++)
        this->_comboBoxSumFunction->addItem(SUM_FUNCTIONS[i]);
    this->_layoutHead->addWidget(this->_labelSumFunction);
    this->_layoutHead->addWidget(this->_comboBoxSumFunction);

    this->_labelActFunction->setText("Activation function");
    for(int i=0;i<COUNT_ACT_FUNCTIONS;i++)
        this->_comboBoxActFunction->addItem(ACT_FUNCTIONS[i]);
    this->_layoutHead->addWidget(this->_labelActFunction);
    this->_layoutHead->addWidget(this->_comboBoxActFunction);

    this->_mainLayout->addLayout(this->_layoutHead);

    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->slotCreateWidgetsInRow();
    this->_widgetScrollArea->setLayout(this->_layoutScrollArea);
    this->_scrollArea->setWidget(this->_widgetScrollArea);
    this->_scrollArea->setFixedWidth(this->_widgetScrollArea->width()+this->_scrollArea->verticalScrollBar()->sizeHint().width());
    this->_scrollArea->setFixedHeight(SCROLL_AREA_HEIGHT);

    this->_layoutBunch->addWidget(this->_scrollArea);

    this->_mainLayout->addLayout(this->_layoutBunch);

    this->_pushButtonSubmit->setText("OK");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->setLayout(this->_mainLayout);

    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);
    this->setWindowTitle("Output Layer");

    connect(this->_spinBoxCountOutput,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxCountOutputValueChanged(int)));
    connect(this->_checkBoxSame,SIGNAL(clicked(bool)),this,SLOT(slotCheckBoxSameClicked(bool)));
    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
    connect(this->_comboBoxDataType->first(),SIGNAL(currentIndexChanged(int)),this,SLOT(slotFirstComboBoxDataTypeCurrentIndexChanged(int)));
    connect(this->_spinBoxMinimum->first(),SIGNAL(valueChanged(int)),this,SLOT(slotFirstSpinBoxMinimumValueChanged(int)));
    connect(this->_spinBoxMaximum->first(),SIGNAL(valueChanged(int)),this,SLOT(slotFirstSpinBoxMaximumValueChanged(int)));
    connect(this->_spinBoxTolerance->first(),SIGNAL(valueChanged(double)),this,SLOT(slotFirstSpinBoxToleranceValueChanged(double)));
    connect(this->_threadWidgetRowOperation,SIGNAL(signalCreateWidgetsInRow()),this,SLOT(slotCreateWidgetsInRow()));
    connect(this->_threadWidgetRowOperation,SIGNAL(signalDeleteWidgetsInRow()),this,SLOT(slotDeleteWidgetsInRow()));
    qRegisterMetaType<ThreadWidgetRowOperation::OperationType>("ThreadWidgetRowOperation::OperationType");
    connect(this->_threadWidgetRowOperation,SIGNAL(signalWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType)),this,SLOT(slotWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType)));
    connect(this->_threadWidgetRowOperation,SIGNAL(signalOperationFinished()),this,SLOT(slotThreadOperationFinished()));

    this->_countOutput=this->_spinBoxCountOutput->value();
}
FormOutputLayerNew::~FormOutputLayerNew(){
    delete this->_pushButtonSubmit;
    for(size_t i=0;i<this->_countOutput;i++){
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
    delete this->_labelTolerance;
    delete this->_spinBoxTolerance;
    delete this->_layoutTolerance;
    delete this->_widgetTolerance;
    delete this->_layoutRowsScrollArea;

    delete this->_layoutScrollArea;
    delete this->_widgetScrollArea;
    delete this->_scrollArea;
    delete this->_layoutBunch;

    delete this->_spinBoxCountOutput;
    delete this->_labelCountOutput;
    delete this->_checkBoxSame;
    delete this->_comboBoxSumFunction;
    delete this->_labelSumFunction;
    delete this->_labelActFunction;
    delete this->_comboBoxActFunction;

    delete this->_layoutHead;

    delete this->_mainLayout;

    delete this->_threadWidgetRowOperation;
}

void FormOutputLayerNew::slotCreateWidgetsInRow(){

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

    this->_layoutTolerance->push_back(new QHBoxLayout());
    this->_widgetTolerance->push_back(new QWidget());
    this->_labelTolerance->push_back(new QLabel());
    this->_labelTolerance->back()->setText("Tolerance");
    this->_spinBoxTolerance->push_back(new QDoubleSpinBox());
    this->_spinBoxTolerance->back()->setMinimum(TOLERANCE_MIN);
    this->_spinBoxTolerance->back()->setMaximum(TOLERANCE_MAX);
    this->_spinBoxTolerance->back()->setDecimals(TOLERANCE_DECIMALS);
    this->_spinBoxTolerance->back()->setSingleStep(TOLERANCE_SINGLE_STEP);
    this->_spinBoxTolerance->back()->setLocale(LOCAL_FOR_DECIMAL_SEPARATOR);
    this->_layoutTolerance->back()->addWidget(this->_labelTolerance->back());
    this->_layoutTolerance->back()->addWidget(this->_spinBoxTolerance->back());
    this->_widgetTolerance->back()->setStyleSheet(WIDGET_STYLESHEET_DARK);
    this->_widgetTolerance->back()->setLayout(this->_layoutTolerance->back());
    this->_layoutRowsScrollArea->back()->addWidget(this->_widgetTolerance->back());

    if(this->_checkBoxSame->checkState()){
        this->_comboBoxDataType->back()->setCurrentIndex(this->_comboBoxDataType->first()->currentIndex());
        this->_comboBoxDataType->back()->setEnabled(false);

        this->_spinBoxMinimum->back()->setValue(this->_spinBoxMinimum->first()->value());
        this->_spinBoxMinimum->back()->setEnabled(false);

        this->_spinBoxMaximum->back()->setValue(this->_spinBoxMaximum->first()->value());
        this->_spinBoxMaximum->back()->setEnabled(false);

        this->_spinBoxTolerance->back()->setValue(this->_spinBoxTolerance->first()->value());
        this->_spinBoxTolerance->back()->setEnabled(false);
    }

    this->_layoutScrollArea->addLayout(this->_layoutRowsScrollArea->back());
}
void FormOutputLayerNew::slotDeleteWidgetsInRow(){
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

    delete this->_widgetMaximum->back();
    this->_widgetMaximum->pop_back();

    delete this->_labelTolerance->back();
    this->_labelTolerance->pop_back();

    delete this->_spinBoxTolerance->back();
    this->_spinBoxTolerance->pop_back();

    delete this->_layoutTolerance->back();
    this->_layoutTolerance->pop_back();

    delete this->_widgetTolerance->back();
    this->_widgetTolerance->pop_back();

    delete this->_layoutRowsScrollArea->back();
    this->_layoutRowsScrollArea->pop_back();
}
void FormOutputLayerNew::slotWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType operationType){
    int heightRow=this->_layoutRowsScrollArea->first()->sizeHint().height()+this->_layoutRowsScrollArea->first()->layout()->spacing();

    if(operationType==ThreadWidgetRowOperation::OperationType::AddRow){
        this->_widgetScrollArea->setFixedHeight(this->_widgetScrollArea->geometry().height()+heightRow);
    }else if(operationType==ThreadWidgetRowOperation::OperationType::RemoveRow){
        this->_widgetScrollArea->setFixedHeight(this->_widgetScrollArea->geometry().height()-heightRow);
    }
}
void FormOutputLayerNew::_threadOperationStarted(){
    this->setEnabled(false);
    this->setWindowOpacity(FORM_TRANSPARENT);
}
void FormOutputLayerNew::slotThreadOperationFinished(){
    this->setEnabled(true);
    this->setWindowOpacity(FORM_OPAQUE);
    this->_spinBoxCountOutput->setFocus();
}
void FormOutputLayerNew::slotSpinBoxCountOutputValueChanged(int value){
    while(this->_threadWidgetRowOperation->isRunning())
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    int diff=std::abs(value-(int)this->_countOutput);

    this->_threadOperationStarted();
        if((size_t)value>this->_countOutput){
            this->_threadWidgetRowOperation->setOperationType(ThreadWidgetRowOperation::OperationType::AddRow,diff);
        }
        else{
            this->_threadWidgetRowOperation->setOperationType(ThreadWidgetRowOperation::OperationType::RemoveRow,diff);
        }
        this->_threadWidgetRowOperation->start();

    this->_countOutput=value;
}
void FormOutputLayerNew::slotCheckBoxSameClicked(bool state){
    if(state){
        for(size_t i=1;i<this->_countOutput;i++){
            this->_comboBoxDataType->at(i)->setCurrentIndex(this->_comboBoxDataType->first()->currentIndex());
            this->_comboBoxDataType->at(i)->setEnabled(false);
            this->_spinBoxMinimum->at(i)->setValue(this->_spinBoxMinimum->first()->value());
            this->_spinBoxMinimum->at(i)->setEnabled(false);
            this->_spinBoxMaximum->at(i)->setValue(this->_spinBoxMaximum->first()->value());
            this->_spinBoxMaximum->at(i)->setEnabled(false);
            this->_spinBoxTolerance->at(i)->setValue(this->_spinBoxTolerance->first()->value());
            this->_spinBoxTolerance->at(i)->setEnabled(false);
        }
    }else{
        for(size_t i=1;i<this->_countOutput;i++){
            this->_comboBoxDataType->at(i)->setCurrentIndex(0);
            this->_comboBoxDataType->at(i)->setEnabled(true);
            this->_spinBoxMinimum->at(i)->setValue(0);
            this->_spinBoxMinimum->at(i)->setEnabled(true);
            this->_spinBoxMaximum->at(i)->setValue(0);
            this->_spinBoxMaximum->at(i)->setEnabled(true);
            this->_spinBoxTolerance->at(i)->setValue(0);
            this->_spinBoxTolerance->at(i)->setEnabled(true);
        }
    }
}
void FormOutputLayerNew::slotComboBoxDataTypeCurrentIndexChanged(int currentIndex){
    int objectIndex=sender()->property(PROPERTY_INDEX).value<int>();

    if(currentIndex==TYPE_NATIVE_INDEX){
        this->_spinBoxMinimum->at(objectIndex)->setValue(0);
        this->_spinBoxMinimum->at(objectIndex)->setEnabled(false);
        this->_spinBoxMaximum->at(objectIndex)->setValue(1);
        this->_spinBoxMaximum->at(objectIndex)->setEnabled(false);
        this->_spinBoxTolerance->at(objectIndex)->setValue(0);
    }else{
        this->_spinBoxMinimum->at(objectIndex)->setValue(0);
        this->_spinBoxMinimum->at(objectIndex)->setEnabled(true);
        this->_spinBoxMaximum->at(objectIndex)->setValue(0);
        this->_spinBoxMaximum->at(objectIndex)->setEnabled(true);
        this->_spinBoxTolerance->at(objectIndex)->setValue(0);
    }
}
void FormOutputLayerNew::slotPushButtonSubmitClicked(){
    int sumFunction;
    int actFunction;
    int types[this->_countOutput];
    int minimums[this->_countOutput];
    int maximums[this->_countOutput];
    double tolerances[this->_countOutput];

    sumFunction=this->_comboBoxSumFunction->currentIndex();
    actFunction=this->_comboBoxActFunction->currentIndex();
    for(size_t i=0;i<this->_countOutput;i++){
        types[i]=this->_comboBoxDataType->at(i)->currentIndex();
        minimums[i]=this->_spinBoxMinimum->at(i)->value();
        maximums[i]=this->_spinBoxMaximum->at(i)->value();
        tolerances[i]=this->_spinBoxTolerance->at(i)->value();
    }

    emit signalOutputLayerNewParameters(this->_countOutput,sumFunction,actFunction,types,minimums,maximums,tolerances);

    this->close();
}
void FormOutputLayerNew::slotFirstComboBoxDataTypeCurrentIndexChanged(int index){
    if(this->_checkBoxSame->checkState()){
        for(size_t i=1;i<this->_countOutput;i++){
            this->_comboBoxDataType->at(i)->setCurrentIndex(index);
            this->_spinBoxMinimum->at(i)->setEnabled(false);
            this->_spinBoxMaximum->at(i)->setEnabled(false);
        }
    }

}
void FormOutputLayerNew::slotFirstSpinBoxMinimumValueChanged(int value){
    if(this->_checkBoxSame->checkState()){
        for(size_t i=1;i<this->_countOutput;i++){
            this->_spinBoxMinimum->at(i)->setValue(value);
        }
    }
}
void FormOutputLayerNew::slotFirstSpinBoxMaximumValueChanged(int value){
    if(this->_checkBoxSame->checkState()){
        for(size_t i=1;i<this->_countOutput;i++){
            this->_spinBoxMaximum->at(i)->setValue(value);
        }
    }
}
void FormOutputLayerNew::slotFirstSpinBoxToleranceValueChanged(double value){
    if(this->_checkBoxSame->checkState()){
        for(size_t i=1;i<this->_countOutput;i++){
            this->_spinBoxTolerance->at(i)->setValue(value);
        }
    }
}
