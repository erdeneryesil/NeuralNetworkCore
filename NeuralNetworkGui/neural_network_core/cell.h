#ifndef CELL_H
#define CELL_H

#include"defines_core.h"
#include<cstddef>

//-------------------------------------------------
class Cell// The base class used to derive class OutputCell and class HiddenCell.
{
public:
  //-------------------------------------------------
  class SummationFunction{// This class, which stores and manages the preferred summation function, calculates and returns the result value. Instances of this class are used in the output layer(class OutputLayerPattern) and hidden layers(class HiddenLayerPattern).
  public:
    enum class Type{WeightedTotal,Multiplication,Maximum,Minimum,Majority,IncrementalTotal};// Names of summation function types. Used to detect which function is selected.
    typedef double(SummationFunction::*FunctionPointer)(const Cell*const,const double*const)const;// Definition of the function pointer, which will point to the preferred summation function.
    SummationFunction(const SummationFunction::Type& type);// Constructor. Parameters : The type of the summation function(type).
    Type getType()const;// Returns _type.
    FunctionPointer getFunctionPointer()const;// Returns _functionPointer.
  private:
    Type _type;// Stores the type of preferred summation function.
    FunctionPointer _functionPointer;// Points to the preferred summation function that returns the result by executing the necessary calculations.
    
    // Summation functions that execute the necessary calculations and return the result.
    // Parameters : Pointer of the cell object (cell) - Input values entered in the cell(inputs(array)).
    double _weightedTotal(const Cell*const cell,const double*const inputs)const;// Weighted total.
    double _multiplication(const Cell*const cell,const double*const inputs)const;// Multiplication.
    double _maximum(const Cell*const cell,const double*const inputs)const;// Maximum.
    double _minimum(const Cell*const cell,const double*const inputs)const;// Minimum.
    double _majority(const Cell*const cell,const double*const inputs)const;// Majority.
    double _incrementalTotal(const Cell*const cell,const double*const inputs)const;//Incremental total.
  };
  //-------------------------------------------------
  class ActivationFunction{// This class, which stores and manages the preferred activation function, calculates and returns the result value. Instances of this class are used in the output layer(class OutputLayerPattern) and hidden layers(class HiddenLayerPattern).
  public:
    enum class Type{Sigmoid,TanH,ReLU,LeakyReLU,Swish,Softplus};// Names of activation function types. Used to detect which function is selected.
    typedef double(ActivationFunction::*FunctionPointer)(const Cell*const)const;// Definition of the function pointer, which will point to the preferred activation function and derivative of that.

    ActivationFunction(const ActivationFunction::Type& type);// Constructor. Parameters : The type of the activation function(type).
    static double rangeMin(const ActivationFunction::Type& type);// Returns the minimum value of the preferred activation function output. Parameters : The type of the activation function(type).
    static double rangeMax(const ActivationFunction::Type& type);// Returns the maximum value of the preferred activation function output. Parameters : The type of the activation function(type).
    Type getType()const;// Returns _type.
    FunctionPointer getActivationFunctionPointer()const;// Returns _functionPointer.
    FunctionPointer getDerivativeActivationFunctionPointer()const;// Returns _derivativeFunctionPointer.

  private:
    Type _type;// Stores the type of preferred activation function.
    FunctionPointer _functionPointer;// Points to the preferred activation function that returns the result by executing the necessary calculations.
    FunctionPointer _derivativeFunctionPointer;// Points to the derivative of the preferred activation function that returns the result by executing the necessary calculations.

    // Activation functions that execute the necessary calculations and return the result.
    // Parameters : Only pointer of the cell object(cell).
    double _sigmoid(const Cell*const cell)const;// Sigmoid.
    double _tanH(const Cell*const cell)const;// TanH(Hyperbolic tangent).
    double _reLU(const Cell*const cell)const;// ReLU(Rectified linear unit).
    double _leakyReLU(const Cell*const cell)const;// Leaky ReLU(Leaky rectified linear unit).
    double _swish(const Cell*const cell)const;// Swish.
    double _softplus(const Cell*const cell)const;// Softplus.

