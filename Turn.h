/*Israel Bond
 * MiniChess player
 * CS442
 
 File contains class declarations for: Move, Turn & Player. ALL data is public
 I know this is very BAD practices but I was trying to just get it working and 
 worry about syntactic sugar later!*/
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

class Move // : public Turn
{
    public:
        Move();

        void S_Move(Point&,Point&,int&,char&);
        char* Make_string();
        int value;
        char type;
        void Display_M();
        Point to;
        Point from;
        char word[5];
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

        int Board_Eval(int);
        bool Game_Over(int);
        void Make_Move( Move);
        void Display_Turn(void);
        void Change_Player(void);
        void Set_Piece_List(void);
        int Peice_Value(char&);
        bool Opponent(char,char);
        void Unmove(bool &,Move&);
        void Change_player(void);
        void Display_Vars(void);                
        void Display_Board();
        void Remove_List(Move*&); 
        void Server_Dis(Move);

        char playing;
        char** board;
        int player;
        int turn_count; 
        Peice pieces[MAX_P];
        Move * list;//list[MOVES];
};

class Player : public Turn
{
    public:
    Player();
    void Run(void);
    Move* Generate_Moves(int,int&,int&);
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
    bool Promotions(bool&);

    bool propawn;
};

