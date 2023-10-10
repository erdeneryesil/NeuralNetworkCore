#include"form_output_layer_open.h"
#include"gui/defines_gui.h"

FormOutputLayerOpen::FormOutputLayerOpen(const OutputLayerPattern*const outputLayerPattern){

    this->_countOutput=outputLayerPattern->getCountOriginal();
    int sumFunction=(int)outputLayerPattern->getSumFunc()->getType();
    int actFunction=(int)outputLayerPattern->getActFunc()->getType();
    int dataTypes[this->_countOutput];
    int minimums[this->_countOutput];
    int maximums[this->_countOutput];
    double tolerances[this->_countOutput];
    for(size_t i=0;i<this->_countOutput;i++){
        dataTypes[i]=(int)outputLayerPattern->getType(i);
        minimums[i]=outputLayerPattern->getLimit(i)->getOriginalMin();
        maximums[i]=outputLayerPattern->getLimit(i)->getOriginalMax();
        tolerances[i]=outputLayerPattern->getTolerance(i);
    }

    this->_mainLayout=new QVBoxLayout();
    this->_layoutHead=new QHBoxLayout();

    this->_labelCountOutput=new QLabel();
    this->_labelSumFunction=new QLabel();
    this->_comboBoxSumFunction=new QComboBox();
    this->_labelActFunction=new QLabel();
    this->_comboBoxActFunction=new QComboBox();

    this->_scrollArea=new QScrollArea();
    this->_layoutRowsScrollArea=new QVector<QHBoxLayout*>();
    this->_layoutScrollArea=new QVBoxLayout();
    this->_widgetScrollArea=new QWidget();
    this->_layoutBunch=new QHBoxLayout();

    this->_layoutDataType=new QVector<QHBoxLayout*>();
    this->_widgetDataType=new QVector<QWidget*>();
    this->_labelDataType=new QVector<QLabel*>();
    this->_layoutMinimum=new QVector<QHBoxLayout*>();
    this->_widgetMinimum=new QVector<QWidget*>();
    this->_labelMinimum=new QVector<QLabel*>();
    this->_layoutMaximum=new QVector<QHBoxLayout*>();
    this->_widgetMaximum=new QVector<QWidget*>();
    this->_labelMaximum=new QVector<QLabel*>();
    this->_layoutTolerance=new QVector<QHBoxLayout*>();
    this->_widgetTolerance=new QVector<QWidget*>();
    this->_labelTolerance=new QVector<QLabel*>();
    this->_spinBoxTolerance=new QVector<QDoubleSpinBox*>();

    this->_pushButtonSubmit=new QPushButton();

    this->_labelCountOutput->setText("Number of outputs : "+QString::number(this->_countOutput));
    this->_labelSumFunction->setText("Summation function");
    for(int i=0;i<COUNT_SUM_FUNCTIONS;i++)
        this->_comboBoxSumFunction->addItem(SUM_FUNCTIONS[i]);
    this->_comboBoxSumFunction->setCurrentIndex(sumFunction);

    this->_labelActFunction->setText("Activation function");
    for(int i=0;i<COUNT_ACT_FUNCTIONS;i++)
        this->_comboBoxActFunction->addItem(ACT_FUNCTIONS[i]);
    this->_comboBoxActFunction->setCurrentIndex(actFunction);

    this->_layoutHead->addWidget(this->_labelCountOutput);
    this->_layoutHead->addWidget(this->_labelSumFunction);
    this->_layoutHead->addWidget(this->_comboBoxSumFunction);
    this->_layoutHead->addWidget(this->_labelActFunction);
    this->_layoutHead->addWidget(this->_comboBoxActFunction);
    this->_mainLayout->addLayout(this->_layoutHead);

    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_createItemsRows(dataTypes,minimums,maximums,tolerances);
    this->_widgetScrollArea->setLayout(this->_layoutScrollArea);
    this->_scrollArea->setWidget(this->_widgetScrollArea);
    this->_scrollArea->setFixedWidth(this->_widgetScrollArea->width()+this->_scrollArea->verticalScrollBar()->sizeHint().width());
    this->_scrollArea->setFixedHeight(SCROLL_AREA_HEIGHT);

    this->_layoutBunch->addWidget(this->_scrollArea);

    this->_mainLayout->addLayout(this->_layoutBunch);

    this->_pushButtonSubmit->setText("SAVE");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->setWindowTitle("Output Layer");

    this->setLayout(this->_mainLayout);

    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
}
FormOutputLayerOpen::~FormOutputLayerOpen(){
    delete this->_pushButtonSubmit;

    for(size_t i=0;i<this->_countOutput;i++){
        delete this->_spinBoxTolerance->back();
        this->_spinBoxTolerance->pop_back();
        delete this->_labelTolerance->back();
        this->_labelTolerance->pop_back();
        delete this->_layoutTolerance->back();
        this->_layoutTolerance->pop_back();
        delete this->_widgetTolerance->back();
        this->_widgetTolerance->pop_back();

        delete this->_labelMaximum->back();
        this->_labelMaximum->pop_back();
        delete  this->_layoutMaximum->back();
        this->_layoutMaximum->pop_back();
        delete this->_widgetMaximum->back();
        this->_widgetMaximum->pop_back();

        delete this->_labelMinimum->back();
        this->_labelMinimum->pop_back();
        delete this->_layoutMinimum->back();
        this->_layoutMinimum->pop_back();
        delete this->_widgetMinimum->back();
        this->_widgetMinimum->pop_back();

        delete this->_labelDataType->back();
        this->_labelDataType->pop_back();
        delete     this->_layoutDataType->back();
        this->_layoutDataType->pop_back();
        delete this->_widgetDataType->back();
        this->_widgetDataType->pop_back();

        delete this->_layoutRowsScrollArea->back();
        this->_layoutRowsScrollArea->pop_back();
    }
    delete this->_spinBoxTolerance;
    delete this->_labelTolerance;
    delete this->_layoutTolerance;
    delete this->_widgetTolerance;
    delete this->_labelMaximum;
    delete this->_layoutMaximum;
    delete this->_widgetMaximum;
    delete this->_labelMinimum;
    delete this->_layoutMinimum;
    delete this->_widgetMinimum;
    delete this->_labelDataType;
    delete this->_layoutDataType;
    delete this->_widgetDataType;
    delete this->_layoutRowsScrollArea;

    delete this->_layoutBunch;
    delete this->_layoutScrollArea;
    delete this->_widgetScrollArea;
    delete this->_scrollArea;

    delete this->_layoutHead;
    delete this->_comboBoxActFunction;
    delete this->_labelActFunction;
    delete this->_comboBoxSumFunction;
    delete this->_labelSumFunction;
    delete this->_labelCountOutput;

    delete this->_mainLayout;
}
void FormOutputLayerOpen::_createItemsRows(const int*const dataTypes,const int*const minimums,const int*const maximums,const double*const tolerances){
    int labelDataTypeMaxWidth=0;
    int labelMinimumMaxWidth=0;
    int labelMaximumMaxWidth=0;

    for(size_t i=0;i<this->_countOutput;i++){
        this->_layoutRowsScrollArea->push_back(new QHBoxLayout());

        this->_layoutDataType->push_back(new QHBoxLayout());
        this->_widgetDataType->push_back(new QWidget());
        this->_labelDataType->push_back(new QLabel());
        this->_labelDataType->back()->setText("Output"+QString::number(i)+" : "+DATA_TYPES[dataTypes[i]]);
        if(this->_labelDataType->back()->sizeHint().width()>labelDataTypeMaxWidth)
            labelDataTypeMaxWidth=this->_labelDataType->back()->sizeHint().width();
        this->_layoutDataType->back()->addWidget(this->_labelDataType->back());
        this->_widgetDataType->back()->setStyleSheet(WIDGET_STYLESHEET_LIGHT);
        this->_widgetDataType->back()->setLayout(this->_layoutDataType->back());
        this->_layoutRowsScrollArea->back()->addWidget(this->_widgetDataType->back());

        this->_layoutMinimum->push_back(new QHBoxLayout());
        this->_widgetMinimum->push_back(new QWidget());
        this->_labelMinimum->push_back(new QLabel());
        this->_labelMinimum->back()->setText("Minimum : "+QString::number(minimums[i]));
        if(this->_labelMinimum->back()->sizeHint().width()>labelMinimumMaxWidth)
            labelMinimumMaxWidth=this->_labelMinimum->back()->sizeHint().width();
        this->_layoutMinimum->back()->addWidget(this->_labelMinimum->back());
        this->_widgetMinimum->back()->setStyleSheet(WIDGET_STYLESHEET_DARK);
        this->_widgetMinimum->back()->setLayout(this->_layoutMinimum->back());
        this->_layoutRowsScrollArea->back()->addWidget(this->_widgetMinimum->back());

        this->_layoutMaximum->push_back(new QHBoxLayout());
        this->_widgetMaximum->push_back(new QWidget());
        this->_labelMaximum->push_back(new QLabel());
        this->_labelMaximum->back()->setText("Maximum : "+QString::number(maximums[i]));
        if(this->_labelMaximum->back()->sizeHint().width()>labelMaximumMaxWidth)
            labelMaximumMaxWidth=this->_labelMaximum->back()->sizeHint().width();
        this->_layoutMaximum->back()->addWidget(this->_labelMaximum->back());
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
        this->_spinBoxTolerance->back()->setValue(tolerances[i]);
        this->_layoutTolerance->back()->addWidget(this->_labelTolerance->back());
        this->_layoutTolerance->back()->addWidget(this->_spinBoxTolerance->back());
        this->_widgetTolerance->back()->setStyleSheet(WIDGET_STYLESHEET_LIGHT);
        this->_widgetTolerance->back()->setLayout(this->_layoutTolerance->back());
        this->_layoutRowsScrollArea->back()->addWidget(this->_widgetTolerance->back());

        this->_layoutScrollArea->addLayout(this->_layoutRowsScrollArea->back());
    }
    for(size_t i=0;i<this->_countOutput;i++){
        this->_labelDataType->at(i)->setFixedWidth(labelDataTypeMaxWidth) ;
        this->_labelMinimum->at(i)->setFixedWidth(labelMinimumMaxWidth);
        this->_labelMaximum->at(i)->setFixedWidth(labelMaximumMaxWidth);
    }
}
void FormOutputLayerOpen::slotPushButtonSubmitClicked(){
    int sumFunction=this->_comboBoxSumFunction->currentIndex();
    int actFunction=this->_comboBoxActFunction->currentIndex();
    double tolerances[this->_countOutput];

    for(size_t i=0;i<this->_countOutput;i++){
        tolerances[i]=this->_spinBoxTolerance->at(i)->value();
    }
    emit signalOutputLayerOpenParameters(this->_countOutput,sumFunction,actFunction,tolerances);
    this->close();
}
