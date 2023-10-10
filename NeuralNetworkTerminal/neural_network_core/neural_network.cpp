#include"neural_network.h"
#include<iostream>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<iomanip>
#include <csignal>
#include"../kbhit.h"

//-------------------------------------------------
InputLayerPattern::InputLayerPattern(const size_t& countOriginal,const Data::Type*const types,const Data::Limit*const*const limits){

    this->_countOriginal=countOriginal;
    this->_types=new Data::Type[this->_countOriginal];
    this->_limits=new Data::Limit*[this->_countOriginal];
    this->_lengths=new size_t[this->_countOriginal];
    this->_totalLength=INT_0;

    for(size_t i=INT_0;i<this->_countOriginal;i++){
        this->_types[i]=types[i];
        this->_limits[i]=new Data::Limit(limits[i]);

        size_t length=TransformedData::length(types[i],limits[i]->getOriginalMax());

        this->_totalLength+=length;
        this->_lengths[i]=length;
    }

}
InputLayerPattern::InputLayerPattern(const size_t& countOriginal,const Data::Type& type,const Data::Limit& limit){
    this->_countOriginal=countOriginal;
    this->_types=new Data::Type[this->_countOriginal];
    this->_limits=new Data::Limit*[this->_countOriginal];
    this->_lengths=new size_t[this->_countOriginal];
    this->_totalLength=INT_0;

    size_t length=TransformedData::length(type,limit.getOriginalMax());

    for(size_t i=INT_0;i<this->_countOriginal;i++){
        this->_types[i]=type;
        this->_limits[i]=new Data::Limit(limit);

        this->_totalLength+=length;
        this->_lengths[i]=length;
    }
}
InputLayerPattern::InputLayerPattern(const InputLayerPattern& inputLayerPatternObj){
    this->_countOriginal=inputLayerPatternObj._countOriginal;
    this->_types=new Data::Type[this->_countOriginal];
    this->_limits=new Data::Limit*[this->_countOriginal];
    this->_lengths=new size_t[this->_countOriginal];
    this->_totalLength=INT_0;

    for(size_t i=INT_0;i<this->_countOriginal;i++){
        this->_types[i]=inputLayerPatternObj._types[i];
        this->_limits[i]=new Data::Limit(*inputLayerPatternObj._limits[i]);

        size_t length=TransformedData::length(inputLayerPatternObj._types[i],inputLayerPatternObj._limits[i]->getOriginalMax());

        this->_totalLength+=length;
        this->_lengths[i]=length;
    }
}
InputLayerPattern::~InputLayerPattern(){

    for(size_t i=INT_0;i<this->_countOriginal;i++){
        delete this->_limits[i];
    }
    delete[] this->_limits;
    delete[] this->_types;

    delete[] this->_lengths;
}
size_t InputLayerPattern::getCountOriginal()const{
    return this->_countOriginal;
}
size_t InputLayerPattern::getLength(const size_t& index)const{
    return this->_lengths[index];
}
size_t InputLayerPattern::getTotalLength()const{
    return this->_totalLength;
}
Data::Type InputLayerPattern::getType(const size_t& index)const{
    return this->_types[index];
}
const Data::Limit* InputLayerPattern::getLimit(const size_t& index)const{
    return this->_limits[index];
}
TransformedData** InputLayerPattern::createSample(const int*const originals)const{

    TransformedData** datas=new TransformedData*[this->_countOriginal];
    for(size_t i=INT_0;i<this->_countOriginal;i++){
        switch(this->_types[i]){
        case Data::Type::Binary:
            datas[i]=new TransformedData(new Binary(originals[i],this->_limits[i]->getOriginalMax()));
            break;
        case Data::Type::Flag:
            datas[i]=new TransformedData(new Flag(originals[i],this->_limits[i]->getOriginalMax()));
            break;
        case Data::Type::Narrowed:
            datas[i]=new TransformedData(new Narrowed(originals[i],this->_limits[i]->getOriginalMin(),this->_limits[i]->getOriginalMax()));
            break;
        case Data::Type::Native:
            datas[i]=new TransformedData(new Native(originals[i]));
            break;
        }
    }
    return datas;
}
//-------------------------------------------------
OutputLayerPattern::OutputLayerPattern(const size_t& countOriginal,const Data::Type*const types,const Data::Limit*const*const limits,const double*const tolerances,const Cell::SummationFunction::Type& sumFuncType,const Cell::ActivationFunction::Type& actFuncType)
    :InputLayerPattern(countOriginal,types,limits)
{
    this->_tolerances=new double[this->_countOriginal];
    for(size_t i=INT_0;i<this->_countOriginal;i++)
        this->_tolerances[i]=tolerances[i];

    this->_sumFunc=new Cell::SummationFunction(sumFuncType);
    this->_actFunc=new Cell::ActivationFunction(actFuncType);
}
OutputLayerPattern::OutputLayerPattern(const size_t& countOriginal,const Data::Type& type,const Data::Limit& limit,const double& tolerance,const Cell::SummationFunction::Type& sumFuncType,const Cell::ActivationFunction::Type& actFuncType)
    :InputLayerPattern(countOriginal,type,limit)
{
    this->_tolerances=new double[this->_countOriginal];
    for(size_t i=INT_0;i<this->_countOriginal;i++)
        this->_tolerances[i]=tolerance;

    this->_sumFunc=new Cell::SummationFunction(sumFuncType);
    this->_actFunc=new Cell::ActivationFunction(actFuncType);
}
OutputLayerPattern::OutputLayerPattern(const OutputLayerPattern& outputLayerPatternObj)
    :InputLayerPattern((InputLayerPattern)outputLayerPatternObj){
    this->_tolerances=new double[this->_countOriginal];
    for(size_t i=INT_0;i<this->_countOriginal;i++)
        this->_tolerances[i]=outputLayerPatternObj._tolerances[i];

    this->_sumFunc=new Cell::SummationFunction(outputLayerPatternObj._sumFunc->getType());
    this->_actFunc=new Cell::ActivationFunction(outputLayerPatternObj._actFunc->getType());
}
OutputLayerPattern::~OutputLayerPattern(){
    delete[] this->_tolerances;
    delete this->_sumFunc;
    delete this->_actFunc;
}
double OutputLayerPattern::getTolerance(const size_t& index)const{
    return this->_tolerances[index];
}
int NeuralNetwork::getEpoch()const{
    return this->_epoch;
}
const Cell::SummationFunction* OutputLayerPattern::getSumFunc()const{
    return this->_sumFunc;
}
const Cell::ActivationFunction* OutputLayerPattern::getActFunc()const{
    return this->_actFunc;
}
void OutputLayerPattern::setSumFunc(const Cell::SummationFunction::Type& sumFuncType){
    delete this->_sumFunc;
    this->_sumFunc=new Cell::SummationFunction(sumFuncType);
}
void OutputLayerPattern::setActFunc(const Cell::ActivationFunction::Type& actFuncType){
    double scaledMin=Cell::ActivationFunction::rangeMin(actFuncType);
    double scaledMax=Cell::ActivationFunction::rangeMax(actFuncType);
    for(size_t i=0;i<this->_countOriginal;i++){
        this->_limits[i]->setScaledMin(LayerType::Output,scaledMin);
        this->_limits[i]->setScaledMax(LayerType::Output,scaledMax);
    }
    delete this->_actFunc;
    this->_actFunc=new Cell::ActivationFunction(actFuncType);
}
void OutputLayerPattern::setTolerance(const size_t& index,const double& tolerance){
    this->_tolerances[index]=tolerance;
}
//-------------------------------------------------
HiddenLayerPattern::HiddenLayerPattern(const size_t& countLayer,const size_t*const countsCell,const Cell::SummationFunction::Type*const sumFuncTypes,const Cell::ActivationFunction::Type*const actFuncTypes){
    this->_countLayer=countLayer;
    this->_countsCell=new size_t[this->_countLayer];
    this->_sumFuncs=new Cell::SummationFunction*[this->_countLayer];
    this->_actFuncs=new Cell::ActivationFunction*[this->_countLayer];

    for(size_t i=INT_0;i<this->_countLayer;i++){
        this->_countsCell[i]=countsCell[i];
        this->_sumFuncs[i]=new Cell::SummationFunction(sumFuncTypes[i]);
        this->_actFuncs[i]=new Cell::ActivationFunction(actFuncTypes[i]);
    }
}
HiddenLayerPattern::HiddenLayerPattern(const HiddenLayerPattern& hiddenLayerPatternObj){
    this->_countLayer=hiddenLayerPatternObj._countLayer;
    this->_countsCell=new size_t[this->_countLayer];
    this->_sumFuncs=new Cell::SummationFunction*[this->_countLayer];
    this->_actFuncs=new Cell::ActivationFunction*[this->_countLayer];

    for(size_t i=INT_0;i<this->_countLayer;i++){
        this->_countsCell[i]=hiddenLayerPatternObj._countsCell[i];
        this->_sumFuncs[i]=new Cell::SummationFunction(hiddenLayerPatternObj._sumFuncs[i]->getType());
        this->_actFuncs[i]=new Cell::ActivationFunction(hiddenLayerPatternObj._actFuncs[i]->getType());
    }
}
HiddenLayerPattern::~HiddenLayerPattern(){
    delete[] this->_countsCell;
    for(size_t i=INT_0;i<this->_countLayer;i++){
        delete this->_sumFuncs[i];
        delete this->_actFuncs[i];
    }
    delete[] this->_sumFuncs;
    delete[] this->_actFuncs;
}
size_t HiddenLayerPattern::getCountLayer()const{
    return this->_countLayer;
}
size_t HiddenLayerPattern::getCountCell(const size_t& index)const{
    return this->_countsCell[index];
}
const Cell::SummationFunction* HiddenLayerPattern::getSumFunc(const size_t& index)const{
    return this->_sumFuncs[index];
}
const Cell::ActivationFunction* HiddenLayerPattern::getActFunc(const size_t& index)const{
    return this->_actFuncs[index];
}
void HiddenLayerPattern::setSumFunc(const size_t& index,const Cell::SummationFunction::Type& sumFuncType){
    delete this->_sumFuncs[index];
    this->_sumFuncs[index]=new Cell::SummationFunction(sumFuncType);
}
void HiddenLayerPattern::setActFunc(const size_t& index,const Cell::ActivationFunction::Type& actFuncType){
    delete this->_actFuncs[index];
    this->_actFuncs[index]=new Cell::ActivationFunction(actFuncType);
}
//-------------------------------------------------
LogEW::LogEW(const std::string& fileEW,const HiddenLayerPattern*const hiddenLayerPatternOfNN,const OutputLayerPattern*const outputLayerPatternOfNN,const char*const separatorOfNN,const double*const lambdaOfNN,const double*const alfaOfNN)
    :_hiddenLayerPatternOfNN(hiddenLayerPatternOfNN),_outputLayerPatternOfNN(outputLayerPatternOfNN),_separatorOfNN(separatorOfNN),_lambdaOfNN(lambdaOfNN),_alfaOfNN(alfaOfNN){
    this->_file=fileEW;

    this->_countTraining=INT_0;
    this->loadTrainingsFromFile();

    this->_newErrorValue=DOUBLE_NEG_1;
    this->_newUpdatedWeight=INT_0;
}
LogEW::~LogEW(){
    this->_clearData(this->_countTraining);
}
void LogEW::_clearData(size_t countLoadedTrainig){
    for(size_t i=INT_0;i<countLoadedTrainig;i++){
        delete[] this->_sumFuncTypesOfHiddenLayer[i];
        delete[] this->_actFuncTypesOfHiddenLayer[i];
        delete[] this->_tolerances[i];
        delete[] this->_errorValues[i];
        delete[] this->_updatedWeights[i];
    }
    if(countLoadedTrainig>0){
        delete[] this->_sumFuncTypesOfHiddenLayer;
        delete[] this->_actFuncTypesOfHiddenLayer;
        delete[] this->_sumFuncTypesOfOutputLayer;
        delete[] this->_actFuncTypesOfOutputLayer;
        delete[] this->_tolerances;
        delete[] this->_lambdas;
        delete[] this->_alfas;
        delete[] this->_countsSample;
        delete[] this->_countsEW;
        delete[] this->_errorValues;
        delete[] this->_updatedWeights;
    }

    this->_newErrorValue=DOUBLE_NEG_1;
    this->_newUpdatedWeight=INT_0;
    this->_countTraining=INT_0;
}
void LogEW::createNewFile()const{
    std::ofstream oStream(this->_file,std::ios::out);
    oStream.close();
}
void LogEW::_loadOneTrainingFromFile(const size_t& indexTraining,const std::string& lineFromFile){
    size_t boundaryFuncTypesOfHiddenLayer=this->_hiddenLayerPatternOfNN->getCountLayer()*INT_POS_2;
    size_t boundaryFuncTypesOfOutputLayer=boundaryFuncTypesOfHiddenLayer+INT_POS_2;
    size_t boundaryTolerances=boundaryFuncTypesOfOutputLayer+this->_outputLayerPatternOfNN->getCountOriginal();
    size_t boundaryLambda=boundaryTolerances+INT_POS_1;
    size_t boundaryAlfa=boundaryLambda+INT_POS_1;
    size_t boundaryCountSample=boundaryAlfa+INT_POS_1;

    int countEWTotal=(std::count(lineFromFile.begin(),lineFromFile.end(),*this->_separatorOfNN)+INT_POS_1-boundaryCountSample);
    int countEW=countEWTotal/INT_POS_2;

    this->_sumFuncTypesOfHiddenLayer[indexTraining]=new Cell::SummationFunction::Type[this->_hiddenLayerPatternOfNN->getCountLayer()];
    this->_actFuncTypesOfHiddenLayer[indexTraining]=new Cell::ActivationFunction::Type[this->_hiddenLayerPatternOfNN->getCountLayer()];
    this->_tolerances[indexTraining]=new double[this->_outputLayerPatternOfNN->getCountOriginal()];


    if(countEWTotal<INT_0){
      this->_errorValues[indexTraining]=new double[INT_0];
      this->_updatedWeights[indexTraining]=new size_t[INT_0];

      this->_clearData(indexTraining+INT_POS_1);
      throw std::invalid_argument(THROW_MESSAGE_EW_FILE);
    }

    this->_errorValues[indexTraining]=new double[countEW];
    this->_updatedWeights[indexTraining]=new size_t[countEW];

    if(countEWTotal%INT_POS_2!=INT_0){
        this->_clearData(indexTraining+INT_POS_1);
        throw std::invalid_argument(THROW_MESSAGE_EW_FILE);
    }

    size_t startSubString=INT_0;
    size_t endSubString;
    size_t counterInLine=INT_0;

    size_t counterFuncTypesOfHiddenLayer=INT_0;
    size_t counterSumFuncTypesOfHiddenLayer=INT_0;
    size_t counterActFuncTypesOfHiddenLayer=INT_0;
    size_t counterFuncTypesOfOutputLayer=INT_0;
    size_t counterTolerance=INT_0;
    size_t counterEW=INT_0;

    this->_countsEW[indexTraining]=countEW;
    do{
        try {

            endSubString=lineFromFile.find(*this->_separatorOfNN,startSubString);

            if(counterInLine<boundaryFuncTypesOfHiddenLayer){
                if(counterFuncTypesOfHiddenLayer%INT_POS_2==INT_0){
                    this->_sumFuncTypesOfHiddenLayer[indexTraining][counterSumFuncTypesOfHiddenLayer]=(Cell::SummationFunction::Type)(std::stoi(lineFromFile.substr(startSubString,endSubString-startSubString)));
                    counterSumFuncTypesOfHiddenLayer++;
                }
                else{
                    this->_actFuncTypesOfHiddenLayer[indexTraining][counterActFuncTypesOfHiddenLayer]=(Cell::ActivationFunction::Type)(std::stoi(lineFromFile.substr(startSubString,endSubString-startSubString)));
                    counterActFuncTypesOfHiddenLayer++;
                }
                counterFuncTypesOfHiddenLayer++;
            }else if(counterInLine<boundaryFuncTypesOfOutputLayer){
                if(counterFuncTypesOfOutputLayer%INT_POS_2==INT_0){
                    this->_sumFuncTypesOfOutputLayer[indexTraining]=(Cell::SummationFunction::Type)(std::stoi(lineFromFile.substr(startSubString,endSubString-startSubString)));
                }else{
                    this->_actFuncTypesOfOutputLayer[indexTraining]=(Cell::ActivationFunction::Type)(std::stoi(lineFromFile.substr(startSubString,endSubString-startSubString)));
                }
                counterFuncTypesOfOutputLayer++;
            }else if(counterInLine<boundaryTolerances){
                this->_tolerances[indexTraining][counterTolerance]=std::stod(lineFromFile.substr(startSubString,endSubString-startSubString));
                counterTolerance++;
            }else if(counterInLine<boundaryLambda){
                this->_lambdas[indexTraining]=std::stod(lineFromFile.substr(startSubString,endSubString-startSubString));
            }else if(counterInLine<boundaryAlfa){
                this->_alfas[indexTraining]=std::stod(lineFromFile.substr(startSubString,endSubString-startSubString));
            }else if(counterInLine<boundaryCountSample){
                this->_countsSample[indexTraining]=std::stoi(lineFromFile.substr(startSubString,endSubString-startSubString));
            }else{
                this->_errorValues[indexTraining][counterEW]=std::stod(lineFromFile.substr(startSubString,endSubString-startSubString));
                startSubString=endSubString+INT_POS_1;
                endSubString=lineFromFile.find(*this->_separatorOfNN,startSubString);
                this->_updatedWeights[indexTraining][counterEW++]=std::stoi(lineFromFile.substr(startSubString,endSubString-startSubString));
            }
            startSubString=endSubString+INT_POS_1;
            counterInLine++;

        }  catch (std::exception&e) {
            this->_clearData(indexTraining+INT_POS_1);
            throw std::invalid_argument(THROW_MESSAGE_EW_FILE);
        }
    }while(endSubString!=std::string::npos);

}
void LogEW::loadTrainingsFromFile(){
    this->_clearData(this->_countTraining);

    std::ifstream iStream(this->_file,std::ios::in);
    std::string line=EMPTY_STRING;

    while(getline(iStream,line))
        this->_countTraining++;

    if(this->_countTraining==INT_0){
        iStream.close();
        return;
    }
    iStream.clear();
    iStream.seekg(0, std::ios::beg);

    this->_sumFuncTypesOfHiddenLayer=new Cell::SummationFunction::Type*[this->_countTraining];
    this->_actFuncTypesOfHiddenLayer=new Cell::ActivationFunction::Type*[this->_countTraining];
    this->_sumFuncTypesOfOutputLayer=new Cell::SummationFunction::Type[this->_countTraining];
    this->_actFuncTypesOfOutputLayer=new Cell::ActivationFunction::Type[this->_countTraining];
    this->_tolerances=new double*[this->_countTraining];
    this->_lambdas=new double[this->_countTraining];
    this->_alfas=new double[this->_countTraining];
    this->_countsSample=new int[this->_countTraining];
    this->_countsEW=new size_t[this->_countTraining];
    this->_errorValues=new double*[this->_countTraining];
    this->_updatedWeights=new size_t*[this->_countTraining];

    size_t counterTraining=INT_0;

    for(size_t i=0;i<this->_countTraining;i++){
        getline(iStream,line);
        try {
            this->_loadOneTrainingFromFile(counterTraining,line);
        }catch (std::exception&e) {
            iStream.close();
            throw e;
        }
        counterTraining++;
    }

    iStream.close();
}
void LogEW::addNewTrainingInFile(const int &countSample)const{
    std::ofstream oStream(this->_file,std::ios::app);
    if(!this->isFileEmpty())oStream<<NEW_LINE_CHAR;

    for(size_t i=0;i<this->_hiddenLayerPatternOfNN->getCountLayer();i++){
        oStream<<(int)this->_hiddenLayerPatternOfNN->getSumFunc(i)->getType()<<*this->_separatorOfNN;
        oStream<<(int)this->_hiddenLayerPatternOfNN->getActFunc(i)->getType()<<*this->_separatorOfNN;
    }

    oStream<<(int)this->_outputLayerPatternOfNN->getSumFunc()->getType()<<*this->_separatorOfNN;
    oStream<<(int)this->_outputLayerPatternOfNN->getActFunc()->getType()<<*this->_separatorOfNN;

    for(size_t i=0;i<this->_outputLayerPatternOfNN->getCountOriginal();i++){
        oStream<<this->_outputLayerPatternOfNN->getTolerance(i)<<*this->_separatorOfNN;
    }

    oStream<<*this->_lambdaOfNN<<*this->_separatorOfNN;
    oStream<<*this->_alfaOfNN<<*this->_separatorOfNN;
    oStream<<countSample;

    oStream.close();
}
void LogEW::addErrorInFile(const double& errorValue,const size_t& updatedWeight)const{
    std::ofstream oStream(this->_file,std::ios::app);
    oStream<<*this->_separatorOfNN<<errorValue<<*this->_separatorOfNN<<updatedWeight;
    oStream.close();
}
std::string LogEW::getFile()const{
    return this->_file;
}
bool LogEW::isFileEmpty()const{
    std::ifstream iStream(this->_file,std::ios::in);
    std::string line;

    if(getline(iStream,line)){
        iStream.close();
        return false;
    }

    iStream.close();
    return true;
}
size_t LogEW::getCountTraining()const{
    return this->_countTraining;
}
Cell::SummationFunction::Type LogEW::getSumFuncTypeOfHiddenLayer(const size_t& indexTraining,const size_t& indexHiddenLayer)const{
    return this->_sumFuncTypesOfHiddenLayer[indexTraining][indexHiddenLayer];
}
Cell::ActivationFunction::Type LogEW::getActFuncTypeOfHiddenLayer(const size_t& indexTraining,const size_t& indexHiddenLayer)const{
    return this->_actFuncTypesOfHiddenLayer[indexTraining][indexHiddenLayer];
}
Cell::SummationFunction::Type LogEW::getSumFuncTypeOfOutputLayer(const size_t& indexTraining)const{
    return this->_sumFuncTypesOfOutputLayer[indexTraining];
}
Cell::ActivationFunction::Type LogEW::getActFuncTypeOfOutputLayer(const size_t& indexTraining)const{
    return this->_actFuncTypesOfOutputLayer[indexTraining];
}
double LogEW::getTolerance(const size_t& indexTraining,const size_t& indexTolerance)const{
    return this->_tolerances[indexTraining][indexTolerance];
}
double LogEW::getLambda(const size_t& indexTraining)const{
    return this->_lambdas[indexTraining];
}
double LogEW::getAlfa(const size_t& indexTraining)const{
    return this->_alfas[indexTraining];
}
int LogEW::getCountSample(const size_t& indexTraining)const{
    return this->_countsSample[indexTraining];
}
size_t LogEW::getCountEWInATraining(const size_t& indexTraining)const{
    return this->_countsEW[indexTraining];
}
double LogEW::getErrorValue(const size_t& indexTraining,const size_t& indexErrorValue)const{
    return this->_errorValues[indexTraining][indexErrorValue];
}
size_t LogEW::getUpdatedWeight(const size_t& indexTraining,const size_t& indexUpdatedWeight)const{
    return this->_updatedWeights[indexTraining][indexUpdatedWeight];
}
void LogEW::setNewErrorValue(const double& errorValue){
    this->_newErrorValue=errorValue;
}
double LogEW::getNewErrorValue()const{
    return this->_newErrorValue;
}
void LogEW::setNewUpdatedWeight(const size_t& updatedWeight){
    this->_newUpdatedWeight=updatedWeight;
}
size_t LogEW::getNewUpdatedWeight()const{
    return this->_newUpdatedWeight;
}
//-------------------------------------------------
NeuralNetwork::NeuralNetwork(const double& lambda,const double& alfa,const InputLayerPattern& inputLayerPattern,const HiddenLayerPattern& hiddenLayerPattern,const OutputLayerPattern& outputLayerPattern,const std::string& parametersFile,const char& separator,const double& randomWeightMin,const double& randomWeightMax){
    std::setlocale(LC_ALL, "C");//ondalık sayı ayıracının . karakteri olması için...
    this->_lambda=lambda;
    this->_alfa=alfa;
    this->_epoch=INT_0;

    this->_inputLayerPattern=new InputLayerPattern(inputLayerPattern);
    this->_hiddenLayerPattern=new HiddenLayerPattern(hiddenLayerPattern);
    this->_outputLayerPattern=new OutputLayerPattern(outputLayerPattern);

    this->_countBiasCell=this->_hiddenLayerPattern->getCountLayer()+INT_POS_1;

    //input cell setup
    this->_inputCells=new InputCell*[this->_inputLayerPattern->getTotalLength()];
    for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++){
        this->_inputCells[i]=new InputCell();
    }

    //bias cells setup
    this->_biasCells=new BiasCell*[this->_countBiasCell];
    for(size_t i=INT_0;i<this->_countBiasCell;i++){
        this->_biasCells[i]=new BiasCell();
    }

    //hidden cells setup
    this->_hiddenCells=new HiddenCell**[this->_hiddenLayerPattern->getCountLayer()];

    //hiddenLayer0 setup
    this->_hiddenCells[INT_0]=new HiddenCell*[this->_hiddenLayerPattern->getCountCell(INT_0)];

    for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(INT_0);j++){
        this->_hiddenCells[INT_0][j]=new HiddenCell(this->_inputLayerPattern->getTotalLength()+INT_POS_1,randomWeightMin,randomWeightMax);
    }

    //hiddenLayer1,2,... setup
    for(size_t i=INT_POS_1;i<this->_hiddenLayerPattern->getCountLayer();i++){
        this->_hiddenCells[i]=new HiddenCell*[this->_hiddenLayerPattern->getCountCell(i)];
        for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(i);j++){
            this->_hiddenCells[i][j]=new HiddenCell(this->_hiddenLayerPattern->getCountCell(i-INT_POS_1)+INT_POS_1,randomWeightMin,randomWeightMax);
        }
    }

    //outputcells setup
    this->_outputCells=new OutputCell*[this->_outputLayerPattern->getTotalLength()];
    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
        this->_outputCells[i]=new OutputCell(this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)+INT_POS_1,randomWeightMin,randomWeightMax);
    }
    this->_separator=separator;
    this->_parametersFile=parametersFile;
    this->_logEW=new LogEW(parametersFile+SUFFIX_EW_FILE_NAME,this->_hiddenLayerPattern,this->_outputLayerPattern,&this->_separator,&this->_lambda,&this->_alfa);

    this->saveNeuralNetwork();
    this->_logEW->createNewFile();

}
NeuralNetwork::NeuralNetwork(const std::string& parametersFile,const char& separator){
    std::setlocale(LC_ALL, "C");//ondalık sayı ayıracının . karakteri olması için...

    this->_separator=separator;
    this->_parametersFile=parametersFile;

    std::ifstream iStream(this->_parametersFile,std::ios::in);
    std::string fileContents=EMPTY_STRING;
    getline(iStream,fileContents);
    iStream.close();

    size_t countParameter=std::count(fileContents.begin(),fileContents.end(),separator)+INT_POS_1;
    size_t counterParameter=INT_0;

    if(countParameter<COUNT_MIN_PARAMETERS){
        throw std::invalid_argument(THROW_MESSAGE_NEURALNETWORK_FILE);
    }

    std::string* parameters=new std::string[countParameter];

    size_t start=INT_0;
    size_t end;
    int parameterIndex=INT_0;

    do{
        end=fileContents.find(separator,start);
        std::string parameter=fileContents.substr(start,end-start);
        try {
            std::stod(parameter);
        }  catch (...) {
            delete[]parameters;
            throw std::invalid_argument(THROW_MESSAGE_NEURALNETWORK_FILE);
        }
        parameters[parameterIndex++]=parameter;
        start=end+INT_POS_1;
    }while(end!=std::string::npos);


    parameterIndex=INT_0;

    counterParameter++;
    size_t countOriginalInputValue=std::stoi(parameters[parameterIndex]);
    counterParameter+=countOriginalInputValue*COUNT_PARAMETER_OF_INPUT_LAYER_IN_FILE;

    if(countParameter<=counterParameter){
        delete[]parameters;
        throw std::invalid_argument(THROW_MESSAGE_NEURALNETWORK_FILE);
    }

    Data::Type* inputTypes=new Data::Type[countOriginalInputValue];
    Data::Limit** inputLimits=new Data::Limit*[countOriginalInputValue];

    for(size_t i=INT_0;i<countOriginalInputValue;i++){
        int originalMin;
        int originalMax;
        inputTypes[i]=(Data::Type)std::stoi(parameters[++parameterIndex]);
        originalMin=std::stoi(parameters[++parameterIndex]);
        originalMax=std::stoi(parameters[++parameterIndex]);

        if(inputTypes[i]==Data::Type::Native){
            inputLimits[i]=new Data::Limit(inputTypes[i],LayerType::Input);
        }else{
            inputLimits[i]=new Data::Limit(inputTypes[i],LayerType::Input,originalMin,originalMax);
        }
    }

    this->_inputLayerPattern=new InputLayerPattern(countOriginalInputValue,inputTypes,inputLimits);
    delete[]inputTypes;
    for(size_t i=INT_0;i<countOriginalInputValue;i++)delete inputLimits[i];
    delete[]inputLimits;

    counterParameter++;
    size_t countHiddenLayer=std::stoi(parameters[++parameterIndex]);
    counterParameter+=countHiddenLayer*COUNT_PARAMETER_OF_HIDDEN_LAYER_IN_FILE;

    if(countParameter<=counterParameter){
        delete[]parameters;
        delete this->_inputLayerPattern;
        throw std::invalid_argument(THROW_MESSAGE_NEURALNETWORK_FILE);
    }

    size_t* countsHiddenCell=new size_t[countHiddenLayer];
    Cell::SummationFunction::Type* sumFuncTypesOfHiddenLayers=new Cell::SummationFunction::Type[countHiddenLayer];
    Cell::ActivationFunction::Type* actFuncTypesOfHiddenLayers=new Cell::ActivationFunction::Type[countHiddenLayer];

    for(size_t i=INT_0;i<countHiddenLayer;i++){
        countsHiddenCell[i]=std::stoi(parameters[++parameterIndex]);
        sumFuncTypesOfHiddenLayers[i]=(Cell::SummationFunction::Type)std::stoi(parameters[++parameterIndex]);
        actFuncTypesOfHiddenLayers[i]=(Cell::ActivationFunction::Type)std::stoi(parameters[++parameterIndex]);
    }


    this->_hiddenLayerPattern=new HiddenLayerPattern(countHiddenLayer,countsHiddenCell,sumFuncTypesOfHiddenLayers,actFuncTypesOfHiddenLayers);
    delete[]countsHiddenCell;
    delete[]sumFuncTypesOfHiddenLayers;
    delete[]actFuncTypesOfHiddenLayers;

    counterParameter++;
    size_t countOriginalOutputValue=std::stoi(parameters[++parameterIndex]);
    counterParameter+=countOriginalOutputValue*COUNT_PARAMETER_OF_OUTPUT_LAYER_IN_FILE_LOOP+COUNT_PARAMETER_OF_OUTPUT_LAYER_IN_FILE;
    if(countParameter<=counterParameter){
        delete[]parameters;
        delete this->_inputLayerPattern;
        delete this->_hiddenLayerPattern;

        throw std::invalid_argument(THROW_MESSAGE_NEURALNETWORK_FILE);
    }

    Data::Type* outputTypes=new Data::Type[countOriginalOutputValue];
    Data::Limit** outputLimits=new Data::Limit*[countOriginalOutputValue];
    double* outputTolerances=new double[countOriginalOutputValue];
    Cell::SummationFunction::Type sumFuncTypeOfOutput;
    Cell::ActivationFunction::Type actFuncTypeOfOutput;

    for(size_t i=INT_0;i<countOriginalOutputValue;i++){

        outputTypes[i]=(Data::Type)std::stoi(parameters[++parameterIndex]);
        int originalMin=std::stoi(parameters[++parameterIndex]);
        int originalMax=std::stoi(parameters[++parameterIndex]);
        double scaledMin=std::stod(parameters[++parameterIndex]);
        double scaledMax=std::stod(parameters[++parameterIndex]);

        if(outputTypes[i]==Data::Type::Native){
            outputLimits[i]=new Data::Limit(outputTypes[i],LayerType::Output,scaledMin,scaledMax);
        }else{
            outputLimits[i]=new Data::Limit(outputTypes[i],LayerType::Output,originalMin,originalMax,scaledMin,scaledMax);
        }
        outputTolerances[i]=std::stod(parameters[++parameterIndex]);
    }
    sumFuncTypeOfOutput=(Cell::SummationFunction::Type)std::stoi(parameters[++parameterIndex]);
    actFuncTypeOfOutput=(Cell::ActivationFunction::Type)std::stoi(parameters[++parameterIndex]);

    this->_outputLayerPattern=new OutputLayerPattern(countOriginalOutputValue,outputTypes,outputLimits,outputTolerances,sumFuncTypeOfOutput,actFuncTypeOfOutput);
    delete[]outputTypes;
    for(size_t i=INT_0;i<countOriginalOutputValue;i++)delete outputLimits[i];
    delete[]outputLimits;
    delete[]outputTolerances;

    this->_countBiasCell=this->_hiddenLayerPattern->getCountLayer()+INT_POS_1;

    //input cell setup
    this->_inputCells=new InputCell*[this->_inputLayerPattern->getTotalLength()];
    for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++){
        this->_inputCells[i]=new InputCell();
    }

    //bias cells setup
    this->_biasCells=new BiasCell*[this->_countBiasCell];
    for(size_t i=INT_0;i<this->_countBiasCell;i++){
        this->_biasCells[i]=new BiasCell();
    }

    counterParameter+=this->_hiddenLayerPattern->getCountCell(INT_0)*(this->_inputLayerPattern->getTotalLength()+INT_POS_1);
    if(countParameter<=counterParameter){
        delete[]parameters;

        for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++){
            delete this->_inputCells[i];
        }
        delete[] this->_inputCells;
        delete this->_inputLayerPattern;

        for(size_t i=INT_0;i<this->_countBiasCell;i++){
            delete this->_biasCells[i];
        }
        delete[] this->_biasCells;
        delete this->_hiddenLayerPattern;
        delete this->_outputLayerPattern;

        throw std::invalid_argument(THROW_MESSAGE_NEURALNETWORK_FILE);
    }

    //hidden cells setup
    this->_hiddenCells=new HiddenCell**[this->_hiddenLayerPattern->getCountLayer()];
    //hiddenLayer0 setup
    this->_hiddenCells[INT_0]=new HiddenCell*[this->_hiddenLayerPattern->getCountCell(INT_0)];
    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(INT_0);i++){
        double* inputWeight=new double[this->_inputLayerPattern->getTotalLength()+INT_POS_1];
        for(size_t j=INT_0;j<this->_inputLayerPattern->getTotalLength()+INT_POS_1;j++){
            inputWeight[j]=std::stod(parameters[++parameterIndex]);
        }
        this->_hiddenCells[INT_0][i]=new HiddenCell(this->_inputLayerPattern->getTotalLength()+INT_POS_1,inputWeight);
        delete[] inputWeight;
    }

    for(size_t i=INT_POS_1;i<this->_hiddenLayerPattern->getCountLayer();i++){
        for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(i);j++){
            for(size_t k=INT_0;k<this->_hiddenLayerPattern->getCountCell(i-INT_POS_1)+INT_POS_1;k++){
                counterParameter++;
            }
        }
    }

    if(countParameter<=counterParameter){
        delete[]parameters;

        for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++){
            delete this->_inputCells[i];
        }
        delete[] this->_inputCells;
        delete this->_inputLayerPattern;

        for(size_t i=INT_0;i<this->_countBiasCell;i++){
            delete this->_biasCells[i];
        }
        delete[] this->_biasCells;

        for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(INT_0);i++){
            delete this->_hiddenCells[INT_0][i];
        }
        delete[] this->_hiddenCells[INT_0];
        delete[] this->_hiddenCells;
        delete this->_hiddenLayerPattern;

        delete this->_outputLayerPattern;

        throw std::invalid_argument(THROW_MESSAGE_NEURALNETWORK_FILE);
    }

    //hiddenLayer1,2,... setup
    for(size_t i=INT_POS_1;i<this->_hiddenLayerPattern->getCountLayer();i++){
        this->_hiddenCells[i]=new HiddenCell*[this->_hiddenLayerPattern->getCountCell(i)];
        for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(i);j++){
            double* inputWeight=new double[this->_hiddenLayerPattern->getCountCell(i-INT_POS_1)+INT_POS_1];
            for(size_t k=INT_0;k<this->_hiddenLayerPattern->getCountCell(i-INT_POS_1)+INT_POS_1;k++){
                inputWeight[k]=std::stod(parameters[++parameterIndex]);
            }
            this->_hiddenCells[i][j]=new HiddenCell(this->_hiddenLayerPattern->getCountCell(i-INT_POS_1)+INT_POS_1,inputWeight);
            delete[] inputWeight;
        }
    }


    counterParameter+=this->_outputLayerPattern->getTotalLength()*(this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)+INT_POS_1);

    if(countParameter<=counterParameter){
        delete[]parameters;

        for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++){
            delete this->_inputCells[i];
        }
        delete[] this->_inputCells;
        delete this->_inputLayerPattern;

        for(size_t i=INT_0;i<this->_countBiasCell;i++){
            delete this->_biasCells[i];
        }
        delete[] this->_biasCells;

        for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountLayer();i++){
            for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(i);j++){
                delete this->_hiddenCells[i][j];
            }
            delete[] this->_hiddenCells[i];
        }
        delete[] this->_hiddenCells;
        delete this->_hiddenLayerPattern;

        delete this->_outputLayerPattern;

        throw std::invalid_argument(THROW_MESSAGE_NEURALNETWORK_FILE);
    }

    //outputcells setup
    this->_outputCells=new OutputCell*[this->_outputLayerPattern->getTotalLength()];
    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
        double* inputWeight=new double[this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)+INT_POS_1];
        for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)+INT_POS_1;j++){
            inputWeight[j]=std::stod(parameters[++parameterIndex]);
        }
        this->_outputCells[i]=new OutputCell(this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)+INT_POS_1,inputWeight);
        delete[] inputWeight;
    }

    counterParameter+=COUNT_PARAMETER_OF_TRAINING_SETTINGS_IN_FILE;
    if(countParameter!=counterParameter){
        delete[]parameters;

        for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++){
            delete this->_inputCells[i];
        }
        delete[] this->_inputCells;
        delete this->_inputLayerPattern;

        for(size_t i=INT_0;i<this->_countBiasCell;i++){
            delete this->_biasCells[i];
        }
        delete[] this->_biasCells;

        for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountLayer();i++){
            for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(i);j++){
                delete this->_hiddenCells[i][j];
            }
            delete[] this->_hiddenCells[i];
        }
        delete[] this->_hiddenCells;
        delete this->_hiddenLayerPattern;

        for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
            delete this->_outputCells[i];
        }
        delete[]this->_outputCells;
        delete this->_outputLayerPattern;

        throw std::invalid_argument(THROW_MESSAGE_NEURALNETWORK_FILE);
    }

    this->_lambda=std::stod(parameters[++parameterIndex]);
    this->_alfa=std::stod(parameters[++parameterIndex]);
    this->_epoch=std::stoi(parameters[++parameterIndex]);

    try{
        this->_logEW=new LogEW(this->_parametersFile+SUFFIX_EW_FILE_NAME,this->_hiddenLayerPattern,this->_outputLayerPattern,&this->_separator,&this->_lambda,&this->_alfa);
    }catch(std::exception& e){
        delete[]parameters;

        for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++){
            delete this->_inputCells[i];
        }
        delete[] this->_inputCells;
        delete this->_inputLayerPattern;

        for(size_t i=INT_0;i<this->_countBiasCell;i++){
            delete this->_biasCells[i];
        }
        delete[] this->_biasCells;

        for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountLayer();i++){
            for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(i);j++){
                delete this->_hiddenCells[i][j];
            }
            delete[] this->_hiddenCells[i];
        }
        delete[] this->_hiddenCells;
        delete this->_hiddenLayerPattern;

        for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
            delete this->_outputCells[i];
        }
        delete[]this->_outputCells;
        delete this->_outputLayerPattern;
        throw std::invalid_argument(THROW_MESSAGE_EW_FILE);
    }

    delete[]parameters;
}
NeuralNetwork::~NeuralNetwork(){

    for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++){
        delete this->_inputCells[i];
    }
    delete[] this->_inputCells;
    delete this->_inputLayerPattern;

    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
        delete this->_outputCells[i];
    }
    delete[]this->_outputCells;
    delete this->_outputLayerPattern;

    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountLayer();i++){
        for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(i);j++){
            delete this->_hiddenCells[i][j];
        }
        delete[] this->_hiddenCells[i];
    }
    delete[] this->_hiddenCells;
    delete this->_hiddenLayerPattern;

    for(size_t i=INT_0;i<this->_countBiasCell;i++){
        delete this->_biasCells[i];
    }
    delete[] this->_biasCells;

    delete this->_logEW;
}

