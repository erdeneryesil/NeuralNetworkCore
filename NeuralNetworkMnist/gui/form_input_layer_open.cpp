#include"form_input_layer_open.h"
#include"gui/defines_gui.h"

FormInputLayerOpen::FormInputLayerOpen(const InputLayerPattern*const inputLayerPattern){
    this->_countInput=inputLayerPattern->getCountOriginal();
    int inputTypes[this->_countInput];
    int minimums[this->_countInput];
    int maximums[this->_countInput];
    for(int i=0;i<this->_countInput;i++){
        inputTypes[i]=(int)inputLayerPattern->getType(i);
        minimums[i]=inputLayerPattern->getLimit(i)->getOriginalMin();
        maximums[i]=inputLayerPattern->getLimit(i)->getOriginalMax();
    }

    this->_mainLayout=new QVBoxLayout();

    this->_scrollArea=new QScrollArea();
    this->_layoutRowsScrollArea=new QVector<QHBoxLayout*>();
    this->_layoutScrollArea=new QVBoxLayout();
    this->_widgetScrollArea=new QWidget();

    this->_layoutDataType=new QVector<QHBoxLayout*>();
    this->_widgetDataType=new QVector<QWidget*>();
    this->_labelDataType=new QVector<QLabel*>();
    this->_layoutMinimum=new QVector<QHBoxLayout*>();
    this->_widgetMinimum=new QVector<QWidget*>();
    this->_labelMinimum=new QVector<QLabel*>();
    this->_layoutMaximum=new QVector<QHBoxLayout*>();
    this->_widgetMaximum=new QVector<QWidget*>();
    this->_labelMaximum=new QVector<QLabel*>();

    this->_pushButtonSubmit=new QPushButton();

    this->_scrollArea->setFixedHeight(SCROLL_AREA_HEIGHT);
    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_createItemsRows(inputTypes,minimums,maximums);
    this->_widgetScrollArea->setLayout(this->_layoutScrollArea);
    this->_scrollArea->setWidget(this->_widgetScrollArea);
    this->_scrollArea->setFixedWidth(this->_widgetScrollArea->width()+this->_scrollArea->verticalScrollBar()->sizeHint().width());
    this->_scrollArea->setFixedHeight(SCROLL_AREA_HEIGHT);

    this->_mainLayout->addWidget(this->_scrollArea);

    this->_pushButtonSubmit->setText("OK");
    this->_mainLayout->addWidget(this->_pushButtonSubmit);

    this->setWindowTitle("Input Layer");

    this->setLayout(this->_mainLayout);

    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    connect(this->_pushButtonSubmit,SIGNAL(clicked()),this,SLOT(slotPushButtonSubmitClicked()));
}
FormInputLayerOpen::~FormInputLayerOpen(){
    delete this->_pushButtonSubmit;

    for(int i=0;i<this->_countInput;i++){

        delete this->_labelDataType->back();
        this->_labelDataType->pop_back();
        delete this->_layoutDataType->back();
        this->_layoutDataType->pop_back();
        delete this->_widgetDataType->back();
        this->_widgetDataType->pop_back();

        delete this->_labelMinimum->back();
        this->_labelMinimum->pop_back();
        delete this->_layoutMinimum->back();
        this->_layoutMinimum->pop_back();
        delete this->_widgetMinimum->back();
        this->_widgetMinimum->pop_back();

        delete this->_labelMaximum->back();
        this->_labelMaximum->pop_back();
        delete this->_layoutMaximum->back();
        this->_layoutMaximum->pop_back();
        delete this->_widgetMaximum->back();
        this->_widgetMaximum->pop_back();

        delete this->_layoutRowsScrollArea->back();
        this->_layoutRowsScrollArea->pop_back();
    }
    delete this->_labelDataType;
    delete this->_layoutDataType;
    delete this->_widgetDataType;
    delete this->_labelMinimum;
    delete this->_layoutMinimum;
    delete this->_widgetMinimum;
    delete this->_labelMaximum;
    delete this->_layoutMaximum;
    delete this->_widgetMaximum;
    delete this->_layoutRowsScrollArea;

     delete this->_layoutScrollArea;
    delete this->_widgetScrollArea;
    delete this->_scrollArea;

   delete this->_mainLayout;
 }

