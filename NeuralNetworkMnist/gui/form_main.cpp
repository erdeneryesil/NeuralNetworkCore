#include"form_main.h"
#include"gui/defines_gui.h"
#include<thread>

NeuralNetwork* FormMain::neuralNetwork=nullptr;
FormMain* SignalEpochHandler::owner=nullptr;

FormMain::FormMain(){
    this->_mainLayout=new QHBoxLayout();

    this->_scrollArea=new QScrollArea();
    this->_widgetScrollArea=new QWidget();
    this->_layoutScrollArea=new QGridLayout();

    this->_layoutNNAsset=new QVBoxLayout();
    this->_pushButtonNew=new QPushButton();
    this->_pushButtonOpen=new QPushButton();
    this->_pushButtonEdit=new QPushButton();
    this->_treeWidgetNN=new QTreeWidget();

    this->_layoutNNAction=new QVBoxLayout();
    this->_pushButtonTrain=new QPushButton();
    this->_checkBoxGraph=new QCheckBox();
    this->_pushButtonTest=new QPushButton();
    this->_pushButtonRun=new QPushButton();
    this->_labelInformation=new QLabel();
    this->_textEditInformation=new QTextEdit();

    this->_graphicViewNN=new QGraphicsView();
    this->_graphicSceneNN=new QGraphicsScene();

    this->_threadDiagramNN=new ThreadDiagramNN(this);

    this->_pushButtonNew->setText("New");
    this->_pushButtonNew->setFixedSize(FORM_MAIN_CONTROL_WIDTH,FORM_MAIN_CONTROL_HEIGHT);
    this->_pushButtonOpen->setText("Open");
    this->_pushButtonOpen->setFixedSize(FORM_MAIN_CONTROL_WIDTH,FORM_MAIN_CONTROL_HEIGHT);
    this->_pushButtonEdit->setText("Edit");
    this->_pushButtonEdit->setFixedSize(FORM_MAIN_CONTROL_WIDTH,FORM_MAIN_CONTROL_HEIGHT);
    this->_treeWidgetNN->setFixedSize(FORM_MAIN_CONTROL_WIDTH,FORM_MAIN_LIST_HEIGHT);
    this->_treeWidgetNN->setColumnCount(2);
    this->_treeWidgetNN->setHeaderHidden(true);
    this->_layoutNNAsset->addWidget(this->_pushButtonNew);
    this->_layoutNNAsset->addWidget(this->_pushButtonOpen);
    this->_layoutNNAsset->addWidget(this->_pushButtonEdit);
    this->_layoutNNAsset->addWidget(this->_treeWidgetNN);

    this->_pushButtonTrain->setFixedSize(FORM_MAIN_CONTROL_WIDTH,FORM_MAIN_CONTROL_HEIGHT);
    this->_checkBoxGraph->setText("Show Graph");
    this->_checkBoxGraph->setFixedSize(FORM_MAIN_CONTROL_WIDTH,FORM_MAIN_CONTROL_HEIGHT);
    this->_pushButtonTest->setText("Test");
    this->_pushButtonTest->setFixedSize(FORM_MAIN_CONTROL_WIDTH,FORM_MAIN_CONTROL_HEIGHT);
    this->_pushButtonRun->setText("Run");
    this->_pushButtonRun->setFixedSize(FORM_MAIN_CONTROL_WIDTH,FORM_MAIN_CONTROL_HEIGHT);
    this->_labelInformation->setFixedSize(FORM_MAIN_CONTROL_WIDTH,FORM_MAIN_LABEL_HEIGHT);
    this->_textEditInformation->setReadOnly(true);
    this->_textEditInformation->setFixedWidth(FORM_MAIN_CONTROL_WIDTH);
    this->_textEditInformation->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    this->_textEditInformation->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
    this->_layoutNNAction->addWidget(this->_pushButtonTrain);
    this->_layoutNNAction->addWidget(this->_checkBoxGraph);
    this->_layoutNNAction->addWidget(this->_pushButtonTest);
    this->_layoutNNAction->addWidget(this->_pushButtonRun);
    this->_layoutNNAction->addWidget(this->_labelInformation);

    this->_layoutNNAction->addWidget(this->_textEditInformation);

    this->_layoutScrollArea->addLayout(this->_layoutNNAsset,0,0,1,1);
    this->_layoutScrollArea->addLayout(this->_layoutNNAction,1,0,1,1);
    this->_layoutScrollArea->addWidget(this->_graphicViewNN,0,1,2,1);

    this->_widgetScrollArea->setLayout(this->_layoutScrollArea);

    this->_graphicViewNN->setMinimumSize(FORM_MAIN_GRAPHICS_VIEW_WIDTH,this->_layoutNNAsset->sizeHint().height()+this->_layoutNNAction->sizeHint().height()+this->_layoutScrollArea->verticalSpacing());
    this->_graphicViewNN->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setWidgetResizable(true);

    this->_scrollArea->setWidget(this->_widgetScrollArea);

    this->_mainLayout->addWidget(this->_scrollArea);


    this->_mainLayout->setSpacing(0);
    this->_mainLayout->setMargin(0);

    this->setLayout(this->_mainLayout);
    int formWidth=this->_widgetScrollArea->sizeHint().width()+this->_scrollArea->verticalScrollBar()->sizeHint().width();
    int formHeight=this->_widgetScrollArea->sizeHint().height()+this->_scrollArea->horizontalScrollBar()->sizeHint().height();
    this->resize(formWidth,formHeight);

    this->_viewNoNeuralNetwork();
    this->_setTextsNoNeuralNetwork();

    this->_graphicSceneNN->setSceneRect(0,0,_graphicViewNN->width()-2*_graphicViewNN->frameWidth(),_graphicViewNN->height()-2*_graphicViewNN->frameWidth());
    this->_graphicViewNN->setScene(_graphicSceneNN);

    this->_penLine.setColor(COLOR_LINE);
    this->_penEllipse.setColor(COLOR_ELLIPSE_BORDER);
    this->_brushInputCell.setColor(COLOR_INPUT_CELLS);
    this->_brushInputCell.setStyle(Qt::SolidPattern);
    this->_brushHiddenCell.setColor(COLOR_HIDDEN_CELLS);
    this->_brushHiddenCell.setStyle(Qt::SolidPattern);
    this->_brushOutputCell.setColor(COLOR_OUTPUT_CELLS);
    this->_brushOutputCell.setStyle(Qt::SolidPattern);
    this->_brushBiasCell.setColor(COLOR_BIAS_CELLS);
    this->_brushBiasCell.setStyle(Qt::SolidPattern);
    this->_rCell=R_CELL;
    this->_rDot=R_DOT;
    this->_paddingGraphicScene=R_CELL;

    SignalEpochHandler::owner=this;
    this->_errorValues=new QVector<qreal>();
    this->_updatedWeights=new QVector<qreal>();
    this->_countEW=0;
    this->_countSample=0;

    connect(this,SIGNAL(signalTextEditInformationSetText(QString)),this->_textEditInformation,SLOT(setText(QString)));
    connect(this->_pushButtonNew,SIGNAL(clicked()),this,SLOT(slotPushButtonNewClicked()));
    connect(this->_pushButtonOpen,SIGNAL(clicked()),this,SLOT(slotPushButtonOpenClicked()));
    connect(this->_pushButtonEdit,SIGNAL(clicked()),this,SLOT(slotPushButtonEditClicked()));
    connect(this->_pushButtonTrain,SIGNAL(clicked()),this,SLOT(slotPushButtonTrainClicked()));
    connect(this->_checkBoxGraph,SIGNAL(clicked(bool)),this,SLOT(slotCheckBoxGraphClicked(bool)));
    connect(this->_pushButtonTest,SIGNAL(clicked()),this,SLOT(slotPushButtonTestClicked()));
    connect(this->_pushButtonRun,SIGNAL(clicked()),this,SLOT(slotPushButtonRunClicked()));
    connect(this->_treeWidgetNN, SIGNAL(expanded(QModelIndex)), this, SLOT(slotTreeWidget(QModelIndex)));
    connect(this->_treeWidgetNN, SIGNAL(collapsed(QModelIndex)), this, SLOT(slotTreeWidget(QModelIndex)));
    connect(this->_threadDiagramNN,SIGNAL(signalPrepareGraphicScene()),this,SLOT(slotPrepareGraphicSceneForNNDiagram()));
    connect(this->_threadDiagramNN,SIGNAL(signalAddLine(qreal,qreal,qreal,qreal,QPen)),this,SLOT(slotAddLineForNNDiagram(qreal,qreal,qreal,qreal,QPen)));
    connect(this->_threadDiagramNN,SIGNAL(signalAddEllipse(qreal,qreal,qreal,qreal,QPen,QBrush)),this,SLOT(slotAddEllipseForNNDiagram(qreal,qreal,qreal,qreal,QPen,QBrush)));

    //**********

    this->_formInputLayerNew=nullptr;
    this->_formHiddenLayersNew=nullptr;
    this->_formOutputLayerNew=nullptr;
    this->_formOtherSettingsNew=nullptr;
    this->_formInputLayerOpen=nullptr;
    this->_formHiddenLayersOpen=nullptr;
    this->_formOutputLayerOpen=nullptr;
    this->_formOtherSettingsOpen=nullptr;
    this->_formNNFile=nullptr;
    this->_formSamplesFile=nullptr;
    this->_formRun=nullptr;
    this->_graphEW=nullptr;

    //**********

    this->_inputPattern=nullptr;
    this->_hiddenPattern=nullptr;
    this->_outputPattern=nullptr;

    //************
}
FormMain::~FormMain(){
    delete this->_threadDiagramNN;
    delete this->_graphicSceneNN;
    delete this->_graphicViewNN;

    delete this->_pushButtonTrain;
    delete this->_checkBoxGraph;
    delete this->_pushButtonTest;
    delete this->_pushButtonRun;
    delete this->_labelInformation;
    delete this->_textEditInformation;
    delete this->_layoutNNAction;

    delete this->_pushButtonNew;
    delete this->_pushButtonOpen;
    delete this->_pushButtonEdit;
    delete this->_treeWidgetNN;
    delete this->_layoutNNAsset;

    delete this->_layoutScrollArea;

    delete this->_widgetScrollArea;

    delete this->_scrollArea;

    delete this->_mainLayout;

    //************

    if(FormMain::neuralNetwork)
        delete FormMain::neuralNetwork;
    if(this->_inputPattern)
        delete this->_inputPattern;
    if(this->_hiddenPattern)
        delete this->_hiddenPattern;
    if(this->_outputPattern)
        delete this->_outputPattern;


    //************
    if(this->_formInputLayerNew)
        delete this->_formInputLayerNew;
    if(this->_formHiddenLayersNew)
        delete this->_formHiddenLayersNew;
    if(this->_formOutputLayerNew)
        delete this->_formOutputLayerNew;
    if(this->_formOtherSettingsNew)
        delete this->_formOtherSettingsNew;
    if(this->_formInputLayerOpen)
        delete this->_formInputLayerOpen;
    if(this->_formHiddenLayersOpen)
        delete this->_formHiddenLayersOpen;
    if(this->_formOutputLayerOpen)
        delete this->_formOutputLayerOpen;
    if(this->_formOtherSettingsOpen)
        delete this->_formOtherSettingsOpen;
    if(this->_formNNFile)
        delete this->_formNNFile;
    if(this->_formSamplesFile)
        delete this->_formSamplesFile;
    if(this->_formRun)
        delete this->_formRun;
    if(this->_graphEW)
        delete this->_graphEW;
    //***********

    this->_errorValues->clear();
    delete this->_errorValues;

    this->_updatedWeights->clear();
    delete this->_updatedWeights;

}


