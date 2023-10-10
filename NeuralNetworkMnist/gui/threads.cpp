#include"gui/defines_gui.h"
#include"gui/threads.h"
#include"gui/graph_ew.h"
#include"gui/form_main.h"
#include<thread>

ThreadWidgetRowOperation::ThreadWidgetRowOperation(){}
ThreadWidgetRowOperation::~ThreadWidgetRowOperation(){}
void ThreadWidgetRowOperation::run(){

    if(this->_operationType==OperationType::AddRow){
        this->_addRow(this->_countRow);
    }else if(this->_operationType==OperationType::RemoveRow){
        this->_removeRow(this->_countRow);
    }
}
void ThreadWidgetRowOperation::setOperationType(const OperationType &operationType, const int &countRow){
    this->_operationType=operationType;
    this->_countRow=countRow;
}
void ThreadWidgetRowOperation::_removeRow(const int& countRow){
    for(int i=0;i<countRow;i++){
        emit this->signalDeleteWidgetsInRow();
        emit this->signalWidgetScrollAreaSetHeight(this->_operationType);
    }
    emit this->signalOperationFinished();
}
void ThreadWidgetRowOperation::_addRow(const int& countRow){
    for(int i=0;i<countRow;i++){
        emit this->signalCreateWidgetsInRow();
        emit this->signalWidgetScrollAreaSetHeight(this->_operationType);
    }
    emit this->signalOperationFinished();
}