void FormInputLayerOpen::_createItemsRows(const int*const dataTypes,const int*const minimums,const int*const maximums){
    int labelDataTypeMaxWidth=0;
    int labelMinimumMaxWidth=0;
    int labelMaximumMaxWidth=0;

    for(int i=0;i<this->_countInput;i++){
        this->_layoutRowsScrollArea->push_back(new QHBoxLayout());

        this->_widgetDataType->push_back(new QWidget());
        this->_layoutDataType->push_back(new QHBoxLayout());
        this->_labelDataType->push_back(new QLabel());
        this->_labelDataType->back()->setText("Input"+QString::number(i)+" : "+DATA_TYPES[dataTypes[i]]);
        if(this->_labelDataType->back()->sizeHint().width()>labelDataTypeMaxWidth)
            labelDataTypeMaxWidth=this->_labelDataType->back()->sizeHint().width();
        this->_layoutDataType->back()->addWidget(this->_labelDataType->back());
        this->_widgetDataType->back()->setLayout(this->_layoutDataType->back());
        this->_widgetDataType->back()->setStyleSheet(WIDGET_STYLESHEET_LIGHT);
        this->_layoutRowsScrollArea->back()->addWidget(this->_widgetDataType->back());

        this->_widgetMinimum->push_back(new QWidget());
        this->_layoutMinimum->push_back(new QHBoxLayout());
        this->_labelMinimum->push_back(new QLabel());
        this->_labelMinimum->back()->setText("Minimum : "+QString::number(minimums[i]));
        if(this->_labelMinimum->back()->sizeHint().width()>labelMinimumMaxWidth)
            labelMinimumMaxWidth=this->_labelMinimum->back()->sizeHint().width();
        this->_layoutMinimum->back()->addWidget(this->_labelMinimum->back());
        this->_widgetMinimum->back()->setLayout(this->_layoutMinimum->back());
        this->_widgetMinimum->back()->setStyleSheet(WIDGET_STYLESHEET_DARK);
        this->_layoutRowsScrollArea->back()->addWidget(this->_widgetMinimum->back());

        this->_widgetMaximum->push_back(new QWidget());
        this->_layoutMaximum->push_back(new QHBoxLayout());
        this->_labelMaximum->push_back(new QLabel());
        this->_labelMaximum->back()->setText("Maximum : "+QString::number(maximums[i]));
        if(this->_labelMaximum->back()->sizeHint().width()>labelMaximumMaxWidth)
            labelMaximumMaxWidth=this->_labelMaximum->back()->sizeHint().width();
        this->_layoutMaximum->back()->addWidget(this->_labelMaximum->back());
        this->_widgetMaximum->back()->setLayout(this->_layoutMaximum->back());
        this->_widgetMaximum->back()->setStyleSheet(WIDGET_STYLESHEET_LIGHT);
        this->_layoutRowsScrollArea->back()->addWidget(this->_widgetMaximum->back());

        this->_layoutScrollArea->addLayout(this->_layoutRowsScrollArea->back());

    }

    for(int i=0;i<this->_countInput;i++){
        this->_labelDataType->at(i)->setFixedWidth(labelDataTypeMaxWidth) ;
        this->_labelMinimum->at(i)->setFixedWidth(labelMinimumMaxWidth);
        this->_labelMaximum->at(i)->setFixedWidth(labelMaximumMaxWidth);
    }
}
void FormInputLayerOpen::slotPushButtonSubmitClicked(){
    emit signalInputLayerOpenParameters();
    this->close();
}
