#include "mnist_loader.h"
#include <iostream>
#include <fstream>

//g++ -std=c++17 *.cpp  -o convertMNIST



int main() {

  int countSamplesTrain=60000;
  mnist_loader mnistLoaderTrain("train-images-idx3-ubyte","train-labels-idx1-ubyte", countSamplesTrain);
  std::ofstream oStreamTrain("trainMNIST",std::ios::out);

  for(int i=0;i<countSamplesTrain;i++){
    int rows  = mnistLoaderTrain.rows();
    int cols  = mnistLoaderTrain.cols();
    int label = mnistLoaderTrain.labels(i);
    std::vector<double> image = mnistLoaderTrain.images(i);//-0.5 ile +0.5 arasında sayılar içeriyor

    for (int y=0; y<rows; y++) {
      for (int x=0; x<cols; x++) {
        int pixelValue=(image[y*cols+x] == 0.0)? 0 : 1;
        oStreamTrain<<pixelValue<<";";
      }
    }
    oStreamTrain<<label;
    if(i!=countSamplesTrain-1)
      oStreamTrain<<"\n";
  }
  oStreamTrain.close();



  int countSamplesTest=10000;
  mnist_loader mnistLoaderTest("t10k-images-idx3-ubyte","t10k-labels-idx1-ubyte", countSamplesTest);
  std::ofstream oStreamTest("testMNIST",std::ios::out);

  for(int i=0;i<countSamplesTest;i++){
    int rows  = mnistLoaderTest.rows();
    int cols  = mnistLoaderTest.cols();
    int label = mnistLoaderTest.labels(i);
    std::vector<double> image = mnistLoaderTest.images(i);

    for (int y=0; y<rows; y++) {
      for (int x=0; x<cols; x++) {
        int pixelValue=(image[y*cols+x] == 0.0)? 0 : 1;
        oStreamTest<<pixelValue<<";";
      }
    }
    oStreamTest<<label;
    if(i!=countSamplesTest-1)
      oStreamTest<<"\n";
  }
  oStreamTest.close();

  return 0;
}
