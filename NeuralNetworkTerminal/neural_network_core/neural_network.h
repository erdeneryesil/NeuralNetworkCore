#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include"cell.h"
#include"data.h"
#include<string>

//-------------------------------------------------
class InputLayerPattern{/*Contains and manages the features of the input layer of a artificial neural network.
                          This class can be considered as a template. The features of the input layer are handled by this class.
                          But cells(or neurons) that compose the input layer of a artificial neural network are not included in this class.
                          In the content of this class, how many real-world data are passed to the input of an artificial neural network, which ANN data types that real-world data are converted to, how many cells each real-world data is represented, etc.
                        */
protected:
  //This class is also the base class from which derived OutputLayerPattern. Therefore, all of the following variables are also members OutputLayerPattern class.
  size_t _countOriginal;// Stores the number of real-world data in the input layer (or output layer).
  Data::Type* _types;// Stores the ANN data types that real-world data converted to. The number of elements of this array is equal to variable _countOriginal.
  Data::Limit** _limits;// Stores minimum and maximum limits of data in the input layer(or output layer). The number of elements of this array is equal to varibale _countOriginal.
  size_t* _lengths;// Stores the number of cells of each ANN data. The number of elements of this array is equal to varibale _countOriginal.
  size_t _totalLength;// Stores the number of all cells in the input layer(or output layer).
public:
  InputLayerPattern(const size_t& countOriginal,const Data::Type*const types,const Data::Limit*const*const limits);// Constructor. Parameters : Number of real-world data(countOriginal) - Array of ANN data types(types) - Array of minimum and maximum limits of data(limits).
  InputLayerPattern(const size_t& countOriginal,const Data::Type& type,const Data::Limit& limit);// Constructor. This used if all ANN data types are the same. Parameters : Number of real-world data(countOriginal) - ANN data type(type) - Minimum and maximum limit of data(limit).
  InputLayerPattern(const InputLayerPattern& inputLayerPatternObj);// Copy constructor.
  ~InputLayerPattern();// Destructor
  size_t getCountOriginal()const;// Returns _countOriginal.
  size_t getLength(const size_t& index)const;// Returns _lengths[index]. Parameters : Index of the ANN data(index).
  size_t getTotalLength()const;// Returns _totalLength.
  Data::Type getType(const size_t& index)const;// Returns _types[index]. Parameters : Index of the ANN data(index).
  const Data::Limit* getLimit(const size_t& index)const;// Returns _limits[index]. Parameters : Index of the ANN data(index).
  TransformedData** createSample(const int*const originals)const;// Takes the real world data of a sample to be passed as input to the artificial neural network as a parameter and returns it by converting it to ANN data types. Parameters : Real world data of an example(originals(array)).
};
//-------------------------------------------------
class OutputLayerPattern:public InputLayerPattern{/*Contains and manages the features of the output layer of a artificial neural network.
                                                    Inherited from class InputLayerPattern.
                                                    This class can be considered as a template just like class InputLayerPattern.
                                                    Cells(or neurons) that compose the output layer of a artificial neural network are not included in this class.
                                                    Features such as how many cells are in the output layer or what real world data the outputs from these cells will be converted to are handled by this class.
                                                  */
  double* _tolerances;// Stores tolerances of the output cells. The number of elements of this array is equal to number of all output cells (_totalLength).
  Cell::SummationFunction* _sumFunc;// Stores an instance of SummationFunction object as a pointer. It represents the preferred summation function of the output layer and executes calculations according to this summation function.
  Cell::ActivationFunction* _actFunc;// Stores an instance of ActivationFunction object as a pointer. It represents the preferred activation function of the output layer and executes calculations according to this activation function.
public:
  OutputLayerPattern(const size_t& countOriginal,const Data::Type*const types,const Data::Limit*const*const limits,const double*const tolerances,const Cell::SummationFunction::Type& sumFuncType,const Cell::ActivationFunction::Type& actFuncType);// Constructor. Parameters : Number of real-world data(countOriginal) - Array of ANN data types(types) - Array of minimum and maximum limits of data(limits) - Array of tolerances(tolerances) - Type of the preferred summation function(sumFuncType) - Type of the preferred activation function(actFuncType).
  OutputLayerPattern(const size_t& countOriginal,const Data::Type& type,const Data::Limit& limit,const double& tolerance,const Cell::SummationFunction::Type& sumFuncType,const Cell::ActivationFunction::Type& actFuncType);// Constructor. This used if all output data types are the same. Parameters : Number of real-world data(countOriginal) - ANN data type(type) - Minimum and maximum limit of data(limit) - The tolerance value(tolerance) - Type of the preferred summation function(sumFuncType) - Type of the preferred activation function(actFuncType).
  OutputLayerPattern(const OutputLayerPattern& outputLayerPatternObj);// Copy constructor.
  ~OutputLayerPattern();// Destructor.
  double getTolerance(const size_t& index)const;// Returns _tolerances[index]. Parameters : Index of the ANN data(index).
  const Cell::SummationFunction* getSumFunc()const;// Returns _sumFunc.
  const Cell::ActivationFunction* getActFunc()const;// Returns _actFunc.
  void setSumFunc(const Cell::SummationFunction::Type& sumFuncType);// Makes the necessary assignments to _sumFunc, depending on the type of the summation function passed as a parameter. Parameters : Type of the preferred summation function(sumFuncType).
  void setActFunc(const Cell::ActivationFunction::Type& actFuncType);// Makes the necessary assignments to _actFunc, depending on the type of the activation function passed as a parameter. Parameters : Type of the preferred activation function(actFuncType).
  void setTolerance(const size_t& index,const double& tolerance);// Assigns the tolerance value to _tolerances[index]. Parameters : Index of the ANN data(index) - Tolerance value(tolerance).
};
//-------------------------------------------------
class HiddenLayerPattern{/* Contains and manages the features of the hidden layers of a artificial neural network.
                            This class can be considered as a template just like classes InputLayerPattern and OutputLayerPattern.
                            Cells(or neurons) that compose the hidden layers of a artificial neural network are not included in this class.
                            The number of hidden layers, the number of cells of each hidden layer, the summation and activation functions of each hidden layer are stored in this class.
                        */
  size_t _countLayer;// Stores the number of hidden layers of the artificial neural network.
  size_t *_countsCell;// Stores the number of cells in each hidden layer. The number of elements of this array is equal to varibale _countLayer.
  Cell::SummationFunction** _sumFuncs;// This array stores instances of SummationFunction objects as pointer. That is a pointer array and the number of elements of it is equal to variable _countLayer.
  Cell::ActivationFunction** _actFuncs;// This array stores instances of ActivationFunction objects as pointer. That is a pointer array and the number of elements of it is equal to variable _countLayer.
public:
  HiddenLayerPattern(const size_t& countLayer,const size_t*const countsCell,const Cell::SummationFunction::Type*const sumFuncTypes,const Cell::ActivationFunction::Type*const actFuncTypes);// Constructor. Parameters : Number of hidden layer(countLayer) - The array containing the number of cells in each hidden layer(countsCell) - Array of the preferred summation function types(sumFuncTypes) - Array of the preferred activation function types(actFuncTypes).
  HiddenLayerPattern(const HiddenLayerPattern& hiddenLayerPatternObj);// Copy constructor.
  ~HiddenLayerPattern();// Destructor.
  size_t getCountLayer()const;// Returns _countLayer.
  size_t getCountCell(const size_t& index)const;// Returns _countsCell[index]. Parameters : Index of the hidden layer(index).
  const Cell::SummationFunction* getSumFunc(const size_t& index)const;// Returns _sumFuncs[index]. Parameters : Index of the hidden layer(index).
  const Cell::ActivationFunction* getActFunc(const size_t& index)const;// Returns _actFuncs[index]. Parameters : Index of the hidden layer(index).
  void setSumFunc(const size_t& index,const Cell::SummationFunction::Type& sumFuncType);// Makes the necessary assignments to _sumFuncs[index], depending on the type of summation function passed as a parameter. Parameters : Index of the hidden layer(index) - Type of the preferred summation function(sumFuncType).
  void setActFunc(const size_t& index,const Cell::ActivationFunction::Type& actFuncType);// Makes the necessary assignments to _actFuncs[index], depending on the type of activation function passed as a parameter. Parameters : Index of the hidden layer(index) - Type of the preferred activation function(actFuncType).
};
//-------------------------------------------------
class LogEW{/*LogEW is abbreviation for 'Log of Errors(E) and updated Weights(W)'.
              Training a neural network with all training data for one cycle is called 'epoch'.
              Class LogEW stores both total error values calculated and number of updated weights in a file at the end of an epoch. And repeats that every epoch.
              This file also contains the properties that the network had at the time of that training.
              The following are the data saved in the LogEW file.
                        - Summation and activation functions of hidden layers and output layer (Because they are can be changed for each training).
                        - Tolerances of the output layer data (Because they are can be changed for each training).
                        - Lambda and alfa values of the neural network (Because they are can be changed for each training).
                        - The number of samples to be used in the training.
                        - At the end of each period, both the calculated total error value and the number of updated weights.

              The features mentioned in the first 4 of the 5 items listed above are added to the LogEW file only once for each training.
              However, both the total calculated errors and the number of updated weights are added to the LogEW file at the end of each cycle throughout the training.
              Any training can go on for thousands of epochs.

              LogEW file stores records for each training in a single line. So, the number of lines in the LogEW file means the number of trainings.
            */
private:
  const HiddenLayerPattern*const _hiddenLayerPatternOfNN;// The HiddenLayerPattern object pointer of the NeuralNetwork object during the training in question. Used to access the hidden layer features.
  const OutputLayerPattern*const _outputLayerPatternOfNN;// The OutputLayerPattern object pointer of the NeuralNetwork object during the training in question. Used to access the output layer features.
  const char*const _separatorOfNN;// The data in the LogEW and neural network files are ordered one after another using the separator character. For example comma(,), semicolon(;), pipe(|), space( ).
  const double*const _lambdaOfNN; // The lambda value of the NeuralNetwork object during the training in question.
  const double*const _alfaOfNN;// The alfa value of the NeuralNetwork object during the training in question.

