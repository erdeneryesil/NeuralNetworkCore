#include"menu.h"

void Menu::listMainMenuItems(){
  std::cout<<"\t0. Determine another neural network"<<std::endl;
  std::cout<<"\t1. Exec an operation using the current neural network"<<std::endl;
  std::cout<<"\t2. Exit\n"<<std::endl;
}
void Menu::listDetermineNNItems(){
  std::cout<<"\t0. Open a neural network"<<std::endl;
  std::cout<<"\t1. Create a new neural network\n"<<std::endl;
}
void Menu::listDataTypes(){
  std::cout<<"\t0. Binary"<<std::endl;
  std::cout<<"\t1. Flag"<<std::endl;
  std::cout<<"\t2. Narrowed"<<std::endl;
  std::cout<<"\t3. Native\n"<<std::endl;
}
void Menu::listSummationFunctions(){
  std::cout<<"\t0. WeightedTotal"<<std::endl;
  std::cout<<"\t1. Multiplication"<<std::endl;
  std::cout<<"\t2. Maximum"<<std::endl;
  std::cout<<"\t3. Minimum"<<std::endl;
  std::cout<<"\t4. Majority"<<std::endl;
  std::cout<<"\t5. IncrementalTotal\n"<<std::endl;
}
void Menu::listActivationFunctions(){
  std::cout<<"\t0. Sigmoid"<<std::endl;
  std::cout<<"\t1. TanH"<<std::endl;
  std::cout<<"\t2. ReLU"<<std::endl;
  std::cout<<"\t3. LeakyReLU"<<std::endl;
  std::cout<<"\t4. Swish"<<std::endl;
  std::cout<<"\t5. Softplus\n"<<std::endl;
}
void Menu::listSeparatorCharacters(){
  std::cout<<"\t0. Space"<<std::endl;
  std::cout<<"\t1. Comma  ,"<<std::endl;
  std::cout<<"\t2. Semicolon  ;"<<std::endl;
  std::cout<<"\t3. Pipe  |\n"<<std::endl;

}
void Menu::listOperations(){
  std::cout<<"\t0. Train"<<std::endl;
  std::cout<<"\t1. Test"<<std::endl;
  std::cout<<"\t2. Run"<<std::endl;
  std::cout<<"\t3. Inform\n"<<std::endl;
}
void Menu::headline(std::string title,int countTrailingNewline){
  std::cout<<"\n\n----------------------------------------------\n"<<title<<std::string(countTrailingNewline,'\n');

}

Data::Type* Menu::determineDataTypes(LayerType layerType,int countData){
  headline("TYPES OF "+std::string(layerType==LayerType::Input?"INPUT":"OUTPUT")+" DATA",INT_POS_1);
  listDataTypes();

  Data::Type* types=new Data::Type[countData];
  for(int i=INT_0;i<countData;i++){
    std::string info="Enter the Data::Type to convert "+std::string(layerType==LayerType::Input?"INPUT":"OUTPUT")+"["+std::to_string(i)+"]";

    getValue<Data::Type>(info,types[i],COUNT_DATA_TYPE);
  }

  return types;
}
Data::Limit** Menu::determineLimits(LayerType layerType,int countData,Data::Type* types,double scaledMin,double scaledMax){
  headline("LIMITS OF "+std::string(layerType==LayerType::Input?"INPUT":"OUTPUT")+" DATA",INT_POS_2);

  Data::Limit** limits=new Data::Limit*[countData];
  int selectionMin;
  int selectionMax;

  for(int i=INT_0;i<countData;i++){
    if(types[i]==Data::Type::Native){
      std::string info="Default minimum value of "+std::string(layerType==LayerType::Input?"INPUT":"OUTPUT")+"["+std::to_string(i)+"]";
      std::cout.width(WIDTH_INPUT_TEXT);
      std::cout<<std::left<<info<<": 0"<<std::endl;

      info="Default maximum value of "+std::string(layerType==LayerType::Input?"INPUT":"OUTPUT")+"["+std::to_string(i)+"]";
      std::cout.width(WIDTH_INPUT_TEXT);
      std::cout<<std::left<<info<<": 1"<<std::endl;

      if(layerType==LayerType::Input){
        limits[i]=new Data::Limit(types[i],LayerType::Input);
      }
      else if(layerType==LayerType::Output){
        limits[i]=new Data::Limit(types[i],LayerType::Output,scaledMin,scaledMax);
      }
    }else{
      std::string info="Enter the minimum value of "+std::string(layerType==LayerType::Input?"INPUT":"OUTPUT")+"["+std::to_string(i)+"]";
      getValue<int>(info,selectionMin);

      info="Enter the maximum value of "+std::string(layerType==LayerType::Input?"INPUT":"OUTPUT")+"["+std::to_string(i)+"]";
      getValue<int>(info,selectionMax);

      if(layerType==LayerType::Input){
        limits[i]=new Data::Limit(types[i],LayerType::Input,selectionMin,selectionMax);
      }
      else if(layerType==LayerType::Output){
        limits[i]=new Data::Limit(types[i],LayerType::Output,selectionMin,selectionMax,scaledMin,scaledMax);
      }
    }
  }

  return limits;
}


