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
<b>-testMNIST :</b> Test data was also converted and stored.















