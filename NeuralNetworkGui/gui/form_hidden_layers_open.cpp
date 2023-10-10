#include"form_hidden_layers_open.h"
#include"gui/defines_gui.h"

FormHiddenLayersOpen::FormHiddenLayersOpen(const HiddenLayerPattern*const hiddenLayerPattern){

    this->_countHiddenLayer=hiddenLayerPattern->getCountLayer();
    int countsCell[this->_countHiddenLayer];
    int sumFunctions[this->_countHiddenLayer];
    int actFunctions[this->_countHiddenLayer];

    for(size_t i=0;i<this->_countHiddenLayer;i++){
        countsCell[i]=hiddenLayerPattern->getCountCell(i);
        sumFunctions[i]=(int)hiddenLayerPattern->getSumFunc(i)->getType();
        actFunctions[i]=(int)hiddenLayerPattern->getActFunc(i)->getType();
    }

    this->_mainLayout=new QVBoxLayout();

    this->_scrollArea=new QScrollArea();
    this->_layoutRowsScrollArea=new QVector<QHBoxLayout*>();
    this->_layoutScrollArea=new QVBoxLayout();
    this->_widgetScrollArea=new QWidget();

    this->_layoutCountCell=new QVector<QHBoxLayout*>();
    this->_widgetCountCell=new QVector<QWidget*>();
    this->_labelCountCell=new QVector<QLabel*>();
    this->_layoutSumFunction=new QVector<QHBoxLayout*>();
    this->_widgetSumFunction=new QVector<QWidget*>();
    this->_labelSumFunction=new QVector<QLabel*>();
    this->_comboBoxSumFunction=new QVector<QComboBox*>();
    this->_layoutActFunction=new QVector<QHBoxLayout*>();
    this->_widgetActFunction=new QVector<QWidget*>();
    this->_labelActFunction=new QVector<QLabel*>();
    this->_comboBoxActFunction=new QVector<QComboBox*>();

    this->_pushButtonSubmit=new QPushButton();

    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_createItemsRows(countsCell,sumFunctions,actFunctions);
    this->_widgetScrollArea->setLayout(this->_layoutScrollArea);
    this->_scrollArea->setWidget(this->_widgetScrollArea);
    this->_scrollArea->setFixedWidth(this->_widgetScrollArea->width()+this->_scrollArea->verticalScrollBar()->sizeHint().width());
    this->_scrollArea->setFixedHeight(SCROLL_AREA_HEIGHT);

    this->_mainLayout->addWidget(this->_scrollArea);

    this->_pushButtonSubmit->setText("SAVE");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->setWindowTitle("Hidden Layers");

    this->setLayout(this->_mainLayout);

    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
}

FormHiddenLayersOpen::~FormHiddenLayersOpen(){
    delete this->_pushButtonSubmit;
    for(size_t i=0;i<this->_countHiddenLayer;i++){
        delete this->_labelCountCell->back();
        this->_labelCountCell->pop_back();
        delete this->_layoutCountCell->back();
        this->_layoutCountCell->pop_back();
        delete this->_widgetCountCell->back();
        this->_widgetCountCell->pop_back();

        delete this->_labelSumFunction->back();
        this->_labelSumFunction->pop_back();
        delete this->_comboBoxSumFunction->back();
        this->_comboBoxSumFunction->pop_back();
        delete this->_layoutSumFunction->back();
        this->_layoutSumFunction->pop_back();
        delete  this->_widgetSumFunction->back();
        this->_widgetSumFunction->pop_back();

        delete  this->_labelActFunction->back();
        this->_labelActFunction->pop_back();
        delete this->_comboBoxActFunction->back();
        this->_comboBoxActFunction->pop_back();
        delete  this->_layoutActFunction->back();
        this->_layoutActFunction->pop_back();
        delete this->_widgetActFunction->back();
        this->_widgetActFunction->pop_back();

        delete  this->_layoutRowsScrollArea->back();
        this->_layoutRowsScrollArea->pop_back();
    }
    delete this->_labelCountCell;
    delete this->_layoutCountCell;
    delete this->_widgetCountCell;
    delete this->_labelSumFunction;
    delete this->_comboBoxSumFunction;
    delete this->_layoutSumFunction;
    delete this->_widgetSumFunction;
    delete this->_labelActFunction;
    delete this->_comboBoxActFunction;
    delete this->_layoutActFunction;
    delete this->_widgetActFunction;
    delete this->_layoutRowsScrollArea;

    delete this->_layoutScrollArea;
    delete this->_widgetScrollArea;
    delete this->_scrollArea;

    delete this->_mainLayout;
}

void FormHiddenLayersOpen::_createItemsRows(const int*const countsCell,const int*const sumFunctions, const int*const actFunctions){
    for(size_t i=0;i<this->_countHiddenLayer;i++){
        this->_layoutRowsScrollArea->push_back(new QHBoxLayout());

        this->_layoutCountCell->push_back(new QHBoxLayout());
        this->_widgetCountCell->push_back(new QWidget());
        this->_labelCountCell->push_back(new QLabel());
        this->_labelCountCell->back()->setText("Number of cells : "+QString::number(countsCell[i]));
        this->_layoutCountCell->back()->addWidget(this->_labelCountCell->back());
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
        this->_comboBoxSumFunction->back()->setCurrentIndex(sumFunctions[i]);
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
        this->_comboBoxActFunction->back()->setCurrentIndex(actFunctions[i]);
        this->_layoutActFunction->back()->addWidget(this->_labelActFunction->back());
        this->_layoutActFunction->back()->addWidget(this->_comboBoxActFunction->back());
        this->_widgetActFunction->back()->setLayout(this->_layoutActFunction->back());
        this->_widgetActFunction->back()->setStyleSheet(WIDGET_STYLESHEET_LIGHT);
        this->_layoutRowsScrollArea->back()->addWidget(this->_widgetActFunction->back());

        this->_layoutScrollArea->addLayout(this->_layoutRowsScrollArea->back());
    }
}

void FormHiddenLayersOpen::slotPushButtonSubmitClicked(){
    int sumFunctions[this->_countHiddenLayer];
    int actFunctions[this->_countHiddenLayer];

    for(size_t i=0;i<this->_countHiddenLayer;i++){
        sumFunctions[i]=this->_comboBoxSumFunction->at(i)->currentIndex();
        actFunctions[i]=this->_comboBoxActFunction->at(i)->currentIndex();
    }
    emit signalHiddenLayersOpenParameters(this->_countHiddenLayer,sumFunctions,actFunctions);

    this->close();
}
