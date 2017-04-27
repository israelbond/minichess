
#include "Player.h"

Player::Player()
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

Player::~Player()
{

}

void Player::Display_Player()
{
/*    fprintf(stderr,"Player %c\n", playing);
    fprintf(stderr,"turn %d\n", turn_count);
    fprintf(stderr,"%s\n", board);
*/
    cout<<"PLAYER "<<playing<<endl;
    cout<<"turn # "<<turn_count<<endl;
    for(int i = 0; i<ROW; ++i)
        cout<<board[i]<<endl;
}

