
#include "Turn.h"

Turn::Turn(){
//    Starting_State();
    Set_Turn();
}

Turn::~Turn()
{
//ALL VARIABLE MEMORY IS STATIC 
}

//function uses standard in to fill class variables
//"playing" is a char representing the side playing 
//"turn_count" is an integer representing turn number
void Turn::Set_Turn()
{
    fscanf(stdin, "%d", &turn_count);
    fscanf(stdin, "%s", &playing);

    for(int i=0; i < ROW; ++i)
    {
        fscanf(stdin,"%s", board[i]);
    }
}

//Funstion sets up a new game with a starting chess board,
//and White player on first turn.
void Turn::Starting_State()
{
    int i=0,j=0;
    playing = 'W';
    turn_count = 1;

    char temp[ROW][COL] = {{'k','q','b','n','r','\0'},
                     {'p','p','p','p','p','\0'},
                     {'.','.','.','.','.','\0'},
                     {'.','.','.','.','.','\0'},
                     {'P','P','P','P','P','\0'},
                     {'R','N','B','Q','K','\0'}
                    };
    for(;i<ROW;++i)
    {
        for(;j<COL;++j)
        {
            board[i][j] = temp[i][j];
        }
        j=0;
    }
}
//Function uses standard out to produce an output of class
//variables
void Turn::Display_Turn()
{
    
    fprintf(stdout,"%d ", turn_count);
    fprintf(stdout,"%c\n", playing);
    for(int i = 0; i<ROW; ++i)
        fprintf(stdout,"%s\n",board[i]);
}

