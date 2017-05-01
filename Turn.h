#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;


const int ROW = 6;
const int COL = 6;

class Turn
{
    public:
        Turn();
        ~Turn();
        void Starting_State(void);
        void Set_Turn(void);
        void Display_Turn(void);

    protected:
    char playing;
    char board[ROW][COL];
    int turn_count; 
};