ThreadDiagramNN::ThreadDiagramNN(const FormMain * const parentGUI):_parentGUI(parentGUI){}
ThreadDiagramNN::~ThreadDiagramNN(){}
void ThreadDiagramNN::run(){

    if(!FormMain::NeuralNetworkObject())return;

    emit this->signalPrepareGraphicScene();

    bool shorten;
    int countInputCell;
    int countInputDot;

    if(FormMain::NeuralNetworkObject()->getInputLayerPattern()->getTotalLength()<MAX_COUNT_CELL_IN_DIAGRAM){
        shorten=false;
        countInputCell=FormMain::NeuralNetworkObject()->getInputLayerPattern()->getTotalLength();
        countInputDot=0;
    }else{
        shorten=true;
        countInputCell=COUNT_SHORTENED_CELL_IN_DIAGRAM;
        countInputDot=COUNT_DOT;
    }
    QVector<qreal>* xInputCell=new QVector<qreal>(countInputCell);
    QVector<qreal>* yInputCell=new QVector<qreal>(countInputCell);
    QVector<qreal>* xInputDot=new QVector<qreal>(countInputDot);
    QVector<qreal>* yInputDot=new QVector<qreal>(countInputDot);

    QVector<qreal>*xBiasCell=new QVector<qreal>(FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()+1);
    QVector<qreal>*yBiasCell=new QVector<qreal>(FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()+1);

    qreal yIncrease=(this->_parentGUI->getGraphicsView()->height()-2*this->_parentGUI->getGraphicsView()->frameWidth()-2*this->_parentGUI->getPaddingGraphicScene())/(qreal)(this->_parentGUI->getMaxCountCell()-1);
    qreal xIncrease=(this->_parentGUI->getGraphicsView()->width()-2*this->_parentGUI->getGraphicsView()->frameWidth()-2*this->_parentGUI->getPaddingGraphicScene())/(FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()+1);
    qreal x=this->_parentGUI->getPaddingGraphicScene();
    qreal y=this->_parentGUI->getPaddingGraphicScene()+((qreal)(this->_parentGUI->getMaxCountCell()-(countInputCell+countInputDot+1))/2)*yIncrease;

    if(shorten){
        int counterCell=0;
        int counterDot=0;
        for(int i=0;i<countInputCell+countInputDot;i++){
            if(i<countInputCell-1 || i==countInputCell+countInputDot-1){
                (*xInputCell)[counterCell]=x-this->_parentGUI->getRCell()/2;
                (*yInputCell)[counterCell++]=y-this->_parentGUI->getRCell()/2;
            }else{
                (*xInputDot)[counterDot]=x-this->_parentGUI->getRDot()/2;
                (*yInputDot)[counterDot++]=y-this->_parentGUI->getRDot()/2;
            }
            y+=yIncrease;
        }
    }else{
        for(int i=0;i<countInputCell;i++){
            (*xInputCell)[i]=x-this->_parentGUI->getRCell()/2;
            (*yInputCell)[i]=y-this->_parentGUI->getRCell()/2;
            y+=yIncrease;
        }

    }

    (*xBiasCell)[0]=x-this->_parentGUI->getRCell()/2;
    (*yBiasCell)[0]=y-this->_parentGUI->getRCell()/2;
    x+=xIncrease;

    QVector<QVector<qreal>*>*xHiddenCell=new QVector<QVector<qreal>*>(FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer());
    QVector<QVector<qreal>*>*yHiddenCell=new QVector<QVector<qreal>*>(FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer());
    QVector<QVector<qreal>*>*xHiddenDot=new QVector<QVector<qreal>*>(FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer());
    QVector<QVector<qreal>*>*yHiddenDot=new QVector<QVector<qreal>*>(FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer());

    int countHiddenCell[FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()];
    int countHiddenDot[FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()];
    for(size_t i=0;i<FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer();i++){

        if(FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountCell(i)<MAX_COUNT_CELL_IN_DIAGRAM){
            shorten=false;
            countHiddenCell[i]=FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountCell(i);
            countHiddenDot[i]=0;
        }else{
            shorten=true;
            countHiddenCell[i]=COUNT_SHORTENED_CELL_IN_DIAGRAM;
            countHiddenDot[i]=COUNT_DOT;
        }

        (*xHiddenCell)[i]=new QVector<qreal>(countHiddenCell[i]);
        (*yHiddenCell)[i]=new QVector<qreal>(countHiddenCell[i]);
        (*xHiddenDot)[i]=new QVector<qreal>(countHiddenDot[i]);
        (*yHiddenDot)[i]=new QVector<qreal>(countHiddenDot[i]);

        y=this->_parentGUI->getPaddingGraphicScene()+((qreal)(this->_parentGUI->getMaxCountCell()-(countHiddenCell[i]+countHiddenDot[i]+1))/2)*yIncrease;

        if(shorten){
            int counterCell=0;
            int counterDot=0;
            for(int j=0;j<countHiddenCell[i]+countHiddenDot[i];j++){
                if(j<countHiddenCell[i]-1 || j==countHiddenCell[i]+countHiddenDot[i]-1){
                    (*(*xHiddenCell)[i])[counterCell]=x-this->_parentGUI->getRCell()/2;
                    (*(*yHiddenCell)[i])[counterCell++]=y-this->_parentGUI->getRCell()/2;
                }else{
                    (*(*xHiddenDot)[i])[counterDot]=x-this->_parentGUI->getRDot()/2;
                    (*(*yHiddenDot)[i])[counterDot++]=y-this->_parentGUI->getRDot()/2;
                }
                y+=yIncrease;
            }
        }else{
            for(int j=0;j<countHiddenCell[i];j++){
                (*(*xHiddenCell)[i])[j]=x-this->_parentGUI->getRCell()/2;
                (*(*yHiddenCell)[i])[j]=y-this->_parentGUI->getRCell()/2;
                y+=yIncrease;
            }
        }

        (*xBiasCell)[i+1]=x-this->_parentGUI->getRCell()/2;
        (*yBiasCell)[i+1]=y-this->_parentGUI->getRCell()/2;
        x+=xIncrease;
    }

    int countOutputCell;
    int countOutputDot;

    if(FormMain::NeuralNetworkObject()->getOutputLayerPattern()->getTotalLength()<MAX_COUNT_CELL_IN_DIAGRAM){
        shorten=false;
        countOutputCell=FormMain::NeuralNetworkObject()->getOutputLayerPattern()->getTotalLength();
        countOutputDot=0;
    }else{
        shorten=true;
        countOutputCell=COUNT_SHORTENED_CELL_IN_DIAGRAM;
        countOutputDot=COUNT_DOT;
    }

    QVector<qreal>*xOutputCell=new QVector<qreal>(countOutputCell);
    QVector<qreal>*yOutputCell=new QVector<qreal>(countOutputCell);
    QVector<qreal>*xOutputDot=new QVector<qreal>(countOutputDot);
    QVector<qreal>*yOutputDot=new QVector<qreal>(countOutputDot);

    y=this->_parentGUI->getPaddingGraphicScene()+((qreal)(this->_parentGUI->getMaxCountCell()-(countOutputCell+countOutputDot))/2)*yIncrease;

    if(shorten){
        int counterCell=0;
        int counterDot=0;
        for(int i=0;i<countOutputCell+countOutputDot;i++){
            if(i<countOutputCell-1 || i==countOutputCell+countOutputDot-1){
                (*xOutputCell)[counterCell]=x-this->_parentGUI->getRCell()/2;
                (*yOutputCell)[counterCell++]=y-this->_parentGUI->getRCell()/2;
            }else{
                (*xOutputDot)[counterDot]=x-this->_parentGUI->getRDot()/2;
                (*yOutputDot)[counterDot++]=y-this->_parentGUI->getRDot()/2;
            }
            y+=yIncrease;
        }
    }else{
        for(int i=0;i<countOutputCell;i++){
            (*xOutputCell)[i]=x-this->_parentGUI->getRCell()/2;
            (*yOutputCell)[i]=y-this->_parentGUI->getRCell()/2;
            y+=yIncrease;
        }
    }

    for(int i=0;i<countInputCell;i++){
        for(int j=0;j<countHiddenCell[0];j++){
            emit this->signalAddLine((*xInputCell)[i]+this->_parentGUI->getRCell()/2,(*yInputCell)[i]+this->_parentGUI->getRCell()/2,(*(*xHiddenCell)[0])[j]+this->_parentGUI->getRCell()/2,(*(*yHiddenCell)[0])[j]+this->_parentGUI->getRCell()/2,this->_parentGUI->getPenLine());
        }
        emit this->signalAddEllipse((*xInputCell)[i],(*yInputCell)[i],this->_parentGUI->getRCell(),this->_parentGUI->getRCell(),this->_parentGUI->getPenEllipse(),this->_parentGUI->getBrushInputCell());
    }

    for(int i=0;i<countInputDot;i++){
        emit this->signalAddEllipse((*xInputDot)[i],(*yInputDot)[i],this->_parentGUI->getRDot(),this->_parentGUI->getRDot(),this->_parentGUI->getPenEllipse(),this->_parentGUI->getBrushInputCell());
    }

    for(int j=0;j<countHiddenCell[0];j++){
        emit this->signalAddLine((*xBiasCell)[0]+this->_parentGUI->getRCell()/2,(*yBiasCell)[0]+this->_parentGUI->getRCell()/2,(*(*xHiddenCell)[0])[j]+this->_parentGUI->getRCell()/2,(*(*yHiddenCell)[0])[j]+this->_parentGUI->getRCell()/2,this->_parentGUI->getPenLine());
    }
    emit this->signalAddEllipse((*xBiasCell)[0],(*yBiasCell)[0],this->_parentGUI->getRCell(),this->_parentGUI->getRCell(),this->_parentGUI->getPenEllipse(),this->_parentGUI->getBrushBiasCell());


    for(size_t i=0;i<FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()-1;i++){
        for(int j=0;j<countHiddenCell[i];j++){
            for(int k=0;k<countHiddenCell[i+1];k++){
                emit this->signalAddLine((*(*xHiddenCell)[i])[j]+this->_parentGUI->getRCell()/2,(*(*yHiddenCell)[i])[j]+this->_parentGUI->getRCell()/2,(*(*xHiddenCell)[i+1])[k]+this->_parentGUI->getRCell()/2,(*(*yHiddenCell)[i+1])[k]+this->_parentGUI->getRCell()/2,this->_parentGUI->getPenLine());
            }
        }
        for(int k=0;k<countHiddenCell[i+1];k++){
            emit this->signalAddLine((*xBiasCell)[i+1]+this->_parentGUI->getRCell()/2,(*yBiasCell)[i+1]+this->_parentGUI->getRCell()/2,(*(*xHiddenCell)[i+1])[k]+this->_parentGUI->getRCell()/2,(*(*yHiddenCell)[i+1])[k]+this->_parentGUI->getRCell()/2,this->_parentGUI->getPenLine());
        }
    }

    for(int i=0;i<countHiddenCell[FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()-1];i++){
        for(int j=0;j<countOutputCell;j++){
            emit this->signalAddLine((*(*xHiddenCell)[FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()-1])[i]+this->_parentGUI->getRCell()/2,(*(*yHiddenCell)[FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()-1])[i]+this->_parentGUI->getRCell()/2,(*xOutputCell)[j]+this->_parentGUI->getRCell()/2,(*yOutputCell)[j]+this->_parentGUI->getRCell()/2,this->_parentGUI->getPenLine());
        }
    }

    for(int i=0;i<countOutputCell;i++){
        emit this->signalAddLine((*xBiasCell)[FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()]+this->_parentGUI->getRCell()/2,(*yBiasCell)[FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer()]+this->_parentGUI->getRCell()/2,(*xOutputCell)[i]+this->_parentGUI->getRCell()/2,(*yOutputCell)[i]+this->_parentGUI->getRCell()/2,this->_parentGUI->getPenLine());
        emit this->signalAddEllipse((*xOutputCell)[i],(*yOutputCell)[i],this->_parentGUI->getRCell(),this->_parentGUI->getRCell(),this->_parentGUI->getPenEllipse(),this->_parentGUI->getBrushOutputCell());
    }

    for(int i=0;i<countOutputDot;i++){
        emit this->signalAddEllipse((*xOutputDot)[i],(*yOutputDot)[i],this->_parentGUI->getRDot(),this->_parentGUI->getRDot(),this->_parentGUI->getPenEllipse(),this->_parentGUI->getBrushOutputCell());
    }

    for(size_t i=0;i<FormMain::NeuralNetworkObject()->getHiddenLayerPattern()->getCountLayer();i++){
        for(int j=0;j<countHiddenCell[i];j++){
            emit this->signalAddEllipse((*(*xHiddenCell)[i])[j],(*(*yHiddenCell)[i])[j],this->_parentGUI->getRCell(),this->_parentGUI->getRCell(),this->_parentGUI->getPenEllipse(),this->_parentGUI->getBrushHiddenCell());
        }
        emit this->signalAddEllipse((*xBiasCell)[i+1],(*yBiasCell)[i+1],this->_parentGUI->getRCell(),this->_parentGUI->getRCell(),this->_parentGUI->getPenEllipse(),this->_parentGUI->getBrushBiasCell());

        for(int j=0;j<countHiddenDot[i];j++){
            emit this->signalAddEllipse((*(*xHiddenDot)[i])[j],(*(*yHiddenDot)[i])[j],this->_parentGUI->getRDot(),this->_parentGUI->getRDot(),this->_parentGUI->getPenEllipse(),this->_parentGUI->getBrushHiddenCell());
        }
    }

    xInputCell->clear();
    yInputCell->clear();
    xInputDot->clear();
    yInputDot->clear();
    delete xInputCell;
    delete yInputCell;
    delete xInputDot;
    delete yInputDot;

    xBiasCell->clear();
    delete xBiasCell;
    yBiasCell->clear();
    delete yBiasCell;

    while(xHiddenCell->size()>0){
        xHiddenCell->back()->clear();
        delete xHiddenCell->back();
        xHiddenCell->pop_back();
    }
    delete xHiddenCell;
    while(yHiddenCell->size()>0){
        yHiddenCell->back()->clear();
        delete yHiddenCell->back();
        yHiddenCell->pop_back();
    }
    delete yHiddenCell;
    while(xHiddenDot->size()>0){
        xHiddenDot->back()->clear();
        delete xHiddenDot->back();
        xHiddenDot->pop_back();
    }
    delete xHiddenDot;
    while(yHiddenDot->size()>0){
        yHiddenDot->back()->clear();
        delete yHiddenDot->back();
        yHiddenDot->pop_back();
    }
    delete yHiddenDot;

    xOutputCell->clear();
    yOutputCell->clear();
    xOutputDot->clear();
    yOutputDot->clear();
    delete xOutputCell;
    delete yOutputCell;
    delete xOutputDot;
    delete yOutputDot;
}


