# NeuralNetworkTerminal

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/6793f415-9f60-4ddf-9627-bd88ae2da029" width="500"/>
</p>

NeuralNetworkTerminal is an application run in terminal, where operations such as creating, training and testing an artificial neural network can be performed using the NeuralNetworkCore library.

When we run the application, we see the name of our application, 'NEURAL NETWORK TERMINAL', at the top.

Since the application will be managed via terminal, the options will be determined using numbers. So, no matter what level of the menu, we will make every choice with numbers.

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
The dataset contains 7 fields. The first 6 of these will be our input data, and the last column, charges, will be our output data.

## Creating a New Artificial Neural Network
### Step 'OPEN OR CREATE A NEURALNETWORK'