  std::string _file;// Stores the location and name of LogEW file.

  size_t _countTraining;// Stores that how many times the neural network has been trained. In order to detect this, it is checked how many rows of data the LogEW file contains. Because each training is on one line.
  Cell::SummationFunction::Type** _sumFuncTypesOfHiddenLayer;// Stores summation function types used in the hidden layers in each training stored in LogEW file. It is two-dimensional array. The first dimension represents trainings and the second dimension represents hidden layers.
  Cell::ActivationFunction::Type** _actFuncTypesOfHiddenLayer;// Stores activation function types used in the hidden layers in each training stored in LogEW file. It is two-dimensional array. The first dimension represents trainings and the second dimension represents hidden layers.
  Cell::SummationFunction::Type* _sumFuncTypesOfOutputLayer;// Stores the summation function type used in the output layer in each training stored in LogEW file. It is single-dimensional array. That single dimension represents trainings.
  Cell::ActivationFunction::Type* _actFuncTypesOfOutputLayer;// Stores the activation function type used in the output layer in each training stored in LogEW file. It is single-dimensional array. That single dimension represents trainings.
  double** _tolerances;// Stores tolerance values used in the output layers in each training stored in LogEW file. It is two-dimensional array. The first dimension represents trainings and the second dimension represents number of the data in output layer.
  double* _lambdas;// Stores lambda value of the artificial neural network in each training stored in LogEW file. It is single-dimensional array. That single dimension represents trainings.
  double* _alfas;// Stores alfa value of the artificial neural network in each training stored in LogEW file. It is single-dimensional array. That single dimension represents trainings.
  int* _countsSample;// Stores the number of samples used in each training stored in LogEW file. It is single-dimensional array. That single dimension represents trainings.
  size_t* _countsEW;// Stores the number of errors or updated weights in each training stored in LogEW file.It also represents the number of epoch. It is single-dimensional array. That single dimension represents trainings.
  double** _errorValues;// Stores the error values calculated as a result of each epoch in the trainings stored in the LogEW file. It is a two-dimensional array. The first dimension represents the trainings and the second dimension represents the epochs.
  size_t** _updatedWeights;// Stores the numbers of updated weights as a result of each epoch in the trainings stored in the LogEW file. It is a two-dimensional array. The first dimension represents the trainings and the second dimension represents the epochs.

