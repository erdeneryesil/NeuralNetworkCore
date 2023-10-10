#include"graph_ew.h"
#include"gui/defines_gui.h"
#include"form_main.h"

GraphEW* TrainingLine::parent=nullptr;
TrainingLine::TrainingLine(const bool& isTrainingPrevious, const size_t& trainingIndex, const qreal& x1, const qreal& y1, const qreal& x2, const qreal& y2)
    :QGraphicsLineItem(x1,y1,x2,y2),_isTrainingPrevious(isTrainingPrevious),_trainingIndex(trainingIndex){

    size_t countHiddenLayer=FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer();
    this->_sumFuncTypesOfHiddenLayer=new QVector<Cell::SummationFunction::Type>(countHiddenLayer);
    this->_actFuncTypesOfHiddenLayer=new QVector<Cell::ActivationFunction::Type>(countHiddenLayer);
    size_t countOriginalOutput=FormMain::NeuralNetworkObject()->getOutputLayerPattern()->getCountOriginal();
    this->_tolerances=new QVector<double>(countOriginalOutput);

    if(isTrainingPrevious){
        for(size_t i=0;i<countHiddenLayer;i++){
            (*this->_sumFuncTypesOfHiddenLayer)[i]=FormMain::NeuralNetworkObject()->getLogEW()->getSumFuncTypeOfHiddenLayer(trainingIndex,i);
            (*this->_actFuncTypesOfHiddenLayer)[i]=FormMain::NeuralNetworkObject()->getLogEW()->getActFuncTypeOfHiddenLayer(trainingIndex,i);
        }
        this->_sumFuncTypeOfOutputLayer=FormMain::NeuralNetworkObject()->getLogEW()->getSumFuncTypeOfOutputLayer(trainingIndex);
        this->_actFuncTypeOfOutputLayer=FormMain::NeuralNetworkObject()->getLogEW()->getActFuncTypeOfOutputLayer(trainingIndex);

        for(size_t i=0;i<countOriginalOutput;i++)
            (*this->_tolerances)[i]=FormMain::NeuralNetworkObject()->getLogEW()->getTolerance(trainingIndex,i);

        this->_lambda=FormMain::NeuralNetworkObject()->getLogEW()->getLambda(trainingIndex);
        this->_alfa=FormMain::NeuralNetworkObject()->getLogEW()->getAlfa(trainingIndex);
        this->_countSample=FormMain::NeuralNetworkObject()->getLogEW()->getCountSample(trainingIndex);
        this->_countEW=FormMain::NeuralNetworkObject()->getLogEW()->getCountEWInATraining(trainingIndex);
    }else{
        for(size_t i=0;i<countHiddenLayer;i++){
            (*this->_sumFuncTypesOfHiddenLayer)[i]=FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getSumFunc(i)->getType();
            (*this->_actFuncTypesOfHiddenLayer)[i]=FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getActFunc(i)->getType();
        }
        this->_sumFuncTypeOfOutputLayer=FormMain::NeuralNetworkObject()->getOutputLayerPattern()->getSumFunc()->getType();
        this->_actFuncTypeOfOutputLayer=FormMain::NeuralNetworkObject()->getOutputLayerPattern()->getActFunc()->getType();

        for(size_t i=0;i<countOriginalOutput;i++)
            (*this->_tolerances)[i]=FormMain::NeuralNetworkObject()->getOutputLayerPattern()->getTolerance(i);

        this->_lambda=FormMain::NeuralNetworkObject()->getLambda();
        this->_alfa=FormMain::NeuralNetworkObject()->getAlfa();
        this->_countSample=TrainingLine::parent->getParentForm()->getCountSample();
        this->_countEW=TrainingLine::parent->getParentForm()->getCountEW();
    }

    this->setToolTip(this->getToolTipText());
}
TrainingLine::~TrainingLine(){
    this->_sumFuncTypesOfHiddenLayer->clear();
    delete this->_sumFuncTypesOfHiddenLayer;

    this->_actFuncTypesOfHiddenLayer->clear();
    delete this->_actFuncTypesOfHiddenLayer;

    this->_tolerances->clear();
    delete this->_tolerances;
}
size_t TrainingLine::getCountEW()const{
    return this->_countEW;
}
QString TrainingLine::getToolTipText(){
    QString info="Training Index \t\t: "+QString::number(this->_trainingIndex);
    info.append("\nNumber Of Samples\t: "+QString::number(this->_countSample));
    info.append("\nNumber Of EW\t\t: "+QString::number(this->_countEW));

    info.append("\n\nHidden Layers\n");
    for(int i=0;i<this->_sumFuncTypesOfHiddenLayer->size();i++){
        info.append("Summation Function ("+QString::number(i)+") \t: "+SUM_FUNCTIONS[(int)this->_sumFuncTypesOfHiddenLayer->at(i)]+"\n");
        info.append("Activation Function ("+QString::number(i)+") \t: "+ACT_FUNCTIONS[(int)this->_actFuncTypesOfHiddenLayer->at(i)]+"\n");
    }
    info.append("\nOutput Layer\n");
    info.append("Summation Function \t: "+SUM_FUNCTIONS[(int)this->_sumFuncTypeOfOutputLayer]+"\n");
    info.append("Activation Function \t: "+ACT_FUNCTIONS[(int)this->_actFuncTypeOfOutputLayer]+"\n");
    for(int i=0;i<this->_tolerances->size();i++)
        info.append("Tolerance ("+QString::number(i)+")\t\t: "+QString::number((*this->_tolerances)[i])+"\n");

    info.append("\nLambda \t\t\t: "+QString::number(this->_lambda));
    info.append("\n\nAlfa \t\t\t: "+QString::number(this->_alfa));

    return info;
}
void TrainingLine::updateCountEW(){
    this->_countEW=TrainingLine::parent->getParentForm()->getCountEW();
}

