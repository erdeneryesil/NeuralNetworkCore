# NeuralNetworkCore



Using the NeuralNetworkCore library, an artificial neural network with the preferred features can be designed, trained, tested, and output values can be calculated by passing input values. Through NeuralNetworkCore, artificial neural networks can be designed that use feed-forward, supervised learning method and can be trained by the generalized delta rule.

NeuralNetworkCore library contains class NeuralNetwork that represents an artificial neural network, as well as the classes that model the components that build any artificial neural network.

<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/6a6d164a-9431-40a6-9237-5cd61cd7223e" width="500"/>
</p>


Class NeuralNetwork is the only class whose instances will be created by those who will use this library. 

The others in the NeuralNetworkCore library are classes that model the components of an artificial neural network. Instances of these classes are brought together in class NeuralNetwork to model an artificial neural network.

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
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/93bf5acd-3f1d-477e-9dde-b097127538b1" width="500"/>
</p>
Contains and manages the features of the input layer of a artificial neural network. This class can be considered as a template. The features of the input layer are handled by this class. But cells(or neurons) that compose the input layer of a artificial neural network are not included in this class.

In the content of this class, how many real-world data are passed to the input of an artificial neural network, which ANN data types that real-world data are converted to, how many cells each real-world data is represented, etc.

### Class HiddenLayerPattern
<p align="center">
<img src="https://github.com/erdeneryesil/NeuralNetworkCore/assets/14914042/29c6f441-d7ee-4b0e-bfc4-313c6bb7d509" width="500"/>
</p>
Contains and manages the features of the hidden layers of a artificial neural network. This class can be considered as a template just like classes InputLayerPattern and OutputLayerPattern. Cells(or neurons) that compose the hidden layers of a artificial neural network are not included in this class.

The number of hidden layers, the number of cells of each hidden layer, the summation and activation functions of each hidden layer are stored in this class.
