double NeuralNetwork::getLambda()const{
    return this->_lambda;
}
double NeuralNetwork::getAlfa()const{
    return this->_alfa;
}
char NeuralNetwork::getSeparator()const{
    return this->_separator;
}
std::string NeuralNetwork::getParametersFile()const{
    return this->_parametersFile;
}
const HiddenLayerPattern*  NeuralNetwork::getHiddenLayerPattern()const{
    return this->_hiddenLayerPattern;
}
const OutputLayerPattern*  NeuralNetwork::getOutputLayerPattern()const{
    return this->_outputLayerPattern;
}
const InputLayerPattern*  NeuralNetwork::getInputLayerPattern()const{
    return this->_inputLayerPattern;
}
const LogEW* NeuralNetwork::getLogEW()const{
    return this->_logEW;
}

void NeuralNetwork::setLambda(const double& lambda){
    this->_lambda=lambda;
}
void NeuralNetwork::setAlfa(const double& alfa){
    this->_alfa=alfa;
}
void NeuralNetwork::setSumFuncOfHiddenLayer(const size_t& index,const Cell::SummationFunction::Type& sumFuncType){
    this->_hiddenLayerPattern->setSumFunc(index,sumFuncType);
}
void NeuralNetwork::setActFuncOfHiddenLayer(const size_t& index,const Cell::ActivationFunction::Type& actFuncType){
    this->_hiddenLayerPattern->setActFunc(index,actFuncType);
}
void NeuralNetwork::setSumFuncOfOutputLayer(const Cell::SummationFunction::Type& sumFuncType){
    this->_outputLayerPattern->setSumFunc(sumFuncType);
}
void NeuralNetwork::setActFuncOfOutputLayer(const Cell::ActivationFunction::Type& actFuncType){
    this->_outputLayerPattern->setActFunc(actFuncType);
}
void NeuralNetwork::setTolerance(const size_t& index,const double& tolerance){
    this->_outputLayerPattern->setTolerance(index,tolerance);
}