ThreadGraphEW* GraphEW::_threadGraphEWObject=nullptr;
GraphEW::GraphEW(const FormMain*const parentForm):_parentForm(parentForm){
    this->_mainLayout=new QVBoxLayout();
    this->_layoutHead=new QHBoxLayout();

    this->_checkBoxPreviousTrainings=new QCheckBox();
    this->_checkBoxMaxEWBasedOnAllTrainings=new QCheckBox();
    this->_view=new QGraphicsView();
    this->_scene=new QGraphicsScene();

    this->_checkBoxPreviousTrainings->setText("Previous Trainings");
    this->_checkBoxPreviousTrainings->setFixedWidth(this->_checkBoxPreviousTrainings->sizeHint().width());
    this->_layoutHead->addWidget(this->_checkBoxPreviousTrainings);
    this->_checkBoxMaxEWBasedOnAllTrainings->setText("Maximum values are based on all trainings. ");
    this->_checkBoxMaxEWBasedOnAllTrainings->setChecked(true);
    this->_layoutHead->addWidget(this->_checkBoxMaxEWBasedOnAllTrainings);

    this->_view->setFixedHeight(ERROR_GRAPH_VIEW_HEIGHT);
    this->_view->setFixedWidth(ERROR_GRAPH_VIEW_WIDTH);
    this->_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->_scene->setSceneRect(ERROR_GRAPH_SCENE_X,ERROR_GRAPH_SCENE_Y,this->_view->width()-2*this->_view->frameWidth(),this->_view->height()-2*this->_view->frameWidth()-this->_view->horizontalScrollBar()->sizeHint().height());
    this->_view->setScene(this->_scene);

    this->_mainLayout->addLayout(this->_layoutHead);
    this->_mainLayout->addWidget(this->_view);

    this->setLayout(this->_mainLayout);

    this->setWindowTitle("Errors and Updated Weights");

    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setWindowModality(Qt::WindowModality::ApplicationModal);

    this->_trainingLine=new QVector<TrainingLine*>();
    this->_penTraining.setColor(ERROR_GRAPH_PEN_TRAINING_COLOR);
    this->_penTraining.setWidth(ERROR_GRAPH_PEN_TRAINING_WIDTH);
    this->_penError.setColor(ERROR_GRAPH_PEN_ERROR_COLOR);
    this->_penError.setWidth(ERROR_GRAPH_PEN_ERROR_WIDTH);
    this->_brushError.setStyle(Qt::SolidPattern);
    this->_brushError.setColor(ERROR_GRAPH_PEN_ERROR_COLOR);
    this->_penWeight.setColor(ERROR_GRAPH_PEN_WEIGHT_COLOR);
    this->_penWeight.setWidth(ERROR_GRAPH_PEN_WEIGHT_WIDTH);
    this->_brushWeight.setStyle(Qt::SolidPattern);
    this->_brushWeight.setColor(ERROR_GRAPH_PEN_WEIGHT_COLOR);

    GraphEW::_threadGraphEWObject=new ThreadGraphEW(this);
    this->_scrolling=false;

    connect(GraphEW::_threadGraphEWObject,SIGNAL(signalDrawCompleted()),this,SLOT(slotDrawCompleted()));
    connect(GraphEW::_threadGraphEWObject,SIGNAL(signalPrepareDraw()),this,SLOT(slotPrepareDraw()));

    qRegisterMetaType<size_t>("size_t");
    connect(GraphEW::_threadGraphEWObject,SIGNAL(signalTrainingLineCreated(bool,size_t,qreal,qreal,qreal,qreal)),this,SLOT(slotTrainingLineCreated(bool,size_t,qreal,qreal,qreal,qreal)));
    connect(GraphEW::_threadGraphEWObject,SIGNAL(signalErrorEllipseCreated(qreal,qreal)),this,SLOT(slotErrorEllipseCreated(qreal,qreal)));
    connect(GraphEW::_threadGraphEWObject,SIGNAL(signalWeightEllipseCreated(qreal,qreal)),this,SLOT(slotWeightEllipseCreated(qreal,qreal)));
    connect(this->_threadGraphEWObject,SIGNAL(signalErrorLineCreated(qreal,qreal,qreal,qreal)),this,SLOT(slotErrorLineCreated(qreal,qreal,qreal,qreal)));
    connect(this->_threadGraphEWObject,SIGNAL(signalWeightLineCreated(qreal,qreal,qreal,qreal)),this,SLOT(slotWeightLineCreated(qreal,qreal,qreal,qreal)));
    connect(this->_threadGraphEWObject,SIGNAL(signalCountEWIncreased()),this,SLOT(slotCountEWIncreased()));

    connect(GraphEW::_threadGraphEWObject,SIGNAL(signalSceneNeedsSettingRectForExpand(qreal)),this,SLOT(slotSceneNeedsSettingRectForExpand(qreal)));
    connect(this->_checkBoxPreviousTrainings,SIGNAL(stateChanged(int)),this,SLOT(slotCheckBoxPreviousTrainings(int)));
    connect(this->_checkBoxMaxEWBasedOnAllTrainings,SIGNAL(stateChanged(int)),this,SLOT(slotCheckBoxMaxEWBasedOnAllTrainings(int)));
    connect(this->_view->horizontalScrollBar(),SIGNAL(sliderMoved(int)),this,SLOT(slotScrollBarMoved(int)));
    connect(this->_view->horizontalScrollBar(),SIGNAL(sliderPressed()),this,SLOT(slotScrollBarPressed()));
    connect(this->_view->horizontalScrollBar(),SIGNAL(sliderReleased()),this,SLOT(slotScrollBarReleased()));

    TrainingLine::parent=this;

    if(FormMain::NeuralNetworkObject()->getActionMode()==NeuralNetwork::ActionMode::Train){
        GraphEW::_threadGraphEWObject->setOperationType(ThreadGraphEW::OperationType::DrawPreviousEWOfCurrentTraining);
    }else{
        GraphEW::_threadGraphEWObject->setOperationType(ThreadGraphEW::OperationType::DrawPreviousTrainings);
        this->_checkBoxPreviousTrainings->setChecked(true);
        this->_checkBoxPreviousTrainings->setEnabled(false);
    }

    GraphEW::_threadGraphEWObject->start();

}
GraphEW::~GraphEW(){
    this->_threadGraphEWObject->deleteLater();

    this->_checkBoxPreviousTrainings->deleteLater();
    this->_checkBoxMaxEWBasedOnAllTrainings->deleteLater();
    this->_scene->deleteLater();
    this->_view->deleteLater();
    this->_layoutHead->deleteLater();
    this->_mainLayout->deleteLater();

    this->_clearTrainingLine();
    delete this->_trainingLine;
}
void GraphEW::_clearTrainingLine(){
    while(this->_trainingLine->size()>0){
        delete this->_trainingLine->back();
        this->_trainingLine->pop_back();
    }
}
void GraphEW::closeEvent(QCloseEvent *){
    this->_threadGraphEWObject->setStopAllDrawings(true);
}
const FormMain* GraphEW::getParentForm()const{
    return this->_parentForm;
}
void GraphEW::slotPrepareDraw(){
    this->setWindowOpacity(FORM_TRANSPARENT);
    this->setEnabled(false);
    this->_clearTrainingLine();
    //this->_view->items().clear();
    this->_scene->clear();
    this->_scene->setSceneRect(ERROR_GRAPH_SCENE_X,ERROR_GRAPH_SCENE_Y,this->_view->width()-2*this->_view->frameWidth(),this->_view->height()-2*this->_view->frameWidth()-this->_view->horizontalScrollBar()->sizeHint().height());
    this->_view->setScene(this->_scene);
}
void GraphEW::slotDrawCompleted(){
    if(!this->_scrolling)
        this->_view->horizontalScrollBar()->setSliderPosition(this->_view->horizontalScrollBar()->maximum());

    this->setWindowOpacity(FORM_OPAQUE);
    this->setEnabled(true);
}