NeuralNetwork* FormMain::NeuralNetworkObject(){
    return FormMain::neuralNetwork;
}
void FormMain::resizeEvent(QResizeEvent*){
    this->_threadDiagramNN->start();
}
bool FormMain::isGraphEWShowing()const{
    if(this->_graphEW) return true;
    return false;
}
const QVector<qreal>* FormMain::getErrorValues()const{
    return this->_errorValues;
}
const QVector<qreal>* FormMain::getUpdatedWeights() const{
    return this->_updatedWeights;
}
size_t FormMain::getCountEW()const{
    return this->_countEW;
}
int FormMain::getCountSample()const{
    return this->_countSample;
}
const QGraphicsView* FormMain::getGraphicsView()const{
    return this->_graphicViewNN;
}
int FormMain::getPaddingGraphicScene()const{
    return this->_paddingGraphicScene;
}
size_t FormMain::getMaxCountCell()const{
    return this->_maxCountCell;
}
int FormMain::getRCell()const{
    return this->_rCell;
}
int FormMain::getRDot()const{
    return this->_rDot;
}
const QPen& FormMain::getPenLine()const{
    return this->_penLine;
}
const QPen& FormMain::getPenEllipse()const{
    return this->_penEllipse;
}
const QBrush& FormMain::getBrushInputCell()const{
    return this->_brushInputCell;
}
const QBrush& FormMain::getBrushHiddenCell()const{
    return this->_brushHiddenCell;
}
const QBrush& FormMain::getBrushOutputCell()const{
    return this->_brushOutputCell;
}
const QBrush& FormMain::getBrushBiasCell()const{
    return this->_brushBiasCell;
}