    // Derivatives of the activation functions, which are used in the backpropagation algorithm.
    // Parameters : Pointer of the cell object(cell).
    double _sigmoidDerivative(const Cell*const cell)const;// Derivative of Sigmoid.
    double _tanHDerivative(const Cell*const cell)const;// Derivative of TanH.
    double _reLUDerivative(const Cell*const cell)const;// Derivative of ReLU.
    double _leakyReLUDerivative(const Cell*const cell)const;// Derivative of Leaky ReLU.
    double _swishDerivative(const Cell*const cell)const;// Derivative of Swish.
    double _softplusDerivative(const Cell*const cell)const;// Derivative of Softplus.
  };
  //-------------------------------------------------
  Cell(const size_t& countWeight,const double*const inputWeights);// Constructor. Parameters : The number of input connections the cell has(countWeight) - The weights of the input connections that the cell has(inputWeights(array)).
  Cell(const size_t& countWeight,const double& randomWeightMin,const double& randomWeightMax);// Constructor. Parameters : The number of input connections the cell has(countWeight) - Minimum value for the random weight to be generated.(randomWeightMin) - Maximum value for the random weight to be generated.(randomWeightMax).
  ~Cell();// Destructor
  size_t getCountWeight()const;// Returns _countWeight.
  double getInputWeight(const size_t& index)const;// Returns _inputWeights[index]. Parameters : Index of the connection(index).
  double getDeltaInputWeight(const size_t& index)const;// Returns _deltaInputWeights[index]. Parameters : Index of the connection(index).
  double getNet()const;// Returns _net.
  double getOutput()const;// Returns _output.
  void setOutput(const double& output);// Assigns the parameter value to _output.
  double getDelta()const;// Returns _delta.
  void calculateNet(const SummationFunction*const summationFunction,const double*const inputs);// Calculates net value of the cell. Parameters : Pointer of the preferred summation function(summationFunction) - Input values(inputs(array)).
  void calculateOutput(const ActivationFunction*const activationFunction);// Calculates output value of the cell. Parameters : Pointer of the preferred activation function(activationFunction).
  void calculateDeltaInputWeight(const double& lambda,const double& alfa, const double*const previousLayerOutputs);// Calculates the modification in all weight values of the cell. Parameters : Lambda value(lambda) - Alfa value(alfa) - Outputs of previous layer cells(previousLayerOutputs(array)).
  void updateInputWeight();// Updates all weight values of the cell.
private:
  void _setWeightRandom(const double& min,const double& max);// Assigns the weight values of the cell randomly when a neural network is created for the first time. Parameters : Minimum value of random weight value(min) - Maximum value of random weight value(max).
protected:
  size_t _countWeight;// Stores the number of input connections(Number of weights).
  double* _inputWeights;// Stores weights of all input connections of the cell. That is an array.
  double* _deltaInputWeights;// Stores delta of input weights(modification in all weight values). That is an array.
  double _net;// Stores net value of the cell.
  double _output;// Stores output value of the cell.
  double _delta;// Stores delta value of the cell.
};
//-------------------------------------------------
class BiasCell// Bias cell of an artificial neural network. Also it is base class of InputCell.
{
protected:
  double _input;// Stores the input value that feeds the cell.
public:
  BiasCell();// Constructor.
  double getInput()const;// Returns _input.
};
//-------------------------------------------------
class OutputCell:public Cell// Output cell of an artificial neural network. Inherited from class Cell.
{
private:
  double _expectedOutput;// Stores the expected output value of the output cell.
  double _error;// Stores the error value of the output cell, which is the difference between the expected output value and the actual output value.
public:
  OutputCell(const size_t& countWeight,const double*const inputWeights);// Constructor. Parameters : Number of input connections(countWeight) - Weights of all input connections(inputWeights(array)).
  OutputCell(const size_t& countWeight,const double& randomWeightMin,const double& randomWeightMax);// Constructor. Parameters : Number of input connections(countWeight) - Minimum value of random weight value(randomWeightMin) - Maximum value of random weight value(randomWeightMax).

  double getExpectedOutput()const;// Returns _expectedOutput.
  void setExpectedOutput(const double& value);// Assigns the parameter value to _expectedOutput.
  double getError()const;// Returns _error.
  void setError(const double& error);// Assigns the parameter value to _error.
  void calculateError();// Calculates the error value of the output cell.
  void calculateDelta(const ActivationFunction*const activationFunction);// Calculates the delta value of the output cell. Parameters : Pointer of the activation function object of the output layer(activationFunction).
};
//-------------------------------------------------
class HiddenCell:public Cell// Hidden layer cell that can be located in any hidden layer of artificial neural network. Inherited from class Cell.
{
public:
  HiddenCell(const size_t& countWeight,const double*const inputWeights);// Constructor. Parameters : Number of input connections(countWeight) - Weights of all input connections(inputWeights(array)).
  HiddenCell(const size_t& countWeight,const double& randomWeightMin,const double& randomWeightMax);// Constructor. Parameters : Number of input connections(countWeight) - Minimum value of random weight value(randomWeightMin) - Maximum value of random weight value(randomWeightMax).
  void calculateDelta(const ActivationFunction*const activationFunction,const int& cellIndex,const int& countPreviousLayerCell,const Cell*const*const previousLayerCells);// Calculates the delta value of a hidden layer cell. Parameters : Pointer of the activation function object of the output layer(activationFunction) - Index of the cell(cellIndex) - Number of cells of the previous layer(countPreviousLayerCell) - Pointers of all cell objects in the previous layer(previousLayerCells(array)).
};
//-------------------------------------------------
class InputCell:public BiasCell// Input cell of an artificial neural network. Inherited from class BiasCell.
{
public:
  InputCell();// Constructor.
  void setInput(const double& input);// Assigns the parameter value to _input.
};
//-------------------------------------------------
#endif // CELL_H
