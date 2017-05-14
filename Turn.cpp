
#include "Turn.h"

Turn::Turn(): list_index(0), list_max(0), check{NULL}
{
    Starting_State();
    Set_Piece_List();
    //       Set_Turn();
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
    //    Set_Player();
}

//sets variable to varify which side is playing
void Turn::Set_Player()
{
    if(playing == 'W')
        player = 1;
    else
        player = 0;
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

//Function uses standard out to produce an output of class variables
void Turn::Display_Turn()
{

    fprintf(stdout,"%d ", turn_count);
    fprintf(stdout,"%c\n", playing);
    for(int i = 0; i<ROW; ++i)
        fprintf(stdout,"%s\n",board[i]);
}
  //FUNCTION: FOO NEGAMAX...
    char** Turn::Moved(Move to_move)
    {
        char** temp = NULL;
//belongs to the side on move,//XXX could cause issuses when
//                                      eveluating '.'
if(((isupper(board[to_move.from.x][to_move.from.y])|| board[to_move.from.x][to_move.from.y]=='.') && player)
||(!player && !isupper(board[to_move.from.x][to_move.from.y])))
{
//return copy of the board containing the move to be returned
temp = Copy_Board();
//move piece
Make_Move(temp,to_move);
//return new board 
return temp;
}            
//otherwise throw exception
return NULL;


}


//function returns values of peice on board
int Turn::Peice_Value(char& peice)
{
    char temp = peice;
    switch(temp)
    {
        case '.': return 0;
        case 'P': return 1; 
        case 'p': return 1;
        case 'N': return 3;
        case 'n': return 3;
        case 'B': return 3;
        case 'b': return 3;
        case 'Q': return 9;
        case 'q': return 9;
        case 'K': return 100;
        case 'k': return 100;
        case 'R': return 5;
        case 'r': return 5;
        default:
                  cout<<"\nUNRECONGNIZED CHARACTER"<<endl;
                  return 0;
    }
    cout<<"\nERROR PEICE VALUE"<<endl;
    return 0;
}    
//function returns true on attacks and false on teammate peice value
//XOR
bool Turn::Opponent(char& me, char& them)
{
    if(them != '.')
    {
        if((isupper(me)) != (isupper(them))) return true;
        /*    else if(isupper(me) == isupper(them))
              {
              cout<<"SAME TEAM!!"; 
              return false;
              }
              */
    }
    return false;
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
void Player::Run()
{
    int list_index=0, list_max=0;
    list = Generate_Moves();
    

}
Move * Player::Generate_Moves()
{
    Move * temp = new Move[MOVES];
    Move * ret_list = NULL;
    if(player)//WHITE
    {
        for(int i=ROW-1; i >=0; --i)
        {    
            for(int j=COL-2; j>=0; --j)
            { 
                if(isupper(board[i][j]))//is a white piece
                    White_Moves(temp,list_index,i,j,board[i][j]);
            }
        }
        //sort list
//        int used[list_max];//Move index varification
        list_max = list_index;
        list_index = 0;
        ret_list = new Move[list_max];
        Sort_Moves(temp,ret_list,list_index,list_max);
    }
    else//BLACK
    {
        for(int i=0; i < ROW; ++i)
        {    
            for(int j = 0; j<COL-1; ++j)
            { 
                if(!isupper(board[i][j]) && board[i][j] != '.')// is a black piece
                    Black_Moves(move_list,i,j,board[i][j]);
                    
            }
        }  
    }
}

Move* Player::Sort_Moves(Move old_list[], Move new_list[],int& list_index,int& list_max)
{
    Copy_Moves(old_list, list_index, list_max, new_list);
    //splitmerge

    
}

//copy moves: invokes Set_Move
void Player::Copy_Moves(Move old_list[],Move new_list[],int& list_index, int& list_max)
{
    for(int i = list_index; i<list_max; ++i)
    {
        Move Set_Move(old_list[i],new_list[i]);
    }
}
//function to invoke proper peice to generate moves from
void Player::White_Moves(int& x, int& y, char& peice)
{  
    char temp = peice;
    switch(temp)
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

void Player::Black_Moves(int& x, int& y, char& peice)
{  
    char temp = peice;
    switch(temp)
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
    int row = to_check.dim.x , col = to_check.dim.y, 
        therex=0, therey=0, peicev=0;
    //values for setting moves
    Point from_here;
    from_here.Set_Point(xpos,ypos);
    Point to_there;
    //loop through all states
    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            //validate if posistion is on board
            therex = xpos + to_check.shape[i][j].x;
            therey = ypos + to_check.shape[i][j].y;
            if( therex >=0 && therex < ROW && 
                    therey >=0 && therey < COL -1)
            {
                //move for Pawn 
                if(j == 0 && board[therex][therey] == '.') //Opponent(board[xpos][ypos], board[therex][therey]))
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                }//possible Pawn attack
                else if(Opponent(board[xpos][ypos], board[therex][therey])) //board[therex][therey] == '.')
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                }
            }
        }
    }
}

