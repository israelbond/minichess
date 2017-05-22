/*Israel Bond
 * MiniChess player
 * CS442
 
 file contains class declarations for: POINT & PEICE */
#include <cstdio>
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
    void Show();

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

        int score;
        Point dim;
        Point ** shape;

};