InputLayerPattern* Menu::determineInputLayerPattern(){
  headline("NUMBER OF INPUT DATA",INT_POS_2);

  int countInput;
  std::string info="Enter the number of input data";
  getValue<int>(info,countInput,INT_POS_1,INT_POS_1);

  Data::Type* types=determineDataTypes(LayerType::Input,countInput);
  Data::Limit** limits=determineLimits(LayerType::Input,countInput,types);
  InputLayerPattern* inputLayerPattern=new InputLayerPattern(countInput,types,limits);

  for(int i=INT_0;i<countInput;i++){
    delete limits[i];
  }
  delete[] limits;
  delete[] types;

  return inputLayerPattern;
}

size_t* Menu::determineCellNumbersOfHiddenLayers(int countHiddenLayer){
  headline("CELL NUMBERS OF HIDDEN LAYERS",INT_POS_2);

  size_t* countsHiddenCell=new size_t[countHiddenLayer];
  for(int i=INT_0;i<countHiddenLayer;i++){
    std::string info="Enter the cell number of HIDDEN LAYER["+std::to_string(i)+"]";
    getValue<size_t>(info,countsHiddenCell[i],INT_POS_1,INT_POS_1);
  }

  return countsHiddenCell;
}
Cell::SummationFunction::Type* Menu::determineSummationFunctionTypesOfHiddenLayers(int countHiddenLayer){
  headline("SUMMATION FUNCTIONS OF HIDDEN LAYERS",INT_POS_1);
  listSummationFunctions();

  Cell::SummationFunction::Type* sumFuncTypes=new Cell::SummationFunction::Type[countHiddenLayer];
  for(int i=INT_0;i<countHiddenLayer;i++){
    std::string info="Enter the summation function of HIDDEN LAYER["+std::to_string(i)+"]";
    getValue<Cell::SummationFunction::Type>(info,sumFuncTypes[i],COUNT_SUMMATION_FUNCTION_TYPE);
  }

  return sumFuncTypes;
}
Cell::ActivationFunction::Type* Menu::determineActivationFunctionTypesOfHiddenLayers(int countHiddenLayer){
  headline("ACTIVATION FUNCTIONS OF HIDDEN LAYERS",INT_POS_1);
  listActivationFunctions();

  Cell::ActivationFunction::Type* actFuncTypes=new Cell::ActivationFunction::Type[countHiddenLayer];
  for(int i=INT_0;i<countHiddenLayer;i++){
    std::string info="Enter the activation function of HIDDEN LAYER["+std::to_string(i)+"]";
    getValue<Cell::ActivationFunction::Type>(info,actFuncTypes[i],COUNT_ACTIVATION_FUNCTION_TYPE);
  }

  return actFuncTypes;
}
HiddenLayerPattern* Menu::determineHiddenLayerPattern(){
  headline("NUMBER OF HIDDEN LAYER",INT_POS_2);

  size_t countLayer;
  std::string info="Enter the number of hidden layer";
  getValue<size_t>(info,countLayer,INT_POS_1,INT_POS_1);

  size_t* countsCell=determineCellNumbersOfHiddenLayers(countLayer);
  Cell::SummationFunction::Type* sumFuncTypes=determineSummationFunctionTypesOfHiddenLayers(countLayer);
  Cell::ActivationFunction::Type* actFuncTypes=determineActivationFunctionTypesOfHiddenLayers(countLayer);

  HiddenLayerPattern* hiddenLayerPattern=new HiddenLayerPattern(countLayer,countsCell,sumFuncTypes,actFuncTypes);

  delete[] countsCell;
  delete[] sumFuncTypes;
  delete[] actFuncTypes;

  return hiddenLayerPattern;
}