void FormMain::slotPushButtonNewClicked(){
    this->_formInputLayerNew=new FormInputLayerNew();
    this->_formInputLayerNew->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formInputLayerNew,SIGNAL(signalInputLayerNewParameters(size_t,int*const,int*const,int*const)),this,SLOT(slotInputLayerNewParameters(size_t,int*const,int*const,int*const)));
    connect(this->_formInputLayerNew,SIGNAL(destroyed()),this,SLOT(slotDestroyedInputLayerNew()));
    this->_formInputLayerNew->show();
}
void FormMain::slotPushButtonOpenClicked(){
    this->_formNNFile=new FormNNFile();
    this->_formNNFile->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formNNFile,SIGNAL(signalNNFileParameters(char,std::string)),this,SLOT(slotNNFileParameters(char,std::string)));
    connect(this->_formNNFile,SIGNAL(destroyed()),this,SLOT(slotDestroyedNNFile()));
    this->_formNNFile->show();
}
void FormMain::slotPushButtonEditClicked(){
    this->_formInputLayerOpen=new FormInputLayerOpen(FormMain::neuralNetwork->getInputLayerPattern());
    this->_formInputLayerOpen->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formInputLayerOpen,SIGNAL(signalInputLayerOpenParameters()),this,SLOT(slotInputLayerOpenParameters()));
    connect(this->_formInputLayerOpen,SIGNAL(destroyed()),this,SLOT(slotDestroyedInputLayerOpen()));
    this->_formInputLayerOpen->show();
}
void FormMain::slotPushButtonTrainClicked(){
    if(FormMain::NeuralNetworkObject()->getActionMode()==NeuralNetwork::ActionMode::Train){
        FormMain::NeuralNetworkObject()->setStopTraining(true);
        this->_errorValues->clear();
        this->_updatedWeights->clear();
        this->_countEW=0;
        this->_countSample=0;
    }else{
        emit signalTextEditInformationSetText("");
        this->_formSamplesFile=new FormSamplesFile(FormSamplesFile::FileType::TrainingSet);
        this->_formSamplesFile->setAttribute(Qt::WA_DeleteOnClose);
        connect(this->_formSamplesFile,SIGNAL(signalSamplesFileParameters(int,std::string)),this,SLOT(slotSamplesFileParameters(int,std::string)));
        connect(this->_formSamplesFile,SIGNAL(destroyed()),this,SLOT(slotDestroyedSamplesFile()));
        this->_formSamplesFile->show();
    }

}
void FormMain::slotCheckBoxGraphClicked(bool state){
    if(state){
        this->_graphEW=new GraphEW(this);
        this->_graphEW->setAttribute(Qt::WA_DeleteOnClose);
        connect(this->_graphEW,SIGNAL(destroyed()),this,SLOT(slotDestroyedGraphEW()));
        this->_graphEW->show();
    }
}
void FormMain::slotPushButtonTestClicked(){
    emit signalTextEditInformationSetText("");
    this->_formSamplesFile=new FormSamplesFile(FormSamplesFile::FileType::TestSet);
    this->_formSamplesFile->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formSamplesFile,SIGNAL(signalSamplesFileParameters(int,std::string)),this,SLOT(slotSamplesFileParameters(int,std::string)));
    connect(this->_formSamplesFile,SIGNAL(destroyed()),this,SLOT(slotDestroyedSamplesFile()));
    this->_formSamplesFile->show();
}
void FormMain::slotPushButtonRunClicked(){
    emit signalTextEditInformationSetText("");
    this->_formRun=new FormRun();
    this->_formRun->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formRun,SIGNAL(signalRunParameters(int*const)),this,SLOT(slotRunParameters(int*const)));
    connect(this->_formRun,SIGNAL(destroyed()),this,SLOT(slotDestroyedRun()));
    this->_formRun->show();
}
void FormMain::slotTreeWidget(QModelIndex){
    this->_treeWidgetNN->resizeColumnToContents(0);
    this->_treeWidgetNN->resizeColumnToContents(1);
}

//****

void FormMain::slotInputLayerNewParameters(size_t countInput, int * const types, int * const minimums, int * const maximums){
    Data::Limit** limits=new Data::Limit*[countInput];
    for(size_t i=0;i<countInput;i++){
        if((Data::Type)types[i]==Data::Type::Native)
            limits[i]=new Data::Limit((Data::Type)types[i],LayerType::Input);
        else
            limits[i]=new Data::Limit((Data::Type)types[i],LayerType::Input,minimums[i],maximums[i]);
    }

    this->_inputPattern=new InputLayerPattern(countInput,(Data::Type*)types,limits);

    for(size_t i=0;i<countInput;i++)
        delete limits[i];
    delete[]limits;


    this->_formHiddenLayersNew=new FormHiddenLayersNew();
    this->_formHiddenLayersNew->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formHiddenLayersNew,SIGNAL(signalHiddenLayersNewParameters(size_t,size_t*const,int*const,int*const)),this,SLOT(slotHiddenLayersNewParameters(size_t,size_t*const,int*const,int*const)));
    connect(this->_formHiddenLayersNew,SIGNAL(destroyed()),this,SLOT(slotDestroyedHiddenLayersNew()));
    this->_formHiddenLayersNew->show();
}
void FormMain::slotHiddenLayersNewParameters(size_t countLayer,size_t*const countsCell,int*const sumFunctions,int*const actFunctions){
    this->_hiddenPattern=new HiddenLayerPattern(countLayer,countsCell,(Cell::SummationFunction::Type*)sumFunctions,(Cell::ActivationFunction::Type*)actFunctions);

    this->_formOutputLayerNew=new FormOutputLayerNew();
    this->_formOutputLayerNew->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formOutputLayerNew,SIGNAL(signalOutputLayerNewParameters(size_t,int,int,int*const,int*const,int*const,double*const)),this,SLOT(slotOutputLayerNewParameters(size_t,int,int,int*const,int*const,int*const,double*const)));
    connect(this->_formOutputLayerNew,SIGNAL(destroyed()),this,SLOT(slotDestroyedOutputLayerNew()));
    this->_formOutputLayerNew->show();
}
void FormMain::slotOutputLayerNewParameters(size_t countOutput, int sumFunction, int actFunction, int * const types, int * const minimums, int * const maximums, double * const tolerances){
    Data::Limit** limits=new Data::Limit*[countOutput];
    double scaledMin=Cell::ActivationFunction::rangeMin((Cell::ActivationFunction::Type)actFunction);
    double scaledMax=Cell::ActivationFunction::rangeMax((Cell::ActivationFunction::Type)actFunction);

    for(size_t i=0;i<countOutput;i++){
        if((Data::Type)types[i]==Data::Type::Native)
            limits[i]=new Data::Limit((Data::Type)types[i],LayerType::Output,scaledMin,scaledMax);
        else
            limits[i]=new Data::Limit((Data::Type)types[i],LayerType::Output,minimums[i],maximums[i],scaledMin,scaledMax);
    }

    this->_outputPattern=new OutputLayerPattern(countOutput,(Data::Type*)types,limits,tolerances,(Cell::SummationFunction::Type)sumFunction,(Cell::ActivationFunction::Type)actFunction);

    for(size_t i=0;i<countOutput;i++)
        delete limits[i];
    delete[]limits;

    this->_formOtherSettingsNew=new FormOtherSettingsNew();
    this->_formOtherSettingsNew->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formOtherSettingsNew,SIGNAL(signalOtherSettingsNewParameters(double,double,double,double,std::string,char)),this,SLOT(slotOtherSettingsNewParameters(double,double,double,double,std::string,char)));
    connect(this->_formOtherSettingsNew,SIGNAL(destroyed()),this,SLOT(slotDestroyedOtherSettingsNew()));
    this->_formOtherSettingsNew->show();
}
void FormMain::slotOtherSettingsNewParameters(double lambda, double alfa, double randomWeightMin, double randomWeightMax, std::string parametersFileName, char separator){
    if(FormMain::neuralNetwork){
        delete FormMain::neuralNetwork;
        FormMain::neuralNetwork=nullptr;
    }

    this->_formOtherSettingsNew->setWindowOpacity(FORM_TRANSPARENT);
    this->_formOtherSettingsNew->setEnabled(false);
    this->setWindowOpacity(FORM_TRANSPARENT);
    this->setEnabled(false);

    std::thread t(&FormMain::_createNNWithParameters,this,lambda,alfa,parametersFileName,separator,randomWeightMin,randomWeightMax);
    t.join();

    this->_setMaxCountCellForDiagramNN();
    this->_threadDiagramNN->start();
    this->_fillTreeWidget();
    this->_viewAvailableNeuralNetwork();
    this->_setTextsAvailableNeuralNetwork();

    this->_formOtherSettingsNew->setWindowOpacity(FORM_OPAQUE);
    this->_formOtherSettingsNew->setEnabled(true);
    this->setEnabled(true);
    this->setWindowOpacity(FORM_OPAQUE);
}

