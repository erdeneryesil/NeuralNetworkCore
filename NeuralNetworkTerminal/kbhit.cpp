//reference: http://linux-sxs.org/programming/kbhit.html

#include"kbhit.h"
#include<unistd.h> // read()

Keyboard::Keyboard(){
    tcgetattr(0,&this->_initialSettings);
    this->_newSettings = this->_initialSettings;
    this->_newSettings.c_lflag &= ~ICANON;
    this->_newSettings.c_lflag &= ~ECHO;
    this->_newSettings.c_lflag &= ~ISIG;
    this->_newSettings.c_cc[VMIN] = 1;
    this->_newSettings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &this->_newSettings);
    this->_peekCharacter=-1;
}

Keyboard::~Keyboard(){
    tcsetattr(0, TCSANOW, &this->_initialSettings);
}

int Keyboard::kbhit(){
    unsigned char ch;
    int nread;
    if (this->_peekCharacter != -1) return 1;
    this->_newSettings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &this->_newSettings);
    nread = read(0,&ch,1);
    this->_newSettings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &this->_newSettings);

    if (nread == 1){
        this->_peekCharacter = ch;
        return 1;
    }
    return 0;
}

int Keyboard::getch(){
    char ch;

    if (this->_peekCharacter != -1){
        ch = this->_peekCharacter;
        this->_peekCharacter = -1;
    }
    else read(0,&ch,1);
    return ch;
}