void GraphEW::slotTrainingLineCreated(bool isTrainingPrevious, size_t trainingIndex, qreal x1, qreal y1, qreal x2, qreal y2){
    this->_trainingLine->push_back(new TrainingLine(isTrainingPrevious,trainingIndex,x1,y1,x2,y2));
    this->_trainingLine->back()->setPen(this->_penTraining);
    this->_scene->addItem(this->_trainingLine->back());
}
void GraphEW::slotErrorEllipseCreated(qreal x1, qreal y1){
    qreal r=ERROR_GRAPH_EW_ELLIPSE_R;
    this->_scene->addEllipse(x1-r/2,y1-r/2,r,r,this->_penError,this->_brushError);
}
void GraphEW::slotWeightEllipseCreated(qreal x1, qreal y1){
    qreal r=ERROR_GRAPH_EW_ELLIPSE_R;
    this->_scene->addEllipse(x1-r/2,y1-r/2,r,r,this->_penWeight,this->_brushWeight);
}
void GraphEW::slotErrorLineCreated(qreal x1, qreal y1, qreal x2, qreal y2){
    QLine errorLine(x1,y1,x2,y2);
    this->_scene->addLine(errorLine,this->_penError);
}
void GraphEW::slotWeightLineCreated(qreal x1, qreal y1, qreal x2, qreal y2){
    QLine weightLine(x1,y1,x2,y2);
    this->_scene->addLine(weightLine,this->_penWeight);
}
void GraphEW::slotCountEWIncreased(){
    TrainingLine* currentTrainingLine=this->_trainingLine->back();
    currentTrainingLine->updateCountEW();
    currentTrainingLine->setToolTip(currentTrainingLine->getToolTipText());
}
void GraphEW::slotSceneNeedsSettingRectForExpand(qreal xError){
    this->_scene->setSceneRect(QRect(0,0,xError,this->_scene->height()));
}
void GraphEW::slotCheckBoxPreviousTrainings(int){
    while(this->_threadGraphEWObject->isRunning())QThread::msleep(1);

    if(this->_checkBoxPreviousTrainings->checkState()){
        GraphEW::getThreadGraphEWObject()->setOperationType(ThreadGraphEW::OperationType::DrawPreviousTrainings);
    }else{
        GraphEW::getThreadGraphEWObject()->setOperationType(ThreadGraphEW::OperationType::DrawPreviousEWOfCurrentTraining);
    }

    GraphEW::getThreadGraphEWObject()->start();
}
void GraphEW::slotCheckBoxMaxEWBasedOnAllTrainings(int){
    while(this->_threadGraphEWObject->isRunning())QThread::msleep(1);

    if(this->_checkBoxMaxEWBasedOnAllTrainings->checkState()){
         GraphEW::getThreadGraphEWObject()->setYEWActualMaxBasedOnAllTrainings(true);
    }else{
         GraphEW::getThreadGraphEWObject()->setYEWActualMaxBasedOnAllTrainings(false);
    }

    if(GraphEW::getThreadGraphEWObject()->getOperationType()==ThreadGraphEW::OperationType::DrawNewEW)
        GraphEW::getThreadGraphEWObject()->setOperationType(ThreadGraphEW::OperationType::DrawPreviousEWOfCurrentTraining);

    GraphEW::getThreadGraphEWObject()->start();
}
bool GraphEW::getScrolling()const{
    return this->_scrolling;
}
qreal GraphEW::getSceneWidth()const{
    return this->_scene->width();
}
qreal GraphEW::getSceneHeight()const{
    return this->_scene->height();
}
qreal GraphEW::getViewWidth()const{
    return this->_view->width();
}
qreal GraphEW::getPenTrainingWidth()const{
    return this->_penTraining.width();
}
ThreadGraphEW* GraphEW::getThreadGraphEWObject(){
    return GraphEW::_threadGraphEWObject;
}
void GraphEW::slotScrollBarMoved(int){this->_scrolling=true;}
void GraphEW::slotScrollBarPressed(){this->_scrolling=true;}
void GraphEW::slotScrollBarReleased(){this->_scrolling=false;}