void Player::Move_B_Pawn(int& xpos, int& ypos,Peice & to_check)
{
    //grab values for dimentions of piece "positions"
    int row = to_check.dim.x , col = to_check.dim.y, 
        therex=0, therey=0, peicev=0;
    //values for setting moves
    Point from_here;
    from_here.Set_Point(xpos,ypos);
    Point to_there;
    //loop through all states
    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            //validate if posistion is on board
            therex = xpos + to_check.shape[i][j].x;
            therey = ypos + to_check.shape[i][j].y;
            if( therex >=0 && therex < ROW && 
                    therey >=0 && therey < COL -1)
            {
                //Move for Pawn 
                if(j == 0 && board[therex][therey] == '.') //Opponent(board[xpos][ypos], board[therex][therey]))
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                }//possible Pawn attack
                else if(Opponent(board[xpos][ypos], board[therex][therey])) //board[therex][therey] == '.')
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                }
            }
        }
    }
}

void Player::Move_Knight(int& xpos, int& ypos,Peice & to_check)
{
    //grab values for dimentions of piece "positions"
    int row = to_check.dim.x , col = to_check.dim.y, 
        therex=0, therey=0, peicev=0;
    //values for setting moves
    Point from_here;
    from_here.Set_Point(xpos,ypos);
    Point to_there;
    //loop through all states
    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            //validate if posistion is on board
            therex = xpos + to_check.shape[i][j].x;
            therey = ypos + to_check.shape[i][j].y;
            if( therex >=0 && therex < ROW && 
                    therey >=0 && therey < COL -1)
            {
                //attack or move for Knight 
                if( board[therex][therey] == '.' || Opponent(board[xpos][ypos], board[therex][therey]))
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                }
            }
        }
    }
}

