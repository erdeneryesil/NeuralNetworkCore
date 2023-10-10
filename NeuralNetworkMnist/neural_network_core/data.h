#ifndef DATA_H
#define DATA_H

#include"defines_core.h"
#include<math.h>
#include<stdexcept>

enum class LayerType{Input,Hidden,Output};// Names of layer types.

class Data{/* The base class that derives the Binary, Flag, Narrow and Native classes, which will be described as 'artificial neural network(ANN) data types' in these source code files.
              Real-world data is converted into 'ANN data types' so that they can be handled by the artificial neural network.
          */
          
protected:
  double*_digits;/* Stores the digits(or bits) that converted from real-world data to ANN data types (Binary, Flag, Narrowed or Native) as a double array.
  Elements of the _digits array can store values in different ranges, depending both on which layer of the neural network the ANN data is in and on the preferred activation function.
  -If the ANN data is in the input layer, it stores values between 0.0 and 1.0.
  -If the ANN data is in the output layer:
                - If preferred activation function is Sigmoid, it stores values between 0.0 and 1.0.
                - If preferred activation function is TanH, it stores values between -1.0 and 1.0.
                - If preferred activation function is ReLU, it stores values between 0.0 and 1.0.
                - If preferred activation function is LeakyReLU, it stores values between -1.0 and 1.0.
                - If preferred activation function is Swish, it stores values between -1.0 and 1.0.
                - If preferred activation function is Softplus, it stores values between 0.0 and 1.0.
  */
  
  size_t _length;// Stores the number of elements of _digits array.
public:
  virtual ~Data();// Destructor.
  size_t getLength()const;// Returns _length.
  virtual double getValue(const double&,const double&)const{throw std::invalid_argument(THROW_MESSAGE_DATA_GETVALUE_2_PARAMETERS);};// This virtual function ensures that the getValue function with two parameters can be executed on only Narrowed and Native objects. Otherwise, it throws an exception.
  virtual double getValue(const size_t&,const double&,const double&)const{throw std::invalid_argument(THROW_MESSAGE_DATA_GETVALUE_3_PARAMETERS);}// This virtual function ensures that the getValue function with three parameters can be executed on only Binary and Flag objects. Otherwise, it throws an exception.
  virtual double getOriginal()const{throw std::invalid_argument(THROW_MESSAGE_DATA_GETORIGINAL_NO_PARAMETER);}// This virtual function ensures that the getOriginal function with no parameters can be executed on only Binary, Flag and Native objects. Otherwise, it throws an exception.
  virtual double getOriginal(const int&,const int&)const{throw std::invalid_argument(THROW_MESSAGE_DATA_GETORIGINAL_2_PARAMETERS);};// This virtual function ensures that the getOriginal function with two parameters can be executed on only Narrowed objects. Otherwise, it throws an exception.
  enum class Type{Binary,Flag,Narrowed,Native};// ANN data type name. Used to detect which type of ANN data an real-world data has been converted to.
  
  class Limit{// Stores and manages the minimum and maximum limits of both real-world data and ANN data types.
  private:
    int _originalMin;// Stores the minimum value of a real-world data.
    int _originalMax;// Stores the maximum value of a real-world data.
    double _scaledMin;// Stores the minimum value of elements of _digits array.
    double _scaledMax;// Stores the maximum value of elements of _digits array.
  public:
    Limit();// Constructor. It is empty function.
    Limit(const Data::Type& dataType,const LayerType& layerType);// Constructor. For instantiating a Native object in input layer.
    Limit(const Data::Type& dataType,const LayerType& layerType,const double& scaledMin,const double& scaledMax);// Constructor. For instantiating a Native object in output layer.
    Limit(const Data::Type& dataType,const LayerType& layerType,const int& originalMin,const int& originalMax);// Constructor. For instantiating a Binary,Flag or Narrowed object in input layer.
    Limit(const Data::Type& dataType,const LayerType& layerType,const int& originalMin,const int& originalMax,const double& scaledMin,const double& scaledMax);// Constructor. For instantiating a Binary,Flag or Narrowed object in output layer.
    Limit(const Limit*const limit);// Copy constructor.
    