int NeuralNetwork::_correctCountSampleInFile(const int& countSample, const std::string& samplesFile){
    int countFileLine=this->getCountLinesOfFile(samplesFile);
    if(countFileLine<countSample)
        return countFileLine;
    else
        return countSample;
}
const int*const* NeuralNetwork::_convertSamplesFileToArray(const int& countSample, const std::string& samplesFile){
    std::string* samplesOriginalString=new std::string[countSample];

    std::ifstream iStream(samplesFile,std::ios::in);
    std::string fileLine=EMPTY_STRING;

    for(int i=INT_0;i<countSample;i++){
        getline(iStream,fileLine);
        samplesOriginalString[i]=fileLine;
    }
    iStream.close();

    int** samplesOriginal=new int*[countSample];
    size_t countItemInLine=this->_inputLayerPattern->getCountOriginal()+this->_outputLayerPattern->getCountOriginal();

    for(int i=INT_0;i<countSample;i++){
        samplesOriginal[i]=new int[countItemInLine];
        std::string* line=new std::string[countItemInLine];

        size_t start=INT_0;
        size_t end;
        size_t counterInLine=INT_0;
        do{
            end=samplesOriginalString[i].find(this->_separator,start);
            if(counterInLine>=countItemInLine){
                delete[] line;
                delete[] samplesOriginalString;

                for(int k=INT_0;k<=i;k++){
                    delete[] samplesOriginal[k];
                }
                delete[] samplesOriginal;

                throw std::invalid_argument(THROW_MESSAGE_SAMPLES_FILE);
            }
            line[counterInLine++]=samplesOriginalString[i].substr(start,end-start);
            start=end+INT_POS_1;
        }while(end!=std::string::npos);

        for(size_t j=INT_0;j<countItemInLine;j++){
            std::string valueStr=line[j];
            try{
                samplesOriginal[i][j]=std::stoi(valueStr);
            }catch(std::exception& e){
                delete[] line;
                delete[] samplesOriginalString;

                for(int k=INT_0;k<=i;k++){
                    delete[] samplesOriginal[k];
                }
                delete[] samplesOriginal;

                throw std::invalid_argument(THROW_MESSAGE_SAMPLES_FILE);
            }
        }
        delete[] line;
    }
    delete[] samplesOriginalString;

    return samplesOriginal;
}
void NeuralNetwork::_calculateNetsOfHiddenLayer(const size_t& indexHiddenLayer){
    double* inputValue;

    if(indexHiddenLayer==INT_0){
        inputValue=new double[this->_inputLayerPattern->getTotalLength()+INT_POS_1];

        for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++){
            inputValue[i]=this->_inputCells[i]->getInput();
        }
        inputValue[this->_inputLayerPattern->getTotalLength()]=this->_biasCells[indexHiddenLayer]->getInput();
    }else{
        inputValue=new double[this->_hiddenLayerPattern->getCountCell(indexHiddenLayer-INT_POS_1)+INT_POS_1];

        for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(indexHiddenLayer-INT_POS_1);i++){
            inputValue[i]=this->_hiddenCells[indexHiddenLayer-INT_POS_1][i]->getOutput();
        }
        inputValue[this->_hiddenLayerPattern->getCountCell(indexHiddenLayer-INT_POS_1)]=this->_biasCells[indexHiddenLayer]->getInput();
    }

    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(indexHiddenLayer);i++){
        this->_hiddenCells[indexHiddenLayer][i]->calculateNet(this->_hiddenLayerPattern->getSumFunc(indexHiddenLayer),inputValue);
    }

    delete[] inputValue;
}
void NeuralNetwork::_calculateOutputsOfHiddenLayer(const size_t& indexHiddenLayer){
    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(indexHiddenLayer);i++){
        this->_hiddenCells[indexHiddenLayer][i]->calculateOutput(this->_hiddenLayerPattern->getActFunc(indexHiddenLayer));
    }
}
void NeuralNetwork::_calculateNetsOfOutputLayer(){
    double* inputValue=new double[this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)+INT_POS_1];

    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1);i++){
        inputValue[i]=this->_hiddenCells[this->_hiddenLayerPattern->getCountLayer()-INT_POS_1][i]->getOutput();
    }
    inputValue[this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)]=this->_biasCells[this->_hiddenLayerPattern->getCountLayer()]->getInput();

    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
        this->_outputCells[i]->calculateNet(this->_outputLayerPattern->getSumFunc(),inputValue);
    }

    delete[] inputValue;
}
void NeuralNetwork::_calculateOutputsOfOutputLayer(){
    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
        this->_outputCells[i]->calculateOutput(this->_outputLayerPattern->getActFunc());
    }
}
void NeuralNetwork::_calculateErrorsOfOutputLayer(){
    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
        this->_outputCells[i]->calculateError();
    }
}
void NeuralNetwork::_calculateDeltasOfOutputLayer(){
    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
        this->_outputCells[i]->calculateDelta(this->_outputLayerPattern->getActFunc());
    }
}
void NeuralNetwork::_calculateDeltasOfHiddenLayer(const size_t& indexHiddenLayer){
    if(indexHiddenLayer==this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)
        for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(indexHiddenLayer);i++)
            this->_hiddenCells[indexHiddenLayer][i]->calculateDelta(this->_hiddenLayerPattern->getActFunc(indexHiddenLayer),i,this->_outputLayerPattern->getTotalLength(),(const Cell*const*)(this->_outputCells));
    else
        for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(indexHiddenLayer);i++)
            this->_hiddenCells[indexHiddenLayer][i]->calculateDelta(this->_hiddenLayerPattern->getActFunc(indexHiddenLayer),i,this->_hiddenLayerPattern->getCountCell(indexHiddenLayer+INT_POS_1),(const Cell*const*)(this->_hiddenCells[indexHiddenLayer+INT_POS_1]));

}
void NeuralNetwork::_calculateDeltaInputWeightsOfOutputLayer(){
    double* previousLayerOutputs=new double[this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)+INT_POS_1];

    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1);i++)
        previousLayerOutputs[i]=this->_hiddenCells[this->_hiddenLayerPattern->getCountLayer()-INT_POS_1][i]->getOutput();

    previousLayerOutputs[this->_hiddenLayerPattern->getCountCell(this->_hiddenLayerPattern->getCountLayer()-INT_POS_1)]=this->_biasCells[this->_hiddenLayerPattern->getCountLayer()]->getInput();

    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++)
        this->_outputCells[i]->calculateDeltaInputWeight(this->_lambda,this->_alfa,previousLayerOutputs);

    delete[] previousLayerOutputs;
}
void NeuralNetwork::_calculateDeltaInputWeightsOfHiddenLayer(const size_t& indexHiddenLayer){
    double* previousLayerOutputs;

    if(indexHiddenLayer==INT_0){
        previousLayerOutputs=new double[this->_inputLayerPattern->getTotalLength()+INT_POS_1];
        for(size_t i=INT_0;i<this->_inputLayerPattern->getTotalLength();i++)
            previousLayerOutputs[i]=this->_inputCells[i]->getInput();
        previousLayerOutputs[this->_inputLayerPattern->getTotalLength()]=this->_biasCells[INT_0]->getInput();
    }else{
        previousLayerOutputs=new double[this->_hiddenLayerPattern->getCountCell(indexHiddenLayer-INT_POS_1)+INT_POS_1];
        for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(indexHiddenLayer-INT_POS_1);i++)
            previousLayerOutputs[i]=this->_hiddenCells[indexHiddenLayer-INT_POS_1][i]->getOutput();
        previousLayerOutputs[this->_hiddenLayerPattern->getCountCell(indexHiddenLayer-INT_POS_1)]=this->_biasCells[indexHiddenLayer]->getInput();
    }

    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(indexHiddenLayer);i++)
        this->_hiddenCells[indexHiddenLayer][i]->calculateDeltaInputWeight(this->_lambda,this->_alfa,previousLayerOutputs);

    delete[] previousLayerOutputs;
}
void NeuralNetwork::_updateInputWeightsOfOutputLayer(){
    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++)
        this->_outputCells[i]->updateInputWeight();
}
void NeuralNetwork::_updateInputWeightsOfHiddenLayer(const size_t& indexHiddenLayer){
    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountCell(indexHiddenLayer);i++)
        this->_hiddenCells[indexHiddenLayer][i]->updateInputWeight();
}
void NeuralNetwork::_deleteTrainingArrays(const int& countSample, const int*const*const trainingSamplesOriginal, const TransformedData*const*const*const trainingSamplesInputsTransformed, const TransformedData*const*const*const trainingSamplesOutputsTransformed){

    for(int i=INT_0;i<countSample;i++){
        delete[] trainingSamplesOriginal[i];
    }
    delete[] trainingSamplesOriginal;

    for(int i=INT_0;i<countSample;i++){
        for(size_t j=INT_0;j<this->_inputLayerPattern->getCountOriginal();j++){
            delete trainingSamplesInputsTransformed[i][j];
        }
        for(size_t j=INT_0;j<this->_outputLayerPattern->getCountOriginal();j++){
            delete trainingSamplesOutputsTransformed[i][j];
        }

        delete[] trainingSamplesInputsTransformed[i];
        delete[] trainingSamplesOutputsTransformed[i];
    }
    delete[] trainingSamplesInputsTransformed;
    delete[] trainingSamplesOutputsTransformed;
}
int NeuralNetwork::getCountLinesOfFile(const std::string& file){
    std::ifstream iStream(file,std::ios::in);
    std::string line=EMPTY_STRING;
    int countLine=0;

    while(getline(iStream,line))countLine++;

    iStream.close();
    return countLine;
}
bool NeuralNetwork::_controlError(const double& error)const{
    if(error>std::numeric_limits<float>::max()){
        return false;
    }

    if(std::isnan(error) || std::isinf(error)){
        return false;
    }
    return true;
}
bool NeuralNetwork::_controlWeights()const{
    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountLayer();i++){
        for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(i);j++){
            for(size_t k=INT_0;k<this->_hiddenCells[i][j]->getCountWeight();k++){
                double weight=this->_hiddenCells[i][j]->getInputWeight(k);
                if(weight>std::numeric_limits<float>::max() || weight<-std::numeric_limits<float>::max()){
                    return false;
                }
                if(std::isnan(weight) || std::isinf(weight)){
                    return false;
                }
            }
        }
    }
    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
        for(size_t j=INT_0;j<this->_outputCells[i]->getCountWeight();j++){
            double weight=this->_outputCells[i]->getInputWeight(j);
            if(weight>std::numeric_limits<float>::max() || weight<-std::numeric_limits<float>::max()){
                return false;
            }
            if(std::isnan(weight) || std::isinf(weight)){
                return false;
            }
        }
    }
    return true;
}
bool NeuralNetwork::_controlOutputs(const int& countSample, const int*const*const trainingSamplesOriginal){
    for(int i=INT_0;i<countSample;i++){
        int counterInLine=INT_0;

        int* inputsOriginal=new int[this->_inputLayerPattern->getCountOriginal()];
        for(size_t j=INT_0;j<this->_inputLayerPattern->getCountOriginal();j++){
            inputsOriginal[j]=trainingSamplesOriginal[i][counterInLine++];
        }
        double* outputs=this->run(inputsOriginal);
        delete[] inputsOriginal;
        for(size_t j=INT_0;j<this->_outputLayerPattern->getCountOriginal();j++){
            if(std::isnan(outputs[j]) || std::isinf(outputs[j])){
                delete[]outputs;
                return false;
            }
        }
        delete[]outputs;
    }
    return true;
}