  double _newErrorValue;// Stores the current error value calculated while the neural network is being trained.
  size_t _newUpdatedWeight;// Stores the current number of updated weights while the neural network is being trained.

  void _loadOneTrainingFromFile(const size_t& indexTraining,const std::string& lineFromFile);// Reads the line corresponding to the index value in the LogEW file, the line represents a single training, and then extracts the data in that line and makes assignments to the necessary variables. Parameters : Index(or line number) of the training(indexTraining) - The line in LogEW file(lineFromFile).
  void _clearData(size_t countLoadedTrainig);// Deletes from memory all arrays defined as pointer in this class.

public:
  LogEW(const std::string& fileEW,const HiddenLayerPattern*const hiddenLayerPatternOfNN,const OutputLayerPattern*const outputLayerPatternOfNN,const char*const separatorOfNN,const double*const lambdaOfNN,const double*const alfaOfNN);// Constructor. Parameters : Location and name of LogEW file(fileEW) - Current HiddenLayerPattern and OutputLayerPattern object pointers of the NeuralNetwork object (hiddenLayerPatternOfNN, outputLayerPatternOfNN) - Separator character used in neural network and LogEW files(separatorOfNN) - Current lambda and alfa values of neural network(lambdaOfNN, alfaOfNN).
  ~LogEW();// Destructor.
  void createNewFile()const;// Creates a new LogEW file.
  std::string getFile()const;// Returns the location and name of LogEW file.
  bool isFileEmpty()const;// Returns whether LogEW file is empty or not.