void FormMain::slotInputLayerOpenParameters(){
    this->_formHiddenLayersOpen=new FormHiddenLayersOpen(FormMain::neuralNetwork->getHiddenLayerPattern());
    this->_formHiddenLayersOpen->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formHiddenLayersOpen,SIGNAL(signalHiddenLayersOpenParameters(size_t,int*const,int*const)),this,SLOT(slotHiddenLayersOpenParameters(size_t,int*const,int*const)));
    connect(this->_formHiddenLayersOpen,SIGNAL(destroyed()),this,SLOT(slotDestroyedHiddenLayersOpen()));
    this->_formHiddenLayersOpen->show();
}
void FormMain::slotHiddenLayersOpenParameters(size_t countLayer, int * const sumFunctions, int * const actFunctions){
    for(size_t i=0;i<countLayer;i++){
        FormMain::neuralNetwork->setSumFuncOfHiddenLayer(i,(Cell::SummationFunction::Type)sumFunctions[i]);
        FormMain::neuralNetwork->setActFuncOfHiddenLayer(i,(Cell::ActivationFunction::Type)actFunctions[i]);
    }

    this->_treeWidgetNN->clear();
    this->_fillTreeWidget();
    FormMain::neuralNetwork->saveNeuralNetwork();

    this->_formOutputLayerOpen=new FormOutputLayerOpen(FormMain::neuralNetwork->getOutputLayerPattern());
    this->_formOutputLayerOpen->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formOutputLayerOpen,SIGNAL(signalOutputLayerOpenParameters(size_t,int,int,double*const)),this,SLOT(slotOutputLayerOpenParameters(size_t,int,int,double*const)));
    connect(this->_formOutputLayerOpen,SIGNAL(destroyed()),this,SLOT(slotDestroyedOutputLayerOpen()));
    this->_formOutputLayerOpen->show();
}
void FormMain::slotOutputLayerOpenParameters(size_t countOutput, int sumFunction, int actFunction, double * const tolerances){
    FormMain::neuralNetwork->setSumFuncOfOutputLayer((Cell::SummationFunction::Type)sumFunction);
    FormMain::neuralNetwork->setActFuncOfOutputLayer((Cell::ActivationFunction::Type)actFunction);
    for(size_t i=0;i<countOutput;i++){
        FormMain::neuralNetwork->setTolerance(i,tolerances[i]);
    }

    this->_treeWidgetNN->clear();
    this->_fillTreeWidget();
    FormMain::neuralNetwork->saveNeuralNetwork();

    this->_formOtherSettingsOpen=new FormOtherSettingsOpen(FormMain::neuralNetwork->getLambda(),FormMain::neuralNetwork->getAlfa(),FormMain::neuralNetwork->getSeparator(),FormMain::neuralNetwork->getParametersFile());
    this->_formOtherSettingsOpen->setAttribute(Qt::WA_DeleteOnClose);
    connect(this->_formOtherSettingsOpen,SIGNAL(signalOtherSettingsOpenParameters(double,double)),this,SLOT(slotOtherSettingsOpenParameters(double,double)));
    connect(this->_formOtherSettingsOpen,SIGNAL(destroyed()),this,SLOT(slotDestroyedOtherSettingsOpen()));
    this->_formOtherSettingsOpen->show();

}
void FormMain::slotOtherSettingsOpenParameters(double lambda, double alfa){
    FormMain::neuralNetwork->setLambda(lambda);
    FormMain::neuralNetwork->setAlfa(alfa);

    this->_treeWidgetNN->clear();
    this->_fillTreeWidget();
    FormMain::neuralNetwork->saveNeuralNetwork();
}

void FormMain::slotNNFileParameters(char separator, std::string parametersFileName){
    if(FormMain::neuralNetwork){
        delete FormMain::neuralNetwork;
        FormMain::neuralNetwork=nullptr;
    }

    this->_formNNFile->setWindowOpacity(FORM_TRANSPARENT);
    this->_formNNFile->setEnabled(false);
    this->setWindowOpacity(FORM_TRANSPARENT);
    this->setEnabled(false);
    std::thread t(&FormMain::_createNNFromFile,this,parametersFileName,separator);
    t.join();

    if(this->_errorCreateNNFromFile){
        QMessageBox::warning(this,"Error",this->_exceptionWhatCreateNNFromFile,QMessageBox::Ok);
        delete FormMain::neuralNetwork;
        FormMain::neuralNetwork=nullptr;
        this->_treeWidgetNN->clear();
        this->_graphicSceneNN->clear();
        this->_viewNoNeuralNetwork();
        this->_setTextsNoNeuralNetwork();
        this->_formNNFile->setWindowOpacity(FORM_OPAQUE);
        this->_formNNFile->setEnabled(true);
        this->setEnabled(true);
        this->setWindowOpacity(FORM_OPAQUE);
        return;
    }

    this->_setMaxCountCellForDiagramNN();
    this->_threadDiagramNN->start();
    this->_fillTreeWidget();
    this->_viewAvailableNeuralNetwork();
    this->_setTextsAvailableNeuralNetwork();

    this->_formNNFile->setWindowOpacity(FORM_OPAQUE);
    this->_formNNFile->setEnabled(true);
    this->setEnabled(true);
    this->setWindowOpacity(FORM_OPAQUE);
}