Cell::SummationFunction::Type Menu::determineSummationFunctionTypeOfOutputLayer(){
  headline("SUMMATION FUNCTION OF OUTPUT LAYER",INT_POS_1);
  listSummationFunctions();

  Cell::SummationFunction::Type sumFuncType;
  std::string info="Enter the summation function of OUTPUT LAYER";
  getValue<Cell::SummationFunction::Type>(info,sumFuncType,COUNT_SUMMATION_FUNCTION_TYPE);

  return sumFuncType;
}
Cell::ActivationFunction::Type Menu::determineActivationFunctionTypeOfOutputLayer(){
  headline("ACTIVATION FUNCTION OF OUTPUT LAYER",INT_POS_1);
  listActivationFunctions();

  Cell::ActivationFunction::Type actFuncType;
  std::string info="Enter the activation function of OUTPUT LAYER";
  getValue<Cell::ActivationFunction::Type>(info,actFuncType,COUNT_ACTIVATION_FUNCTION_TYPE);

  return actFuncType;
}
double* Menu::determineTolerances(int countData){
  headline("TOLERANCES OF OUTPUT DATA",INT_POS_2);

  double* tolerances=new double[countData];
  for(int i=INT_0;i<countData;i++){
    std::string info="Enter the tolerance of OUTPUT["+std::to_string(i)+"]";
    getValue<double>(info,tolerances[i],INT_POS_2,DOUBLE_0,DOUBLE_POS_1);
  }

  return tolerances;
}
OutputLayerPattern* Menu::determineOutputLayerPattern(){
  headline("NUMBER OF OUTPUT DATA",INT_POS_2);
  int countOutput;
  std::string info="Enter the number of output data";
  getValue<int>(info,countOutput,INT_POS_1,INT_POS_1);

  Data::Type* types=determineDataTypes(LayerType::Output,countOutput);
  Cell::SummationFunction::Type sumFuncType=determineSummationFunctionTypeOfOutputLayer();
  Cell::ActivationFunction::Type actFuncType=determineActivationFunctionTypeOfOutputLayer();
  double scaledMin=Cell::ActivationFunction::rangeMin(actFuncType);
  double scaledMax=Cell::ActivationFunction::rangeMax(actFuncType);
  Data::Limit** limits=determineLimits(LayerType::Output,countOutput,types,scaledMin,scaledMax);
  double* tolerances=determineTolerances(countOutput);
  OutputLayerPattern* outputLayerPattern=new OutputLayerPattern(countOutput,types,limits,tolerances,sumFuncType,actFuncType);

  delete[] types;
  for(int i=INT_0;i<countOutput;i++){
    delete limits[i];
  }
  delete[] limits;
  delete[]tolerances;

  return outputLayerPattern;
}

