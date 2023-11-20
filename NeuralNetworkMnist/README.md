# NeuralNetworkMnist

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/8763af07-52a9-491d-b3aa-1f761be65078" width="800"/>
</p>

NeuralNetworkMnist is a customized version of <a href="https://github.com/erdeneryesil/NeuralNetworkCore/tree/master/NeuralNetworkGui">NeuralNetworkGui</a> for the Mnist database. Although it largely has the same visual design as NeuralNetworkGui, it includes some changes. As a result, NeuralNetworkMnist is a graphical user interface application that can perform operations such as creating, training, testing artificial neural network etc. using the NeuralNetworkCore library, just like NeuralNetworkGui.

There is a menu on the left side of the application and an empty white area on the right side. When an artificial neural network is created or an existing artificial neural network is opened, there will be a drawing symbolizing the architecture of the artificial neural network in that empty white space.

## The MNIST Database

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/8a776959-a4cb-45f1-bf72-eda68467a896" width="600"/>
</p>
Mnist database is a dataset containing images of handwritten numbers. It contains tens of thousands of examples. There are a total of 70000 hand-written number images. 60000 of them are used for training and the remaining 10000 are used for testing. <br/><br/>


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/ffe29058-c306-4dbd-a271-345758b9958d" width="600"/>
</p>
Each of these images is the same size. It is 28x28 pixels in size and therefore each image contains a total of 784 pixels. <br/><br/>


<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/e3f8ba2d-c1fd-450f-aa80-e1092b21263d" width="600"/>
</p>
In the Mnist database, there is not only these images but also a label data about which digit each image represents. <br/><br/>


<a href="http://yann.lecun.com/exdb/mnist/">
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/30946c9c-9949-40ce-83a2-1669d559e5f7" width="600"/>
</p>
</a>

The MNIST database can be accessed at http://yann.lecun.com/exdb/mnist/

The files included in the MNIST database are listed below.

<b>-training set images (train-images-idx3-ubyte.gz) :</b> This file contains 60000 images to be used for training. <br/>
<b>-training set labels (train-labels-idx1-ubyte.gz):</b> This file contains label data indicating which number each of the images to be used for training represents.<br/>
<b>-test set images (t10k-images-idx3-ubyte.gz) :</b> This file contains 10000 images to be used for testing. <br/>
<b>-test set labels (t10k-labels-idx1-ubyte.gz):</b> This file contains label data indicating which number each of the images to be used for testing represents.<br/>

## MNIST loader
The contents of the 4 files in the Mnist database are not directly accessible and readable. In other words, it is not possible to read the content by opening it with an application such as notepad. However, these contents need to be handled and processed by NeuralNetworkMnist. <a href="https://github.com/arpaka/mnist-loader ">MNIST loader</a> project was used to achieve this transformation.


The files in the <a href="http://yann.lecun.com/exdb/mnist/">MNIST database</a> and the source codes of the <a href="https://github.com/arpaka/mnist-loader ">MNIST loader project</a>  are located in the <a href="https://github.com/erdeneryesil/NeuralNetworkCore/tree/master/NeuralNetworkMnist/convertMnist">convertMnist</a> directory. When the <b>main.cpp</b> file is compiled and run, two files named <b>trainMNIST</b> and <b>testMNIST</b> will be created.

<b>-trainMNIST :</b> Training data in the MNIST database has become available to be handled by NeuralNetworkMnist and it was saved to this file.<br />
<b>-testMNIST :</b> Test data was also converted and stored.<br />

## Creating a New Artificial Neural Network

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/08706771-f9f6-450e-abe8-26a65468ffa4" width="800"/>
</p>

<b>New</b> button is clicked and the artifical neural network to be created is designed step by step.<br/><br/>
Step 1 : The features of the input layer are determined.<br/>
Step 2 : The features of the hidden layers are determined.<br/>
Step 3 : The features of the output layer are determined.<br/>
Step 4 : File and training parameters are determined.<br/>


