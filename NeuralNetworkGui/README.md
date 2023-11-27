# NeuralNetworkGui

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/fbcb7247-ce68-42c3-a17e-6f97933f2e87" width="800"/>
</p>

NeuralNetworkGui is a graphical user interface application that allows operations such as creating, training, testing artificial neural network etc. using the NeuralNetworkCore library. The front-end of the application was developed using the Qt Framework.

There is a menu on the left side of the application and an empty white area on the right side. When an artificial neural network is created or an existing artificial neural network is opened, there will be a drawing symbolizing the architecture of the artificial neural network in that empty white space.

Let's see how to create an artificial neural network, how to open it, how to train and test it using an <a href="https://www.kaggle.com/datasets/mirichoi0218/insurance" >example problem</a>.

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
The dataset contains 7 fields. The first 6 of these will be our input data, and the last column, charges, will be our output data.

## Creating a New Artificial Neural Network

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/552a6965-a114-4176-852e-7d56beab6b05" width="800"/>
</p>

Button <b>New</b> is clicked and the artifical neural network to be created is designed step by step.<br/><br/>
Step 1 : The features of the input layer are determined.<br/>
Step 2 : The features of the hidden layers are determined.<br/>
Step 3 : The features of the output layer are determined.<br/>
Step 4 : File and training parameters are determined.<br/>

### Step 1: Input Layer

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/a05749b2-6320-4139-9ba7-78d973469006" width="800"/>
</p>

The features that need to be determined in the <b>Input Layer</b> window:<br/>
-The number of real-world data that will be passed to the input layer of the artificial neural network.<br/>
-Real-world input data passed to the artificial neural network must be converted to <b>ANN data types</b> before it can be processed by the neural network.<br/>
-The min and max range of the input values.<br/><br/>

Let's design the input layer for our example:<br/>
-The number of inputs : 6<br/>
-<b>ANN data types</b> into which real-world input data will be converted.<br/>
 	&nbsp; &nbsp;&nbsp; &nbsp;-Age -> Binary<br/>
 	&nbsp; &nbsp;&nbsp; &nbsp;-Sex -> Native<br/>
 	&nbsp; &nbsp;&nbsp; &nbsp;-Bmi -> Narrowed<br/>
 	&nbsp; &nbsp;&nbsp; &nbsp;-Children -> Binary<br/>
 	&nbsp; &nbsp;&nbsp; &nbsp;-Smooker -> Binary<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-Region -> Flag<br/>
-The min and max range of the input values:<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-Age : min=18, max=64<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-Sex : Sex was converted to Native. That's why Min= 0, Max=1<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-Bmi : Min=15960, Max=53130 <br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-Children : Min=0, Max=5<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-Smoker: Min = -1 Max=1 <br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-Region: Min= -2, Max=+2<br/><br/>


### Step 2: Hidden Layers

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/426fdabd-e26b-4530-9fd0-7f45423e7b9a" width="800"/>
</p>
The features that need to be determined in the <b>Hidden Layers</b> window:<br/>
-The number of hidden layers <br/>
-The number of cells each hidden layer has<br/>
-The summation function of each hidden layer<br/>
-The activation function of each hidden layer<br/><br/>

Let's design the hidden layers for our example:<br/>
-The number of hidden layers : 2<br/>
-First hidden layer:<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The number of cells : 22<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The summation Function : Weighted Total<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The activation Function : TanH<br/>
-Second hidden layer:<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The number of cells : 18<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The summation Function : Weighted Total<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The activation Function : Sigmoid<br/><br/>

 ### Step 3: Output Layer

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/8df42eb1-b6f7-45ac-82b1-5dd71ad159a8" width="800"/>
</p>

The features that need to be determined in the <b>Output Layer</b> window:<br/>
-The number of real world output data. (The artificial neural network can contain more than 1 output data ) <br/>
-The summation function of the output layer<br/>
-The activation function of the output layer<br/>
-Just like inputs, output data needs to be converted into <b>ANN data types</b> that the artificial neural network can process.<br/>
-The min and max range of the output values.<br/>
-The tolerance values of the output cells. When training our network, what is the acceptable margin of error regarding the expected outputs from the output cells? Each output cell will produce a value between 0 and 1. Therefore, we must take this into consideration when determining the tolerance.<br/><br/>