double Menu::determineSingleTrainingParameter(std::string parameterName){
  double parameter;
  std::string info="Enter "+parameterName;
  getValue<double>(info,parameter);

  return parameter;
}
double* Menu::determineTrainingParameters(){
  double* parameters=new double[COUNT_TRAINING_PARAMETER];//lambda,alfa,randomMin,randomWeightMax

  headline("TRAINING SETTINGS",INT_POS_2);
  parameters[0]=determineSingleTrainingParameter("Lambda");
  parameters[1]=determineSingleTrainingParameter("Alfa");
  parameters[2]=determineSingleTrainingParameter("Random weight min");
  parameters[3]=determineSingleTrainingParameter("Random weight max");

  return parameters;
}

char Menu::determineSeparator(){
  headline("SEPARATOR CHARACTER",INT_POS_1);
  listSeparatorCharacters();
  Separator separator;

  std::string info="Enter the separator character";
  getValue<Separator>(info,separator,COUNT_SEPARATOR);

  return SEPARATORS[(int)separator];
}
std::string Menu::determineParametersFileName(){
  headline("FILE NAME",INT_POS_2);
  std::string fileName;

  std::string info="Enter the file name";
  getValue(info,fileName,true);
  return fileName;
}
std::string Menu::determineParametersFileLocation(){
  headline("FILE LOCATION",INT_POS_2);
  std::string fileLocation;

  std::string info="Enter the location of the file";
  getValue(info,fileLocation,false);

  return fileLocation;
}

NeuralNetwork* Menu::determineNeuralNetwork(){
  headline("OPEN OR CREATE A NEURAL NETWORK",INT_POS_1);
  listDetermineNNItems();

  std::string info="Enter your selection";
  NeuralNetworkDefinition NNDefinition;
  getValue<NeuralNetworkDefinition>(info,NNDefinition,COUNT_NEURALNETWORK_DEFINITION);

  NeuralNetwork* neuralNetwork;

  switch((int)NNDefinition){
    case 0:
    {
      char separator=determineSeparator();
      std::string parametersFile=determineParametersFileLocation();

      neuralNetwork=new NeuralNetwork(parametersFile,separator);
      break;
    }
    case 1:
    {
      InputLayerPattern* inputLayerPattern=determineInputLayerPattern();
      HiddenLayerPattern* hiddenLayerPattern=determineHiddenLayerPattern();
      OutputLayerPattern* outputLayerPattern=determineOutputLayerPattern();
      double* trainingParameters=determineTrainingParameters();
      double lambda=trainingParameters[0];
      double alfa=trainingParameters[1];
      double randomWeightMin=trainingParameters[2];
      double randomWeightMax=trainingParameters[3];
      char separator=determineSeparator();
      std::string parametersFile=determineParametersFileName();

      neuralNetwork=new NeuralNetwork(lambda,alfa,*inputLayerPattern,*hiddenLayerPattern,*outputLayerPattern,parametersFile,separator,randomWeightMin,randomWeightMax);

      delete inputLayerPattern;
      delete hiddenLayerPattern;
      delete outputLayerPattern;
      delete[] trainingParameters;

      break;
    }
  }

  return neuralNetwork;
}

Menu::Operation Menu::determineOperation(){
  headline("OPERATION",INT_POS_1);
  listOperations();
  Operation operation;

  std::string info="Enter the operation";
  getValue<Operation>(info,operation,COUNT_OPERATION);

  return operation;
}

