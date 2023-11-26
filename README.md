# NeuralNetworkCore



Using the NeuralNetworkCore library, an artificial neural network with the preferred features can be designed, trained, tested, and output values can be calculated by passing input values. Through NeuralNetworkCore, artificial neural networks can be designed that use feed-forward, supervised learning method and can be trained by the generalized delta rule.

The NeuralNetworkCore library contains class NeuralNetwork that represents an artificial neural network, as well as the classes that model the components that build any artificial neural network.

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/6a6d164a-9431-40a6-9237-5cd61cd7223e" width="500"/>
</p>


Class NeuralNetwork is the only class whose instances will be created by those who will use this library. 

The others in the NeuralNetworkCore library are classes that model the components of an artificial neural network. Instances of these classes are put together in class NeuralNetwork to model an artificial neural network.

Let's take a brief look at the classes included in the NeuralNetworkCore library, from the simplest to the most complex.


### Class InputCell
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/8de27759-fe21-4a98-9e79-f0885db4ec49" width="500"/>
</p>
It is the class that represents the cells in the input layer of an artificial neural network.

### Class BiasCell
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/a540a6b4-a092-4c8f-8051-6b7265a568e6" width="500"/>
</p>
It is the class that represents the bias cells of an artificial neural network.

### Class HiddenCell
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/9a17023b-600a-4801-b2f9-5d98ba70c462" width="500"/>
</p>
Models the cells in hidden layers.


### Class OutputCell
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/6fae50a9-f451-462c-9acb-45457a9fd4a9" width="500"/>
</p>
Models the cells in an output layer.

### Class InputLayerPattern
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/93bf5acd-3f1d-477e-9dde-b097127538b1" height="400"/>
</p>
Contains and manages the features of the input layer of an artificial neural network. This class can be considered as a template. The features of the input layer are handled by this class. But cells(or neurons) that compose the input layer of an artificial neural network are not included in this class.

In the content of this class, how many real-world data are passed to the input of an artificial neural network, which ANN data types that real-world data are converted to, how many cells each real-world data is represented, etc.

### Class HiddenLayerPattern
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/29c6f441-d7ee-4b0e-bfc4-313c6bb7d509" height="400"/>
</p>
Contains and manages the features of the hidden layers of an artificial neural network. This class can be considered as a template just like class InputLayerPattern. Cells(or neurons) that compose the hidden layers of an artificial neural network are not included in this class.

The number of hidden layers, the number of cells of each hidden layer, the summation and activation functions of each hidden layer are stored in this class.

### Class OutputLayerPattern
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/337ca0b1-94fe-4c14-96fb-90918f0c5f4c" height="400"/>
</p>
Contains and manages the features of the output layer of an artificial neural network. This class can be considered as a template just like classes InputLayerPattern and HiddenLayerPattern. Cells(or neurons) that compose the output layer of an artificial neural network are not included in this class.

Features such as how many cells are in the output layer or what real world data the outputs from these cells will be converted to are handled by this class.

### Class LogEW
LogEW is abbreviation for 'Log of Errors(E) and updated Weights(W)'.

Training an artificial neural network with all training data for one cycle is called 'epoch'. Class LogEW stores both total error values calculated and number of updated weights in a file at the end of an epoch. And repeats that every epoch. This file also contains the properties that the artificial neural network had at the time of that training.
The following are the data saved in file LogEW.
- Summation and activation functions of hidden layers and output layer (Because they are can be changed for each training).
- Tolerances of the output layer data (Because they are can be changed for each training).
- Lambda and alfa values of the neural network (Because they are can be changed for each training).
- The number of samples to be used in the training.
- At the end of each period, both the calculated total error value and the number of updated weights.

The features mentioned in the first 4 of the 5 items listed above are added to file LogEW only once for each training. However, both the total calculated errors and the number of updated weights are added to file LogEW at the end of each cycle throughout the training. Any training can go on for thousands of epochs. File LogEW stores records for each training in a single line. So, the number of lines in file LogEW means the number of trainings.   

### Class NeuralNetwork
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/52535dc0-f05a-4635-8780-cc186e4b587b" height="400"/>
</p>
This class represents an artificial neural network. Since all other classes model the components of an artificial neural network, they are directly or indirectly included in this class and build an artificial neural network.