ThreadGraphEW::ThreadGraphEW(const GraphEW*const parentGUI):_parentGUI(parentGUI){
    this->_xPreviousTrainingVirtual=new QVector<qreal>();
    this->_yTopTrainingVirtual=ERROR_GRAPH_YGRAPHMIN;
    this->_yBottomTrainingVirtual=this->_parentGUI->getSceneHeight()-ERROR_GRAPH_YGRAPHMIN;

    this->_yEWActualMaxBasedOnAllTrainings=true;
    this->_yWeightActualMaxAllTrainings=ERROR_GRAPH_INITIAL_WEIGHTACTUALMAX;
    this->_yErrorActualMaxAllTrainings=ERROR_GRAPH_INITIAL_ERRORACTUALMAX;
    this->_yWeightActualMaxCurrentTraining=ERROR_GRAPH_INITIAL_WEIGHTACTUALMAX;
    this->_yErrorActualMaxCurrentTraining=ERROR_GRAPH_INITIAL_ERRORACTUALMAX;
    this->_yErrorActualMaxPreviousTrainings=new QVector<qreal>();
    this->_yWeightActualMaxPreviousTrainings=new QVector<qreal>();

    this->_xPreviousEWVirtual=new QVector<QVector<qreal>*>();

    this->_yPreviousErrorActual=new QVector<QVector<qreal>*>();
    this->_yPreviousErrorVirtual=new QVector<QVector<qreal>*>();
    this->_yCurrentErrorVirtual=new QVector<qreal>();
    this->_yErrorActualMin=ERROR_GRAPH_YMIN;

    this->_yErrorVirtualMin=ERROR_GRAPH_YGRAPHMIN;
    this->_yErrorVirtualMax=this->_parentGUI->getSceneHeight()-ERROR_GRAPH_YGRAPHMIN;

    this->_yPreviousWeightActual=new QVector<QVector<qreal>*>();
    this->_yPreviousWeightVirtual=new QVector<QVector<qreal>*>();
    this->_yCurrentWeightVirtual=new QVector<qreal>();
    this->_yWeightActualMin=ERROR_GRAPH_YMIN;
    this->_yWeightVirtualMin=ERROR_GRAPH_YGRAPHMIN;
    this->_yWeightVirtualMax=this->_parentGUI->getSceneHeight()-ERROR_GRAPH_YGRAPHMIN;
    this->_xCurrentEWVirtual=new QVector<qreal>();

    this->_isReadyToDrawNewEW=false;
    this->_isDrawingNewEWFinished=true;
    this->_stopAllDrawings=false;

    this->_loadYEWActualMaxPreviousTrainings();
    this->_checkYEWActualMaxAllTrainingsWithPreviousTrainings();
}
ThreadGraphEW::~ThreadGraphEW(){
    this->_clearPreviousContainers();
    this->_clearCurrentContainers();
    delete _xPreviousTrainingVirtual;
    delete _xPreviousEWVirtual;
    delete _xCurrentEWVirtual;
    delete _yPreviousErrorActual;
    delete _yPreviousErrorVirtual;
    delete _yCurrentErrorVirtual;
    delete _yPreviousWeightActual;
    delete _yPreviousWeightVirtual;
    delete _yCurrentWeightVirtual;

    this->_yErrorActualMaxPreviousTrainings->clear();
    delete this->_yErrorActualMaxPreviousTrainings;
    this->_yWeightActualMaxPreviousTrainings->clear();
    delete this->_yWeightActualMaxPreviousTrainings;
}
bool ThreadGraphEW::isReadyToDrawNewEW()const{
    return this->_isReadyToDrawNewEW;
}
bool ThreadGraphEW::isDrawingNewEWFinished()const{
    return this->_isDrawingNewEWFinished;
}
bool ThreadGraphEW::isNewEWMaximum()const{
    return this->_isNewEWMaximum;
}
void ThreadGraphEW::setOperationType(const OperationType& operationType){
    this->_operationType=operationType;

    if(operationType==OperationType::DrawNewEW)
    {
        FormMain::NeuralNetworkObject()->getMutex()->lock();
        this->_isDrawingNewEWFinished=false;
        FormMain::NeuralNetworkObject()->getMutex()->unlock();
    }
}
ThreadGraphEW::OperationType ThreadGraphEW::getOperationType()const{
    return this->_operationType;
}
void ThreadGraphEW::setStopAllDrawings(const bool& stop){
    this->_stopAllDrawings=stop;
}
void ThreadGraphEW::setYEWActualMaxBasedOnAllTrainings(const bool& basedOnAllTrainnigs){
    this->_yEWActualMaxBasedOnAllTrainings=basedOnAllTrainnigs;
}
void ThreadGraphEW::run(){
    switch(this->_operationType){
    case OperationType::DrawPreviousTrainings:
        this->_drawEWOfPreviousTrainings();
        break;
    case OperationType::DrawPreviousEWOfCurrentTraining:
        this->_drawPreviousEWOfCurrentTraining();
        break;
    case OperationType::DrawNewEW:
        this->_drawNewEW();
        break;
    }
}
void ThreadGraphEW::_clearPreviousContainers(){

    this->_xPreviousTrainingVirtual->clear();

    while(this->_xPreviousEWVirtual->size()>0){
        this->_xPreviousEWVirtual->back()->clear();
        delete this->_xPreviousEWVirtual->back();
        this->_xPreviousEWVirtual->pop_back();
    }

    while(this->_yPreviousErrorActual->size()>0){
        this->_yPreviousErrorActual->back()->clear();
        delete this->_yPreviousErrorActual->back();
        this->_yPreviousErrorActual->pop_back();

        this->_yPreviousWeightActual->back()->clear();
        delete this->_yPreviousWeightActual->back();
        this->_yPreviousWeightActual->pop_back();
    }

    while(this->_yPreviousErrorVirtual->size()>0){
        this->_yPreviousErrorVirtual->back()->clear();
        delete this->_yPreviousErrorVirtual->back();
        this->_yPreviousErrorVirtual->pop_back();

        this->_yPreviousWeightVirtual->back()->clear();
        delete this->_yPreviousWeightVirtual->back();
        this->_yPreviousWeightVirtual->pop_back();
    }
}
void ThreadGraphEW::_clearCurrentContainers(){
    this->_xCurrentEWVirtual->clear();
    this->_yCurrentErrorVirtual->clear();
    this->_yCurrentWeightVirtual->clear();
}

