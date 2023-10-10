//reference: http://linux-sxs.org/programming/kbhit.html

#ifndef KBHIT_H
#define KBHIT_H

#include<termios.h>

class Keyboard{
    public:
        Keyboard();
        ~Keyboard();
        int kbhit();
        int getch();

    private:
        struct termios _initialSettings;
        struct termios _newSettings;
        int _peekCharacter;
};

#endif