When this class is instantiated, 2 files are created. The first is the file (called file ANN) where all the properties of the artificial network are stored. The second is file LogEW, where the trainings applied to the artificial neural network is recorded, and the details about this file are specified in class LogEW. These two files are named using a user-specified phrase. For example, if the user determined the name "my_ann" while creating the artificial neural network, file ANN is named "my_ann" and file LogEw is named "my_annEW".

Apart from files ANN and LogEW, training and test set samples should be stored in different files. There is no relationship between the names of these files and the name of the artificial neural network. Training and test set files can have any name.

The data in file ANN, file LogEW, training set file and test set file are ordered one after another using the separator character, and this separator character is determined by the user when creating the artificial neural network. There are 4 options that the user can specify as separator characters. These are space( ), comma(,), semicolon(;) and pipe(|) characters.

## Data Types
The real-world input and output values passed to an artificial neural network must be numerical in order for the neural network to understand them. For this reason within the NeuralNetworkCore library, there are classes that convert real-world input and output values into data types that the artificial neural network can handle. These are Binary, Flag, Narrowed and Native classes. These classes will be called to as ‘ANN data types’.

### Binary
Converts real-world data into a type that is very similar to the binary number system, but with some differences, so that the artificial neural network can handle it.Unlike the binary number system, this class has 2 major features.The first of these is that it can also take account of the sign of numbers. And the second the bits may be different from 0-1 values. For example, if an instance of this class is used in the output layer and the preferred activation function is TanH, the bits will be -1 or 1. When converting real-world data to an instance of class Binary, the range of this data is important because the number of digits in the Binary instance will be calculated based on the absolute value of these minimum and maximum values.


<ins><b>Example 1:</b></ins> Let's say you have a real-world data that can take values between -7 and 63. The current value of this data is 3. If this data is converted to Binary instance (preferred activation function is Sigmoid) :
- Minimum value -7 (without sign)           :   1 1 1           - 3 digits.
- Minimum value -7 (with the sign)          :   0 1 1 1         - 4 digits. First bit is the sign. 0 indicates negative.
- Maimum value 63 (without sign)           :   1 1 1 1 1 1     - 6 digits.
- Maximum value 63 (with the sign)        :   1 1 1 1 1 1 1   - 7 digits. First bit is the sign. 1 indicates positive.

The maximum number of digits is 7. So the instance of class Binary must contain 7 digits.
- Current value 3                           :   1 0 0 0 0 1 1   - It must be represented as 7 digits in total.

<ins><b>Example 2:</ins></b> If the activation function chosen in Example 1 is TanH :
 - Current value 3                           :   1 -1 -1 -1 -1 1 1

<ins><b>Example 3:</ins></b> Let's say you have a real-world data that can take values between -63 and 7. The current value of this data is 3. If this data is converted to Binary instance (preferred activation function is Sigmoid) :
- Minimum value -63 (without sign)          :   1 1 1 1 1 1     - 6 digits.
- Minimum value -63 (with the sign)         :   0 1 1 1 1 1 1   - 7 digits. First bit is the sign. 0 indicates negative.
- Maximum value 7 (without sign)            :   1 1 1           - 3 digits.
- Maximum value 7 (with the sign)           :   1 1 1 1         - 4 digits. First bit is the sign. 1 indicates positive.

The maximum number of digits is 7. So the instance of class Binary must contain 7 digits.
- Current value 3

### Flag
Works in flag logic. The flag representing the current value of the real-world data is enabled, all other flags are disabled. In the input layer of the artificial neural network, 1 represents the enabled flag and 0 represents the disabled flag. However, in the output layer, the flags can also store a pair of -1 and 1 depending on the preferred activation function.

Like class Binary, instance of class Flag can take account of the sign of numbers.

<ins><b>Example 1:</ins></b> Let's say you have a real-world data that can take values between 0 and 5. The current value of this data is 3. If this data is converted to Flag instance (preferred activation function is Sigmoid) :
- Flags        : 1 0 0 0 1 0 0          - sign(+) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))

<ins><b>Example 2:</ins></b> Minimum:-5, Maximum: 5, Current Value:3,  Activation Function: Sigmoid
- Flags        : 1 0 0 0 1 0 0          - sign(+) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))

<ins><b>Example 3:</ins></b> Minimum:-5, Maximum: 5, Current Value:-3,  Activation Function: Sigmoid
- Flags        : 0 0 0 0 1 0 0          - sign(-) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))