  void addNewTrainingInFile(const int& countSample)const;// Creates a new line for the training in LogEW file. Parameters : Number of samples used in the training(countSample).
  void addErrorInFile(const double& errorValue,const size_t& updatedWeight)const;// During an ongoing training, at the end of an epoch, it saves the error value calculated and the number of updated weights in the LogEW file.

  void loadTrainingsFromFile();// Reads all trainings(or lines) saved in the LogEW file and makes the necessary assignments. This function uses _loadOneTrainingFromFile function.

  size_t getCountTraining()const;// Returns number of trainings or lines in LogEW file.
  Cell::SummationFunction::Type getSumFuncTypeOfHiddenLayer(const size_t& indexTraining,const size_t& indexHiddenLayer)const;// Returns _sumFuncTypesOfHiddenLayer[indexTraining][indexHiddenLayer]. Parameters : Index of the training in LogEW file(indexTraining) - Index of the hidden layer(indexHiddenLayer).
  Cell::ActivationFunction::Type getActFuncTypeOfHiddenLayer(const size_t& indexTraining,const size_t& indexHiddenLayer)const;// Returns _actFuncTypesOfHiddenLayer[indexTraining][indexHiddenLayer]. Parameters : Index of the training in LogEW file(indexTraining) - Index of the hidden layer(indexHiddenLayer).
  Cell::SummationFunction::Type getSumFuncTypeOfOutputLayer(const size_t& indexTraining)const;// Returns _sumFuncTypesOfOutputLayer[indexTraining]. Parameters : Index of the training in LogEW file(indexTraining).
  Cell::ActivationFunction::Type getActFuncTypeOfOutputLayer(const size_t& indexTraining)const;// Returns _actFuncTypesOfOutputLayer[indexTraining]. Parameters : Index of the training in LogEW file(indexTraining).
  double getTolerance(const size_t& indexTraining,const size_t& indexTolerance)const;// Returns _tolerances[indexTraining][indexTolerance]. Parameters : Index of the training in LogEW file(indexTraining) - Index of the tolerance value used in the output layer(indexTolerance).
  double getLambda(const size_t& indexTraining)const;// Returns _lambdas[indexTraining]. Parameters : Index of the training in LogEW file(indexTraining).
  double getAlfa(const size_t& indexTraining)const;// Returns _alfas[indexTraining]. Parameters : Index of the training in LogEW file(indexTraining).
  int getCountSample(const size_t& indexTraining)const;// Returns this->_countsSample[indexTraining]. Parameters : Index of the training in LogEW file(indexTraining).
  size_t getCountEWInATraining(const size_t& indexTraining)const;// Returns this->_countsEW[indexTraining]. Parameters : Index of the training in LogEW file(indexTraining).
  double getErrorValue(const size_t& indexTraining,const size_t& indexErrorValue)const;// Returns _errorValues[indexTraining][indexErrorValue]. Parameters : Index of the training in LogEW file(indexTraining) - Index of the error value(indexErrorValue).
  size_t getUpdatedWeight(const size_t& indexTraining,const size_t& indexUpdatedWeight)const;// Returns _updatedWeights[indexTraining][indexUpdatedWeight]. Parameters : Index of the training in LogEW file(indexTraining) - Index of the number of updated weight(indexUpdatedWeight).

