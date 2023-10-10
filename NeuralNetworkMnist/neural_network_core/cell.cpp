#include"cell.h"
#include<random>
#include<chrono>
//-------------------------------------------------
Cell::Cell(const size_t& countWeight,const double*const inputWeights){
  this->_countWeight=countWeight;
  this->_inputWeights=new double[this->_countWeight];
  this->_deltaInputWeights=new double[this->_countWeight];

  for(size_t i=INT_0;i<this->_countWeight;i++){
    this->_inputWeights[i]=inputWeights[i];
    this->_deltaInputWeights[i]=DOUBLE_0;
  }

  this->_net=DOUBLE_0;
  this->_output=DOUBLE_0;
  this->_delta=DOUBLE_0;
}
Cell::Cell(const size_t& countWeight,const double& randomWeightMin,const double& randomWeightMax){
  this->_countWeight=countWeight;
  this->_inputWeights=new double[this->_countWeight];
  this->_deltaInputWeights=new double[this->_countWeight];

  for(size_t i=INT_0;i<this->_countWeight;i++)
    this->_deltaInputWeights[i]=DOUBLE_0;

  this->_setWeightRandom(randomWeightMin,randomWeightMax);

  this->_net=DOUBLE_0;
  this->_output=DOUBLE_0;
  this->_delta=DOUBLE_0;
}
void Cell::_setWeightRandom(const double& min,const double& max){
  unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine randomGenerator(seed);
  std::uniform_real_distribution<double> distribution(min,max);

  for(size_t i=INT_0;i<this->_countWeight;i++)
    this->_inputWeights[i]=distribution(randomGenerator);
}
Cell::~Cell(){
  delete[] this->_inputWeights;
  delete[] this->_deltaInputWeights;
}
size_t Cell::getCountWeight() const{
  return this->_countWeight;
}
double Cell::getInputWeight(const size_t& index) const{
  return this->_inputWeights[index];
}
double Cell::getDeltaInputWeight(const size_t& index) const{
  return this->_deltaInputWeights[index];
}
double Cell::getNet() const{
  return this->_net;
}
double Cell::getOutput() const{
  return this->_output;
}
void Cell::setOutput(const double& output){
  this->_output=output;
}
double Cell::getDelta() const{
  return this->_delta;
}
void Cell::calculateNet(const SummationFunction*const summationFunction,const double*const inputs){
  this->_net=(summationFunction->*(summationFunction->getFunctionPointer()))(this,inputs);
}
void Cell::calculateOutput(const ActivationFunction*const activationFunction){
  this->_output=(activationFunction->*(activationFunction->getActivationFunctionPointer()))(this);
}
void Cell::calculateDeltaInputWeight(const double& lambda,const double& alfa, const double*const previousLayerOutputs){
  for(size_t i=INT_0;i<this->_countWeight;i++){
    this->_deltaInputWeights[i]=lambda*this->_delta*previousLayerOutputs[i]+alfa*this->_deltaInputWeights[i];
  }
}
void Cell::updateInputWeight(){
  for(size_t i=INT_0;i<this->_countWeight;i++){
    this->_inputWeights[i]+=this->_deltaInputWeights[i];
  }
}
//-------------------------------------------------
Cell::SummationFunction::SummationFunction(const SummationFunction::Type& type){
  this->_type=type;
  switch(this->_type){
    case Cell::SummationFunction::Type::WeightedTotal:
    this->_functionPointer=&Cell::SummationFunction::_weightedTotal;
    break;
    case Cell::SummationFunction::Type::Multiplication:
    this->_functionPointer=&Cell::SummationFunction::_multiplication;
    break;
    case Cell::SummationFunction::Type::Maximum:
    this->_functionPointer=&Cell::SummationFunction::_maximum;
    break;
    case Cell::SummationFunction::Type::Minimum:
    this->_functionPointer=&Cell::SummationFunction::_minimum;
    break;
    case Cell::SummationFunction::Type::Majority:
    this->_functionPointer=&Cell::SummationFunction::_majority;
    break;
    case Cell::SummationFunction::Type::IncrementalTotal:
    this->_functionPointer=&Cell::SummationFunction::_incrementalTotal;
    break;
  }
}
Cell::SummationFunction::Type Cell::SummationFunction::getType()const{
  return this->_type;
}
Cell::SummationFunction::FunctionPointer Cell::SummationFunction::getFunctionPointer()const{
  return this->_functionPointer;
}
double Cell::SummationFunction::_weightedTotal(const Cell*const cell,const double*const inputs)const{

  double net=DOUBLE_0;
  for(size_t i=INT_0;i<cell->_countWeight;i++){
    net+=cell->_inputWeights[i]*inputs[i];
  }
  return net;
}
double Cell::SummationFunction::_multiplication(const Cell*const cell,const double*const inputs)const{

  double net=DOUBLE_POS_1;

  for(size_t i=INT_0;i<cell->_countWeight;i++){
    net*=cell->_inputWeights[i]*inputs[i];
  }
  return net;
}
double Cell::SummationFunction::_maximum(const Cell*const cell,const double*const inputs)const{

 double net=cell->_inputWeights[INT_0]*inputs[INT_0];

  for(size_t i=INT_POS_1;i<cell->_countWeight;i++){
    if(net<cell->_inputWeights[i]*inputs[i])
      net=cell->_inputWeights[i]*inputs[i];
  }
  return net;
}
double Cell::SummationFunction::_minimum(const Cell*const cell,const double*const inputs)const{

  double net=cell->_inputWeights[INT_0]*inputs[INT_0];

  for(size_t i=INT_POS_1;i<cell->_countWeight;i++){
    if(net>cell->_inputWeights[i]*inputs[i])
      net=cell->_inputWeights[i]*inputs[i];
  }
  return net;
}
double Cell::SummationFunction::_majority(const Cell*const cell,const double*const inputs)const{

  double positive=DOUBLE_0;
  double negative=DOUBLE_0;

  for(size_t i=INT_0;i<cell->_countWeight;i++){
    if(cell->_inputWeights[i]*inputs[i]>DOUBLE_0)positive++;
    else negative++;
  }

  if(positive>negative)return positive;
  else return negative;
}
double Cell::SummationFunction::_incrementalTotal(const Cell*const cell,const double*const inputs)const{

  double net=cell->_net;
 for(size_t i=INT_0;i<cell->_countWeight;i++){
    net+=cell->_inputWeights[i]*inputs[i];
  }
  return net;
}
//-----------------------------------------------
Cell::ActivationFunction::ActivationFunction(const ActivationFunction::Type& type){
  this->_type=type;
  switch(this->_type){
    case ActivationFunction::Type::Sigmoid:
    this->_functionPointer=&Cell::ActivationFunction::_sigmoid;
    this->_derivativeFunctionPointer=&Cell::ActivationFunction::_sigmoidDerivative;
    break;
    case ActivationFunction::Type::TanH:
    this->_functionPointer=&Cell::ActivationFunction::_tanH;
    this->_derivativeFunctionPointer=&Cell::ActivationFunction::_tanHDerivative;
    break;
    case ActivationFunction::Type::ReLU:
    this->_functionPointer=&Cell::ActivationFunction::_reLU;
    this->_derivativeFunctionPointer=&Cell::ActivationFunction::_reLUDerivative;
    break;
    case ActivationFunction::Type::LeakyReLU:
    this->_functionPointer=&Cell::ActivationFunction::_leakyReLU;
    this->_derivativeFunctionPointer=&Cell::ActivationFunction::_leakyReLUDerivative;
    break;
    case ActivationFunction::Type::Swish:
    this->_functionPointer=&Cell::ActivationFunction::_swish;
    this->_derivativeFunctionPointer=&Cell::ActivationFunction::_swishDerivative;
    break;
    case ActivationFunction::Type::Softplus:
    this->_functionPointer=&Cell::ActivationFunction::_softplus;
    this->_derivativeFunctionPointer=&Cell::ActivationFunction::_softplusDerivative;
    break;
  }
}
double Cell::ActivationFunction::rangeMin(const ActivationFunction::Type& type){
  switch(type){
    case ActivationFunction::Type::Sigmoid:
    return DOUBLE_0;
    case ActivationFunction::Type::TanH:
    return DOUBLE_NEG_1;
    case ActivationFunction::Type::ReLU:
    return DOUBLE_0;
    case ActivationFunction::Type::LeakyReLU:
    return DOUBLE_NEG_1;
    case ActivationFunction::Type::Swish:
    return DOUBLE_NEG_1;
    case ActivationFunction::Type::Softplus:
    return DOUBLE_0;
    default:
    return DOUBLE_0;
  }

}
double Cell::ActivationFunction::rangeMax(const ActivationFunction::Type& type){
  switch(type){
    case ActivationFunction::Type::Sigmoid:
    return DOUBLE_POS_1;
    case ActivationFunction::Type::TanH:
    return DOUBLE_POS_1;
    case ActivationFunction::Type::ReLU:
    return DOUBLE_POS_1;
    case ActivationFunction::Type::LeakyReLU:
    return DOUBLE_POS_1;
    case ActivationFunction::Type::Swish:
    return DOUBLE_POS_1;
    case ActivationFunction::Type::Softplus:
    return DOUBLE_POS_1;
    default:
    return DOUBLE_0;
  }
}
Cell::ActivationFunction::Type Cell::ActivationFunction::getType()const{
  return this->_type;
}
Cell::ActivationFunction::FunctionPointer Cell::ActivationFunction::getActivationFunctionPointer()const{
  return this->_functionPointer;
}
Cell::ActivationFunction::FunctionPointer Cell::ActivationFunction::getDerivativeActivationFunctionPointer()const{
  return this->_derivativeFunctionPointer;
}
double Cell::ActivationFunction::_sigmoid(const Cell*const cell)const{

  return DOUBLE_POS_1/(DOUBLE_POS_1+std::exp(-cell->_net));
}
double Cell::ActivationFunction::_tanH(const Cell*const cell)const{

  return (std::exp(cell->_net)-std::exp(-cell->_net))/(std::exp(cell->_net)+std::exp(-cell->_net));
}
double Cell::ActivationFunction::_reLU(const Cell*const cell)const{

  return cell->_net<DOUBLE_0?DOUBLE_0:cell->_net;
}
double Cell::ActivationFunction::_leakyReLU(const Cell*const cell)const{

  return cell->_net<DOUBLE_0?LEAKY_CONST*cell->_net:cell->_net;
}
double Cell::ActivationFunction::_swish(const Cell*const cell)const{

  return cell->_net*this->_sigmoid(cell);
}
double Cell::ActivationFunction::_softplus(const Cell*const cell)const{
  return std::log(DOUBLE_POS_1+std::exp(cell->_net));
}
double Cell::ActivationFunction::_sigmoidDerivative(const Cell*const cell)const{
  return cell->_output*(DOUBLE_POS_1-cell->_output);
}
double Cell::ActivationFunction::_tanHDerivative(const Cell*const cell)const{

  return DOUBLE_POS_1-std::pow(cell->_output,INT_POS_2);
}
double Cell::ActivationFunction::_reLUDerivative(const Cell*const cell)const{

  return cell->_net<DOUBLE_0?DOUBLE_0:DOUBLE_POS_1;
}
double Cell::ActivationFunction::_leakyReLUDerivative(const Cell*const cell)const{

  return cell->_net<DOUBLE_0?LEAKY_CONST:DOUBLE_POS_1;
}
double Cell::ActivationFunction::_swishDerivative(const Cell*const cell)const{

  return (DOUBLE_POS_1+std::exp(-cell->_net)+cell->_net*std::exp(-cell->_net))/std::pow((DOUBLE_POS_1+std::exp(-cell->_net)),INT_POS_2);
}
double Cell::ActivationFunction::_softplusDerivative(const Cell*const cell)const{

  return DOUBLE_POS_1/(DOUBLE_POS_1+std::exp(-cell->_net));
}
//-------------------------------------------------
BiasCell::BiasCell(){
  this->_input=DOUBLE_POS_1;
}
double BiasCell::getInput() const{
  return this->_input;
}
//-------------------------------------------------
HiddenCell::HiddenCell(const size_t& countWeight,const double*const inputWeights)
:Cell(countWeight,inputWeights){}
HiddenCell::HiddenCell(const size_t& countWeight,const double& randomWeightMin,const double& randomWeightMax)
:Cell(countWeight,randomWeightMin,randomWeightMax){}
void HiddenCell::calculateDelta(const ActivationFunction*const activationFunction,const int& cellIndex,const int& countPreviousLayerCell,const Cell*const*const previousLayerCells){
  this->_delta=DOUBLE_0;
  for(int i=INT_0;i<countPreviousLayerCell;i++){
    this->_delta+=previousLayerCells[i]->getDelta()*previousLayerCells[i]->getInputWeight(cellIndex);
  }
  this->_delta*=(activationFunction->*(activationFunction->getDerivativeActivationFunctionPointer()))(this);
}
//-------------------------------------------------
InputCell::InputCell(){
  this->setInput(DOUBLE_0);//_input, InputCell kurucusunda oluşturuluyor ve burada sadece değeri değiştiriliyor
}
void InputCell::setInput(const double& input){
  this->_input=input;
}
//-------------------------------------------------
OutputCell::OutputCell(const size_t& countWeight,const double*const inputWeights)
:Cell(countWeight,inputWeights){
  this->_expectedOutput=DOUBLE_0;
  this->_error=DOUBLE_0;
}
OutputCell::OutputCell(const size_t& countWeight,const double& randomWeightMin,const double& randomWeightMax)
:Cell(countWeight,randomWeightMin,randomWeightMax){
  this->_expectedOutput=DOUBLE_0;
  this->_error=DOUBLE_0;
}
double OutputCell::getExpectedOutput()const{
  return this->_expectedOutput;
}
void OutputCell::setExpectedOutput(const double& value){
  this->_expectedOutput=value;
}
double OutputCell::getError()const{
  return this->_error;
}
void OutputCell::setError(const double& error){
  this->_error=error;
}
void OutputCell::calculateError(){
  this->_error=this->_expectedOutput-this->_output;
}
void OutputCell::calculateDelta(const ActivationFunction*const activationFunction){
  this->_delta=(activationFunction->*(activationFunction->getDerivativeActivationFunctionPointer()))(this)*this->_error;
}
//-------------------------------------------------