    int getOriginalMin()const;// Returns _originalMin.
    int getOriginalMax()const;// Returns _originalMax.
    double getScaledMin()const;// Returns _scaledMin.
    double getScaledMax()const;// Returns _scaledMax.
    void setScaledMin(const LayerType& layerType,const double& scaledMin);//Assigns parameter scaledMin value to _scaledMin. It runs only in output layer.
    void setScaledMax(const LayerType& layerType,const double& scaledMax);//Assigns parameter scaledMax value to _scaledMax. It runs only in output layer.
  };
};
//-------------------------------------------------
class Binary:public Data{/*Converts real-world data into a type that is very similar to the binary number system, but with some differences, so that the artificial neural network can handle it.
                          Unlike the binary number system, this class has 2 major features.
                          The first of these is that it can also take account of the sign of numbers.
                          And the second is the bits may be different from 0-1 values. For example, if an instance of this class is used in the output layer and the preferred activation function is TanH, the bits will be -1 or 1.
                          When converting real-world data to an instance of the Binary class, the range of this data is important because the number of digits in the Binary instance will be calculated based on the absolute value of these minimum and maximum values.

                          Example 1: Let's say you have a real-world data that can take values between -7 and 63. The current value of this data is 3. If this data is converted to Binary instance (preferred activation function is Sigmoid) :
                                    - Minimum value -7 (without sign)           :   1 1 1           - 3 digits.
                                    - Minimum value -7 (with the sign)          :   0 1 1 1         - 4 digits. First bit is the sign. 0 indicates negative.
                                    - Maimum value 63 (without sign)            :   1 1 1 1 1 1     - 6 digits.
                                    - Maximum value 63 (with the sign)          :   1 1 1 1 1 1 1   - 7 digits. First bit is the sign. 1 indicates positive.

                                    The maximum number of digits is 7. So the instance of the Binary class must contain 7 digits.
                                    - Current value 3                           :   1 0 0 0 0 1 1   - It must be represented as 7 digits in total.

                          Example 2: If the activation function chosen in Example 1 is TanH :
                                    - Current value 3                           :   1 -1 -1 -1 -1 1 1

                          Example 3: Let's say you have a real-world data that can take values between -63 and 7. The current value of this data is 3. If this data is converted to Binary instance (preferred activation function is Sigmoid) :
                                    - Minimum value -63 (without sign)          :   1 1 1 1 1 1     - 6 digits.
                                    - Minimum value -63 (with the sign)         :   0 1 1 1 1 1 1   - 7 digits. First bit is the sign. 0 indicates negative.
                                    - Maximum value 7 (without sign)            :   1 1 1           - 3 digits.
                                    - Maximum value 7 (with the sign)           :   1 1 1 1         - 4 digits. First bit is the sign. 1 indicates positive.

                                    The maximum number of digits is 7. So the instance of the Binary class must contain 7 digits.
                                    - Current value 3                         :   1 0 0 0 0 1 1   - It must be represented as 7 digits in total.
  */
private:
    // Converting a number in the decimal number system to an instance of the Binary class is performed in 2 steps. The first of these steps is implemented by the _calculateDigitsReverseOrder function and the second by the _reverseBits function.
    //In this class, 'bit' is the equivalent of 'digit'.
    void _calculateDigitsReverseOrder(int original);// Divides the real-world data by 2 until it has a value less than 2 and puts all remainder values in the _digits array. Finally puts the last quotient value to the _digits array. Parameters : The real-world data(original).
    void _reverseBits();// Reverses the elements of the _digits array after the _calculateDigitsReverseOrder function runs.
public:
    Binary(const int& original,const int& originalMax);// Constructor. Initializes a Binary object by using a real-world data. Parameters : The current value of the real-world data(original) - The maximum value of the real-world data(originalMax).
    Binary(const size_t& countBit,const double*const scaledBits,const int& originalMax,const double& scaledMin,const double& scaledMax);// Constructor. Used for situations where bits are in an array. Parameters : Number of bits(countBit) - Array of bits(scaledBits) - Maximum value of the real-world data(originalMax) - Minimum and maximum values of elements in array scaledBits(scaledMin,scaledMax).
    Binary(const Binary& binaryObj);// Copy constructor.
    double getValue(const size_t& index,const double& scaledMin,const double& scaledMax)const;// Returns the indexed bit by scaling it to the preferred range. Parameters : Index of the bit(index) - Minimum and maximum values of the scaled range(scaledMin,scaledMax).
    double getOriginal()const;// Returns the real-world data in decimal number system.
};
//-------------------------------------------------
class Flag:public Data{/* Works in flag logic. The flag representing the current value of the real-world data is enabled, all other flags are disabled.
                          In the input layer of the artificial neural network, 1 represents the enabled flag and 0 represents the disabled flag. However, in the output layer, the flags can also store a pair of -1 and 1 depending on the preferred activation function.
                          Like Binary class, instance of Flag class can take account of the sign of numbers.

                          Example 1: Let's say you have a real-world data that can take values between 0 and 5. The current value of this data is 3. If this data is converted to Flag instance (preferred activation function is Sigmoid) :
                                    - Flags        : 1 0 0 0 1 0 0          - sign(+) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))

                          Example 2: Minimum:-5, Maximum: 5, Current Value:3,  Activation Function: Sigmoid
                                    - Flags        : 1 0 0 0 1 0 0          - sign(+) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))

                          Example 3: Minimum:-5, Maximum: 5, Current Value:-3,  Activation Function: Sigmoid
                                    - Flags        : 0 0 0 0 1 0 0          - sign(-) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))

                          Example 4: Minimum:-5, Maximum: 4, Current Value:3,  Activation Function: Sigmoid
                                    - Flags        : 1 0 0 0 1 0 0   - sign(+) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))

                          Example 5: Minimum:-5, Maximum: 5, Current Value:-3,  Activation Function: TanH
                                    - Flags        : -1 -1 -1 -1 +1 -1 -1   - sign(-) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))
                      */
public:
  //In this class, 'flag' is the equivalent of 'digit'.
  Flag(const int& original,const int& originalMax);// Constructor. Initializes a Flag object by using a real-world data. Parameters : The current value of the real-world data(original) - The maximum value of the real-world data(originalMax).
  Flag(const size_t& countFlag,const double*const scaledFlags,const int& originalMax,const double& scaledMin,const double& scaledMax);// Constructor. Used for situations where flags are in an array. Parameters : Number of flags(countFlag) - Array of flags(scaledFlags) - Maximum value of the real-world data(originalMax) - Minimum and maximum values of elements in array scaledFlags(scaledMin,scaledMax).
  Flag(const Flag& flagObj);// Copy constructor.
  double getValue(const size_t& index,const double& scaledMin,const double& scaledMax)const;// Returns the indexed flag by scaling it to the desired range. Parameters : Index of the flag(index) - Minimum and maximum values of the scaled range(scaledMin,scaledMax).
  double getOriginal()const;// Returns the index of the flag that stores the largest value, as a real-world data. If there is more than one flag that stores the largest value, it returns the index of the left one.
};
//-------------------------------------------------
class Narrowed:public Data{/*Scales real-world data.
                            A real world data is scaled from 0 to 1 and this scaled data is retained, not modificated.
                            If scaling is required in a different range according to the activation function of the output layer, it is calculated instantly and returned. The value scaled between 0 and 1 stored in Narrowed object is never modificated.
                            _digits array has only 1 element and the scaled value store in _digits[0].

                            Example 1:Minimum value of the real-world data    : 0
                                      Maximum value of the real-world data    : 100
                                      Activation Function                     : Sigmoid(0,1)
                                          If the current value of the real-world data is 0, the Narrowed object stores 0.0
                                          If the current value of the real-world data is 15, the Narrowed object stores 0.15
                                          If the current value of the real-world data is 50, the Narrowed object stores 0.5
                                          If the current value of the real-world data is 100, the Narrowed object stores 1.0

                            Example 2:Minimum value of the real-world data    : 0
                                      Maximum value of the real-world data    : 100
                                      Activation Function                     : TanH(-1,1)
                                          If the current value of the real-world data is 0, the Narrowed object stores -1.0
                                          If the current value of the real-world data is 15, the Narrowed object stores -0.7
                                          If the current value of the real-world data is 50, the Narrowed object stores 0.0
                                          If the current value of the real-world data is 100, the Narrowed object stores 1.0

                            Example 3:Minimum value of the real-world data    : -50
                                      Maximum value of the real-world data    : 50
                                      Activation Function                     : Sigmoid(0,1)
                                          If the current value of the real-world data is -50, the Narrowed object stores 0.0
                                          If the current value of the real-world data is 0, the Narrowed object stores 0.5
                                          If the current value of the real-world data is 50, the Narrowed object stores 1.0
                            */
public:
  Narrowed(const double& value,const double& originalMin,const double& originalMax);// Constructor. Initializes a Narrowed object by scaling real-world data between 0 and 1. The scaled value is stored in _digit[0]. Parameters : The current value of the real-world data(value) - Minimum and maximum values of the real-world data(originalMin,originalMax).
  Narrowed(const Narrowed& narrowedObj);// Copy constructor.
  double getValue(const double& scaledMin,const double& scaledMax)const;// The data already scaled between 0 and 1 is scaled to a different range and returned. The new value is not stored in the object, it is just returned. Parameters : Minimum and maximum values of a preferred new range to scale(scaledMin,scaledMax).
  double getOriginal(const int& originalMin,const int& originalMax)const;// Return the real-world data. Parameters : Minimum and maximum values of the real-world data (originalMin,originalMax).
};
//-------------------------------------------------
class Native:public Data{/*Can be used if the real-world data is already in the range 0-1 and therefore does not need any transformations.
                          The real world data and the data stored in the instance of the Native class are exactly the same and have a value between 0 and 1.
                          The value in Native object is not modificated. If scaling is required in a different range according to the activation function of the output layer, it is calculated instantly and returned.
                          _digits array has only 1 element and the value store in _digits[0].
                        */
public:
  Native(const double& value,const double& originalMin,const double& originalMax);// Constructor. This is used, if Native object is in output layer. Parameters : The current value of the real-world data(value) - Minimum and maximum values of the result range of the preferred activation function(originalMin,originalMax).
  Native(const double& native);// Constructor. The parameter value is put directly into the _digits[0]. Because real-world data already has a value between 0-1.
  Native(const Native& nativeObj);// Copy constructor.
  double getValue(const double& scaledMin,const double& scaledMax)const;// Returns the scaled value of real-world data. Parameters : Minimum and maximum values of the range to scale(scaledMin,scaledMax).
  double getOriginal()const;// Returns the real-world data(_digits[0]).
};
//-------------------------------------------------
class TransformedData{/* Allows ANN data types(Binary, Flag, Narrowed and Native) to be managed through a single class.
                        Stores and manages one of the Binary, Flag, Narrowed or Native objects.
                        All ANN data types were combined under TransformedData class instead of identifying constantly which ANN data type is used to run different operations.
                        A real-world data is converted to either ANN data types for an artificial neural network to handle. But regardless of Binary, Flag, Narrowed or Native types, an artificial neural network will process them as TransformedData.
                      */
public:
  static size_t length(const Data::Type& type,const int& original);// This static function calculates and returns the number of digits the ANN data type object would have if a real-world data were to be transformed. Parameters : ANN data type to convert(type) - Real-world data(original).
  
  TransformedData(Binary* data);// Constructor. Used to store and manage an Binary object.
  TransformedData(Flag* data);// Constructor. Used to store and manage an Flag object.
  TransformedData(Narrowed* data);// Constructor. Used to store and manage an Narrowed object.
  TransformedData(Native* data);// Constructor. Used to store and manage an Native object.
  TransformedData(const TransformedData& data);// Copy constructor.
  ~TransformedData();// Destructor.
  Data::Type getType()const;// Returns _type.
  const Data* getData()const;// Returns _data.
private:
  Data* _data;// Stores an instance of only one of the Binary, Flag, Narrow or Native types as a pointer(Data class is the base class that derives Binary, Flag, Narrow and Native classes).
  Data::Type _type;// Stores ANN data type as Data::Type object.
};
//-------------------------------------------------
#endif // DATA_H