void ThreadGraphEW::_drawEWOfPreviousTrainings(){

    emit signalPrepareDraw();

    this->_isReadyToDrawNewEW=false;
    this->_clearPreviousContainers();

    this->_loadEWFromPreviousTrainings();

    this->_calculateXVirtualIncForPreviousTrainings();

    this->_xCurrent=0;

    for(size_t i=0;i<FormMain::NeuralNetworkObject()->getLogEW()->getCountTraining();i++){

        this->_xCurrent+=this->_parentGUI->getPenTrainingWidth()/2;
        this->_xPreviousTrainingVirtual->push_back(this->_xCurrent);
        this->_xCurrent+=this->_parentGUI->getPenTrainingWidth()/2;

        this->_controlOwerflowXVirtual(this->_xPreviousTrainingVirtual->back()+this->_parentGUI->getPenTrainingWidth()/2);

        emit signalTrainingLineCreated(true,i,(*this->_xPreviousTrainingVirtual)[i],this->_yTopTrainingVirtual,(*this->_xPreviousTrainingVirtual)[i],this->_yBottomTrainingVirtual);

        if(FormMain::NeuralNetworkObject()->getLogEW()->getCountEWInATraining(i)==0){
            this->_xCurrent+=ERROR_GRAPH_SPACE_BETWEEN_TRAININGS;
            continue;
        }

        this->_xPreviousEWVirtual->push_back(new QVector<qreal>());
        this->_yPreviousErrorVirtual->push_back(new QVector<qreal>());
        this->_yPreviousWeightVirtual->push_back(new QVector<qreal>());

        qreal yErrorActualMax;
        qreal yWeightActualMax;
        if(this->_yEWActualMaxBasedOnAllTrainings){
            yErrorActualMax=this->_yErrorActualMaxAllTrainings;
            yWeightActualMax=this->_yWeightActualMaxAllTrainings;
        }else{            
            yErrorActualMax=(*this->_yErrorActualMaxPreviousTrainings)[i];
            yWeightActualMax=(*this->_yWeightActualMaxPreviousTrainings)[i];
        }

        for(size_t j=0;j<FormMain::NeuralNetworkObject()->getLogEW()->getCountEWInATraining(i);j++){

            this->usleep(1);
            if(this->_stopAllDrawings)return;

            this->_xPreviousEWVirtual->back()->push_back(this->_xCurrent);

            this->_yPreviousErrorVirtual->back()->push_back(this->_calculateYErrorVirtual((*(*_yPreviousErrorActual)[i])[j],yErrorActualMax));
            this->_yPreviousWeightVirtual->back()->push_back(this->_calculateYWeightVirtual((*(*_yPreviousWeightActual)[i])[j],yWeightActualMax));
            this->_controlOwerflowXVirtual((*_xPreviousEWVirtual->back())[j]);

            emit signalErrorEllipseCreated((*this->_xPreviousEWVirtual->back())[j],this->_parentGUI->getSceneHeight()-(*this->_yPreviousErrorVirtual->back())[j]);
            emit signalWeightEllipseCreated((*this->_xPreviousEWVirtual->back())[j],this->_parentGUI->getSceneHeight()-(*this->_yPreviousWeightVirtual->back())[j]);

            this->_xCurrent+=this->_xVirtualInc;
        }
        if(FormMain::NeuralNetworkObject()->getLogEW()->getCountEWInATraining(i)>1){
            for(size_t j=0;j<FormMain::NeuralNetworkObject()->getLogEW()->getCountEWInATraining(i)-1;j++){

                this->usleep(1);
                if(this->_stopAllDrawings)return;

                emit signalErrorLineCreated((*this->_xPreviousEWVirtual->back())[j],this->_parentGUI->getSceneHeight()-(*this->_yPreviousErrorVirtual->back())[j],(*this->_xPreviousEWVirtual->back())[j+1],this->_parentGUI->getSceneHeight()-(*this->_yPreviousErrorVirtual->back())[j+1]);
                emit signalWeightLineCreated((*this->_xPreviousEWVirtual->back())[j],this->_parentGUI->getSceneHeight()-(*this->_yPreviousWeightVirtual->back())[j],(*this->_xPreviousEWVirtual->back())[j+1],this->_parentGUI->getSceneHeight()-(*this->_yPreviousWeightVirtual->back())[j+1]);
            }
        }

        this->_xCurrent+=ERROR_GRAPH_SPACE_BETWEEN_TRAININGS-this->_xVirtualInc;
    }

    emit signalDrawCompleted();
}
void ThreadGraphEW::_drawPreviousEWOfCurrentTraining(){
    if(FormMain::NeuralNetworkObject()->getActionMode()!=NeuralNetwork::ActionMode::Train)return;

    FormMain::NeuralNetworkObject()->getMutex()->lock();

    emit signalPrepareDraw();
    this->_isReadyToDrawNewEW=false;
    this->_isNewEWMaximum=false;
    this->_clearCurrentContainers();
    this->_loadYEWActualMaxCurrentTraining();
    this->_checkYEWActualMaxAllTrainingsWithCurrentTraining();

    this->_xCurrent=0;

    this->_xVirtualInc=ERROR_GRAPH_CURRENT_TRAINING_X_INC;

    this->_xCurrent+=this->_parentGUI->getPenTrainingWidth()/2;
    this->_xCurrentTrainingVirtual=this->_xCurrent;
    this->_xCurrent+=this->_parentGUI->getPenTrainingWidth()/2;

    emit signalTrainingLineCreated(false,FormMain::NeuralNetworkObject()->getLogEW()->getCountTraining(),this->_xCurrentTrainingVirtual,this->_yTopTrainingVirtual,this->_xCurrentTrainingVirtual,this->_yBottomTrainingVirtual);

    if(this->_parentGUI->getParentForm()->getErrorValues()->size()==0){
        if(FormMain::NeuralNetworkObject()->getActionMode()==NeuralNetwork::ActionMode::Train){
            this->_isReadyToDrawNewEW=true;
        }
        emit signalDrawCompleted();
        FormMain::NeuralNetworkObject()->getMutex()->unlock();
        return;
    }

    qreal yErrorActualMax;
    qreal yWeightActualMax;
    if(this->_yEWActualMaxBasedOnAllTrainings){
        yErrorActualMax=this->_yErrorActualMaxAllTrainings;
        yWeightActualMax=this->_yWeightActualMaxAllTrainings;
    }else{
        yErrorActualMax=this->_yErrorActualMaxCurrentTraining;
        yWeightActualMax=this->_yWeightActualMaxCurrentTraining;
    }
    for(int i=0;i<this->_parentGUI->getParentForm()->getErrorValues()->size();i++){

        this->usleep(1);
        if(this->_stopAllDrawings){
            FormMain::NeuralNetworkObject()->getMutex()->unlock();
            return;
        }

        this->_xCurrentEWVirtual->push_back(this->_xCurrent);
        this->_yCurrentErrorVirtual->push_back(this->_calculateYErrorVirtual((*this->_parentGUI->getParentForm()->getErrorValues())[i],yErrorActualMax));
        this->_yCurrentWeightVirtual->push_back(this->_calculateYWeightVirtual((*this->_parentGUI->getParentForm()->getUpdatedWeights())[i],yWeightActualMax));
        this->_controlOwerflowXVirtual((*this->_xCurrentEWVirtual)[i]);

        emit signalErrorEllipseCreated((*this->_xCurrentEWVirtual)[i],this->_parentGUI->getSceneHeight()-(*this->_yCurrentErrorVirtual)[i]);
        emit signalWeightEllipseCreated((*this->_xCurrentEWVirtual)[i],this->_parentGUI->getSceneHeight()-(*this->_yCurrentWeightVirtual)[i]);

        this->_xCurrent+=this->_xVirtualInc;
    }
    if(this->_parentGUI->getParentForm()->getErrorValues()->size()>1){
        for(int i=0;i<this->_parentGUI->getParentForm()->getErrorValues()->size()-1;i++){

            this->usleep(1);
            if(this->_stopAllDrawings){
                FormMain::NeuralNetworkObject()->getMutex()->unlock();
                return;
            }

            emit signalErrorLineCreated((*this->_xCurrentEWVirtual)[i],this->_parentGUI->getSceneHeight()-(*this->_yCurrentErrorVirtual)[i],(*this->_xCurrentEWVirtual)[i+1],this->_parentGUI->getSceneHeight()-(*this->_yCurrentErrorVirtual)[i+1]);
            emit signalWeightLineCreated((*this->_xCurrentEWVirtual)[i],this->_parentGUI->getSceneHeight()-(*this->_yCurrentWeightVirtual)[i],(*this->_xCurrentEWVirtual)[i+1],this->_parentGUI->getSceneHeight()-(*this->_yCurrentWeightVirtual)[i+1]);
        }
    }

    emit signalDrawCompleted();

    if(FormMain::NeuralNetworkObject()->getActionMode()==NeuralNetwork::ActionMode::Train){
        this->_isReadyToDrawNewEW=true;
    }

    FormMain::NeuralNetworkObject()->getMutex()->unlock();
}
void ThreadGraphEW::_drawNewEW(){
    this->_isNewEWMaximum=this->_checkIfMaxEWIsNewEW();
    if(this->_isNewEWMaximum){
        this->_clearCurrentContainers();
        return;
    }

    qreal yErrorActualMax;
    qreal yWeightActualMax;
    if(this->_yEWActualMaxBasedOnAllTrainings){
        yErrorActualMax=this->_yErrorActualMaxAllTrainings;
        yWeightActualMax=this->_yWeightActualMaxAllTrainings;
    }else{
        yErrorActualMax=this->_yErrorActualMaxCurrentTraining;
        yWeightActualMax=this->_yWeightActualMaxCurrentTraining;
    }

    FormMain::NeuralNetworkObject()->getMutex()->lock();

    this->_xCurrentEWVirtual->push_back(this->_xCurrent);
    this->_yCurrentErrorVirtual->push_back(this->_calculateYErrorVirtual(this->_parentGUI->getParentForm()->getErrorValues()->back(),yErrorActualMax));
    this->_yCurrentWeightVirtual->push_back(this->_calculateYWeightVirtual(this->_parentGUI->getParentForm()->getUpdatedWeights()->back(),yWeightActualMax));
    this->_controlOwerflowXVirtual(this->_xCurrentEWVirtual->back());

    emit signalErrorEllipseCreated(this->_xCurrentEWVirtual->back(),this->_parentGUI->getSceneHeight()-this->_yCurrentErrorVirtual->back());
    emit signalWeightEllipseCreated(this->_xCurrentEWVirtual->back(),this->_parentGUI->getSceneHeight()-this->_yCurrentWeightVirtual->back());
    emit signalCountEWIncreased();

    if(this->_xCurrentEWVirtual->size()>1){
        emit signalErrorLineCreated(this->_xCurrentEWVirtual->back(),this->_parentGUI->getSceneHeight()-this->_yCurrentErrorVirtual->back(),(*this->_xCurrentEWVirtual)[this->_xCurrentEWVirtual->size()-2],this->_parentGUI->getSceneHeight()-(*this->_yCurrentErrorVirtual)[this->_yCurrentErrorVirtual->size()-2]);
        emit signalWeightLineCreated(this->_xCurrentEWVirtual->back(),this->_parentGUI->getSceneHeight()-this->_yCurrentWeightVirtual->back(),(*this->_xCurrentEWVirtual)[this->_xCurrentEWVirtual->size()-2],this->_parentGUI->getSceneHeight()-(*this->_yCurrentWeightVirtual)[this->_yCurrentWeightVirtual->size()-2]);
    }

    emit signalDrawCompleted();
    this->_xCurrent+=this->_xVirtualInc;

    this->_isDrawingNewEWFinished=true;

    this->usleep(1);
    if(!this->_stopAllDrawings)
        this->_isReadyToDrawNewEW=true;

    FormMain::NeuralNetworkObject()->getMutex()->unlock();
}

