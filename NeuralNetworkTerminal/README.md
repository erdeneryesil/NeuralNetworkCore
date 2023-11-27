# NeuralNetworkTerminal

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/6793f415-9f60-4ddf-9627-bd88ae2da029" width="800"/>
</p>

NeuralNetworkTerminal is an application run in terminal, where operations such as creating, training and testing an artificial neural network can be performed using the NeuralNetworkCore library.

When we run the application, we see the name of our application, <b>NEURAL NETWORK TERMINAL</b>, at the top.

Since the application will be managed via terminal, the options will be determined using numbers. So, no matter what level of the menu, every selection will be made with numbers.

The options to be selected in the application were divided into certain categories, and each of these categories was shown as titles written in capital letters.

Let's see how to create an artificial neural network, how to open it, how to train and test it using an <a href="https://www.kaggle.com/datasets/mirichoi0218/insurance
" >example problem</a>.

The example problem is a dataset containing the annual health expenses of a certain number of people living in USA. Some of the characteristics and qualities that individuals have in the list are also included in this data set.

The columns in the list:

<b>Age		:</b>	Person’s age. It is an integer.<br />
It is already numerical data, there is no need for any digitization.

<b>Sex		:</b>	Person’s gender. It is a categorical data.<br />
Options: Female, Male.<br />
Digitization of it : Female=0, Male=1

<b>Bmi		:</b>	The person's body mass index. It is a decimal number. The part on the right side of the decimal point consists 3 digits.<br />
Transformation: To convert body mass index values into integers, they are multiplied by 1000.

<b>Children	:</b>	Number of children covered by the person's health insurance / Number of dependents of the person.It is an integer.<br />
It is already numerical data, there is no need for any digitization.

<b>Smoker		:</b>	Whether the person smokes or not. It is a categorical data.<br />
Options: Yes, No  <br />
Digitization of it : No=-1, Yes=1 (The values -1 and 1 were determined arbitrarily.)

<b>Region		:</b>	The region where the person lives. It is a categorical data. <br />
Options: Southeast , Northeast , Northwest , Southwest . <br />
Digitization of it :   Southeast = -2, Northeast = -1, Northwest = 1, Southwest = 2 (The values were determined arbitrarily.)

<b>Charges	:</b>	Individual medical costs billed by health insurance. It is a decimal number.<br />
Since this data has a very wide range, it was divided into a total of 7 categories <br /><br />
0-5000 &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; : 	0 <br />
5000-10000 &nbsp; &nbsp; &nbsp; :	1 <br />
10000-15000 &nbsp; &nbsp; :	2 <br />
15000-25000 &nbsp; &nbsp; :	3 <br />
25000-35000 &nbsp; &nbsp; :	4 <br />
35000-50000 &nbsp; &nbsp; :	5 <br />
50000-65000 &nbsp; &nbsp; :	6 <br /><br />
<p>Inputs : Age, Sex, Bmi, Children, Smooker, Region</p>
<p>Output: Charges</p>

## Creating a New Artificial Neural Network
### Step 1 : OPEN OR CREATE A NEURALNETWORK
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/356ed31d-9ad8-4c73-8494-5d498ab25157" width="800"/>
</p>

There are 2 options at stage <b>OPEN OR CREATE A NEURALNETWORK</b>.<br /><br />
0 - Open a neural network<br />
1 - Create a new neural network<br /><br />
1 must be entered to create a new neural network.<br /><br />
The features of the artificial neural network need to be determined step by step.

### Step 2 : NUMBER OF INPUT DATA
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/8b4850b6-24a1-42b4-b1dd-31b5530ec681" width="800"/>
</p>
The number of real-world data that will be passed to the input layer of the artificial neural network needs to be entered.<br /><br />
- The number of input data in the example problem is 6.