void Player::Move_Bishop(int& xpos, int& ypos,Peice & to_check)
{
    //grab values for dimentions of piece "positions"
    int row = to_check.dim.x , col = to_check.dim.y, 
        therex=0, therey=0, peicev=0;
    //values for setting moves
    Point from_here;
    from_here.Set_Point(xpos,ypos);
    Point to_there;
    //loop through all states
    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            //validate if posistion is on board
            therex = xpos + to_check.shape[i][j].x;
            therey = ypos + to_check.shape[i][j].y;
            if( therex >=0 && therex < ROW && 
                    therey >=0 && therey < COL -1)
            {
                //**special** Bishop moves
                if(i == 0 && board[therex][therey] == '.')
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;

                }//move for Bishop 
                else if( board[therex][therey] == '.' )//|| Opponent(to_check.type, board[therex][therey]))
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                }//attack for Bishop
                else if(Opponent(board[xpos][ypos], board[therex][therey]))
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                    break;//peice in way for the rest of the path
                }//teammate peice: stop searching path
                else break;



            }
        }
    }   
}
void Player::Move_Queen(int& xpos, int& ypos,Peice & to_check)
{
    //grab values for dimentions of piece "positions"
    int row = to_check.dim.x , col = to_check.dim.y, 
        therex=0, therey=0, peicev=0;
    //values for setting moves
    Point from_here;
    from_here.Set_Point(xpos,ypos);
    Point to_there;
    //loop through all states
    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            //validate if posistion is on board
            therex = xpos + to_check.shape[i][j].x;
            therey = ypos + to_check.shape[i][j].y;
            if( therex >=0 && therex < ROW && 
                    therey >=0 && therey < COL -1)
            {
                //valid move
                if(board[therex][therey] == '.')
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                }//attack on Opponent
                else if(Opponent(board[xpos][ypos], board[therex][therey]))
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                    break;
                }//teammate peice: dont check any further down this path
                else break;
            }//path runs off board
            else break;
        }
    }   
}
void Player::Move_King(int& xpos, int& ypos,Peice & to_check)
{
    //grab values for dimentions of piece "positions"
    int row = to_check.dim.x , col = to_check.dim.y, 
        therex=0, therey=0, peicev=0;
    //values for setting moves
    Point from_here;
    from_here.Set_Point(xpos,ypos);
    Point to_there;
    //loop through all states
    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            //validate if posistion is on board
            therex = xpos + to_check.shape[i][j].x;
            therey = ypos + to_check.shape[i][j].y;
            if( therex >=0 && therex < ROW && 
                    therey >=0 && therey < COL -1)
            {
                //valid move
                if((board[therex][therey]) == '.')
                {
                    to_there.Set_Point(therex,therey);
                    peicev = 0; //--Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                }//attack on Opponent
                else if(Opponent(board[xpos][ypos], board[therex][therey])== true)
                {
                    to_there.Set_Point(therex,therey);
                    peicev = 1000;//DANGER!! MUST TAKE PEICE!!!  --Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                    //                    break;
                }//teammate peice: dont check any further down this path
                //                   else break;
            }
        }
    }
}

void Player::Move_Rook(int& xpos, int& ypos,Peice & to_check)
{ 
    //grab values for dimentions of piece "positions"
    int row = to_check.dim.x , col = to_check.dim.y, 
        therex=0, therey=0, peicev=0;
    //values for setting moves
    Point from_here;
    from_here.Set_Point(xpos,ypos);
    Point to_there;
    //loop through all states
    for(int i=0; i<row; ++i)
    {
        for(int j=0; j<col; ++j)
        {
            //validate if posistion is on board
            therex = xpos + to_check.shape[i][j].x;
            therey = ypos + to_check.shape[i][j].y;
            if( therex >=0 && therex < ROW && 
                    therey >=0 && therey < COL -1)
            {
                //valid move
                if(board[therex][therey] == '.')
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                }//attack on Opponent
                else if(Opponent(board[xpos][ypos], board[therex][therey]))
                {
                    to_there.Set_Point(therex,therey);
                    peicev = Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                    break;
                }//teammate peice: dont check any further down this path
                else break;
            }//path runs off board
            else break;
        }
    }
}

void Player::Display_Moves(void)
{
    for(int i=0; i < list_max; ++i)
    {
        cout<<"MOVE "<<i+1<<'\t';
        list[i].Display_M();
    }
}

Move::Move(): value{0}, type{'x'} /*, next{NULL}*/ {}

void Move::Display_M()
{
    cout<<"\tPoints: "<<value<<"\tType: "<<type;
    cout<<"\tfrom-to: ";
    from.Display_P();
    cout<<"-";
    to.Display_P();
    cout<<endl;
}

void Move::Set_Move(Move & to_add, Move& to_get)
{
    to_add.value = to_get.value;
    to_add.type = to_get.type;
    to_add.from.Set_Point(to_get.from.x,to_get.from.y);
    to_add.to.Set_Point(to_get.to.x,to_get.to.y);
}
void Move::S_Move(Point& go_to, Point& come_from, int& points, char & peice)
{
    type = peice;
    value = points;
    to.Set_Point(go_to.x, go_to.y);
    from.Set_Point(come_from.x, come_from.y);
}

