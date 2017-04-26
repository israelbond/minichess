
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>

class Peice
{
    public:
        Peice();
        ~Peice();
    protected:
        char type;
        Point * shape;

};

class B_Pawn
{
    public:
        
        B_Pawn();
        ~B_Pawn();
};