### Step 3 : TYPES OF INPUT DATA
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/85fcd290-0abd-41e7-883e-73898b5bbace" width="800"/>
</p>
Real-world input data passed to the artificial neural network must be converted to <b>ANN data types</b> before it can be processed by the neural network.<br /><br />
- Age - Binary <br />
- Sex - Native <br />
- Bmi - Narrowed <br />
- Children - Binary <br />
- Smooker - Binary <br />
- Region - Flag <br />

### Step 4 : LIMITS OF INPUT DATA
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/02b5f7a4-e052-40aa-ac8a-861e9e9c8283" width="800"/>
</p>
The min and max range of the input values must be entered.<br /><br />
- Age : min=18, max=64 <br />
- Sex : That was converted to Native. That's why Min= 0, Max=1 <br />
- Bmi : Min=15960, Max=53130 <br />
- Children : Min=0, Max=5 <br />
- Smoker : Min = -1 Max=1 <br />
- Region : Min= -2, Max=2 <br />

### Step 5 : NUMBER OF HIDDEN LAYER
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/08b68f87-e5d7-48a8-8cca-5cceb78ec6f9" width="800"/>
</p>
The number of hidden layers.<br /><br />
-Let the number of hidden layers be set to 2. 

### Step 6 : CELL NUMBERS OF HIDDEN LAYERS
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/05ac7cf2-5c8e-4f81-87bf-061985007710" width="800"/>
</p>
The cell numbers of the first and second hidden layers must be entered respectively.<br /><br />
- Let there be 22 cells in the first hidden layer and 18 cells in the second hidden layer.

### Step 7 : SUMMATION FUNCTIONS OF HIDDEN LAYERS
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/5c9d45db-d2ea-4e8b-bcae-abbc4c305d58" width="800"/>
</p>
The summation functions of the hidden layers must be entered.<br /><br />
- Let both be WeightedTotal, so let's enter 0 for both.

### Step 8 : ACTIVATION FUNCTIONS OF HIDDEN LAYERS
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/3af89375-0015-41a2-9169-84ff04e6e905" width="800"/>
</p>
The activation functions of the hidden layers must be entered.<br /><br />
- Let the activation function of the first hidden layer be TanH, let's enter 1.<br />
- Let the activation function of the second hidden layer be Sigmoid, let's enter 0.

### Step 9 : NUMBER OF OUTPUT DATA
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/dc5e11fc-cc7a-4f1a-b3ca-0cee5fe878e0" width="800"/>
</p>
The number of output data must be entered.<br /><br />
- In the example problem, 1 should be entered since only the medical expense amount will be used as the output.

### Step 10 : TYPES OF OUTPUT DATA
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/1470fc48-93ba-4ce4-b65a-91ceff9fba3c" width="800"/>
</p>
Just like inputs, output data needs to be converted into <b>ANN data types</b> that the artificial neural network can process.<br /><br />
 - Charges - Flag 


### Step 11 : SUMMATION FUNCTION OF OUTPUT LAYER
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/8ded4c9f-6e71-480f-b551-41e0677bd55a" width="800"/>
</p>
The summation function of the output layer must be entered.<br /><br />
- Let the summation function of the output layer be WeightedTotal , let's enter 0.


### Step 12 : ACTIVATION FUNCTION OF OUTPUT LAYER
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/ca5a2739-ceb4-446b-902e-9d57095cf97b" width="800"/>
</p>
The activation function of the output layer must be entered.<br /><br />
- Let the activation function of the output layer be Sigmoid, let's enter 0.


### Step 13 : LIMITS OF OUTPUT DATA
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/3bcfaec6-b519-41f8-9394-ba30dc40c3a8" width="800"/>
</p>
The min and max range of the output value must be entered.<br /><br />
- Charges: Min= 0, Max=6