<ins><b>Example 4:</ins></b> Minimum:-5, Maximum: 4, Current Value:3,  Activation Function: Sigmoid
- Flags        : 1 0 0 0 1 0 0   - sign(+) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))

<ins><b>Example 5:</ins></b> Minimum:-5, Maximum: 5, Current Value:-3,  Activation Function: TanH
- Flags        : -1 -1 -1 -1 +1 -1 -1   - sign(-) , Flag0(disabled) , Flag1(disabled) , Flag2(disabled) , Flag3(enabled) , Flag4(disabled) , Flag5(disabled))


### Narrowed
Scales real-world data. A real world data is scaled from 0 to 1 and this scaled data is retained, not modificated. If scaling is required in a different range according to the activation function of the output layer, it is calculated instantly and returned. The value scaled between 0 and 1 stored in Narrowed object is never modificated.

<ins><b>Example 1:</ins></b> Minimum value of the real-world data    : 0
- Maximum value of the real-world data    : 100
- Activation Function                     : Sigmoid(0,1)
- If the current value of the real-world data is 0, object Narrowed stores 0.0
- If the current value of the real-world data is 15, object Narrowed stores 0.15
- If the current value of the real-world data is 50, object Narrowed stores 0.5
- If the current value of the real-world data is 100, object Narrowed stores 1.0

<ins><b>Example 2:</ins></b> Minimum value of the real-world data    : 0
- Maximum value of the real-world data    : 100
- Activation Function                     : TanH(-1,1)
- If the current value of the real-world data is 0, object Narrowed stores -1.0
- If the current value of the real-world data is 15, object Narrowed stores -0.7
- If the current value of the real-world data is 50, object Narrowed stores 0.0
- If the current value of the real-world data is 100, object Narrowed stores 1.0

<ins><b>Example 3:</ins></b> Minimum value of the real-world data    : -50
- Maximum value of the real-world data    : 50
- Activation Function                     : Sigmoid(0,1)
- If the current value of the real-world data is -50, object Narrowed stores 0.0
- If the current value of the real-world data is 0, object Narrowed stores 0.5
- If the current value of the real-world data is 50, object Narrowed stores 1.0


### Native
Can be used if the real-world data is already in the range 0-1 and therefore does not need any transformations. The real world data and the data stored in the instance of class Native are exactly the same and have a value between 0 and 1. The value in object Native is not modificated. If scaling is required in a different range according to the activation function of the output layer, it is calculated instantly and returned.


## Designing An Artificial Neural Network
To design an artificial neural network, the configurations for the input layer, hidden layers and output layer must be determined by the user. In addition to these basic features of an artificial neural network, the parameters to be used during training of the neural network and the information required to store the artificial neural network as a file should also be passed.

For the input layer:
- Number of the real-world input data
- Minimum and maximum values that real-world input values can take
- ANN data types(Binary, Flag, Narrowed, Native) into which real-world input values will be converted

For the hidden layers:
- Number of hidden layers
- Number of cells each hidden layer will contain
- Summation and activation functions that for each hidden layer

For the output layer
- Number of the real-world input data
- Summation and activation functions that for output layer
- Minimum and maximum values that real-world output values can take
- ANN data types(Binary, Flag, Narrowed, Native) into which real-world output values will be converted
- Tolerances of the output cells.

For training:
- Lambda and alfa values
- Assigns the weight values of the cells randomly when an artificial neural network is created for the first time. For this reason the minimum and maximum values of the range of random numbers must be specified.

For file ANN:
- Separator character(comma(,)  semicolon(;) etc.)
- Locaiton to save file ANN
- Name of file ANN

Let's see how to design the input, hidden and output layers of an artificial neural network on an <a href="https://www.kaggle.com/datasets/mirichoi0218/insurance
" >example problem.</a>

The example problem is a dataset containing the annual health expenses of a certain number of people living in USA. Some of the characteristics and qualities that individuals have in the list are also included in this data set.

The columns in the list:
- <p>Age		: Person’s age. It is an integer.</p>
  <p>It is already numerical data, there is no need for any digitization.</p>
  
- <p>Sex		: Person’s gender. It is a categorical data. Options: Female, Male.</p>
  <p>Digitization of it : Female=0, Male=1</p>
  
