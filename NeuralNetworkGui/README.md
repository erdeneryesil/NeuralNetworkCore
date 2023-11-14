# NeuralNetworkGui

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/fbcb7247-ce68-42c3-a17e-6f97933f2e87" width="800"/>
</p>

NeuralNetworkGui is a graphical user interface application that allows operations such as creating, training, testing artificial neural network etc. using the NeuralNetworkCore library. The front end of the application was developed using the Qt Framework.

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

<b>New</b> button is clicked and the artifical neural network to be created is designed step by step.

Step 1 : The features of the input layer are determined.
Step 2 : The features of the hidden layers are determined.
Step 3 : The features of the output layer are determined.
Step 4 : File and training parameters are determined.

### Step 1: Input Layer

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/a05749b2-6320-4139-9ba7-78d973469006" width="800"/>
</p>

The features that need to be determined in the <b>Input Layer</b> window:<br/><br/>
-The number of real-world data that will be passed to the input layer of the artificial neural network.<br/>
-Real-world input data passed to the artificial neural network must be converted to ‘ANN data types' before it can be processed by the neural network.<br/>
-The min and max range of the input values.<br/><br/>

Let's design the input layer for our example:<br/><br/>
-The number of inputs : 6<br/>
-'ANN data types' into which real-world input data will be converted.<br/>
 	- Age -> Binary<br/>
 	- Sex -> Native<br/>
 	- Bmi -> Narrowed<br/>
 	- Children -> Binary<br/>
 	- Smooker -> Binary<br/>
	- Region -> Flag<br/>





















