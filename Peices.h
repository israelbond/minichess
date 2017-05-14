
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;


class Point 
{
    public:

    Point();
    Point(int,int);
    ~Point();
    void Set_Point(int, int);
    void Display_P();

//    protected:
        int x;
        int y;
};

class Peice
{
    public:
        Peice();
        ~Peice();
        void S_B_Pawn();
        void S_W_Pawn();
        void S_King();
        void S_Queen();
        void S_Rook();
        void S_Knight();
        void S_Bishop();

//    protected:
//        char type;
        int score;
        Point dim;
        Point ** shape;

};

