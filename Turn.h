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
class Move // : public Turn
{
    public:
        Move();

        void S_Move(Point&,Point&,int&,char&);
//        void Insert();
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
        void Set_Move(Move&,Move&);

        int Board_Eval(char**&);
        bool Game_Over(char**&);
        void Make_Move(char**&, Move&);
        void Display_Turn(void);
        void Change_Player(void);
        void Set_Piece_List(void);
        int Peice_Value(char&);
        bool Opponent(char&,char&);
//        void Moved(char**&,Move);
        void Unmove(char**&,Move&);
        char** Copy_Board(char**&);
        void Remove_Board(char**&);
        void Change_player(void);
        void Display_Vars();                
        void Display_Board(char**&);
        void Remove_List(Move*&);
        
//    protected:

        char playing;
        char** board;
        int player;
        int turn_count; 
//        Move piece;
        Peice pieces[MAX_P];
        Move * list;//list[MOVES];
//        int * check;
};

class Player : public Turn
{
    public:

    void Run(void);
    Move* Generate_Moves(char**&,int&,int&);
    Move* Sort_Moves(Move[],Move[],int&,int&);
    void Copy_Moves(Move[],int&,int&,Move[]);
    void Merge_Top_Down(Move[],int&,int&,int&,Move[]);
    void Split_Merge(Move[],int&,int&,Move[]);
    void White_Moves(Move*&,int&,int&,int&,char&);
    void Black_Moves(Move*&,int&,int&,int&,char&);
    void Move_W_Pawn(Move*&,int&,int&,int&,Peice&);
    void Move_B_Pawn(Move*&,int&,int&,int&,Peice&);
    void Move_Knight(Move*&,int&,int&,int&,Peice&);
    void Move_Bishop(Move*&,int&,int&,int&,Peice&);
    void Move_Queen(Move*&,int&,int&,int&,Peice&);
    void Move_King(Move*&,int&,int&,int&,Peice&);
    void Move_Rook(Move*&,int&,int&,int&,Peice&);
    void Display_Moves(Move*&,int&);
};