void NeuralNetwork::saveNeuralNetwork()const{

    std::ofstream oStream(this->_parametersFile,std::ios::out);

    oStream<<std::setprecision(PRECISION)<<std::fixed;

    oStream<<this->_inputLayerPattern->getCountOriginal()<<this->_separator;
    for(size_t i=INT_0;i<this->_inputLayerPattern->getCountOriginal();i++){
        oStream<<(int)this->_inputLayerPattern->getType(i)<<this->_separator;

        oStream<<this->_inputLayerPattern->getLimit(i)->getOriginalMin()<<this->_separator;
        oStream<<this->_inputLayerPattern->getLimit(i)->getOriginalMax()<<this->_separator;
    }

    oStream <<this->_hiddenLayerPattern->getCountLayer()<< this->_separator;

    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountLayer();i++){
        oStream <<this->_hiddenLayerPattern->getCountCell(i)<< this->_separator;
        oStream <<(int)this->_hiddenLayerPattern->getSumFunc(i)->getType()<< this->_separator;
        oStream <<(int)this->_hiddenLayerPattern->getActFunc(i)->getType()<< this->_separator;
    }

    oStream<<this->_outputLayerPattern->getCountOriginal()<<this->_separator;
    for(size_t i=INT_0;i<this->_outputLayerPattern->getCountOriginal();i++){
        oStream<<(int)this->_outputLayerPattern->getType(i)<<this->_separator;

        oStream<<this->_outputLayerPattern->getLimit(i)->getOriginalMin()<<this->_separator;
        oStream<<this->_outputLayerPattern->getLimit(i)->getOriginalMax()<<this->_separator;
        oStream<<this->_outputLayerPattern->getLimit(i)->getScaledMin()<<this->_separator;
        oStream<<this->_outputLayerPattern->getLimit(i)->getScaledMax()<<this->_separator;

        oStream<<this->_outputLayerPattern->getTolerance(i)<<this->_separator;
    }
    oStream<<(int)this->_outputLayerPattern->getSumFunc()->getType()<<this->_separator;
    oStream<<(int)this->_outputLayerPattern->getActFunc()->getType()<<this->_separator;


    for(size_t i=INT_0;i<this->_hiddenLayerPattern->getCountLayer();i++){
        for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountCell(i);j++){
            for(size_t k=INT_0;k<this->_hiddenCells[i][j]->getCountWeight();k++){
                oStream <<this->_hiddenCells[i][j]->getInputWeight(k)<<this->_separator;
            }
        }
    }

    for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
        for(size_t j=INT_0;j<this->_outputCells[i]->getCountWeight();j++){
            oStream <<this->_outputCells[i]->getInputWeight(j)<<this->_separator;
        }
    }

    oStream<<this->_lambda<<this->_separator;
    oStream<<this->_alfa<<this->_separator;
    oStream<<this->_epoch;

    oStream.close();
}