### Step 1: Input Layer

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/af6bd25c-1310-420f-8e4f-bdcd8805af15" width="800"/>
</p>


The features that need to be determined in the <b>Input Layer</b> window:<br/><br/>
-The number of real-world data that will be passed to the input layer of the artificial neural network.<br/>
-Real-world input data passed to the artificial neural network must be converted to ‘ANN data types' before it can be processed by the neural network.<br/>
-The min and max range of the input values.<br/><br/>

Let's design the input layer for Mnist database : <br/>
-The number of inputs : 784<br/>

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/170975b6-7de8-478d-a143-e6f1a1681479" width="400"/>
</p>

Each of the images in the Mnist dataset is 28px wide and 28px high. Therefore, it contains 784 pixels. <br /><br />

-'ANN data types' into which real-world input data will be converted. <br/>
Pixel data in the input layer of the artificial neural network was converted to <b>Native</b> type. <br /><br />

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/8cec5e56-ec5c-4313-ac45-58e3154c6c5b" width="400"/>
</p>

The data called pixels are actually decimal numbers that can have values between -0.5 and 0.5 in the Mnist database. That means that pixel values can include not only black or white, but also shades of gray. As seen in the image above, there are many grayscale pixels.<br /><br />

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/0c405d22-3103-46a0-94a2-6ddcc0c73e67" width="400"/>
</p>

In the convertion made using the <a href="https://github.com/arpaka/mnist-loader ">MNIST loader</a> project, grayscale pixels were assumed to be white and the background color was set to black. <br /><br />

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/2303f947-7400-40b6-96f2-53267ace3105" width="400"/>
</p>

<b>Native</b> data type was preferred because pixels can only take the value 0 or 1. <br /><br />

-The min and max range of the input values: <br/>
Since all input layer data was converted to <b>Native</b> type, min and max values were determined automatically, and there was no need to specify any values.<br />

### Step 2: Hidden Layers

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/b8a6d7c5-e784-47f7-bf1d-5441e8dfe651" width="800"/>
</p>

The features that need to be determined in the <b>Hidden Layers</b> window:<br/><br/>
-The number of hidden layers<br/>
-The number of cells each hidden layer has<br/>
-The summation function of each hidden layer<br/>
-The activation function of each hidden layer<br/><br/>

Let's design the hidden layers for our example: <br/>
-The number of hidden layers : 2<br/>
-First hidden layer:<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The number of cells : 500<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The summation Function : Weighted Total<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The activation Function : Sigmoid<br/>
-Second hidden layer:<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The number of cells : 250<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The summation Function : Weighted Total<br/>
	&nbsp; &nbsp;&nbsp; &nbsp;-The activation Function : Sigmoid<br/><br/>

 ### Step 3: Output Layer
 
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/d4e5aa49-d300-4ecc-a517-17b2f71f9beb" width="800"/>
</p>

The features that need to be determined in the <b>Output Layer</b> window:<br/><br/>

-The number of real world output data. (The artificial neural network can contain more than 1 output data ) <br/>
-The summation function of the output layer<br/>
-The activation function of the output layer<br/>
-Just like inputs, output data needs to be converted into 'ANN data types' that the artificial neural network can process.<br/>
-The min and max range of the output values.<br/>
-The tolerance values of the output cells. When training our network, what is the acceptable margin of error regarding the expected outputs from the output cells? Each output cell will produce a value between 0 and 1. Therefore, we must take this into consideration when determining the tolerance.<br/><br/>

Let's design the output layer for our example:<br/>

-The number of outputs : 1<br/>
-The summation function: Weighted Total<br/>
-The activation function : Sigmoid<br/>
-'ANN data type' into which the digit data will be converted : Flag <br/>
-The min and max range of the output value:  0 – 9<br/>
-The tolerance value : 0.1<br/>