  void setNewErrorValue(const double& errorValue);// Assigns the parameter value to _newErrorValue.
  double getNewErrorValue()const;// Returns _newErrorValue.
  void setNewUpdatedWeight(const size_t& updatedWeight);// Assigns the parameter value to _newUpdatedWeight.
  size_t getNewUpdatedWeight()const;// Returns _newUpdatedWeight.
};
//-------------------------------------------------
class NeuralNetwork{/*This class represents an artificial neural network.
                      Since all other classes model the components of an artificial neural network, they are directly or indirectly included in this class and build an artificial neural network.

                      When this class is instantiated, 2 files are created.
                      The first is the file (called the ANN file) where all the properties of the network are stored.
                      The second is the LogEW file, where the trainings applied to the artificial neural network is recorded, and the details about this file are specified in the LogEW class.
                      These two files are named using a user-specified phrase.
                      For example, if the user determined the name "my_ann" while creating the artificial neural network, the ANN file is named "my_ann" and the LogEw file is named "my_annEW".


                      Apart from ANN and LogEW files, training and test set samples should be stored in different files.
                      There is no relationship between the names of these files and the name of the artificial neural network. Training and test set files can have any name.


                      The data in the ANN file, LogEW file, training set file and test set file are ordered one after another using the separator character, and this separator character is determined by the user when creating the ANN.
                      There are 4 options that the user can specify as separator characters. These are space( ), comma(,), semicolon(;) and pipe(|) characters.
                    */
public:
    NeuralNetwork(const double& lambda,const double& alfa,const InputLayerPattern& inputLayerPattern,const HiddenLayerPattern& hiddenLayerPattern,const OutputLayerPattern& outputLayerPattern,const std::string& parametersFile,const char& separator,const double& randomWeightMin,const double& randomWeightMax);//Constructor. Parameters : Lambda value(lambda) - Alfa velue(alfa) - InputLayerPattern object(inputLayerPattern) - HiddenLayerPattern object(hiddenLayerPattern) - OutputLayerPattern object(outputLayerPattern) - Location and name of ANN file to be created(parametersFile) - Separator character to use in the files(separator) - The minimum and maximum values of the range of random numbers to be generated(randomWeightMin, randomWeightMax).
    NeuralNetwork(const std::string& parametersFile,const char& separator);//Constructor. Parameters : Location and name of ANN file(parametersFile) - Separator character used in the ANN file(separator).
    ~NeuralNetwork();// Destructor.

