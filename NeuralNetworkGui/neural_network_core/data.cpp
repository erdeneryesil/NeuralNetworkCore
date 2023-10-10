#include"data.h"
#include<math.h>

//-------------------------------------------------
Data::Limit::Limit(){

}
Data::Limit::Limit(const Data::Type& dataType,const LayerType& layerType){
  if(layerType==LayerType::Input){
    if(dataType==Data::Type::Native){
      this->_originalMin=INT_0;
      this->_originalMax=INT_POS_1;
      this->_scaledMin=DOUBLE_0;
      this->_scaledMax=DOUBLE_POS_1;
    }else{
      throw std::invalid_argument(THROW_MESSAGE_INPUT_LIMIT_CONSTRUCTOR_2_PARAMETERS_INVALID_DATATYPE);
    }
  }else{
    throw std::invalid_argument(THROW_MESSAGE_INPUT_LIMIT_CONSTRUCTOR_2_PARAMETERS_INVALID_LAYERTYPE);
  }

}
Data::Limit::Limit(const Data::Type& dataType,const LayerType& layerType,const int& originalMin,const int& originalMax){
  if(layerType==LayerType::Input){
    if(dataType==Data::Type::Binary || dataType==Data::Type::Flag){
      this->_originalMin=originalMin;
      this->_originalMax=std::abs(originalMax)>std::abs(originalMin)?std::abs(originalMax):std::abs(originalMin);
      this->_scaledMin=DOUBLE_0;
      this->_scaledMax=DOUBLE_POS_1;
    }else if(dataType==Data::Type::Narrowed){
      this->_originalMin=originalMin;
      this->_originalMax=originalMax;
      this->_scaledMin=DOUBLE_0;
      this->_scaledMax=DOUBLE_POS_1;
    }else{
      throw std::invalid_argument(THROW_MESSAGE_INPUT_LIMIT_CONSTRUCTOR_4_PARAMETERS_INVALID_DATATYPE);
    }
  }else{
    throw std::invalid_argument(THROW_MESSAGE_INPUT_LIMIT_CONSTRUCTOR_4_PARAMETERS_INVALID_LAYERTYPE);
  }
}
Data::Limit::Limit(const Data::Type& dataType,const LayerType& layerType,const int& originalMin,const int& originalMax,const double& scaledMin,const double& scaledMax){
  if(layerType==LayerType::Output){
    if(dataType==Data::Type::Binary || dataType==Data::Type::Flag){
      this->_originalMin=originalMin;
      this->_originalMax=std::abs(originalMax)>std::abs(originalMin)?std::abs(originalMax):std::abs(originalMin);
      this->_scaledMin=scaledMin;
      this->_scaledMax=scaledMax;
    }else if(dataType==Data::Type::Narrowed){
      this->_originalMin=originalMin;
      this->_originalMax=originalMax;
      this->_scaledMin=scaledMin;
      this->_scaledMax=scaledMax;
    }else{
      throw std::invalid_argument(THROW_MESSAGE_OUTPUT_LIMIT_CONSTRUCTOR_6_PARAMETERS_INVALID_DATATYPE);
    }
  }else{
    throw std::invalid_argument(THROW_MESSAGE_OUTPUT_LIMIT_CONSTRUCTOR_6_PARAMETERS_INVALID_LAYERTYPE);
  }
}
Data::Limit::Limit(const Data::Type& dataType,const LayerType& layerType,const double& scaledMin,const double& scaledMax){
  if(layerType==LayerType::Output){
    if(dataType==Data::Type::Native){
      this->_originalMin=INT_0;
      this->_originalMax=INT_POS_1;
      this->_scaledMin=scaledMin;
      this->_scaledMax=scaledMax;
    }else{
      throw std::invalid_argument(THROW_MESSAGE_OUTPUT_LIMIT_CONSTRUCTOR_4_PARAMETERS_INVALID_DATATYPE);
    }
  }else{
    throw std::invalid_argument(THROW_MESSAGE_OUTPUT_LIMIT_CONSTRUCTOR_4_PARAMETERS_INVALID_LAYERTYPE);
  }
}
Data::Limit::Limit(const Limit*const limit){
    this->_originalMin=limit->_originalMin;
    this->_originalMax=limit->_originalMax;
    this->_scaledMin=limit->_scaledMin;
    this->_scaledMax=limit->_scaledMax;
}
int Data::Limit::getOriginalMin()const{
  return this->_originalMin;
}
int Data::Limit::getOriginalMax()const{
  return this->_originalMax;
}
double Data::Limit::getScaledMin()const{
  return this->_scaledMin;
}
double Data::Limit::getScaledMax()const{
  return this->_scaledMax;
}
void Data::Limit::setScaledMin(const LayerType& layerType,const double& scaledMin){
  if(layerType==LayerType::Output)
  this->_scaledMin=scaledMin;
  else
  throw std::invalid_argument(THROW_MESSAGE_LIMIT_SETSCALEDMIN);

}
void Data::Limit::setScaledMax(const LayerType& layerType,const double& scaledMax){
  if(layerType==LayerType::Output)
  this->_scaledMax=scaledMax;
  else
  throw std::invalid_argument(THROW_MESSAGE_LIMIT_SETSCALEDMAX);
}
Data::~Data(){
  delete[]this->_digits;
}
size_t Data::getLength()const{
  return this->_length;
}
//-------------------------------------------------
Binary::Binary(const int& original,const int& originalMax){
  int unsignedOriginalMax=std::abs(original)>std::abs(originalMax)?std::abs(original):std::abs(originalMax);
  size_t countBitMax=TransformedData::length(Data::Type::Binary,std::abs(unsignedOriginalMax));
  size_t countBit=TransformedData::length(Data::Type::Binary,std::abs(original));
  size_t countUnsignedBit=countBit-INT_POS_1;
  this->_length=countBitMax;
  this->_digits=new double[this->_length];

  this->_calculateDigitsReverseOrder(std::abs(original));

  int lengthDifference=countBitMax-countBit;
  for(int i=INT_0;i<lengthDifference;i++)
  this->_digits[countUnsignedBit+i]=DOUBLE_0;

  this->_digits[this->_length-INT_POS_1]=original<DOUBLE_0?DOUBLE_0:DOUBLE_POS_1;
  this->_reverseBits();
}
Binary::Binary(const size_t& countBit,const double*const scaledBits,const int& originalMax,const double& scaledMin,const double& scaledMax){
  size_t countBitMax=TransformedData::length(Data::Type::Binary,std::abs(originalMax));
  int lengthDifference=countBitMax-countBit;
  if(lengthDifference>INT_0)
  this->_length=countBitMax;
  else
  this->_length=countBit;

  this->_digits=new double[this->_length];

  this->_digits[INT_0]=(scaledBits[INT_0]-scaledMin)*DOUBLE_POS_1/(scaledMax-scaledMin);
  int indexMemberDigit=INT_POS_1;
  for(int i=INT_0;i<lengthDifference;i++){
    this->_digits[indexMemberDigit]=DOUBLE_0;
    indexMemberDigit++;
  }

  int indexParamDigit=INT_POS_1;
  for(size_t i=indexMemberDigit;i<this->_length;i++){
    this->_digits[indexMemberDigit]=(scaledBits[indexParamDigit]-scaledMin)*DOUBLE_POS_1/(scaledMax-scaledMin);
    indexMemberDigit++;
    indexParamDigit++;
  }
}
Binary::Binary(const Binary& binaryObj){
  this->_length=binaryObj._length;
  this->_digits=new double[this->_length];

  for(size_t i=INT_0;i<this->_length;i++)
  this->_digits[i]=binaryObj._digits[i];
}
void Binary::_calculateDigitsReverseOrder(int original){
  size_t index=INT_0;
  while(original>=BINARY){
    int remainder=original%BINARY;
    original/=BINARY;

    this->_digits[index]=remainder;
    index++;
  }
  this->_digits[index]=original;
}
void Binary::_reverseBits(){
  double* tempBits=new double[this->_length];
  for(size_t i=INT_0;i<this->_length;i++)
  tempBits[i]=this->_digits[this->_length-INT_POS_1-i];

  for(size_t i=INT_0;i<this->_length;i++)
  this->_digits[i]=tempBits[i];
  delete[]tempBits;
}
double Binary::getValue(const size_t& index,const double& scaledMin,const double& scaledMax)const{
  return scaledMin+this->_digits[index]*(scaledMax-scaledMin)/DOUBLE_POS_1;
}
double Binary::getOriginal()const{
  double original=DOUBLE_0;
  int exponent=INT_0;

  for(int i=this->_length-INT_POS_1;i>=INT_POS_1;i--){
    original+=round(this->_digits[i])*std::pow(BINARY,exponent);
    exponent++;
  }
  return round(this->_digits[INT_0])>DOUBLE_0?original:-original;
}
//-------------------------------------------------
Flag::Flag(const int& original,const int& originalMax){
  this->_length=INT_POS_2+(std::abs(originalMax)>std::abs(original)?std::abs(originalMax):std::abs(original));
  this->_digits=new double[this->_length];

  this->_digits[INT_0]=original<DOUBLE_0?DOUBLE_0:DOUBLE_POS_1;

  for(size_t i=INT_POS_1;i<this->_length;i++){
    if(this->_length-INT_POS_1-i!=(unsigned long)std::abs(original))
    this->_digits[i]=DOUBLE_0;
    else
    this->_digits[i]=DOUBLE_POS_1;
  }
}
Flag::Flag(const size_t& countFlag,const double*const scaledFlags,const int& originalMax,const double& scaledMin,const double& scaledMax){
  int lengthDifference=INT_POS_2+std::abs(originalMax)-countFlag;
  if(lengthDifference>INT_0)
  this->_length=std::abs(originalMax)+INT_POS_2;// +2 işaret ve 0(decimal) için de flag olacak
  else
  this->_length=countFlag;

  this->_digits=new double[this->_length];

  this->_digits[INT_0]=((scaledFlags[INT_0]-scaledMin)*DOUBLE_POS_1/(scaledMax-scaledMin));

  int indexMemberDigit=INT_POS_1;
  for(int i=INT_0;i<lengthDifference;i++){
    this->_digits[indexMemberDigit]=DOUBLE_0;
    indexMemberDigit++;
  }

  int indexParamDigit=INT_POS_1;
  for(size_t i=indexMemberDigit;i<this->_length;i++){
    //this->_digits[indexMemberDigit]=scaledFlags[indexParamDigit];
    this->_digits[indexMemberDigit]=((scaledFlags[indexParamDigit]-scaledMin)*DOUBLE_POS_1/(scaledMax-scaledMin));
    indexMemberDigit++;
    indexParamDigit++;
  }
}
Flag::Flag(const Flag& flagObj){
  this->_length=flagObj._length;
  this->_digits=new double[this->_length];
  for(size_t i=INT_0;i<this->_length;i++){
    this->_digits[i]=flagObj._digits[i];
  }
}
double Flag::getValue(const size_t& index,const double& scaledMin,const double& scaledMax)const{
  return scaledMin+(this->_digits[index])*(scaledMax-scaledMin)/DOUBLE_POS_1;
}
double Flag::getOriginal()const{

  double flagMax=DOUBLE_0;
  int indexMax=INT_NEG_1;
  for(size_t i=INT_POS_1;i<this->_length;i++){
    if(this->_digits[i]>flagMax){
      flagMax=this->_digits[i];
      indexMax=this->_length-INT_POS_1-i;
    }
  }
  return round(this->_digits[INT_0])>DOUBLE_0?indexMax:-indexMax;
}
//-------------------------------------------------
Narrowed::Narrowed(const double& value,const double& originalMin,const double& originalMax){
  this->_length=INT_POS_1;
  this->_digits=new double[this->_length];
  this->_digits[INT_0]=DOUBLE_0+(value-originalMin)*(DOUBLE_POS_1-DOUBLE_0)/(originalMax-originalMin);
}
Narrowed::Narrowed(const Narrowed& narrowedObj){
  this->_length=INT_POS_1;
  this->_digits=new double[this->_length];
  this->_digits[INT_0]=narrowedObj._digits[INT_0];
}
double Narrowed::getValue(const double& scaledMin,const double& scaledMax)const{
  return scaledMin+(this->_digits[INT_0])*(scaledMax-scaledMin)/DOUBLE_POS_1;
}
double Narrowed::getOriginal(const int& originalMin,const int& originalMax)const{
  return originalMin+((this->_digits[INT_0]-DOUBLE_0)*(originalMax-originalMin)/(DOUBLE_POS_1-DOUBLE_0));
}
//-------------------------------------------------
Native::Native(const double& value,const double& originalMin,const double& originalMax){
  this->_length=INT_POS_1;
  this->_digits=new double[this->_length];
  this->_digits[INT_0]=DOUBLE_0+(value-originalMin)*(DOUBLE_POS_1-DOUBLE_0)/(originalMax-originalMin);
}
Native::Native(const double& native){
  this->_length=INT_POS_1;
  this->_digits=new double[this->_length];
  this->_digits[INT_0]=native;
}
Native::Native(const Native& nativeObj){
  this->_length=INT_POS_1;
  this->_digits=new double[this->_length];
  this->_digits[INT_0]=nativeObj._digits[INT_0];
}
double Native::getValue(const double& scaledMin,const double& scaledMax)const{
  return scaledMin+(this->_digits[INT_0])*(scaledMax-scaledMin)/DOUBLE_POS_1;
}
double Native::getOriginal()const{
  return this->_digits[INT_0];
}
//-------------------------------------------------
size_t TransformedData::length(const Data::Type& type,const int& original){
  size_t length=INT_0;
  switch(type){
    case Data::Type::Binary:
    {
      int value=std::abs(original);

      while(value>=BINARY){
        //int remainder=value%BINARY;
        value/=BINARY;
        length++;
      }
      length++;
      length++;//+-işaret
      break;
    }
    case Data::Type::Flag:
    length=std::abs(original)+INT_POS_2;//0 ve +-
    break;
    case Data::Type::Narrowed:
    case Data::Type::Native:
    length=INT_POS_1;
    break;
  }

  return length;
}
TransformedData::TransformedData(Binary* data){
  this->_data=data;
  this->_type=Data::Type::Binary;
}
TransformedData::TransformedData(Flag* data){
  this->_data=data;
  this->_type=Data::Type::Flag;
}
TransformedData::TransformedData(Narrowed* data){
  this->_data=data;
  this->_type=Data::Type::Narrowed;
}
TransformedData::TransformedData(Native* data){
  this->_data=data;
  this->_type=Data::Type::Native;
}
TransformedData::TransformedData(const TransformedData& data){
  this->_type=data._type;

  switch(data._type){
    case Data::Type::Binary:
    this->_data=new Binary(*(Binary*)data._data);
    break;
    case Data::Type::Flag:
    this->_data=new Flag(*(Flag*)data._data);
    break;
    case Data::Type::Narrowed:
    this->_data=new Narrowed(*(Narrowed*)data._data);
    break;
    case Data::Type::Native:
    this->_data=new Native(*(Native*)data._data);
    break;
  }
}
TransformedData::~TransformedData(){
  delete this->_data;
}
const Data* TransformedData::getData()const{
  return this->_data;
}
Data::Type TransformedData::getType()const{
  return this->_type;
}
//-------------------------------------------------
