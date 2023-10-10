#include"form_hidden_layers_new.h"
#include"gui/defines_gui.h"
#include<thread>

FormHiddenLayersNew::FormHiddenLayersNew(){
    this->_mainLayout=new QVBoxLayout();
    this->_layoutHead=new QHBoxLayout();

    this->_labelCountHiddenLayer=new QLabel();
    this->_spinBoxCountHiddenLayers=new QSpinBox();
    this->_spacerCountHiddenLayers=new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum);

    this->_scrollArea=new QScrollArea();
    this->_layoutRowsScrollArea=new QVector<QHBoxLayout*>();
    this->_layoutScrollArea=new QVBoxLayout();
    this->_widgetScrollArea=new QWidget();

    this->_layoutCountCell=new QVector<QHBoxLayout*>();
    this->_widgetCountCell=new QVector<QWidget*>();
    this->_labelCountCell=new QVector<QLabel*>();
    this->_spinBoxCountCell=new QVector<QSpinBox*>();
    this->_layoutSumFunction=new QVector<QHBoxLayout*>();
    this->_widgetSumFunction=new QVector<QWidget*>();
    this->_labelSumFunction=new QVector<QLabel*>();
    this->_comboBoxSumFunction=new QVector<QComboBox*>();
    this->_layoutActFunction=new QVector<QHBoxLayout*>();
    this->_widgetActFunction=new QVector<QWidget*>();
    this->_labelActFunction=new QVector<QLabel*>();
    this->_comboBoxActFunction=new QVector<QComboBox*>();

    this->_pushButtonSubmit=new QPushButton();

    this->_threadWidgetRowOperation=new ThreadWidgetRowOperation();

    this->_labelCountHiddenLayer->setText("Number of hidden layers ");
    this->_spinBoxCountHiddenLayers->setMinimum(COUNT_HIDDEN_LAYER_MIN);
    this->_spinBoxCountHiddenLayers->setMaximum(COUNT_HIDDEN_LAYER_MAX);

    this->_layoutHead->addWidget(this->_labelCountHiddenLayer);
    this->_layoutHead->addWidget(this->_spinBoxCountHiddenLayers);
    this->_layoutHead->addSpacerItem(this->_spacerCountHiddenLayers);
    this->_mainLayout->addLayout(this->_layoutHead);

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
    this->setWindowTitle("Hidden Layers");

    connect(this->_spinBoxCountHiddenLayers,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxCountHiddenLayersValueChanged(int)));
    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));

    connect(this->_threadWidgetRowOperation,SIGNAL(signalCreateWidgetsInRow()),this,SLOT(slotCreateWidgetsInRow()));
    connect(this->_threadWidgetRowOperation,SIGNAL(signalDeleteWidgetsInRow()),this,SLOT(slotDeleteWidgetsInRow()));
    qRegisterMetaType<ThreadWidgetRowOperation::OperationType>("ThreadWidgetRowOperation::OperationType");
    connect(this->_threadWidgetRowOperation,SIGNAL(signalWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType)),this,SLOT(slotWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType)));
    connect(this->_threadWidgetRowOperation,SIGNAL(signalOperationFinished()),this,SLOT(slotThreadOperationFinished()));

    this->_countHiddenLayer=this->_spinBoxCountHiddenLayers->value();
}
FormHiddenLayersNew::~FormHiddenLayersNew(){
    delete this->_pushButtonSubmit;
    for(size_t i=0;i<this->_countHiddenLayer;i++){
        this->slotDeleteWidgetsInRow();
    }
    delete this->_layoutCountCell;
    delete this->_widgetCountCell;
    delete this->_labelCountCell;
    delete this->_spinBoxCountCell;
    delete this->_layoutSumFunction;
    delete this->_widgetSumFunction;
    delete this->_labelSumFunction;
    delete this->_comboBoxSumFunction;
    delete this->_layoutActFunction;
    delete this->_widgetActFunction;
    delete this->_labelActFunction;
    delete this->_comboBoxActFunction;
    delete this->_layoutRowsScrollArea;

    delete this->_layoutScrollArea;
    delete this->_widgetScrollArea;
    delete this->_scrollArea;

    this->_layoutHead->removeItem(this->_spacerCountHiddenLayers);
    delete this->_spacerCountHiddenLayers;
    delete this->_spinBoxCountHiddenLayers;
    delete this->_labelCountHiddenLayer;

    delete this->_layoutHead;
    delete this->_mainLayout;

    delete this->_threadWidgetRowOperation;
}