### Step 14 : TOLERANCES OF OUTPUT DATA
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/c11fa782-ec43-453f-a6c1-6dc27b943c6e" width="800"/>
</p>
The tolerance values of the output cells must be entered. When training our network, what is the acceptable margin of error regarding the expected outputs from the output cells? Each output cell will produce a value between 0 and 1. Therefore, we must take this into consideration when determining the tolerance.<br /><br />
- Let the tolerance value be 0.1.

### Step 15 : TRAININGS SETTINGS
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/677c825f-96be-4698-8987-5bad1291a6e3" width="800"/>
</p>
- Lambda = 0.015 <br />
- Alfa = 0.15 <br />
- When the artificial neural network is first created, the weight value of each cell's connections is determined randomly. The min and max range of that random values needs to be specified.  
Random weight min =-1, Random weight  max=+1 <br />

### Step 16 : SEPARATOR CHARACTER
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/31260e60-214c-4c24-b030-ea143b908b09" width="800"/>
</p>
All data related to the artificial neural network is stored in files, and when sorting the data in the files, a character must be placed between them.<br /><br />
- Let's set the separator character as a semicolon and enter 2.

### Step 17 : FILE NAME
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/9516deca-a008-4a11-a0b0-082c442c65e5" width="800"/>
</p>
The names of the files in which the features of the artificial neural network are stored need to be determined.<br /><br />
-  Let the file name be 'insurance'<br /><br />

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/6bc79392-ef3a-4a8e-85b2-d98ef16f3aa1" width="800"/>
</p>

Two files were created named 'insurance' and 'insuranceEW'.<br />

File <b>insurance</b> stores the properties and parameters of the artificial neural network.<br />
File <b>insuranceEW</b> stores the training records of the artificial neural network.


## Opening an Existing Neural Network
### Step 1 : OPEN OR CREATE A NEURAL NETWORK
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/d9cb1e39-2d3a-48d4-9ec4-23c8f49cc511" width="800"/>
</p>

It has been mentioned before that there are 2 options in stage <b>OPEN OR CREATE NEURAL NETWORK</b>. <br /><br />- To open a previously saved artificial neural network, 0 must be entered.

### Step 2 : SEPARATOR CHARACTER
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/0d070e24-8de3-4545-94c1-4f0f3fb050d7" width="800"/>
</p>
The separator character used in existing artificial neural network files. <br /><br />
- Since we set the separator character of our previously saved artificial neural network as a semicolon, let's enter 2.

### Step 3 : FILE LOCATION
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/1e35ee28-ff1d-4cbd-84bb-8a5129e4bfe5" width="800"/>
</p>
The location of the saved artificial neural network file.<br /><br />
- Since our artificial neural network file is located where the source files of the project are located, we just need to write the name of the file. 


## Operation
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/fe9898fa-831e-4356-8e23-3099d5c68549" width="800"/>
</p>
When a new artificial neural network is created or an existing one is opened, you will be asked what to do.<br /><br />
Operations that can be run using the artificial neural network<br /><br />
0 - Train (Training the artificial neural network)<br />
1 - Test  (Testing the artificial neural network)<br />
2 - Run (Getting the output value by passing the input values to the artificial neural network)<br />
3 - Inform (Listing the features of the artificial neural network.)<br />

## Training The Artificial Neural Network
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/ecebe0e7-f749-4484-895c-c0c881f74532" width="800"/>
</p>
The artificial neural network can be trained by entering 0 in <b>Operation</b> menu.<br /><br />
- Let’s enter 0.<br />
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/55ad77a8-651e-40dd-804f-476e7c1f424c" width="800"/>
</p>
Let's put the training and test set files(<b>Train</b>, <b>Test</b>) in the source file directory, just like <b>insurance</b> and <b>insuranceEW</b> files.<br /> <br />
There were a total of 1338 rows in the dataset of our example problem. In other words, information about 1338 people is included in our data set. 
But since we categorized <b>Charges</b> column between 0-6, data repetition occurred in some records. records decreased from 1338 to 1335, meaning 3 rows were deleted. 
Of the 1335 rows, 935 were transferred to the training set and 400 were transferred to the test set.

