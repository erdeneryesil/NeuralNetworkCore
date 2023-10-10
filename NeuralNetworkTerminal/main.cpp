#include"menu.h"

//g++ neural_network_core/*.cpp neural_network_core/*.h *.cpp *.h  -o neuralNetwork


int main(int argc, char *argv[]){

  std::cout<<"---------------------------------------------------------------------------------------------------------------\n"
  "                                               NEURAL NETWORK TERMINAL                                                \n"
  "---------------------------------------------------------------------------------------------------------------\n";


  Menu::MainMenu selection=Menu::MainMenu::DetermineNN;
  NeuralNetwork *neuralNetwork=nullptr;

  do{
    switch(selection){
      case Menu::MainMenu::DetermineNN:{
        if(neuralNetwork){
          delete neuralNetwork;
        }
        neuralNetwork=Menu::determineNeuralNetwork();
      }
      case Menu::MainMenu::ExecOperation:{
        Menu::execOperation(neuralNetwork);
        break;
      }
      case Menu::MainMenu::Exit:
      return 0;
    }

    Menu::headline("MAIN MENU",INT_POS_1);
    Menu::listMainMenuItems();
    std::string info="Enter your selection";
    Menu::getValue<Menu::MainMenu>(info,selection,COUNT_MAIN_MENU_ITEM);

  }while(selection!=Menu::MainMenu::Exit);


  /*

  neuralNetwork->train(10,"deneme/denemeTrain");


  int input1[]{0,1,2,3};
  int input2[]{1,1,2,3};
  int input3[]{0,2,3,4};
  int input4[]{1,2,3,4};
  int input5[]{0,3,4,5};
  int input6[]{1,3,4,5};
  int input7[]{0,4,5,6};
  int input8[]{1,4,5,6};
  int input9[]{0,5,6,7};
  int input10[]{1,5,6,7};



  double* output=neuralNetwork->run(input1);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input2);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input3);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input4);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input5);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input6);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input7);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input8);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input9);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input10);
  std::cout<<std::round(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<std::round(output[3])<<std::endl;
  delete[] output;


  std::cout<<"---------------------------"<<std::endl;

  output=neuralNetwork->run(input1);
  std::cout<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input2);
  std::cout<<" "<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input3);
  std::cout<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input4);
  std::cout<<" "<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input5);
  std::cout<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input6);
  std::cout<<" "<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input7);
  std::cout<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input8);
  std::cout<<" "<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input9);
  std::cout<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;

  output=neuralNetwork->run(input10);
  std::cout<<" "<<(output[0])<<"\t\t"<<output[1]<<"\t\t"<<output[2]<<"\t\t"<<(output[3])<<std::endl;
  delete[] output;


  std::cout<<neuralNetwork->test(10,"deneme/denemeTrain")<<std::endl;


  delete neuralNetwork;

  */


  return 0;
}