bool NeuralNetwork::train(const int& countSample, const std::string& trainingSamplesFile){
    int countSampleCorrected=this->_correctCountSampleInFile(countSample,trainingSamplesFile);

    this->_logEW->addNewTrainingInFile(countSampleCorrected);

    const int*const* trainingSamplesOriginal=this->_convertSamplesFileToArray(countSampleCorrected,trainingSamplesFile);
    TransformedData*** trainingSamplesInputsTransformed=new TransformedData**[countSampleCorrected];
    TransformedData*** trainingSamplesOutputsTransformed=new TransformedData**[countSampleCorrected];

    for(int i=INT_0;i<countSampleCorrected;i++){
        int counterInLine=INT_0;

        int* inputsOriginal=new int[this->_inputLayerPattern->getCountOriginal()];
        for(size_t j=INT_0;j<this->_inputLayerPattern->getCountOriginal();j++){
            inputsOriginal[j]=trainingSamplesOriginal[i][counterInLine++];
        }
        trainingSamplesInputsTransformed[i]=this->_inputLayerPattern->createSample(inputsOriginal);
        delete[] inputsOriginal;

        int* outputsOriginal=new int[this->_outputLayerPattern->getCountOriginal()];
        for(size_t j=INT_0;j<this->_outputLayerPattern->getCountOriginal();j++){
            outputsOriginal[j]=trainingSamplesOriginal[i][counterInLine++];
        }
        trainingSamplesOutputsTransformed[i]=this->_outputLayerPattern->createSample(outputsOriginal);
        delete[] outputsOriginal;
    }

    bool noError;
    Keyboard *keyboard=new Keyboard();

    do{
        noError=true;
        size_t updatedWeightInAnEpoch=INT_0;
        double totalErrorInAnEpoch=DOUBLE_0;
        for(int i=INT_0;i<countSampleCorrected;i++){

          if(keyboard->kbhit()){
              int keyCode=keyboard->getch();
              if(keyCode==TRAINING_STOP_KEY_LC || keyCode==TRAINING_STOP_KEY_UC){
                std::cout<<"Training is halted. Epoch: "<<this->_epoch<<std::endl;

                this->_deleteTrainingArrays(countSampleCorrected,trainingSamplesOriginal,trainingSamplesInputsTransformed,trainingSamplesOutputsTransformed);
                this->_logEW->loadTrainingsFromFile();
                delete keyboard;
                return false;
              }
          }

            int counterOriginal=INT_0;
            int counterTransformed=INT_0;

            for(size_t j=INT_0;j<this->_inputLayerPattern->getCountOriginal();j++){
                for(size_t k=INT_0;k<this->_inputLayerPattern->getLength(j);k++){
                    Data::Type dataType=trainingSamplesInputsTransformed[i][counterOriginal]->getType();
                    const Data*const data=trainingSamplesInputsTransformed[i][counterOriginal]->getData();

                    double digit;
                    switch(dataType){
                    case Data::Type::Binary:
                    case Data::Type::Flag:
                        digit=data->getValue(k,this->_inputLayerPattern->getLimit(j)->getScaledMin(),this->_inputLayerPattern->getLimit(j)->getScaledMax());
                        break;
                    case Data::Type::Narrowed:
                    case Data::Type::Native:
                        digit=data->getValue(this->_inputLayerPattern->getLimit(j)->getScaledMin(),this->_inputLayerPattern->getLimit(j)->getScaledMax());
                        break;
                    }
                    this->_inputCells[counterTransformed++]->setInput(digit);
                }
                counterOriginal++;
            }

            counterOriginal=INT_0;
            counterTransformed=INT_0;
            for(size_t j=INT_0;j<this->_outputLayerPattern->getCountOriginal();j++){
                for(size_t k=INT_0;k<this->_outputLayerPattern->getLength(j);k++){
                    Data::Type dataType=trainingSamplesOutputsTransformed[i][counterOriginal]->getType();
                    const Data*const data=trainingSamplesOutputsTransformed[i][counterOriginal]->getData();
                    double digit;
                    switch(dataType){
                    case Data::Type::Binary:
                    case Data::Type::Flag:
                        digit=data->getValue(k,this->_outputLayerPattern->getLimit(j)->getScaledMin(),this->_outputLayerPattern->getLimit(j)->getScaledMax());
                        break;
                    case Data::Type::Narrowed:
                    case Data::Type::Native:
                        digit=data->getValue(this->_outputLayerPattern->getLimit(j)->getScaledMin(),this->_outputLayerPattern->getLimit(j)->getScaledMax());
                        break;
                    }

                    this->_outputCells[counterTransformed++]->setExpectedOutput(digit);
                }
                counterOriginal++;
            }

            for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountLayer();j++){
                this->_calculateNetsOfHiddenLayer(j);
                this->_calculateOutputsOfHiddenLayer(j);
            }

            this->_calculateNetsOfOutputLayer();
            this->_calculateOutputsOfOutputLayer();

            bool cellError=false;
            int counterOutputCell=INT_0;
            for(size_t j=INT_0;j<this->_outputLayerPattern->getCountOriginal();j++){
                for(size_t k=INT_0;k<this->_outputLayerPattern->getLength(j);k++){
                    if(std::abs(this->_outputCells[counterOutputCell]->getOutput()-this->_outputCells[counterOutputCell]->getExpectedOutput())>this->_outputLayerPattern->getTolerance(j)){
                        cellError=true;
                        break;
                    }
                    counterOutputCell++;
                }
            }

            if(cellError){
                this->_calculateErrorsOfOutputLayer();

                for(size_t i=INT_0;i<this->_outputLayerPattern->getTotalLength();i++){
                    totalErrorInAnEpoch+=std::abs(this->_outputCells[i]->getError());
                }

                this->_calculateDeltasOfOutputLayer();
                this->_calculateDeltaInputWeightsOfOutputLayer();

                updatedWeightInAnEpoch++;

                for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountLayer();j++){
                    this->_calculateDeltasOfHiddenLayer(j);
                }

                for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountLayer();j++){
                    this->_calculateDeltaInputWeightsOfHiddenLayer(j);
                }

                this->_updateInputWeightsOfOutputLayer();

                for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountLayer();j++){
                    this->_updateInputWeightsOfHiddenLayer(j);
                }

                if(noError)noError=false;
            }
        }

        if(!this->_controlError(totalErrorInAnEpoch)){
            std::cout<<"Training has failed : "<<TRAINING_ERROR_MESSAGE_INCORRECT_ERROR_VALUE<<std::endl;
            this->_deleteTrainingArrays(countSampleCorrected,trainingSamplesOriginal,trainingSamplesInputsTransformed,trainingSamplesOutputsTransformed);
            this->_logEW->loadTrainingsFromFile();
            delete keyboard;
            return false;
        }
        this->_epoch++;

        this->saveNeuralNetwork();

        this->_logEW->addErrorInFile(totalErrorInAnEpoch,updatedWeightInAnEpoch);
        this->_logEW->setNewErrorValue(totalErrorInAnEpoch);
        this->_logEW->setNewUpdatedWeight(updatedWeightInAnEpoch);

        std::cout<<"Epoch: "<<this->_epoch<<" Total errors:"<<totalErrorInAnEpoch<<" Update weights count: "<<updatedWeightInAnEpoch<<std::endl;

    }while(!noError);

    if(!this->_controlOutputs(countSampleCorrected,trainingSamplesOriginal)){
        std::cout<<"Training has failed : "<<TRAINING_ERROR_MESSAGE_INCORRECT_OUTPUT_VALUES<<std::endl;
        this->_deleteTrainingArrays(countSampleCorrected,trainingSamplesOriginal,trainingSamplesInputsTransformed,trainingSamplesOutputsTransformed);
        this->_logEW->loadTrainingsFromFile();
        delete keyboard;
        return false;
    }
    if(!this->_controlWeights()){
        std::cout<<"Training has failed : "<<TRAINING_ERROR_MESSAGE_INCORRECT_WEIGHT_VALUES<<std::endl;
        this->_deleteTrainingArrays(countSampleCorrected,trainingSamplesOriginal,trainingSamplesInputsTransformed,trainingSamplesOutputsTransformed);
        this->_logEW->loadTrainingsFromFile();
        delete keyboard;
        return false;
    }

    std::cout<<"Training is complete. Epoch: "<<this->_epoch<<std::endl;

    this->_deleteTrainingArrays(countSampleCorrected,trainingSamplesOriginal,trainingSamplesInputsTransformed,trainingSamplesOutputsTransformed);
    this->_logEW->loadTrainingsFromFile();
    delete keyboard;
    return true;
}
double* NeuralNetwork::run(const int*const inputsOriginal){
    TransformedData** inputsTransformed;
    inputsTransformed=this->_inputLayerPattern->createSample(inputsOriginal);

    int counterOriginal=INT_0;
    int counterTransformed=INT_0;
    for(size_t j=INT_0;j<this->_inputLayerPattern->getCountOriginal();j++){

        for(size_t k=INT_0;k<this->_inputLayerPattern->getLength(j);k++){
            Data::Type dataType=inputsTransformed[counterOriginal]->getType();
            const Data*const data=inputsTransformed[counterOriginal]->getData();
            double digit;
            switch(dataType){
            case Data::Type::Binary:
            case Data::Type::Flag:
                digit=data->getValue(k,this->_inputLayerPattern->getLimit(j)->getScaledMin(),this->_inputLayerPattern->getLimit(j)->getScaledMax());
                break;
            case Data::Type::Narrowed:
            case Data::Type::Native:
                digit=data->getValue(this->_inputLayerPattern->getLimit(j)->getScaledMin(),this->_inputLayerPattern->getLimit(j)->getScaledMax());
                break;
            }
            this->_inputCells[counterTransformed++]->setInput(digit);
        }
        counterOriginal++;
    }

    for(size_t j=INT_0;j<this->_hiddenLayerPattern->getCountLayer();j++){
        this->_calculateNetsOfHiddenLayer(j);
        this->_calculateOutputsOfHiddenLayer(j);
    }

    this->_calculateNetsOfOutputLayer();
    this->_calculateOutputsOfOutputLayer();

    for(size_t i=INT_0;i<this->_inputLayerPattern->getCountOriginal();i++){
        delete inputsTransformed[i];
    }
    delete[] inputsTransformed;

    double* outputs=new double[this->_outputLayerPattern->getCountOriginal()];
    int counterOutputCell=INT_0;
    for(size_t i=INT_0;i<this->_outputLayerPattern->getCountOriginal();i++){
        double* outputDigits=new double[this->_outputLayerPattern->getLength(i)];
        int counterDigit=INT_0;
        for(size_t j=INT_0;j<this->_outputLayerPattern->getLength(i);j++){
            outputDigits[counterDigit++]=this->_outputCells[counterOutputCell++]->getOutput();
        }
        switch(this->_outputLayerPattern->getType(i)){
        case Data::Type::Binary:
        {
            Binary data(this->_outputLayerPattern->getLength(i),outputDigits,this->_outputLayerPattern->getLimit(i)->getOriginalMax(),this->_outputLayerPattern->getLimit(i)->getScaledMin(),this->_outputLayerPattern->getLimit(i)->getScaledMax());
            outputs[i]=data.getOriginal();
            break;
        }
        case Data::Type::Flag:
        {
            Flag data(this->_outputLayerPattern->getLength(i),outputDigits,this->_outputLayerPattern->getLimit(i)->getOriginalMax(),this->_outputLayerPattern->getLimit(i)->getScaledMin(),this->_outputLayerPattern->getLimit(i)->getScaledMax());
            outputs[i]=data.getOriginal();
            break;
        }
        case Data::Type::Narrowed:
        {
            const Data::Limit*const limit=this->_outputLayerPattern->getLimit(i);
            Narrowed data(outputDigits[INT_0],limit->getScaledMin(),limit->getScaledMax());
            outputs[i]=data.getOriginal(limit->getOriginalMin(),limit->getOriginalMax());
            break;
        }
        case Data::Type::Native:
        {
            const Data::Limit*const limit=this->_outputLayerPattern->getLimit(i);
            Native data(outputDigits[INT_0],limit->getScaledMin(),limit->getScaledMax());
            outputs[i]=data.getOriginal();
            break;
        }
        }
        delete[] outputDigits;
    }

    return outputs;
}
double NeuralNetwork::test(const int& countSample, const std::string& testSamplesFile){
    int countSampleCorrected=this->_correctCountSampleInFile(countSample,testSamplesFile);

        const int*const* testSamplesOriginal=this->_convertSamplesFileToArray(countSample,testSamplesFile);

        int countError=0;
        int countAllOutput=countSampleCorrected*this->_outputLayerPattern->getCountOriginal();

        for(int i=INT_0;i<countSampleCorrected;i++){
            int counterInLine=INT_0;
            int* inputsOriginal=new int[this->_inputLayerPattern->getCountOriginal()];
            int* expectedOutputsOriginal=new int[this->_outputLayerPattern->getCountOriginal()];
            double* outputsOriginal;

            for(size_t j=INT_0;j<this->_inputLayerPattern->getCountOriginal();j++){
                inputsOriginal[j]=testSamplesOriginal[i][counterInLine++];
            }

            outputsOriginal=this->run(inputsOriginal);

            for(size_t j=INT_0;j<this->_outputLayerPattern->getCountOriginal();j++){
                expectedOutputsOriginal[j]=testSamplesOriginal[i][counterInLine++];
                if(std::round(outputsOriginal[j])!=expectedOutputsOriginal[j]){
                    countError++;
                    std::cout<<"Sample Index:"<<i<<",\tOutput Index:"<<j<<",\t";
                    Data::Type outputType=this->_outputLayerPattern->getType(j);
                    if(outputType==Data::Type::Narrowed || outputType==Data::Type::Native)
                      std::cout<<"Output(rounded):"<<std::round(outputsOriginal[j])<<",\t";
                    std::cout<<"Output:"<<outputsOriginal[j]<<",\tExpected Output:"<<expectedOutputsOriginal[j]<<std::endl;
                }
            }

            delete[] inputsOriginal;
            delete[] expectedOutputsOriginal;
            delete[] outputsOriginal;
        }

        for(int i=INT_0;i<countSampleCorrected;i++){
            delete[] testSamplesOriginal[i];
        }
        delete[] testSamplesOriginal;

        std::cout<<"Number of failed outputs:"<<countError<<" - Total number of outputs:"<<countAllOutput<<std::endl;

        return DOUBLE_POS_1-(double)countError/(double)countAllOutput;
}
//-------------------------------------------------