### Step 1 : TRAIN
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/b8a49b96-54c7-4402-9488-1841804b509c" width="800"/>
</p>
 - First, let's enter the location of file <b>Train</b>. Next, let's enter the value 935 since all samples are wanted to be used. <br />

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/49074447-5aac-4743-922d-fa0d4abbec9f" width="800"/>
</p>
- The artificial neural network will start training. At the end of each epoch, the total error value and the number of updated weights are displayed.<br />

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/511ffaf8-5009-43ff-a7b3-aa382d4840db" width="800"/>
</p>
- In this example scenario, the training of the artificial neural network is terminated by the user by pressing the <b>q</b> key on the keyboard when the 7225th epoch value is reached.

## Testing The Artificial Neural Network
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/045d961e-6490-4a29-90c3-69805570c89d" width="800"/>
</p>
The artificial neural network can be tested by entering 1 in <b>Operation</b> menu.<br /><br />
- Let’s enter 1.


### Step 1 : TEST
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/a2dff670-09a6-4160-9572-b622fc63d3fa" width="800"/>
</p>
  - First, let's enter the location of file <b>Test</b>. Next, let's enter the value 400 since all samples are wanted to be used.<br />
  
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/906bca03-98c6-4f6e-bd3f-08665ac6b835" width="800"/>
</p>
Testing is completed. It failed to predict 38 out of 400 samples. Success rate is 90.5%

## Running The Artificial Neural Network
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/7363672a-cccb-4e52-95c5-ff13c16ff9b4" width="800"/>
</p>
The artificial neural network can be run by entering 2 in <b>Operation</b> menu.<br /><br />
- Let’s enter 2.

### Step 1 : RUN
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/c8557f97-4063-4daf-9318-49315b677e7d" width="800"/>
</p>
Input values are passed. <br /> <br />
- Age			52 <br />
- Sex			1 (Male) <br />
- Bmi			42947 <br />
- Children		2 <br />
- Smooker		-1 (He doesn't smoke.) <br />
- Region		1 (Northwest) <br />

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/8a184818-5b15-466b-a66c-8f5e456e0ef2" width="800"/>
</p>

Output	: 4 (25K-35K)


## Displaying The Features Of The Artificial Neural Network
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/2ec32ff8-4336-4bdb-a33b-e12ba17bcb24" width="800"/>
</p>
The features of the artificial neural network can be listed by entering 3 from <b>Operation</b> menu.<br /><br />
-  Let’s enter 3.<br />

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/29d90f25-b7de-49ed-85db-9c0f191a7cde" width="800"/>
</p>

# Attention
The files related to that example problem have been moved to  <a href="https://github.com/erdeneryesil/NeuralNetworkCore/tree/master/NeuralNetworkTerminal/sample">sample</a> directory, you can obtain them from there. You should take this into consideration when specifying the location of the artificial neural network file. 
Descriptions of the files in <a href="https://github.com/erdeneryesil/NeuralNetworkCore/tree/master/NeuralNetworkTerminal/sample">sample</a> directory are below.<br /><br />

- <b>insurance 			:</b>  The file that we created previously and where the properties and parameters of the artificial neural network are stored. This artificial neural network has not been trained yet.<br />

- <b>insuranceEW			:</b> The file where the training records of the artificial neural network we created previously will be stored. This file is empty because the artificial neural network has not been trained yet.<br />

- <b>insuranceTrained		:</b> This is the file where the state of the artificial neural network saved in file <b>insurance</b> is stored after 7225 epochs of training.<br />

- <b>insuranceTrainedEW	:</b> It is the file where the training records of the artificial neural network are stored. Calculated at every epoch, it stores information such as total error values and numbers of updated weight.<br />

- <b>Train				:</b> The training set file.<br />

- <b>Test				:</b> The test set file.<br />