void Menu::informAboutNN(const NeuralNetwork*const neuralNetwork){
  headline("INFORMATION",INT_POS_2);

  std::cout<<"\nInput Layer:"<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Number of inputs"<<": "<<neuralNetwork->getInputLayerPattern()->getCountOriginal()<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Number of cells of input layer"<<": "<<neuralNetwork->getInputLayerPattern()->getTotalLength()<<"\n"<<std::endl;


  for(int i=0;i<neuralNetwork->getInputLayerPattern()->getCountOriginal();i++){
    std::string info="Minimum value of INPUT["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<neuralNetwork->getInputLayerPattern()->getLimit(i)->getOriginalMin()<<std::endl;

    info="Maximum value of INPUT["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<neuralNetwork->getInputLayerPattern()->getLimit(i)->getOriginalMax()<<std::endl;

    info="Data type of INPUT["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<DATA_TYPES[(int)neuralNetwork->getInputLayerPattern()->getType(i)]<<std::endl;

    info="Number of cells of INPUT["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<neuralNetwork->getInputLayerPattern()->getLength(i)<<"\n"<<std::endl;
  }

  std::cout<<"\nHidden Layers:"<<std::endl;
  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Number of hidden layers"<<": "<<neuralNetwork->getHiddenLayerPattern()->getCountLayer()<<"\n"<<std::endl;

  for(int i=0;i<neuralNetwork->getHiddenLayerPattern()->getCountLayer();i++){
    std::string info="Number of cells of HIDDEN LAYER["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<neuralNetwork->getHiddenLayerPattern()->getCountCell(i)<<std::endl;

    info="Summation function of HIDDEN LAYER["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<SUM_FUNC_TYPES[(int)neuralNetwork->getHiddenLayerPattern()->getSumFunc(i)->getType()]<<std::endl;

    info="Activation function of HIDDEN LAYER["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<ACT_FUNC_TYPES[(int)neuralNetwork->getHiddenLayerPattern()->getActFunc(i)->getType()]<<"\n"<<std::endl;
  }

  std::cout<<"\nOutput Layer:"<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Number of outputs"<<": "<<neuralNetwork->getOutputLayerPattern()->getCountOriginal()<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Number of cells of output layer"<<": "<<neuralNetwork->getOutputLayerPattern()->getTotalLength()<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Summation function of output layer"<<": "<<SUM_FUNC_TYPES[(int)neuralNetwork->getOutputLayerPattern()->getSumFunc()->getType()]<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Activation function of output layer"<<": "<<ACT_FUNC_TYPES[(int)neuralNetwork->getOutputLayerPattern()->getActFunc()->getType()]<<"\n"<<std::endl;

  for(int i=0;i<neuralNetwork->getOutputLayerPattern()->getCountOriginal();i++){
    std::string info="Minimum value of OUTPUT["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<neuralNetwork->getOutputLayerPattern()->getLimit(i)->getOriginalMin()<<std::endl;

    info="Maximum value of OUTPUT["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<neuralNetwork->getOutputLayerPattern()->getLimit(i)->getOriginalMax()<<std::endl;

    info="Data type of OUTPUT["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<DATA_TYPES[(int)neuralNetwork->getOutputLayerPattern()->getType(i)]<<std::endl;

    info="Tolerance of OUTPUT["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<neuralNetwork->getOutputLayerPattern()->getTolerance(i)<<std::endl;

    info="Number of cells of OUTPUT["+std::to_string(i)+"]";
    std::cout.width(WIDTH_INPUT_TEXT);
    std::cout<<std::left<<info<<": "<<neuralNetwork->getOutputLayerPattern()->getLength(i)<<"\n"<<std::endl;
  }


  std::cout<<"\nTraining Properties:"<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Lambda"<<": "<<neuralNetwork->getLambda()<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Alfa"<<": "<<neuralNetwork->getAlfa()<<"\n"<<std::endl;



  std::cout<<"\nFile Properties:"<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Neural network file"<<": "<<neuralNetwork->getParametersFile()<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Errors and updated weights file"<<": "<<neuralNetwork->getLogEW()->getFile()<<std::endl;

  std::cout.width(WIDTH_INPUT_TEXT);
  std::cout<<std::left<<"Separator character"<<": "<<neuralNetwork->getSeparator()<<std::endl;

}

