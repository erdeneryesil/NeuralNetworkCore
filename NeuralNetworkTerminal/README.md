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

Age		:	Person’s age. It is an integer.
It is already numerical data, there is no need for any digitization.

Sex		:	Person’s gender. It is a categorical data. Options: Female, Male.
Digitization of it : Female=0, Male=1

Bmi		:	The person's body mass index. It is a decimal number. The part on the right side of the decimal point consists 3 digits.
Transformation: To convert body mass index values into integers, they are multiplied by 1000.

Children	:	Number of children covered by the person's health insurance / Number of dependents of the person.It is an integer.
It is already numerical data, there is no need for any digitization.

Smoker		:	Whether the person smokes or not. It is a categorical data. Options: Yes, No:Hayır  
Digitization of it : No=-1, Yes=1 (The values -1 and 1 were determined arbitrarily.)

Region		:	The region where the person lives. It is a categorical data. 
 Options: Southeast , Northeast , Northwest , Southwest . 
Digitization of it :   Southeast = -2, Northeast = -1, Northwest = 1, Southwest = 2 (The values were determined arbitrarily.)

Charges	:	Individual medical costs billed by health insurance. It is a decimal number.
Since this data has a very wide range, it was divided into a total of 7 categories
