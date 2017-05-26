/*Israel Bond
 * MiniChess player
 * CS442

    This file contains the implementations for base classes which define a 
    location in courtesan coordinates. these objects are used for creating 
    peice locations, dimensions of peices, and board locations.*/

#include "Peices.h"
//Point class contructors/deconstructors
Point::Point() : x{0}, y{0}/*,word{'\0'}*/ {}
Point::Point(int nx, int ny) : x{nx}, y{ny} {}
Point::~Point(){}

//Sets the values of a point to the vars passed in 
void Point::Set_Point(int nx, int ny)
{
    this->x = nx;
    this->y = ny;
}

//function which displays the 2 points in a chess board position format " a2 "
void Point::Show()
{
   cout<<(char)(y + 'a')<<(int)(6-x);
}

//constructor for Pieces **YES I KNOW ITS MISS SPELLED** intentional!
Peice::Peice():  score{0}
{
    int n =0;//used to set peice 2d array dimensions
    shape = NULL;
    dim.Set_Point(n,n);//Point object
}

//Deconstructor for peices
Peice::~Peice()
{
    if(shape)
    {
        for(int i=0; i<dim.x;++i)
        {
            delete [] shape[i];
        }
        delete [] shape;
        shape = NULL;
    }
}

/*                          PIECE SETTING FUNCTIONS                         
 *  The next 7 methods create dynamically allocated arrays which store the 
 *  particulars on the possible moves that piece can perfom. Each function
 *  manually sets all variables.  
 *          NOTE!!
 *          all type variables have been commented out as they seemed redundant 
 *          once i reached a certin point in programming this assignment*/

void Peice::S_B_Pawn()
{

//    type = 'p';
    dim.Set_Point(1,3);
    score = 1;
    shape = new Point*[dim.x];
    for(int i=0; i<dim.x;++i) shape[i] = new Point[dim.y];

    shape[0][0].Set_Point(1,0);//move
    shape[0][1].Set_Point(1,-1);//attack
    shape[0][2].Set_Point(1,1);//attack

}

 void Peice::S_W_Pawn()
{
//    type = 'P';
    dim.Set_Point(1,3);
    score = 1;
     shape = new Point*[dim.x];
    for(int i=0; i<dim.x;++i) shape[i] = new Point[dim.y];

   shape[0][0].Set_Point(-1,0);//move
    shape[0][1].Set_Point(-1,-1);//attack
    shape[0][2].Set_Point(-1,1);//attack

}

void Peice::S_King()
{
//    type = 'k';
    dim.Set_Point(2,4);
    score = 50;
      shape = new Point*[dim.x];
    for(int i=0; i<dim.x;++i) shape[i] = new Point[dim.y];
    //ALL MOVES AND ATTACKS
  shape[0][0].Set_Point(0,-1);    shape[0][1].Set_Point(-1,-1);
    shape[0][2].Set_Point(-1,0);    shape[0][3].Set_Point(-1,1);

    shape[1][0].Set_Point(0,1);     shape[1][1].Set_Point(1,1);
    shape[1][2].Set_Point(1,0);     shape[1][3].Set_Point(1,-1);

}

void Peice::S_Queen()
{
//    type = 'q';
    dim.Set_Point(8,5);
    score = 9;
       shape = new Point*[dim.x];
    for(int i=0; i<dim.x;++i) shape[i] = new Point[dim.y];

    //NORTH    
    shape[0][0].Set_Point(-1,0);    shape[0][1].Set_Point(-2,0);
    shape[0][2].Set_Point(-3,0);    shape[0][3].Set_Point(-4,0);
    shape[0][4].Set_Point(-5,0);    
    
    //SOUTH
    shape[1][0].Set_Point(1,0);    shape[1][1].Set_Point(2,0);
    shape[1][2].Set_Point(3,0);    shape[1][3].Set_Point(4,0);
    shape[1][4].Set_Point(5,0);    
   
    //NORTHWEST
    shape[2][0].Set_Point(-1,-1);    shape[2][1].Set_Point(-2,-2);
    shape[2][2].Set_Point(-3,-3);    shape[2][3].Set_Point(-4,-4);
    shape[2][4].Set_Point(-10,-10);    
   
    //SOUTHWEST
    shape[3][0].Set_Point(1,-1);    shape[3][1].Set_Point(2,-2);
    shape[3][2].Set_Point(3,-3);    shape[3][3].Set_Point(4,-4);
    shape[3][4].Set_Point(-10,-10);    
    //NORTHEAST
    shape[4][0].Set_Point(-1,1);    shape[4][1].Set_Point(-2,2);
    shape[4][2].Set_Point(-3,3);    shape[4][3].Set_Point(-4,4);
    shape[4][4].Set_Point(-10,-10);    
    //SOUTHEAST
    shape[5][0].Set_Point(1,1);    shape[5][1].Set_Point(2,2);
    shape[5][2].Set_Point(3,3);    shape[5][3].Set_Point(4,4);
    shape[5][4].Set_Point(-10,-10);    
    //EAST
    shape[6][0].Set_Point(0,1);    shape[6][1].Set_Point(0,2);
    shape[6][2].Set_Point(0,3);    shape[6][3].Set_Point(0,4);
    shape[6][4].Set_Point(-10,-10);    
    //WEST
    shape[7][0].Set_Point(0,-1);    shape[7][1].Set_Point(0,-2);
    shape[7][2].Set_Point(0,-3);    shape[7][3].Set_Point(0,-4);
    shape[7][4].Set_Point(-10,-10);    
 
}

