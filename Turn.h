#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include "Peices.h"

using namespace std;


const int ROW = 6;
const int COL = 6;
const int MOVES = 52; // Maximum moves for ALL Pieces 
const int MAX_P = 7;

//Class can be used as LLL.... maybe
class Move// : public Turn
{
    public:
        Move();
        void S_Move(Point&,Point&,int&,char&);
        void Insert();
        void Display_M();
//    protected:
        int value;
        char type;
        Point to;
        Point from;
//        Move * next;
};

class Turn
{
    public:
        Turn();
        ~Turn();
        void Starting_State(void);
        void Set_Turn(void);
        void Set_Player(void);
        void Display_Turn(void);
        void Set_Piece_List(void);
        int Peice_Value(char&);
        bool Opponent(char&,char&);
        char** Moved(Move);
        char** Copy_Board(void);
        void Romove_Board(char**&);
                
        
    protected:

        char playing;
        char board[ROW][COL];
        int player;
        int turn_count; 
//        int list_index;
//        int list_max;
        Move piece;
        Peice pieces[MAX_P];
        Move * list;//list[MOVES];
        int * check;
};

class Player : public Turn
{
    public:
    void Generate_Moves(void);
    void White_Moves(int&,int&,char&);
    void Black_Moves(int&,int&,char&);
    void Move_W_Pawn(int&,int&,Peice&);
    void Move_B_Pawn(int&,int&,Peice&);
    void Move_Knight(int&,int&,Peice&);
    void Move_Bishop(int&,int&,Peice&);
    void Move_Queen(int&,int&,Peice&);
    void Move_King(int&,int&,Peice&);
    void Move_Rook(int&,int&,Peice&);
    void Display_Moves(void);
};