void Menu::execOperation(NeuralNetwork* neuralNetwork){
  Operation operation=determineOperation();

  std::string info;
  switch(operation){
    case Operation::Train:
    {
      headline("TRAIN",INT_POS_2);

      info="Enter the location of the training file";
      std::string fileLocation;
      getValue(info,fileLocation,false);

      info="Enter the number of samples";
      int countSample;
      getValue<int>(info,countSample,INT_POS_1,INT_POS_1);

      neuralNetwork->train(countSample,fileLocation);
      break;
    }
    case Operation::Test:
    {
      headline("TEST",INT_POS_2);

      info="Enter the location of the test file";
      std::string fileLocation;
      getValue(info,fileLocation,false);

      info="Enter the number of samples";
      int countSample;
      getValue<int>(info,countSample,INT_POS_1,INT_POS_1);

      double successRate=neuralNetwork->test(countSample,fileLocation);

      std::cout<<"Success Rate : "<<100.0*successRate<<"%"<<std::endl;
      break;
    }
    case Operation::Run:
    {
      headline("RUN",INT_POS_2);

      int countInput=neuralNetwork->getInputLayerPattern()->getCountOriginal();
      int countOutput=neuralNetwork->getOutputLayerPattern()->getCountOriginal();
      int* inputs=new int[countInput];

      for(int i=0;i<countInput;i++){
        std::string info="Enter INPUT["+std::to_string(i)+"]";
        int minValue=neuralNetwork->getInputLayerPattern()->getLimit(i)->getOriginalMin();
        int maxValue=neuralNetwork->getInputLayerPattern()->getLimit(i)->getOriginalMax();
        getValue<int>(info,inputs[i],INT_POS_2,minValue,maxValue);
      }

      double* outputs=neuralNetwork->run(inputs);

      for(int i=0;i<countOutput;i++){
        std::cout.width(WIDTH_INPUT_TEXT);
        std::cout<<std::left<<"OUTPUT["+std::to_string(i)+"]"<<": "<<outputs[i]<<std::endl;
      }

      delete[] inputs;
      delete[] outputs;
      break;
    }
    case Operation::Inform:
    {
      informAboutNN(neuralNetwork);
      break;
    }
  }

}

std::istream& operator>>(std::istream& inputStream, Menu::MainMenu& mainMenu){
  int tempMainMenu;
  if(inputStream>>tempMainMenu)
  mainMenu=(Menu::MainMenu)tempMainMenu;

  return inputStream;
}
std::istream& operator>>(std::istream& inputStream, Data::Type& dataType){
  int tempDataType;
  if(inputStream>>tempDataType)
  dataType=(Data::Type)tempDataType;

  return inputStream;
}
std::istream& operator>>(std::istream& inputStream,Cell::SummationFunction::Type& summationFunctionType){
  int tempSummationFunctionType;
  if(inputStream>>tempSummationFunctionType)
  summationFunctionType=(Cell::SummationFunction::Type)tempSummationFunctionType;

  return inputStream;
}
std::istream& operator>>(std::istream& inputStream,Cell::ActivationFunction::Type& activationFunctionType){
  int tempActivationFunctionType;
  if(inputStream>>tempActivationFunctionType)
  activationFunctionType=(Cell::ActivationFunction::Type)tempActivationFunctionType;

  return inputStream;
}
std::istream& operator>>(std::istream& inputStream, Menu::Separator& separator){
  int tempSeparator;
  if(inputStream>>tempSeparator)
  separator=(Menu::Separator)tempSeparator;

  return inputStream;
}
std::istream& operator>>(std::istream& inputStream, Menu::NeuralNetworkDefinition& definition){
  int tempDefinition;
  if(inputStream>>tempDefinition)
  definition=(Menu::NeuralNetworkDefinition)tempDefinition;

  return inputStream;
}
std::istream& operator>>(std::istream& inputStream, Menu::Operation& operation){
  int tempOperation;
  if(inputStream>>tempOperation)
  operation=(Menu::Operation)tempOperation;

  return inputStream;
}