void FormMain::slotSamplesFileParameters(int countSampleCorrected, std::string samplesFile){

    QString textLabelInformation=this->_labelInformation->text();
    QString textPushButtonTrain=this->_pushButtonTrain->text();

    if(this->_formSamplesFile->getFileType()==FormSamplesFile::FileType::TestSet){
        this->_testInfo.clear();

        std::thread t(&NeuralNetwork::testForGUI,FormMain::NeuralNetworkObject(),countSampleCorrected,samplesFile);
        t.detach();

        this->_viewTestIsOngoing();
        this->_setTextsTestIsOngoing();
        this->_countErrorOfTest=0;
        this->_isTextEditInformationFull=false;

    }else if(this->_formSamplesFile->getFileType()==FormSamplesFile::FileType::TrainingSet){
        this->_errorValues->clear();//her eğitimden önce temizlenmeli
        this->_updatedWeights->clear();//her eğitimden önce temizlenmeli
        this->_countEW=0;//her eğitimden önce bu değişken sıfırlanmalı
        this->_countSample=countSampleCorrected;//her eğitimden önce bu değişken yüklenmeli

        std::thread t(&NeuralNetwork::trainForGUI,FormMain::NeuralNetworkObject(),countSampleCorrected,samplesFile);
        t.detach();
        this->_viewTrainingIsOngoing();
        this->_setTextsTrainingIsOngoing();
        emit signalTextEditInformationSetText("");
    }

    while(FormMain::NeuralNetworkObject()->getVerificationSamplesFile()==NeuralNetwork::VerificationSamplesFile::None){
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    if(FormMain::NeuralNetworkObject()->getVerificationSamplesFile()==NeuralNetwork::VerificationSamplesFile::Denied){
        QMessageBox::warning(this,"Error","The file is incorrect. ",QMessageBox::Ok);
        if(this->_formSamplesFile->getFileType()==FormSamplesFile::FileType::TrainingSet)
            this->_viewTrainingIsFinished();
        else if(this->_formSamplesFile->getFileType()==FormSamplesFile::FileType::TestSet)
            this->_viewTestIsFinished();
        this->_labelInformation->setText(textLabelInformation);
        this->_pushButtonTrain->setText(textPushButtonTrain);
    }

    FormMain::NeuralNetworkObject()->resetVerificationSamplesFile();

}
void FormMain::slotRunParameters(int * const inputs){
    this->_runInfo.clear();
    this->_runInputInfo.clear();
    this->_runOutputInfo.clear();

    this->_runInputInfo.append("Inputs:\n");
    for(size_t i=0;i<FormMain::NeuralNetworkObject()->getInputLayerPattern()->getCountOriginal();i++){
        this->_runInputInfo.append(QString::number(inputs[i])+" ");
        if((i+1)%IMAGE_WIDTH==0){this->_runInputInfo.append("\n");}
    }

    this->_runInfo=this->_runInputInfo;
    emit signalTextEditInformationSetText(this->_runInfo);

    std::promise<bool> promise;
    std::future<bool> future=promise.get_future();

    std::thread thread(&NeuralNetwork::runForGUI,FormMain::NeuralNetworkObject(),inputs,ref(promise));
    thread.join();

    this->_viewRunIsOngoing();
    this->_setTextsRunIsOngoing();

    future.get();

    this->_viewRunIsFinished();
    this->_setTextsRunIsFinished();
}

void FormMain::_createNNFromFile(const std::string &parametersFileName, const char &separator){
    this->_errorCreateNNFromFile=false;
    try{
        FormMain::neuralNetwork=new NeuralNetwork(parametersFileName,separator);
    }catch(std::exception& e){
        this->_errorCreateNNFromFile=true;
        this->_exceptionWhatCreateNNFromFile=e.what();
        return;
    }
}
void FormMain::_createNNWithParameters(const double& lambda, const double& alfa, const std::string& parametersFileName, const char& separator, const double& randomWeightMin, const double& randomWeightMax){
    FormMain::neuralNetwork=new NeuralNetwork(lambda,alfa,*this->_inputPattern,*this->_hiddenPattern,*this->_outputPattern,parametersFileName,separator,randomWeightMin,randomWeightMax);
}
void FormMain::_fillTreeWidget(){
    this->_treeWidgetNN->clear();

    QTreeWidgetItem* inputLayer=new QTreeWidgetItem(this->_treeWidgetNN);
    inputLayer->setText(0,"Input Layer");
    inputLayer->setText(1,"");

    QTreeWidgetItem* originalCountInput=new QTreeWidgetItem();
    originalCountInput->setText(0,"Number Of Original Inputs");
    originalCountInput->setText(1,QString::number(FormMain::neuralNetwork->getInputLayerPattern()->getCountOriginal()));

    inputLayer->addChild(originalCountInput);

    QTreeWidgetItem* inputs=new QTreeWidgetItem();
    inputs->setText(0,"Inputs");
    inputs->setText(1,"");
    inputLayer->addChild(inputs);

    for(size_t i=0;i<FormMain::neuralNetwork->getInputLayerPattern()->getCountOriginal();i++){
        QTreeWidgetItem* inputType=new QTreeWidgetItem();
        QString type="Type["+QString::number(i)+"]";
        inputType->setText(0,type);
        inputType->setText(1,DATA_TYPES[(int)FormMain::neuralNetwork->getInputLayerPattern()->getType(i)]);
        inputs->addChild(inputType);

        QTreeWidgetItem* countInputCell=new QTreeWidgetItem();
        QString countCell="Number Of Cells["+QString::number(i)+"]";
        countInputCell->setText(0,countCell);
        countInputCell->setText(1,QString::number(FormMain::neuralNetwork->getInputLayerPattern()->getLength(i)));
        inputs->addChild(countInputCell);

        QTreeWidgetItem* inputLimit=new QTreeWidgetItem();
        QString limit="Limit["+QString::number(i)+"]";
        inputLimit->setText(0,limit);
        inputLimit->setText(1,QString::number(FormMain::neuralNetwork->getInputLayerPattern()->getLimit(i)->getOriginalMin())+"      "+QString::number(FormMain::neuralNetwork->getInputLayerPattern()->getLimit(i)->getOriginalMax()));
        inputs->addChild(inputLimit);

        QTreeWidgetItem* end=new QTreeWidgetItem();
        end->setText(0,"-----");
        end->setText(1,"-----");
        inputs->addChild(end);
    }

    QTreeWidgetItem* totalCountInputCell=new QTreeWidgetItem();
    totalCountInputCell->setText(0,"Total Number Of Input Cells");
    totalCountInputCell->setText(1,QString::number(FormMain::neuralNetwork->getInputLayerPattern()->getTotalLength()));
    inputLayer->addChild(totalCountInputCell);

    QTreeWidgetItem* hiddenLayer=new QTreeWidgetItem(this->_treeWidgetNN);
    hiddenLayer->setText(0,"Hidden Layer");
    hiddenLayer->setText(1,"");

    QTreeWidgetItem* countHiddenLayer=new QTreeWidgetItem();
    countHiddenLayer->setText(0,"Number Of Layers");
    countHiddenLayer->setText(1,QString::number(FormMain::neuralNetwork->getHiddenLayerPattern()->getCountLayer()));
    hiddenLayer->addChild(countHiddenLayer);

    QTreeWidgetItem* layers=new QTreeWidgetItem();
    layers->setText(0,"Layers");
    layers->setText(1,"");
    hiddenLayer->addChild(layers);

    for(size_t i=0;i<FormMain::neuralNetwork->getHiddenLayerPattern()->getCountLayer();i++){

        QTreeWidgetItem* countHiddenCell=new QTreeWidgetItem();
        QString layer="Number Of Cells["+QString::number(i)+"]";
        countHiddenCell->setText(0,layer);
        countHiddenCell->setText(1,QString::number(FormMain::neuralNetwork->getHiddenLayerPattern()->getCountCell(i)));
        layers->addChild(countHiddenCell);

        QTreeWidgetItem* hiddenSumFunc=new QTreeWidgetItem();
        QString sumFunc="Sum Func["+QString::number(i)+"]";
        hiddenSumFunc->setText(0,sumFunc);
        hiddenSumFunc->setText(1,SUM_FUNCTIONS[(int)FormMain::neuralNetwork->getHiddenLayerPattern()->getSumFunc(i)->getType()]);
        layers->addChild(hiddenSumFunc);

        QTreeWidgetItem* hiddenActFunc=new QTreeWidgetItem();
        QString actFunc="Act Func["+QString::number(i)+"]";
        hiddenActFunc->setText(0,actFunc);
        hiddenActFunc->setText(1,ACT_FUNCTIONS[(int)FormMain::neuralNetwork->getHiddenLayerPattern()->getActFunc(i)->getType()]);
        layers->addChild(hiddenActFunc);

        QTreeWidgetItem* end=new QTreeWidgetItem();
        end->setText(0,"-----");
        end->setText(1,"-----");
        layers->addChild(end);
    }

    QTreeWidgetItem* outputLayer=new QTreeWidgetItem(this->_treeWidgetNN);
    outputLayer->setText(0,"Output Layer");
    outputLayer->setText(1,"");

    QTreeWidgetItem* countOriginalOutput=new QTreeWidgetItem();
    countOriginalOutput->setText(0,"Number Of Original Outputs");
    countOriginalOutput->setText(1,QString::number(FormMain::neuralNetwork->getOutputLayerPattern()->getCountOriginal()));
    outputLayer->addChild(countOriginalOutput);

    QTreeWidgetItem* outputSumFunc=new QTreeWidgetItem();
    outputSumFunc->setText(0,"Sum Func");
    outputSumFunc->setText(1,SUM_FUNCTIONS[(int)FormMain::neuralNetwork->getOutputLayerPattern()->getSumFunc()->getType()]);
    outputLayer->addChild(outputSumFunc);

    QTreeWidgetItem* outputActFunc=new QTreeWidgetItem();
    outputActFunc->setText(0,"Act Func");
    outputActFunc->setText(1,ACT_FUNCTIONS[(int)FormMain::neuralNetwork->getOutputLayerPattern()->getActFunc()->getType()]);
    outputLayer->addChild(outputActFunc);

    QTreeWidgetItem* outputs=new QTreeWidgetItem();
    outputs->setText(0,"Outputs");
    outputs->setText(1,"");
    outputLayer->addChild(outputs);

    for(size_t i=0;i<FormMain::neuralNetwork->getOutputLayerPattern()->getCountOriginal();i++){
        QTreeWidgetItem* outputType=new QTreeWidgetItem();
        QString type="Type["+QString::number(i)+"]";
        outputType->setText(0,type);
        outputType->setText(1,DATA_TYPES[(int)FormMain::neuralNetwork->getOutputLayerPattern()->getType(i)]);
        outputs->addChild(outputType);

        QTreeWidgetItem* countOutputCell=new QTreeWidgetItem();
        QString countCell="Number Of Cells["+QString::number(i)+"]";
        countOutputCell->setText(0,countCell);
        countOutputCell->setText(1,QString::number(FormMain::neuralNetwork->getOutputLayerPattern()->getLength(i)));
        outputs->addChild(countOutputCell);

        QTreeWidgetItem* outputLimit=new QTreeWidgetItem();
        QString limit="Limit["+QString::number(i)+"]";
        outputLimit->setText(0,limit);
        outputLimit->setText(1,QString::number(FormMain::neuralNetwork->getOutputLayerPattern()->getLimit(i)->getOriginalMin())+"      "+QString::number(FormMain::neuralNetwork->getOutputLayerPattern()->getLimit(i)->getOriginalMax()));
        outputs->addChild(outputLimit);

        QTreeWidgetItem* outputTolerance=new QTreeWidgetItem();
        QString tolerance="Tolerance["+QString::number(i)+"]";
        outputTolerance->setText(0,tolerance);
        outputTolerance->setText(1,QString::number(FormMain::neuralNetwork->getOutputLayerPattern()->getTolerance(i)));
        outputs->addChild(outputTolerance);

        QTreeWidgetItem* end=new QTreeWidgetItem();
        end->setText(0,"-----");
        end->setText(1,"-----");
        outputs->addChild(end);
    }

    QTreeWidgetItem* totalCountOutputCell=new QTreeWidgetItem();
    totalCountOutputCell->setText(0,"Total Number Of Output Cells");
    totalCountOutputCell->setText(1,QString::number(FormMain::neuralNetwork->getOutputLayerPattern()->getTotalLength()));
    outputLayer->addChild(totalCountOutputCell);

    QTreeWidgetItem* training=new QTreeWidgetItem(this->_treeWidgetNN);
    training->setText(0,"Training Properties");
    training->setText(1,"");

    QTreeWidgetItem* lambda=new QTreeWidgetItem();
    lambda->setText(0,"Lambda");
    lambda->setText(1,QString::number(FormMain::neuralNetwork->getLambda()));
    training->addChild(lambda);

    QTreeWidgetItem* alfa=new QTreeWidgetItem();
    alfa->setText(0,"Alfa");
    alfa->setText(1,QString::number(FormMain::neuralNetwork->getAlfa()));
    training->addChild(alfa);

    QTreeWidgetItem* file=new QTreeWidgetItem(this->_treeWidgetNN);
    file->setText(0,"File Properties");
    file->setText(1,"");

    QTreeWidgetItem* nnFile=new QTreeWidgetItem();
    nnFile->setText(0,"NeuralNetwork File");
    nnFile->setText(1,FormMain::neuralNetwork->getParametersFile().c_str());
    file->addChild(nnFile);

    QTreeWidgetItem* errorFile=new QTreeWidgetItem();
    errorFile->setText(0,"Error File");
    errorFile->setText(1,FormMain::neuralNetwork->getLogEW()->getFile().c_str());
    file->addChild(errorFile);

    QTreeWidgetItem* separator=new QTreeWidgetItem();
    separator->setText(0,"Separator Character");
    for(int i=0;i<COUNT_SEPARATOR;i++){
        if(FormMain::neuralNetwork->getSeparator()==SEPARATORS[i]){
            separator->setText(1,SEPARATOR_DESCRIPTIONS[i]);
        }
    }
    file->addChild(separator);

    this->_treeWidgetNN->resizeColumnToContents(0);
    this->_treeWidgetNN->resizeColumnToContents(1);
}
void FormMain::_setMaxCountCellForDiagramNN(){
    if(FormMain::neuralNetwork->getInputLayerPattern()->getTotalLength()<MAX_COUNT_CELL_IN_DIAGRAM){
        this->_maxCountCell=FormMain::neuralNetwork->getInputLayerPattern()->getTotalLength()+1;//+1 for bias
    }else{
        this->_maxCountCell=COUNT_SHORTENED_CELL_IN_DIAGRAM+COUNT_DOT+1;//+1 for bias
    }

    for(size_t i=0;i<FormMain::neuralNetwork->getHiddenLayerPattern()->getCountLayer();i++){
        if(FormMain::neuralNetwork->getHiddenLayerPattern()->getCountCell(i)<MAX_COUNT_CELL_IN_DIAGRAM){
            if(1+FormMain::neuralNetwork->getHiddenLayerPattern()->getCountCell(i)>this->_maxCountCell)//+1 for bias
                this->_maxCountCell=FormMain::neuralNetwork->getHiddenLayerPattern()->getCountCell(i)+1;//+1 for bias
        }else{
            if(this->_maxCountCell<COUNT_SHORTENED_CELL_IN_DIAGRAM+COUNT_DOT+1){//+1 for bias
                this->_maxCountCell=COUNT_SHORTENED_CELL_IN_DIAGRAM+COUNT_DOT+1;//+1 for bias
            }
        }
    }

    if(FormMain::neuralNetwork->getOutputLayerPattern()->getTotalLength()<MAX_COUNT_CELL_IN_DIAGRAM){
        if(FormMain::neuralNetwork->getOutputLayerPattern()->getTotalLength()>this->_maxCountCell)
            this->_maxCountCell=FormMain::neuralNetwork->getOutputLayerPattern()->getTotalLength();
    }else{
        if(this->_maxCountCell<COUNT_SHORTENED_CELL_IN_DIAGRAM+COUNT_DOT){
            this->_maxCountCell=COUNT_SHORTENED_CELL_IN_DIAGRAM+COUNT_DOT;
        }
    }
}
void FormMain::_allControlsEnabled(){
    this->_pushButtonNew->setEnabled(true);
    this->_pushButtonOpen->setEnabled(true);
    this->_pushButtonEdit->setEnabled(true);
    this->_treeWidgetNN->setEnabled(true);
    this->_pushButtonTrain->setEnabled(true);
    this->_checkBoxGraph->setEnabled(true);
    this->_pushButtonTest->setEnabled(true);
    this->_pushButtonRun->setEnabled(true);
    this->_labelInformation->setEnabled(true);
    this->_textEditInformation->setEnabled(true);
}
void FormMain::_commonViewOngoingEvents(){
    this->_pushButtonNew->setEnabled(false);
    this->_pushButtonOpen->setEnabled(false);
    this->_pushButtonEdit->setEnabled(false);
    this->_pushButtonTest->setEnabled(false);
    this->_pushButtonRun->setEnabled(false);
    this->_labelInformation->setEnabled(true);
    this->_textEditInformation->setEnabled(true);
}
void FormMain::_viewNoNeuralNetwork(){
    this->_pushButtonNew->setEnabled(true);
    this->_pushButtonOpen->setEnabled(true);
    this->_pushButtonEdit->setEnabled(false);
    this->_treeWidgetNN->resizeColumnToContents(0);
    this->_treeWidgetNN->resizeColumnToContents(1);
    this->_treeWidgetNN->setEnabled(false);
    this->_pushButtonTrain->setEnabled(false);
    this->_checkBoxGraph->setEnabled(false);
    this->_pushButtonTest->setEnabled(false);
    this->_pushButtonRun->setEnabled(false);
    this->_labelInformation->setEnabled(false);
    this->_textEditInformation->setEnabled(false);
}
void FormMain::_viewAvailableNeuralNetwork(){
    this->_allControlsEnabled();
}
void FormMain::_viewTrainingIsOngoing(){
    this->_commonViewOngoingEvents();
    this->_treeWidgetNN->setEnabled(true);
    this->_pushButtonTrain->setEnabled(true);
    this->_checkBoxGraph->setEnabled(true);
}
void FormMain::_viewTrainingIsFinished(){
    this->_allControlsEnabled();

    if(this->_graphEW)this->_graphEW->close();
}
void FormMain::_viewTestIsOngoing(){
    this->_commonViewOngoingEvents();
    this->_treeWidgetNN->setEnabled(false);
    this->_pushButtonTrain->setEnabled(false);
    this->_checkBoxGraph->setEnabled(false);
}
void FormMain::_viewTestIsFinished(){
    this->_allControlsEnabled();
}
void FormMain::_viewRunIsOngoing(){
    this->_commonViewOngoingEvents();
    this->_treeWidgetNN->setEnabled(false);
    this->_pushButtonTrain->setEnabled(false);
    this->_checkBoxGraph->setEnabled(false);
}
void FormMain::_viewRunIsFinished(){
    this->_allControlsEnabled();
}
void FormMain::_setTextsNoNeuralNetwork(){
    this->_pushButtonTrain->setText("Train");
    this->_labelInformation->setText("");
    this->_textEditInformation->setText("");
}
void FormMain::_setTextsAvailableNeuralNetwork(){
    this->_pushButtonTrain->setText("Train");
    this->_labelInformation->setText("The Neural Network is ready to train, test or run");
    this->_textEditInformation->setText("");
}
void FormMain::_setTextsTrainingIsOngoing(){
    this->_pushButtonTrain->setText("Stop Training");
    this->_labelInformation->setText("The Neural Network is being trained");
}
void FormMain::_setTextsTrainingIsFinished(){
    this->_pushButtonTrain->setText("Train");
}
void FormMain::_setTextsTestIsOngoing(){
    this->_labelInformation->setText("The Neural Network is being tested");
}
void FormMain::_setTextsTestIsFinished(){
    this->_labelInformation->setText("Test completed");
}
void FormMain::_setTextsRunIsOngoing(){
    this->_labelInformation->setText("The Neural Network is running");
}
void FormMain::_setTextsRunIsFinished(){
    this->_labelInformation->setText("Run completed");
}
void FormMain::slotDestroyedInputLayerNew(){
    this->_formInputLayerNew=nullptr;
}
void FormMain::slotDestroyedHiddenLayersNew(){
    this->_formHiddenLayersNew=nullptr;
    if(!this->_hiddenPattern){
        delete this->_inputPattern;
        this->_inputPattern=nullptr;
    }
}
void FormMain::slotDestroyedOutputLayerNew(){
    this->_formOutputLayerNew=nullptr;
    if(!this->_outputPattern){
        delete this->_inputPattern;
        this->_inputPattern=nullptr;
        delete this->_hiddenPattern;
        this->_hiddenPattern=nullptr;
    }
}
void FormMain::slotDestroyedOtherSettingsNew(){
    this->_formOtherSettingsNew=nullptr;
    delete this->_inputPattern;
    this->_inputPattern=nullptr;
    delete this->_hiddenPattern;
    this->_hiddenPattern=nullptr;
    delete this->_outputPattern;
    this->_outputPattern=nullptr;
}
void FormMain::slotDestroyedInputLayerOpen(){
    this->_formInputLayerOpen=nullptr;
}
void FormMain::slotDestroyedHiddenLayersOpen(){
    this->_formHiddenLayersOpen=nullptr;
}
void FormMain::slotDestroyedOutputLayerOpen(){
    this->_formOutputLayerOpen=nullptr;
}
void FormMain::slotDestroyedOtherSettingsOpen(){
    this->_formOtherSettingsOpen=nullptr;
}
void FormMain::slotDestroyedGraphEW(){
    this->_graphEW=nullptr;
    this->_checkBoxGraph->setChecked(false);
}
void FormMain::slotDestroyedNNFile(){
    this->_formNNFile=nullptr;
}
void FormMain::slotDestroyedSamplesFile(){
    this->_formSamplesFile=nullptr;
}
void FormMain::slotDestroyedRun(){
    this->_formRun=nullptr;
}
void FormMain::slotPrepareGraphicSceneForNNDiagram(){
    this->_graphicSceneNN->clear();
    this->_graphicSceneNN->setSceneRect(0,0,this->_graphicViewNN->width()-2*this->_graphicViewNN->frameWidth(),this->_graphicViewNN->height()-2*this->_graphicViewNN->frameWidth());
}
void FormMain::slotAddLineForNNDiagram(qreal x1, qreal y1, qreal x2, qreal y2, QPen pen){
    this->_graphicSceneNN->addLine(x1,y1,x2,y2,pen);
}
void FormMain::slotAddEllipseForNNDiagram(qreal x, qreal y, qreal w, qreal h, QPen pen, QBrush brush){
    this->_graphicSceneNN->addEllipse(x,y,w,h,pen,brush);
}
void FormMain::receiveTrainingInfo(const double& error,const size_t& weight){
    this->_errorValues->push_back(error);
    this->_updatedWeights->push_back(weight);
    this->_countEW++;

    if(this->_graphEW){
        if(GraphEW::getThreadGraphEWObject()->isReadyToDrawNewEW()){
            GraphEW::getThreadGraphEWObject()->setOperationType(ThreadGraphEW::OperationType::DrawNewEW);
            GraphEW::getThreadGraphEWObject()->start();

            while(!GraphEW::getThreadGraphEWObject()->isDrawingNewEWFinished()&&!GraphEW::getThreadGraphEWObject()->isNewEWMaximum()){
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }

            if(GraphEW::getThreadGraphEWObject()->isNewEWMaximum()){
                GraphEW::getThreadGraphEWObject()->setOperationType(ThreadGraphEW::OperationType::DrawPreviousEWOfCurrentTraining);
                GraphEW::getThreadGraphEWObject()->start();
            }
        }
    }
}
void FormMain::showOngoingTrainingInfo(const int& countSample,const int& epoch,const double& error,const size_t& weight){
    QString info="Number Of Samples\t\t: "+QString::number(countSample);
    info.append("\nEpoch\t\t\t: "+QString::number(epoch));
    info.append("\nTotal Error\t\t\t: "+QString::number(error));
    info.append("\nNumber Of Updated Weights \t: "+QString::number(weight));

    emit signalTextEditInformationSetText(info);
}
void FormMain::showFinishedTrainingInfo(const NeuralNetwork::StatusTraining& statusTraining,const int& countSample,const int& epoch){
    QString infoStatusTraining;
    switch(statusTraining){
    case NeuralNetwork::StatusTraining::Halted:
        infoStatusTraining="Training has been halted";
        break;
    case NeuralNetwork::StatusTraining::Failed:
        infoStatusTraining="Training has failed\n";
        infoStatusTraining.append(FormMain::NeuralNetworkObject()->getTrainingErrorMessage().c_str());
        break;
    case NeuralNetwork::StatusTraining::Succesfull:
        infoStatusTraining="Training completed successfully";
        break;
    default:
        break;
    }

    QString infoResultTraining;
    infoResultTraining.append("Number Of Samples\t\t: "+QString::number(countSample));
    infoResultTraining.append("\nEpoch\t\t\t: "+QString::number(epoch));
    emit signalTextEditInformationSetText(infoResultTraining);
    this->_labelInformation->setText(infoStatusTraining);

    this->_viewTrainingIsFinished();
    this->_setTextsTrainingIsFinished();
}
void FormMain::showTestInfoSample(const int& indexSample,const size_t& indexOutput,const double& output,const double& expectedOutput){
    this->_countErrorOfTest++;

    if(this->_countErrorOfTest<COUNT_ERROR_OF_TEST_TO_SHOW_MAX){
        QString info="Sample Index\t: "+QString::number(indexSample);

        info.append("\nOutput Index\t: "+QString::number(indexOutput));
        Data::Type outputType=FormMain::NeuralNetworkObject()->getOutputLayerPattern()->getType(indexOutput);
        if(outputType==Data::Type::Narrowed || outputType==Data::Type::Native)
            info.append("\nOutput(rounded)\t: "+QString::number(std::round(output)));

        info.append("\nOutput \t\t: "+QString::number(output));
        info.append("\nExpected Output\t: "+QString::number(expectedOutput));
        info.append("\n-----------------------------------------\n");

        this->_testInfo=info+this->_testInfo;
        emit signalTextEditInformationSetText(this->_testInfo);
    }else{
        if(!this->_isTextEditInformationFull){
            this->_testInfo="There are too many errors\n.\n.\n.";
            this->_isTextEditInformationFull=true;
            emit signalTextEditInformationSetText(this->_testInfo);
        }
    }
}
void FormMain::showTestInfoResult(const int& countError,const int& countAllOutput,const double& result){
    QString info="Success Rate\t\t: "+QString::number(result*100)+"%";
    info.append("\nNumber of failed outputs\t: "+QString::number(countError));
    info.append("\nNumber of successful outputs\t: "+QString::number(countAllOutput-countError));
    info.append("\nTotal number of outputs\t: "+QString::number(countAllOutput));
    info.append("\nNumber of samples\t\t: "+QString::number(FormMain::NeuralNetworkObject()->getCountSample()));
    info.append("\n--------------------------------------------------------------------------------\n");

    info.append(this->_testInfo);
    emit signalTextEditInformationSetText(info);
    this->_viewTestIsFinished();
    this->_setTextsTestIsFinished();
}
void FormMain::showRunInfo(const size_t& indexSingleOutput,const double& singleOutput){
    this->_runOutputInfo.append("Output:\t"+QString::number(std::round(singleOutput))+"\n\n");

    Data::Type outputType=FormMain::NeuralNetworkObject()->getOutputLayerPattern()->getType(indexSingleOutput);
    if(outputType==Data::Type::Narrowed || outputType==Data::Type::Native)
        this->_runOutputInfo.append("\t( "+QString::number(singleOutput)+" )\n\n");

    this->_runInfo.clear();
    this->_runInfo=this->_runOutputInfo+this->_runInputInfo;
    emit signalTextEditInformationSetText(this->_runInfo);
}
void SignalEpochHandler::handleSignal(int){

    if(FormMain::NeuralNetworkObject()->getActionMode()==NeuralNetwork::ActionMode::Train){
        NeuralNetwork::StatusTraining statusTraining=FormMain::NeuralNetworkObject()->getStatusTraining();
        int countSample=FormMain::NeuralNetworkObject()->getCountSample();
        int epoch=FormMain::NeuralNetworkObject()->getEpoch();
        if(statusTraining==NeuralNetwork::StatusTraining::Ongoing){
            double error=FormMain::NeuralNetworkObject()->getLogEW()->getNewErrorValue();
            size_t weight=FormMain::NeuralNetworkObject()->getLogEW()->getNewUpdatedWeight();

            SignalEpochHandler::owner->showOngoingTrainingInfo(countSample,epoch,error,weight);
            SignalEpochHandler::owner->receiveTrainingInfo(error,weight);
        }else{
            SignalEpochHandler::owner->showFinishedTrainingInfo(statusTraining,countSample,epoch);
        }

    }else if(FormMain::NeuralNetworkObject()->getActionMode()==NeuralNetwork::ActionMode::Test){
        if(FormMain::NeuralNetworkObject()->getResultTest()==TEST_RESULT_UNCERTAIN){
            int indexSample=FormMain::NeuralNetworkObject()->getIndexSampleOfTest();
            size_t indexOutput=FormMain::NeuralNetworkObject()->getIndexOutputOfTest();
            double output=FormMain::NeuralNetworkObject()->getOutputOfTest();
            double expectedOutput=FormMain::NeuralNetworkObject()->getExpectedOutputOfTest();
            SignalEpochHandler::owner->showTestInfoSample(indexSample,indexOutput,output,expectedOutput);
        }else{
            int countError=FormMain::NeuralNetworkObject()->getCountErrorOfTest();
            int countAllOutput=FormMain::NeuralNetworkObject()->getCountAllOutputOfTest();
            double result=FormMain::NeuralNetworkObject()->getResultTest();
            SignalEpochHandler::owner->showTestInfoResult(countError,countAllOutput,result);
        }
    }else if(FormMain::NeuralNetworkObject()->getActionMode()==NeuralNetwork::ActionMode::Run){
        size_t indexOutput=FormMain::NeuralNetworkObject()->getIndexSingleOutputOfRun();
        double output=FormMain::NeuralNetworkObject()->getSingleOutputOfRun();
        SignalEpochHandler::owner->showRunInfo(indexOutput,output);
    }
}