Let's design the output layer for our example:<br/>
-The number of outputs : 1<br/>
-The summation function: Weighted Total<br/>
-The activation function : Sigmoid<br/>
-<b>ANN data type</b> into which real-world output data will be converted. <br/>
&nbsp; &nbsp;&nbsp; &nbsp;-Charges -> Flag<br/>
-The min and max range of the output value:  0 – 6<br/>
-The tolerance value : 0.1<br/>

### Step 4: Training And File Settings

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/9b8703a4-66a1-4603-9df5-4367213ec66d" width="800"/>
</p>

The features that need to be determined in the <b>Training and File Settings</b> window:<br/>
-Training features:<br/>
&nbsp; &nbsp;&nbsp; &nbsp;-The lambda value<br/>
&nbsp; &nbsp;&nbsp; &nbsp;-The alfa value<br/>
&nbsp; &nbsp;&nbsp; &nbsp;-‘Random weight min’ ve ‘Random weight  max’Y : When the artificial neural network is first created, the weight value of each cell's connections is determined randomly. The min and max range of that random values needs to be specified.<br/>
-File features:<br/>
&nbsp; &nbsp;&nbsp; &nbsp;-All data related to the artificial neural network is stored in files, and when sorting the data in the files, a character must be placed between them.<br/>
&nbsp; &nbsp;&nbsp; &nbsp;-The location where the files to be created will be stored.<br/>
&nbsp; &nbsp;&nbsp; &nbsp;-The names of the files in which the features of the artificial neural network are stored need to be determined.<br/><br/>

Let’s define training and file parameters:<br/>
-Lambda = 0.015<br/>
-Alfa = 0.15 <br/>
-Random weight min =-1, Random weight  max=+1 <br/>
-Separator Character :  Semicolon (;)<br/>
-Location :  'sample' directory (it is located within the source files of the project)<br/>
-File name : ‘insurance’<br/>

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/982d60f4-7c11-4ae5-8bea-deb5e0775032" width="400"/>
</p>

Two files were created named <b>insurance</b> and <b>insuranceEW</b> in sample directory.

File <b>insurance</b> stores the properties and parameters of the artificial neural network.<br/>
File <b>insuranceEW</b> will store the training records of the artificial neural network.<br/>

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/583b499f-7642-4d3c-ab2d-603576d5b061" width="800"/>
</p>
When the artificial neural network was created, a shape symbolizing the architecture of the artificial neural network was drawn on the right side of our application. On the left, it can be seen that all the features of the artificial neural network are listed under headings.

## Opening an Existing Neural Network

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/cc351675-3ead-4e20-af1b-e035b2583748" width="800"/>
</p>

Button <b>Open</b> is clicked.

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/68e8b154-262c-42b7-b4cb-f7120f03a972" width="800"/>
</p>

The features that need to be determined in <b>Neural Network File</b> window:<br/>
-The separator character used in existing artificial neural network files.<br/>
-The location of the saved artificial neural network file.<br/>

## Editing The Artificial Neural Network

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/f06313bd-3e8c-44a0-baab-c39d3ed22005" width="800"/>
</p>

Button <b>Edit</b> is clicked and the artificial neural network is edited step by step.<br/>
Step 1 : The features of the input layer are viewed.<br/>
Step 2 : Some features of the hidden layers can be edited, the others can only be viewed.<br/>
Step 3 : Some features of the output layer can be edited, the others can only be viewed.<br/>
Step 4 : Training features can be edited but file features can only be viewed.<br/>


### Step 1 : Input Layer

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/6daa1153-3243-4f54-a01e-ca5076763e6a" width="800"/>
</p>

Since the input layer of an existing artificial neural network cannot be edited, only the features of the input layer are viewed in <b>Input Layer</b> window.

### Step 2 : Hidden Layers

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/d165e4b7-59a6-471a-baf4-1f8efa0996be" width="800"/>
</p>

The cell numbers of the hidden layers of an existing artificial neural network cannot be changed. However, the summation and the activation functions can be edited.

### Step 3 : Output Layer

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/2fb1aba3-6cab-48ca-9cb4-b25cddb07161" width="800"/>
</p>

The summation function, the activation function and the tolerance values of the output layer of an existing artificial neural network can be edited. The other features cannot be updated and can only be viewed.

### Step 4 : Training and File Settings

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/e6c0366a-7648-4dd5-9c09-cedca4b6dce2" width="800"/>
</p>

The lambda and the alpha values of an existing artificial neural network can be updated. The separator character and file name cannot be edited.