- <p>Bmi		: The person's body mass index. It is a decimal number. The part on the right side of the decimal point consists 3 digits.</p>
  <p>Transformation: To convert body mass index values into integers, they are multiplied by 1000.</p>
  
- <p>Children	: Number of children covered by the person's health insurance / Number of dependents of the person.It is an integer.</p>
  <p>It is already numerical data, there is no need for any digitization.</p>
  
- <p>Smooker	: Whether the person smokes or not. It is a categorical data. Options: Yes, No:Hayır.</p>
  <p>Digitization of it : No=-1, Yes=1 (The values -1 and 1 were determined arbitrarily).</p>
  
- <p>Region	: The region where the person lives. It is a categorical data. Options: Southeast , Northeast , Northwest , Southwest.</p>
  <p>Digitization of it :   Southeast = -2, Northeast = -1, Northwest = 1, Southwest = 2 (The values were determined arbitrarily).</p>
  
- <p>Charges	: Individual medical costs billed by health insurance. It is a decimal number.</p>
  <p>Since this data has a very wide range, it was divided into a total of 7 categories</p>
  
  - 0-5000				    : 0
  - 5000-10000			 :	1
  - 10000-15000   : 2
  - 15000-25000   : 3
  - 25000-35000   : 4
  - 35000-50000   : 5
  - 50000-65000			:	6
  
<p>Inputs : Age, Sex, Bmi, Children, Smooker, Region</p>
<p>Output: Charges</p>


The artificial neural network created to learn this example.

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/bdad48c5-0cb6-46dc-8afc-78a5da0a8249" height="500"/>
</p>


### Design of the input layer

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/ef44c2c3-7681-4e81-8a6d-e78e4eea0835" height="500"/>
</p>

 Number of inputs
 - 6 (age,sex,bmi,children,smoker,region)
 
Minimum and maximum values that real-world input values can take
- age 		: Min= 18, Max = 64
- sex 		: Min = 0(female), Max = 1(male)
- bmi (x1000) 	: Min = 15960, Max = 53130
- children 		: Min = 0, Max = 5
- smoker 		: Min = -1(no), Max = 1 (yes)
- region 		: Min = -2, Max = 2 (Southeast = -2, Northeast = -1, Northwety = 1, Southwest = 2)

ANN data types into which real-world input values will be converted
- age 		: Binary
- sex 		: Native
- bmi (x1000) 	: Narrowed
- children 		: Binary
- smoker 		: Binary
- region 		: Flag


### Design of the hidden layers

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/6fdcf091-b52a-4405-b571-0bcda60619bb" height="500"/>
</p>


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/5598669b-c818-4e5f-a2b2-292aa4a50e35" height="500"/>
</p>

Number of hidden layers
- 2

Number of cells each hidden layer will contain
- Hidden layer 0 		: 22
- Hidden layer 1		: 18

Summation and activation functions that for each hidden layer
- Summation function of hidden layer 0		: Weighted Total
- Activation function of hidden layer 0		: TanH
- Summation function of hidden layer 0		: Weighted Total
- Activation function of hidden layer 0		: Sigmoid


### Design of the output layer


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/56fa952b-3457-4d82-bbda-2eeef34e005c" height="500"/>
</p>

Number of the real-world input data
- 1

Summation and activation functions that for output layer
- Summation Function	: Weighted Total 
- Activation Function	: Sigmoid

Minimum and maximum values that real-world output values can take
- Min				: 0
- Max			: 65000

ANN data type into which real-world output value will be converted
- Flag
Tolerances of the output cells
- 0.1


## Projects Using The NeuralNetworkCore Library
Applications with 3 different interfaces developed based on the NeuralNetworkCore library:
- <a href="https://github.com/erdeneryesil/NeuralNetworkCore/tree/master/NeuralNetworkTerminal">NeuralNetworkTerminal</a>
- <a href="https://github.com/erdeneryesil/NeuralNetworkCore/tree/master/NeuralNetworkGui">NeuralNetworkGui</a>
- <a href="https://github.com/erdeneryesil/NeuralNetworkCore/tree/master/NeuralNetworkMnist">NeuralNetworkMnist</a>

The source codes of the NeuralNetworkCore library are located in the <b>neural_network_core</b> directory in these 3 projects. Detailed explanations about the classes can be found in the comment lines of files <b>cell.h</b>, <b>data.h</b> and <b>neural_network.h</b> located in the <b>neural_network_core</b> directory.
















