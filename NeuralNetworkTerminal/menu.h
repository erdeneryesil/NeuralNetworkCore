#ifndef MENU_H
#define MENU_H

#include<iostream>
#include<string>
#include"neural_network_core/neural_network.h"


#define COUNT_MAIN_MENU_ITEM 3 //DetermineNN, ExecOperation, Exit
#define COUNT_NEURALNETWORK_DEFINITION 2 //create or open
#define COUNT_DATA_TYPE 4
#define COUNT_ACTIVATION_FUNCTION_TYPE 6
#define COUNT_SUMMATION_FUNCTION_TYPE 6
#define COUNT_TRAINING_PARAMETER 4
#define COUNT_SEPARATOR 4
#define COUNT_OPERATION 4
#define IRRELEVANT_MIN_VALUE -99
#define IRRELEVANT_MAX_VALUE 99
#define WIDTH_INPUT_TEXT 50
#define SEPARATORS (char[]){' ',',',';','|'}
#define ASCI_a 65
#define ASCI_z 90
#define ASCI_A 97
#define ASCI_Z 122
#define ASCI_0 48
#define ASCI_9 57
#define ASCI_UNDERSCORE 95
#define DATA_TYPES (std::string[]){"Binary","Flag","Narrowed","Native"}
#define SUM_FUNC_TYPES (std::string[]){"WeightedTotal","Multiplication","Maximum","Minimum","Majority","IncrementalTotal"}
#define ACT_FUNC_TYPES (std::string[]){"Sigmoid","TanH","ReLU","LeakyReLU","Swish","Softplus"}


class Menu{
public:
  enum class MainMenu{DetermineNN,ExecOperation,Exit};
  enum class NeuralNetworkDefinition{Open,New};
  enum class Separator{Space,Comma,Semicolon,Pipe};
  enum class Operation{Train,Test,Run,Inform};

  template<typename EnumType>
  static typename std::enable_if<std::is_enum<EnumType>::value,void>::type getValue(std::string info,EnumType& value,int countItem) {
    bool confirm;
    do{
      confirm=true;
      std::cout.width(WIDTH_INPUT_TEXT);
      std::cout<<std::left<<info<<": ";
      std::cin>>value;
      if(std::cin.fail() || (int)value<INT_0 || (int)value>=countItem){
        std::cout<<"!!!Wrong Choise!!!\n";
        confirm=false;
        std::cin.clear();
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while(!confirm);
  }

  template<typename NonEnumType>
  static typename std::enable_if<!std::is_enum<NonEnumType>::value,void>::type getValue(std::string info,NonEnumType& value,int countBoundary=INT_0,NonEnumType lowerBound=IRRELEVANT_MIN_VALUE,NonEnumType upperBound=IRRELEVANT_MAX_VALUE) {
    bool confirm;
    do{
      confirm=true;
      std::cout.width(WIDTH_INPUT_TEXT);
      std::cout<<std::left<<info<<": ";
      std::cin>>value;
      switch(countBoundary){
        case 0:
        if(std::cin.fail())
        confirm=false;
        break;
        case 1:
        if(std::cin.fail() || value<lowerBound)
        confirm=false;
        break;
        case 2:
        if(std::cin.fail() || value<lowerBound || value>upperBound)
        confirm=false;
        break;
      }

      if(!confirm){
        std::cout<<"!!!Wrong Choise!!!\n";
        std::cin.clear();
      }

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while(!confirm);
  }

  static void getValue(std::string info,std::string& value,bool onlyAllowedCharacters){
    bool confirm;
    do{
      confirm=true;
      std::cout.width(WIDTH_INPUT_TEXT);
      std::cout<<std::left<<info<<": ";
      std::cin>>value;

      if(onlyAllowedCharacters){
        for(int i=0;i<value.length();i++){
          if(!(((int)value[i]>=ASCI_a && (int)value[i]<=ASCI_z) || ((int)value[i]>=ASCI_A && (int)value[i]<=ASCI_Z) || ((int)value[i]>=ASCI_0 && (int)value[i]<=ASCI_9) || (int)value[i]==ASCI_UNDERSCORE)){
            confirm=false;
            break;
          }
        }
      }

      if(!confirm){
        std::cout<<"!!!Wrong Choise!!!\n";
        std::cin.clear();
      }

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while(!confirm);
  }

  static void listMainMenuItems();
  static void listDetermineNNItems();
  static void listDataTypes();
  static void listSummationFunctions();
  static void listActivationFunctions();
  static void listSeparatorCharacters();
  static void listOperations();
  static void headline(std::string title,int countTrailingNewline);

  static Data::Type* determineDataTypes(LayerType layerType,int countData);
  static Data::Limit** determineLimits(LayerType layerType,int countData,Data::Type* types,double scaledMin=IRRELEVANT_MIN_VALUE,double scaledMax=IRRELEVANT_MAX_VALUE);

  static InputLayerPattern* determineInputLayerPattern();

  static size_t* determineCellNumbersOfHiddenLayers(int countHiddenLayer);
  static Cell::SummationFunction::Type* determineSummationFunctionTypesOfHiddenLayers(int countHiddenLayer);
  static Cell::ActivationFunction::Type* determineActivationFunctionTypesOfHiddenLayers(int countHiddenLayer);
  static HiddenLayerPattern* determineHiddenLayerPattern();

  static Cell::SummationFunction::Type determineSummationFunctionTypeOfOutputLayer();
  static Cell::ActivationFunction::Type determineActivationFunctionTypeOfOutputLayer();
  static double* determineTolerances(int countData);
  static OutputLayerPattern* determineOutputLayerPattern();

  static double determineSingleTrainingParameter(std::string parameterName);
  static double* determineTrainingParameters();

  static char determineSeparator();

  static std::string determineParametersFileName();

  static std::string determineParametersFileLocation();

  static NeuralNetwork* determineNeuralNetwork();

  static Operation determineOperation();

  static void informAboutNN(const NeuralNetwork*const neuralNetwork);

  static void execOperation(NeuralNetwork* neuralNetwork);

  friend std::istream& operator>>(std::istream& inputStream, Menu::MainMenu& mainMenu);
  friend std::istream& operator>>(std::istream& inputStream, Data::Type& dataType);
  friend std::istream& operator>>(std::istream& inputStream,Cell::SummationFunction::Type& summationFunctionType);
  friend std::istream& operator>>(std::istream& inputStream,Cell::ActivationFunction::Type& activationFunctionType);
  friend std::istream& operator>>(std::istream& inputStream, Menu::Separator& separator);
  friend std::istream& operator>>(std::istream& inputStream, Menu::NeuralNetworkDefinition& definition);
  friend std::istream& operator>>(std::istream& inputStream, Menu::Operation& operation);
};

#endif // MENU_H
