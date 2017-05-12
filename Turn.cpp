
#include "Turn.h"

Turn::Turn(): list_Index(0), list_max(0)
{
    Starting_State();
    Set_Piece_List();
    //    Set_Turn();
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
    Set_Player();

    for(int i=0; i < ROW; ++i)
    {
        fscanf(stdin,"%s", board[i]);
    }
}

//sets variable to varify which side is playing
void Turn::Set_Player()
{
    if(playing == 'W')
        player = 1;
    else
        player = -1;
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
        {'R','N','B','Q','K','\0'}};
    for(;i<ROW;++i)
    {
        for(;j<COL;++j)
        {
            board[i][j] = temp[i][j];
        }
        j=0;
    }
}

void Turn::Set_Piece_List()
{
    pieces[0].S_W_Pawn();
    pieces[1].S_B_Pawn();
    pieces[2].S_Knight();
    pieces[3].S_Bishop();
    pieces[4].S_King();
    pieces[5].S_Queen();
    pieces[6].S_Rook();
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

char** Turn::Moved(Move to_move)
{
    //if target piece exits
    if(to_move.from.x < ROW && to_move.from.x >=0 &&
            to_move.from.y < COL-1 && to_move.from.y>=0)
    {
        //and belongs to the side on move,//XXX could cause issuses when
        //                                      eveluating '.'
        if(player && isupper(board[to_move.from.x][to_move.from.y])
                || !player && !isupper(board[to_move.from.x][to_move.from.y]))
        {
            //return copy of the board containing the move to be returned
            char ** temp = Copy_Board();
            //move piece
            //return new board 
        }            

    }
    //otherwise throw exception
    else
        return NULL;


}




char** Turn::Copy_Board()
{
    int i=0;
    char** temp = NULL;
    temp = new char * [ROW];
    for(;i<ROW; ++i)
        temp[i] = new char [COL];
    i=0;
    for(;i<ROW; ++i)
        strcpy(temp[i],board[i]);
    return temp;
}

void Turn::Romove_Board(char**& board)
{
    if(board)
    {
        for(int i=0;i < ROW; ++i)
            delete [] board[i];
        delete [] board;
        board = NULL;
    }
}

Move* Player::Generate_Moves()
{
    if(player)//WHITE
    {
        for(int i=ROW-1; i >=0; --i)
        {    
            for(int j=COL-2; j>=0; --j)
            { 
                if(isupper(board[i][j]))//is a white piece
                    White_Moves(i,j,board[i][j]);
            }
        } 
        
    }
    else//BLACK
    {
        for(int i=0; i < ROW; ++i)
        {    
            for(int j = 0; j<COL-1; ++j)
            { 
                if(islower(board[i][j]))// is a black piece
                    Black_Moves(i,j,board[i][j]);

            }
        } 
 
    }
    list_max = list_Index; // sets move list max limit.
    list_Index = 0;//reset move list counter
}
void Player::White_Moves(int& x, int& y, char& piece)
{   
    switch(piece)
    {
        case '.': break;
        case 'P': Move_W_Pawn(x,y,pieces[0]);
            break;
        case 'N': Move_Knight(x,y,pieces[2]);
            break;
        case 'B': Move_Bishop(x,y,pieces[3]);
            break;
        case 'Q': Move_Queen(x,y,pieces[5]);
            break;
        case 'K': Move_King(x,y,pieces[4]);
            break;
        case 'R': Move_Rook(x,y,pieces[6]);
            break;
        default:
            cout<<"\nUNRECONGNIZED WHITE CHARACTER"<<endl;
    }
}

void Player::Black_Moves(int& x, int& y, char& piece)
{   
    switch(piece)
    {
        case '.': break;
        case 'p': Move_B_Pawn(x,y,pieces[1]);
            break;
        case 'n': Move_Knight(x,y,pieces[2]);
            break;
        case 'b': Move_Bishop(x,y,pieces[3]);
            break;
        case 'q': Move_Queen(x,y,pieces[5]);
            break;
        case 'k': Move_King(x,y,pieces[4]);
            break;
        case 'r': Move_Rook(x,y,pieces[6]);
            break;
        default:
            cout<<"\nUNRECONGNIZED BLACK CHARACTER"<<endl;
    }
}
void Player::Move_W_Pawn(int& xpos, int& ypos,Peice & to_check)
{
    //grab values for dimentions of piece "positions"
    int row = to_check.dim.x , col = to_check.dim.y;
    //loop through all states
   for(int i=0; i<row; ++i)
   {
       for(int j=0; j<col; ++j)
       {
           //validate if posistion is on board
           if();

       }
   }
}

void Player::Move_B_Pawn(int& xpos, int& ypos,Peice & to_check)
{}
void Player::Move_Knight(int& xpos, int& ypos,Peice & to_check)
{}
void Player::Move_Bishop(int& xpos, int& ypos,Peice & to_check)
{}
void Player::Move_Queen(int& xpos, int& ypos,Peice & to_check)
{}
void Player::Move_King(int& xpos, int& ypos,Peice & to_check)
{}
void Player::Move_Rook(int& xpos, int& ypos,Peice & to_check)
{}


Move::Move(): to{0,0}, from{0,0}, value{0}/*, next{NULL}*/ {}

void Move::S_Move(Point& go_to, Point& come_from, int& value)
{

}