    double getLambda()const;// Returns _lambda.
    double getAlfa()const;// Returns _alfa.
    int getEpoch()const;// Returns _epoch.
    char getSeparator()const;// Returns _separator.
    std::string getParametersFile()const;// Returns _parametersFile.
    const HiddenLayerPattern* getHiddenLayerPattern()const;// Returns _hiddenLayerPattern.
    const OutputLayerPattern* getOutputLayerPattern()const;// Returns _outputLayerPattern.
    const InputLayerPattern* getInputLayerPattern()const;// Returns _inputLayerPattern.
    const LogEW* getLogEW()const;// Returns _logEW.

    void setLambda(const double& lambda);// Assigns the parameter value to _lambda.
    void setAlfa(const double& alfa);// Assigns the parameter value to _alfa.
    void setSumFuncOfHiddenLayer(const size_t& index,const Cell::SummationFunction::Type& sumFuncType);// Assigns the summation function of the indexed hidden layer depending on the type of the summation function passed as a parameter. Parameters : Index of the hidden layer(index) - Type of the preferred summation function(sumFuncType).
    void setActFuncOfHiddenLayer(const size_t& index,const Cell::ActivationFunction::Type& actFuncType);// Assigns the activation function of the indexed hidden layer depending on the type of the activation function passed as a parameter. Parameters : Index of the hidden layer(index) - Type of the preferred activation function(actFuncType).
    void setSumFuncOfOutputLayer(const Cell::SummationFunction::Type& sumFuncType);// Assigns the summation function of the output layer depending on the type of the summation function passed as a parameter.
    void setActFuncOfOutputLayer(const Cell::ActivationFunction::Type& actFuncType);// Assigns the activation function of the output layer depending on the type of the activation function passed as a parameter.
    void setTolerance(const size_t& index,const double& tolerance);// Assigns the tolerance of the indexed output data. Parameters : Index of the output data(index) - Tolerance value(tolerance).
    void saveNeuralNetwork()const;// Saves the current neural network to ANN file.

    int getCountLinesOfFile(const std::string& file);// Returns the number of lines of a file. Parameters : The location and name of the file(file).

    bool train(const int& countSample, const std::string& trainingSamplesFile);// Trains the neural network. Parameters : Number of samples of the training set(countSample) - Training set file (trainingSamplesFile).
    double* run(const int*const inputsOriginal);// Calculates the outputs of the inputs passed to the network. Parameters : Input values (inputsOriginal).
    double test(const int& countSample,const std::string& testSamplesFile);// Tests the neural network. Parameters : Number of samples of the test set(countSample) - Test set file (testSamplesFile).

private:
    InputLayerPattern* _inputLayerPattern;// Stores InputLayerPattern object pointer. Can be considered of as the input layer template of the neural network.
    InputCell** _inputCells;// An array that stores InputCell object pointers(InputCell*) that represent input layer cells. It is one-dimensional array.

    OutputLayerPattern* _outputLayerPattern;// Stores OutputLayerPattern object pointer. Can be considered of as the output layer template of the neural network.
    OutputCell** _outputCells;// An array that stores OutputCell object pointers(OutputCell*) that represent output layer cells. It is one-dimensional array.

    HiddenLayerPattern* _hiddenLayerPattern;// Stores HiddenLayerPattern object pointer. Can be considered of as the hidden layers template of the neural network.
    HiddenCell*** _hiddenCells;// An array that stores HiddenCell object pointers(HiddenCell*) that represent hidden layers cells. It is two-dimensional array. Because number of hidden layers is may be more than one.

    size_t _countBiasCell;// Stores the number of bias cell of the neural network.
    BiasCell** _biasCells;// An array that stores BiasCell object pointers(BiasCell*). It is one-dimensional array.

