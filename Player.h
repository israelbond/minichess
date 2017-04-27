#include "Peices.h"

const int ROW = 6;
const int COL = 6;

class Player
{
    public:
        Player();
        ~Player();
        void Display_Player();

    protected:
    char playing;
    char board[ROW][COL];
    int turn_count; 
};