## Training The Artificial Neural Network
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/7e76e029-7fb1-4cac-8ef1-26b3469cd1aa" width="600"/>
</p>

First, let's put the training and test set files(<b>Train</b>, <b>Test</b>) in <b>sample</b> directory, just like files insurance and insuranceEW.

There were a total of 1338 rows in the dataset of our example problem. In other words, information about 1338 people is included in our data set. But since we categorized the <b>Charges</b> column between 0-6, data repetition occurred in some records. The records decreased from 1338 to 1335, meaning 3 rows were deleted. 
Of the 1335 rows, 935 were transferred to the training set and 400 were transferred to the test set.

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/04f82540-6de2-4817-8832-b7e42e88b8e9" width="800"/>
</p>

Button <b>Train</b> is clicked.

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/ccc04d1c-22eb-4c47-89ce-afb47dc0a210" width="800"/>
</p>

Let's enter the location of file <b>Train</b>, which contains the samples we will use to train our network, and the number 935 since we want to use all the samples in this file.

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/4ac781fa-94eb-4aab-b51a-c1353d7141c1" width="800"/>
</p>

The artificial neural network will start training. Epoch, total error value and number of updated weights are displayed simultaneously.

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/d5ee2c7d-9696-487f-ac59-10d54fb5d60e" width="800"/>
</p>

As soon as the training starts, the text on button  <b>Train</b> changes to <b>'Stop Training'</b>. To stop the training, it is necessary to press the same button again.


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/81962ca8-4eb0-4b67-bd51-1fccb9051132" width="800"/>
</p>

By checking check box <b>Show Graph</b>, the total error value and the number of updated weights can be displayed on the graph.


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/862c1822-ee06-4d7a-afbc-04e5269b638c" width="800"/>
</p>

The blue dots represent the numbers of updated weights, and the red dots represent the total error values.


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/ba00944f-e610-467a-a7f3-30c1007b5611" width="800"/>
</p>

In this example scenario, the training of the artificial neural network is terminated by the user by clicking button <b>Stop Training</b> when the 7225th epoch value is reached.


## Testing The Artificial Neural Network

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/51e274f7-9a1b-4a1b-bdde-556417e9b669" width="800"/>
</p>

Button <b>Test</b> is clicked.


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/1f78bdd6-a4ac-4dbb-a7ce-dccf6629871a" width="800"/>
</p>

Let's enter the location of file <b>Test</b>, which contains the samples we will use to test our network, and the number 400 since we want to use all the samples in this file.


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/9ad1e98f-5c44-4268-a4d2-405f40383ff2" width="800"/>
</p>

Testing is completed. It failed to predict 38 out of 400 samples. Success rate is 90.5%


## Running The Artificial Neural Network

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/ed68774d-189b-4106-b9ca-c1a25883665d" width="800"/>
</p>

Button <b>Run</b> is clicked.

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/5f900aee-5177-452b-9bba-9797ef28a8c4" width="800"/>
</p>

All input values are entered with a separator character between them.

-Age &nbsp;  : &nbsp; 52 <br/>
-Sex &nbsp; : &nbsp; 1 (Male)<br/>
-Bmi &nbsp; : &nbsp; 42947<br/>
-Children &nbsp; : &nbsp; 2<br/>
-Smooker &nbsp; : &nbsp; -1 (He doesn't smoke)<br/>
-Region	&nbsp; : &nbsp; 1 (Northwest)<br/>


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/40623420-8770-4606-bc38-8d9f4321af9a" width="800"/>
</p>

-Output &nbsp;  : &nbsp; 4 (25K-35K)


## Note
Descriptions of the files in <a href="https://github.com/erdeneryesil/NeuralNetworkCore/tree/master/NeuralNetworkGui/sample">sample</a> directory are below.

- <b>insurance 			:</b>  The file that we created previously and where the properties and parameters of the artificial neural network are stored. This artificial neural network has not been trained yet.<br />

- <b>insuranceEW			:</b> The file where the training records of the artificial neural network we created previously will be stored. This file is empty because the artificial neural network has not been trained yet.<br />

- <b>insuranceTrained		:</b> This is the file where the state of the artificial neural network saved in file <b>insurance</b> is stored after 7225 epochs of training.<br />

- <b>insuranceTrainedEW	:</b> It is the file where the training records of the artificial neural network are stored. Calculated at every epoch, it stores information such as total error values and numbers of updated weight.<br />

- <b>Train				:</b> The training set file.<br />

- <b>Test				:</b> The test set file.<br />