void FormHiddenLayersNew::_removeHiddenLayerItemsRow(const int& countRow){
    for(int i=0;i<countRow;i++){
        this->slotDeleteWidgetsInRow();
        int heightRow=this->_layoutRowsScrollArea->first()->sizeHint().height()+this->_layoutRowsScrollArea->first()->layout()->spacing();
        this->_widgetScrollArea->setFixedHeight(this->_widgetScrollArea->geometry().height()-heightRow);
    }
}
void FormHiddenLayersNew::_addHiddenLayerItemsRow(const int& countRow){
    for(int i=0;i<countRow;i++){
        this->slotCreateWidgetsInRow();

        int heightRow=this->_layoutRowsScrollArea->first()->sizeHint().height()+this->_layoutRowsScrollArea->first()->layout()->spacing();
        this->_widgetScrollArea->setFixedHeight(this->_widgetScrollArea->geometry().height()+heightRow);
    }
}
void FormHiddenLayersNew::slotCreateWidgetsInRow(){

    this->_layoutRowsScrollArea->push_back(new QHBoxLayout());

    this->_layoutCountCell->push_back(new QHBoxLayout());
    this->_widgetCountCell->push_back(new QWidget());
    this->_labelCountCell->push_back(new QLabel());
    this->_labelCountCell->back()->setText("Number of cells ");
    this->_spinBoxCountCell->push_back(new QSpinBox());
    this->_spinBoxCountCell->back()->setMinimum(COUNT_HIDDEN_CELL_MIN);
    this->_spinBoxCountCell->back()->setMaximum(COUNT_HIDDEN_CELL_MAX);
    this->_layoutCountCell->back()->addWidget(this->_labelCountCell->back());
    this->_layoutCountCell->back()->addWidget(this->_spinBoxCountCell->back());
    this->_widgetCountCell->back()->setLayout(this->_layoutCountCell->back());
    this->_widgetCountCell->back()->setStyleSheet(WIDGET_STYLESHEET_LIGHT);
    this->_layoutRowsScrollArea->back()->addWidget(this->_widgetCountCell->back());

    this->_layoutSumFunction->push_back(new QHBoxLayout());
    this->_widgetSumFunction->push_back(new QWidget());
    this->_labelSumFunction->push_back(new QLabel());
    this->_labelSumFunction->back()->setText("Summation Function");
    this->_comboBoxSumFunction->push_back(new QComboBox());
    for(int i=0;i<COUNT_SUM_FUNCTIONS;i++)
        this->_comboBoxSumFunction->back()->addItem(SUM_FUNCTIONS[i]);
    this->_layoutSumFunction->back()->addWidget(this->_labelSumFunction->back());
    this->_layoutSumFunction->back()->addWidget(this->_comboBoxSumFunction->back());
    this->_widgetSumFunction->back()->setLayout(this->_layoutSumFunction->back());
    this->_widgetSumFunction->back()->setStyleSheet(WIDGET_STYLESHEET_DARK);
    this->_layoutRowsScrollArea->back()->addWidget(this->_widgetSumFunction->back());

    this->_layoutActFunction->push_back(new QHBoxLayout());
    this->_widgetActFunction->push_back(new QWidget());
    this->_labelActFunction->push_back(new QLabel());
    this->_labelActFunction->back()->setText("Activation Function");
    this->_comboBoxActFunction->push_back(new QComboBox());
    for(int i=0;i<COUNT_ACT_FUNCTIONS;i++)
        this->_comboBoxActFunction->back()->addItem(ACT_FUNCTIONS[i]);
    this->_layoutActFunction->back()->addWidget(this->_labelActFunction->back());
    this->_layoutActFunction->back()->addWidget(this->_comboBoxActFunction->back());
    this->_widgetActFunction->back()->setLayout(this->_layoutActFunction->back());
    this->_widgetActFunction->back()->setStyleSheet(WIDGET_STYLESHEET_LIGHT);
    this->_layoutRowsScrollArea->back()->addWidget(this->_widgetActFunction->back());

    this->_layoutScrollArea->addLayout(this->_layoutRowsScrollArea->back());
}
void FormHiddenLayersNew::slotDeleteWidgetsInRow(){
    delete this->_labelCountCell->back();
    this->_labelCountCell->pop_back();
    delete this->_spinBoxCountCell->back();
    this->_spinBoxCountCell->pop_back();
    delete this->_layoutCountCell->back();
    this->_layoutCountCell->pop_back();
    delete this->_widgetCountCell->back();
    this->_widgetCountCell->pop_back();

    delete this->_labelSumFunction->back();
    this->_labelSumFunction->pop_back();
    delete this->_comboBoxSumFunction->back();
    this->_comboBoxSumFunction->pop_back();
    delete  this->_layoutSumFunction->back();
    this->_layoutSumFunction->pop_back();
    delete  this->_widgetSumFunction->back();
    this->_widgetSumFunction->pop_back();

    delete   this->_labelActFunction->back();
    this->_labelActFunction->pop_back();
    delete  this->_comboBoxActFunction->back();
    this->_comboBoxActFunction->pop_back();
    delete  this->_layoutActFunction->back();
    this->_layoutActFunction->pop_back();
    delete  this->_widgetActFunction->back();
    this->_widgetActFunction->pop_back();

    delete  this->_layoutRowsScrollArea->back();
    this->_layoutRowsScrollArea->pop_back();
}
void FormHiddenLayersNew::slotWidgetScrollAreaSetHeight(ThreadWidgetRowOperation::OperationType operationType){
    int heightRow=this->_layoutRowsScrollArea->first()->sizeHint().height()+this->_layoutRowsScrollArea->first()->layout()->spacing();

    if(operationType==ThreadWidgetRowOperation::OperationType::AddRow){
        this->_widgetScrollArea->setFixedHeight(this->_widgetScrollArea->geometry().height()+heightRow);
    }else if(operationType==ThreadWidgetRowOperation::OperationType::RemoveRow){
        this->_widgetScrollArea->setFixedHeight(this->_widgetScrollArea->geometry().height()-heightRow);
    }
}
void FormHiddenLayersNew::_threadOperationStarted(){
    this->setEnabled(false);
    this->setWindowOpacity(FORM_TRANSPARENT);
}
void FormHiddenLayersNew::slotThreadOperationFinished(){
    this->setEnabled(true);
    this->setWindowOpacity(FORM_OPAQUE);
    this->_spinBoxCountHiddenLayers->setFocus();
}
void FormHiddenLayersNew::slotSpinBoxCountHiddenLayersValueChanged(int value){
    while(this->_threadWidgetRowOperation->isRunning())
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    int diff=std::abs(value-(int)this->_countHiddenLayer);

    this->_threadOperationStarted();
    if(value>(int)this->_countHiddenLayer)
        this->_threadWidgetRowOperation->setOperationType(ThreadWidgetRowOperation::OperationType::AddRow,diff);
    else
        this->_threadWidgetRowOperation->setOperationType(ThreadWidgetRowOperation::OperationType::RemoveRow,diff);
    this->_threadWidgetRowOperation->start();

    this->_countHiddenLayer=value;
}
void FormHiddenLayersNew::slotPushButtonSubmitClicked(){

    size_t countsCell[this->_countHiddenLayer];
    int sumFunctions[this->_countHiddenLayer];
    int actFunctions[this->_countHiddenLayer];

    for(size_t i=0;i<this->_countHiddenLayer;i++){
        countsCell[i]=this->_spinBoxCountCell->at(i)->value();
        sumFunctions[i]=this->_comboBoxSumFunction->at(i)->currentIndex();
        actFunctions[i]=this->_comboBoxActFunction->at(i)->currentIndex();
    }
    emit signalHiddenLayersNewParameters(this->_countHiddenLayer,countsCell,sumFunctions,actFunctions);

    this->close();
}