void Peice::S_Rook()
{
//    type = 'r';
    dim.Set_Point(4,5);
    score = 5;
    shape = new Point*[dim.x];
    for(int i=0; i<dim.x;++i) shape[i] = new Point[dim.y];


    //NORTH    
    shape[0][0].Set_Point(-1,0);    shape[0][1].Set_Point(-2,0);
    shape[0][2].Set_Point(-3,0);    shape[0][3].Set_Point(-4,0);
    shape[0][4].Set_Point(-5,0);    
    
    //SOUTH
    shape[1][0].Set_Point(1,0);    shape[1][1].Set_Point(2,0);
    shape[1][2].Set_Point(3,0);    shape[1][3].Set_Point(4,0);
    shape[1][4].Set_Point(5,0);    
 
     //EAST
    shape[2][0].Set_Point(0,1);    shape[2][1].Set_Point(0,2);
    shape[2][2].Set_Point(0,3);    shape[2][3].Set_Point(0,4);
    shape[2][4].Set_Point(-10,-10);    
    //WEST
    shape[3][0].Set_Point(0,-1);    shape[3][1].Set_Point(0,-2);
    shape[3][2].Set_Point(0,-3);    shape[3][3].Set_Point(0,-4);
    shape[3][4].Set_Point(-10,-10);
}

void Peice::S_Knight()
{
 //   type = 'n';
    dim.Set_Point(2,4);
    score = 3;
     shape = new Point*[dim.x];
    for(int i=0; i<dim.x;++i) shape[i] = new Point[dim.y];

   // **special** ALL ATTACKS AND MOVES
    shape[0][0].Set_Point(-2,1);    shape[0][1].Set_Point(-2,-1);
    shape[0][2].Set_Point(-1,-2);    shape[0][3].Set_Point(-1,2);
    
    shape[1][0].Set_Point(1,-2);    shape[1][1].Set_Point(1,2);
    shape[1][2].Set_Point(2,-1);    shape[1][3].Set_Point(2,1);
}

void Peice::S_Bishop()
{
//    type = 'b';
    dim.Set_Point(5,4);
    score = 3;
      shape = new Point*[dim.x];
    for(int i=0; i<dim.x;++i) shape[i] = new Point[dim.y];

  //NSEW MOVES **special**
    shape[0][0].Set_Point(-1,0);     shape[0][1].Set_Point(1,0);
    shape[0][2].Set_Point(0,-1);    shape[0][3].Set_Point(0,1);
 
    //NORTHWEST
    shape[1][0].Set_Point(-1,-1);    shape[1][1].Set_Point(-2,-2);
    shape[1][2].Set_Point(-3,-3);    shape[1][3].Set_Point(-4,-4);
   
    //SOUTHWEST
    shape[2][0].Set_Point(1,-1);    shape[2][1].Set_Point(2,-2);
    shape[2][2].Set_Point(3,-3);    shape[2][3].Set_Point(4,-4);
    
    //NORTHEAST
    shape[3][0].Set_Point(-1,1);    shape[3][1].Set_Point(-2,2);
    shape[3][2].Set_Point(-3,3);    shape[3][3].Set_Point(-4,4);

    //SOUTHEAST
    shape[4][0].Set_Point(1,1);    shape[4][1].Set_Point(2,2);
    shape[4][2].Set_Point(3,3);    shape[4][3].Set_Point(4,4);
}