void ThreadGraphEW::_controlOwerflowXVirtual(const qreal& x){
    if(this->_parentGUI->getSceneWidth()<x)
        emit signalSceneNeedsSettingRectForExpand(x);
}
void ThreadGraphEW::_loadYEWActualMaxPreviousTrainings(){
    FormMain::NeuralNetworkObject()->getMutex()->lock();
    size_t countPreviousTraining=FormMain::NeuralNetworkObject()->getLogEW()->getCountTraining();
    FormMain::NeuralNetworkObject()->getMutex()->unlock();

    for(size_t i=0;i<countPreviousTraining;i++){
        this->_yErrorActualMaxPreviousTrainings->push_back(ERROR_GRAPH_INITIAL_ERRORACTUALMAX);
        this->_yWeightActualMaxPreviousTrainings->push_back(ERROR_GRAPH_INITIAL_WEIGHTACTUALMAX);
        FormMain::NeuralNetworkObject()->getMutex()->lock();
        size_t countEW=FormMain::NeuralNetworkObject()->getLogEW()->getCountEWInATraining(i);
        FormMain::NeuralNetworkObject()->getMutex()->unlock();

        for(size_t j=0;j<countEW;j++){
            FormMain::NeuralNetworkObject()->getMutex()->lock();
            qreal yPreviousErrorActual=FormMain::NeuralNetworkObject()->getLogEW()->getErrorValue(i,j);
            qreal yPreviousWeightActual=FormMain::NeuralNetworkObject()->getLogEW()->getUpdatedWeight(i,j);
            FormMain::NeuralNetworkObject()->getMutex()->unlock();

            if(yPreviousErrorActual>this->_yErrorActualMaxPreviousTrainings->back())
                this->_yErrorActualMaxPreviousTrainings->back()=yPreviousErrorActual;

            if(yPreviousWeightActual>this->_yWeightActualMaxPreviousTrainings->back())
                this->_yWeightActualMaxPreviousTrainings->back()=yPreviousWeightActual;
        }
    }
}
void ThreadGraphEW::_checkYEWActualMaxAllTrainingsWithPreviousTrainings(){
    for(int i=0;i<this->_yErrorActualMaxPreviousTrainings->size();i++){
        if((*this->_yErrorActualMaxPreviousTrainings)[i]>this->_yErrorActualMaxAllTrainings)
            this->_yErrorActualMaxAllTrainings=(*this->_yErrorActualMaxPreviousTrainings)[i];

        if((*this->_yWeightActualMaxPreviousTrainings)[i]>this->_yWeightActualMaxAllTrainings)
            this->_yWeightActualMaxAllTrainings=(*this->_yWeightActualMaxPreviousTrainings)[i];
    }
}
void ThreadGraphEW::_loadEWFromPreviousTrainings(){
    FormMain::NeuralNetworkObject()->getMutex()->lock();
    size_t countPreviousTraining=FormMain::NeuralNetworkObject()->getLogEW()->getCountTraining();
    FormMain::NeuralNetworkObject()->getMutex()->unlock();

    for(size_t i=0;i<countPreviousTraining;i++){
        FormMain::NeuralNetworkObject()->getMutex()->lock();
        size_t countEW=FormMain::NeuralNetworkObject()->getLogEW()->getCountEWInATraining(i);
        FormMain::NeuralNetworkObject()->getMutex()->unlock();

        this->_yPreviousErrorActual->push_back(new QVector<qreal>(countEW));
        this->_yPreviousWeightActual->push_back(new QVector<qreal>(countEW));

        for(size_t j=0;j<countEW;j++){
            FormMain::NeuralNetworkObject()->getMutex()->lock();
            (*this->_yPreviousErrorActual->back())[j]=FormMain::NeuralNetworkObject()->getLogEW()->getErrorValue(i,j);
            (*this->_yPreviousWeightActual->back())[j]=FormMain::NeuralNetworkObject()->getLogEW()->getUpdatedWeight(i,j);
            FormMain::NeuralNetworkObject()->getMutex()->unlock();
        }
    }
}
void ThreadGraphEW::_loadYEWActualMaxCurrentTraining(){
    for(int i=0;i<this->_parentGUI->getParentForm()->getErrorValues()->size();i++){
        if((*this->_parentGUI->getParentForm()->getErrorValues())[i]>this->_yErrorActualMaxCurrentTraining)
            this->_yErrorActualMaxCurrentTraining=(*this->_parentGUI->getParentForm()->getErrorValues())[i];

        if((*this->_parentGUI->getParentForm()->getUpdatedWeights())[i]>this->_yWeightActualMaxCurrentTraining)
            this->_yWeightActualMaxCurrentTraining=(*this->_parentGUI->getParentForm()->getUpdatedWeights())[i];
    }
}
void ThreadGraphEW::_checkYEWActualMaxAllTrainingsWithCurrentTraining(){
    if(this->_yErrorActualMaxCurrentTraining>this->_yErrorActualMaxAllTrainings)
        this->_yErrorActualMaxAllTrainings=this->_yErrorActualMaxCurrentTraining;

    if(this->_yWeightActualMaxCurrentTraining>this->_yWeightActualMaxAllTrainings)
        this->_yWeightActualMaxAllTrainings=this->_yWeightActualMaxCurrentTraining;
}
bool ThreadGraphEW::_checkIfMaxEWIsNewEW(){
    double newError=this->_parentGUI->getParentForm()->getErrorValues()->back();
    size_t newWeight=this->_parentGUI->getParentForm()->getUpdatedWeights()->back();

    bool result=false;
    if(this->_yEWActualMaxBasedOnAllTrainings){
        if(newError>this->_yErrorActualMaxAllTrainings||newWeight>this->_yWeightActualMaxAllTrainings)
            result=true;
    }else{
        if(newError>this->_yErrorActualMaxCurrentTraining||newWeight>this->_yWeightActualMaxCurrentTraining)
            result=true;
    }

    if(newError>this->_yErrorActualMaxCurrentTraining)
        this->_yErrorActualMaxCurrentTraining=newError;

    if(newError>this->_yErrorActualMaxAllTrainings)
        this->_yErrorActualMaxAllTrainings=newError;

    if(newWeight>this->_yWeightActualMaxCurrentTraining)
        this->_yWeightActualMaxCurrentTraining=newWeight;

    if(newWeight>this->_yWeightActualMaxAllTrainings)
        this->_yWeightActualMaxAllTrainings=newWeight;

    return result;
}
void ThreadGraphEW::_calculateXVirtualIncForPreviousTrainings(){
    size_t countPreviousTraining=this->_yPreviousErrorActual->size();
    double totalPreviousTrainingLinesWidth=countPreviousTraining*this->_parentGUI->getPenTrainingWidth();
    double totalSpaceBetweenPreviousTrainings=(countPreviousTraining-1)*ERROR_GRAPH_SPACE_BETWEEN_TRAININGS;

    qreal newXInc=this->_parentGUI->getViewWidth()-totalPreviousTrainingLinesWidth-totalSpaceBetweenPreviousTrainings;
    size_t countEW=0;
    for(size_t i=0;i<countPreviousTraining;i++){
        if((*this->_yPreviousErrorActual)[i]->size()>0)
            countEW+=(*this->_yPreviousErrorActual)[i]->size()-1;
    }
    newXInc/=countEW;
    newXInc-=ERROR_GRAPH_EW_ELLIPSE_R/(qreal)countEW;

    this->_xVirtualInc=newXInc;
}
qreal ThreadGraphEW::_calculateYErrorVirtual(const qreal& yErrorActual,const qreal& yErrorActualMax){
    return this->_yErrorVirtualMin+(yErrorActual-this->_yErrorActualMin)*(this->_yErrorVirtualMax-this->_yErrorVirtualMin)/(yErrorActualMax-this->_yErrorActualMin);
}
qreal ThreadGraphEW::_calculateYWeightVirtual(const qreal& yWeightActual,const qreal& yWeightActualMax){
    return this->_yWeightVirtualMin+(yWeightActual-this->_yWeightActualMin)*(this->_yWeightVirtualMax-this->_yWeightVirtualMin)/(yWeightActualMax-this->_yWeightActualMin);
}

