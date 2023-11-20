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
In the Mnist database, there is not only these images but also a label data about which digit each image represents.