    double _lambda;// Stores lambda value of the neural network.
    double _alfa;// Stores alfa value of the neural network.
    int _epoch;// Stores the current epoch value, while the neural network is being trained.

    char _separator;// Stores the separator character used in ANN file, LogEW file, train set file and test set file.
    std::string _parametersFile;// Stores the location and name of ANN file.

    LogEW* _logEW;// Stores LogEW object pointer.

    int _correctCountSampleInFile(const int& countSample, const std::string& samplesFile);// If the number of samples to be used for training or testing is greater than the number of samples (number of lines) in the file, it returns the number of lines, otherwise it returns specified the number of samples. Parameters : The number of samples to be used(countSample) - Location and name of Training or test set file(samplesFile).
    const int*const* _convertSamplesFileToArray(const int& countSample, const std::string& samplesFile);// Returns the samples in the training or test set files as an array. Parameters : The number of samples to be used(countSample) - Location and name of Training or test set file(samplesFile).

    //Delta rule steps
    void _calculateNetsOfHiddenLayer(const size_t& indexHiddenLayer);// Calculates net values of all cells in a hidden layer. Parameters : Index of the hidden layer(indexHiddenLayer).
    void _calculateOutputsOfHiddenLayer(const size_t& indexHiddenLayer);// Calculates output values of all cells in a hidden layer. Parameters : Index of the hidden layer(indexHiddenLayer).
    void _calculateNetsOfOutputLayer();// Calculates net values of all cells in the output layer.
    void _calculateOutputsOfOutputLayer();// Calculates output values of all cells in the output layer.
    void _calculateErrorsOfOutputLayer();// Calculates error values of all cells in the output layer.
    void _calculateDeltasOfOutputLayer();// Calculates delta values of all cells in the output layer.
    void _calculateDeltasOfHiddenLayer(const size_t& indexHiddenLayer);// Calculates delta values of all cells in a hidden layer. Parameters : Index of the hidden layer(indexHiddenLayer).
    void _calculateDeltaInputWeightsOfOutputLayer();// Calculates the change amount of the weights of all cells in the output layer.
    void _calculateDeltaInputWeightsOfHiddenLayer(const size_t& indexHiddenLayer);// Calculates the change amount of the weights of all cells in a hidden layer. Parameters : Index of the hidden layer(indexHiddenLayer).
    void _updateInputWeightsOfOutputLayer();// Updates the weights of all cells in the output layer.
    void _updateInputWeightsOfHiddenLayer(const size_t& indexHiddenLayer);// Updates the weights of all cells in a hidden layer. Parameters : Index of the hidden layer(indexHiddenLayer).
    void _deleteTrainingArrays(const int& countSample,const int*const*const trainingSamplesOriginal,const TransformedData*const*const*const trainingSamplesInputsTransformed,const TransformedData*const*const*const trainingSamplesOutputsTransformed);// Deletes all used arrays from memory, when training is completed. Parameters : Number of samples used(countSample) - Array of all real-world data in the training set file.(trainingSamplesOriginal) - Array of converted ANN input data(trainingSamplesInputsTransformed) - Array of converted ANN output data(trainingSamplesOutputsTransformed).

    bool _controlError(const double& error)const;// Checks whether the total error value calculated at the end of each epoch is infinite or undefined(NaN) during the training. Parameters : Total error value(error).
    bool _controlWeights()const;// Checks whether the weight values of all cells are infinite or undefined (NaN) when the training is completed.
    bool _controlOutputs(const int& countSample, const int*const*const trainingSamplesOriginal);// When training is complete, it passes the input values of all samples in the training set to the neural network and checks whether the output values of the neural network are infinite or undefined. Parameters : The number of samples to be used(countSample) - Array of all real-world data in the training set file.(trainingSamplesOriginal).
};
//-------------------------------------------------
#endif // NEURAL_NETWORK_H