ThreadSampleImages::ThreadSampleImages(const FormSamplesFile*const parentGUI):_parentGUI(parentGUI){
    this->_images=new QVector<QImage*>();
    this->_imageDigits=new QVector<int>();
    this->_resultImage=nullptr;
    this->_pixmap=nullptr;
}
ThreadSampleImages::~ThreadSampleImages(){
    while(this->_images->size()>0){
        delete this->_images->back();
        this->_images->pop_back();
    }
    delete this->_images;

    this->_imageDigits->clear();
    delete this->_imageDigits;

    if(this->_resultImage)
        delete this->_resultImage;

    if(this->_pixmap)
        delete this->_pixmap;
}
void ThreadSampleImages::run(){
    if(this->_operationType==OperationType::Fill){
        const int*const* imagesArr;

        try {
            imagesArr=FormMain::NeuralNetworkObject()->getImageAsArray(this->_parentGUI->getCountImage(),this->_parentGUI->getSamplesFile());
        }catch (std::exception& e) {
            emit signalFillImagesError();
            return;
        }

        int counterPixel=0;
        for(int i=0;i<this->_parentGUI->getCountImage();i++){
            this->_images->push_back(new QImage(IMAGE_WIDTH,IMAGE_HEIGHT,QImage::Format_Mono));
            for(int j=0;j<IMAGE_WIDTH;j++){
                for(int k=0;k<IMAGE_HEIGHT;k++){
                    this->_images->back()->setPixel(k,j,imagesArr[i][counterPixel]);
                    counterPixel++;
                }
            }

            this->_imageDigits->push_back(imagesArr[i][IMAGE_WIDTH*IMAGE_HEIGHT]);
            counterPixel=0;
        }

        for(int i=0;i<this->_parentGUI->getCountImage();i++)
            delete[] imagesArr[i];
        delete[]imagesArr;

        emit signalFillImagesFinished();

    }else if(this->_operationType==OperationType::Draw){
        QVector<int>* digitIndexes=new QVector<int>();
        for(int i=0;i<this->_parentGUI->getCountImage();i++){
            if(this->_parentGUI->getImageDigitValue()==this->_imageDigits->at(i)){
                digitIndexes->push_back(i);
            }
        }
        this->_columnCountResultImage=RESULT_IMAGE_COLUMN_COUNT;
        this->_rowCountResultImage=std::ceil((double)digitIndexes->size()/(double)this->_columnCountResultImage);
        if(this->_rowCountResultImage==0)this->_rowCountResultImage++;

        emit signalPrepareImageGUI(this->_rowCountResultImage,this->_columnCountResultImage);

        while(!this->_parentGUI->isSceneImageReady())
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if(this->_resultImage)
            delete this->_resultImage;

        this->_resultImage=new QImage(this->_parentGUI->getSceneImageWidth(),this->_parentGUI->getSceneImageHeight(),QImage::Format_Mono);
        this->_resultImage->fill(0);

        QPainter* painter=new QPainter(this->_resultImage);

        int pixelX=0;
        int pixelY=0;

        for(int i=0;i<digitIndexes->size();i++){
            painter->drawImage(pixelX,pixelY,*this->_images->at(digitIndexes->at(i)));
            pixelX+=IMAGE_WIDTH;
            if((i+1)%this->_columnCountResultImage==0){
                pixelY+=IMAGE_HEIGHT;
                pixelX=0;
            }
        }

        if(this->_pixmap)
            delete this->_pixmap;

        this->_pixmap=new QPixmap(QPixmap::fromImage(*this->_resultImage));

        emit signalDrawImage(*this->_pixmap);

        digitIndexes->clear();
        delete digitIndexes;

        delete painter;
    }
}

void ThreadSampleImages::setOperationType(const ThreadSampleImages::OperationType& operationType){
    this->_operationType=operationType;
}
