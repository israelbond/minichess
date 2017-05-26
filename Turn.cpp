/*Israel Bond
 * MiniChess player
 * CS442

 This file contains all method implementations for the Turn class (BASE), 
 the Player (derived from Turn) and Move class(has a) */
#include "Turn.h"

Move::Move(): value{0}, type{'x'},word{'\0'} /*, next{NULL}*/ {}


//function to build a string to be passed to the other player for 
//move on board evaluations
char* Move::Make_string()
{
    char c1 = (char)(this->from.y + 'a');
    int d1 = (6 - this->from.x);
    char c2 = (char)(this->to.y + 'a');
    int d2 = (6 - this->to.x);
    sprintf(word, "%c%d-%c%d" ,c1 ,d1 ,c2 ,d2);
//    fprintf(stdout, "%s", word);
    return word;
}

//function to set a move objects variables with to and from Points(positions)
void Move::S_Move(Point& go_to, Point& come_from, int& points, char & peice)
{
    type = peice;
    value = points;
    to.Set_Point(go_to.x, go_to.y);
    from.Set_Point(come_from.x, come_from.y);
}

void Move::Display_M()
{
    char c1 = (char)(this->from.y + 'a');
    int d1 = (6 - this->from.x);
    char c2 = (char)(this->to.y + 'a');
    int d2 = (6 - this->to.x);
    fprintf(stdout,"%c%d-%c%d",c1,d1,c2,d2);
}

//Base class constructor
Turn::Turn(): board{NULL}, list{NULL}
{
//       Starting_State();
    Set_Piece_List();
    Set_Turn();
}

//Base class destructor
Turn::~Turn()
{
    if(board != NULL)
    {
        for(int i =0; i<ROW; ++i)
        {
            delete [] board[i];
        }
        delete [] board;
        board = NULL;
    }

    if(list != NULL)
        delete [] list;
}

//function uses standard in to fill class variables
//"playing" is a char representing the side playing 
//"turn_count" is an integer representing turn number
void Turn::Set_Turn()
{
    int dumb =0;
    dumb =fscanf(stdin, "%d", &turn_count);
    dumb =fscanf(stdin, "%s", &playing);
    Set_Player();
    board = new char*[ROW];
    for(int j=0;j<ROW;++j) 
        board[j] = new char[COL];
    for(int i=0; i < ROW; ++i)
        dumb=fscanf(stdin,"%s", board[i]);
    if(dumb) ;
    //    Display_Vars();

}
//Sets a MOVE object to the move objects values: BOTH passed by reference
void Turn::Set_Move(Move & to_add, Move& to_get)
{
    to_add.value = to_get.value;
    to_add.type = to_get.type;
    to_add.from.Set_Point(to_get.from.x,to_get.from.y);
    to_add.to.Set_Point(to_get.to.x,to_get.to.y);
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
void Turn::Starting_State()
{
    int i=0;
    turn_count = 1;

    player = -1; playing = 'B';
    char temp[ROW][COL] = {{'k','q','b','n','r','\0'},
        {'p','p','p','p','p','\0'},
        {'.','.','.','.','.','\0'},
        {'.','.','.','.','.','\0'},
        {'P','P','P','P','P','\0'},
        {'R','N','B','Q','K','\0'}};
    board = new char*[ROW];
    for(int j=0;j<ROW;++j) 
        board[j] = new char[COL];
    for(;i<ROW;++i)
    {
        for(int k=0; k<COL; ++k)
            board[i][k] = temp[i][k];
    }
}

//Method called once to initialize the Peice set
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
//Function used for display when playing across the server
void Turn::Server_Dis(Move m)
{
    char c = '\0';
    if(playing == 'W')
        c = 'B';
    else
        c = 'W';
    fprintf(stdout,"\n\n\n%d %c",turn_count,c);
    Display_Board();
}

//Function uses standard out to produce an output of class variables
void Turn::Display_Turn()
{

    fprintf(stdout,"%d ", turn_count);
    fprintf(stdout,"%c\n", playing);
    for(int i = 0; i<ROW; ++i)
        fprintf(stdout,"%s\n",board[i]);
}
//Helper function for debugging by displaying player components and the board
//being played on.
void Turn::Display_Vars()
{
    cout<<"Player  "<<playing<<endl;
    cout<<"P_val   "<<player<<endl;
    cout<<"P_turns "<<turn_count<<endl;
    Display_Board();
}

//function which unmakes a move from the board. varifies if there was a 
//promotion when peice was moved and depending handles each case accordingly
void Turn::Unmove(bool& queen, Move& to_move)
{   //check to see if there was a promotion last move
    if(queen)
    {   //check to see if the pawn promoted was black OR white
        if( board[to_move.to.x][to_move.to.y] =='q')
        {   //set position moved from back to pawn
            board[to_move.from.x][to_move.from.y] = 'p';
            //set the position moved to back to original
            board[to_move.to.x][to_move.to.y] = to_move.type;
            queen = false;
            return;
        }
        else if( board[to_move.to.x][to_move.to.y] =='Q')
        {   //set position moved from back to pawn
            board[to_move.from.x][to_move.from.y] = 'P';
            //set the position moved to back to original
            board[to_move.to.x][to_move.to.y] = to_move.type;
            queen = false;
            return;
        }
    }
    else
    {//their was NO promotion, unmake move 
        board[to_move.from.x][to_move.from.y] = board[to_move.to.x][to_move.to.y];
        board[to_move.to.x][to_move.to.y] = to_move.type;
    }
}

//Method to Make a Move on the board. No need to re evaluate if the position is 
//on the board since this move wouldn't have been in the list if it wasn't
void Turn::Make_Move( Move to_move)
{
    board[to_move.to.x][to_move.to.y] = board[to_move.from.x][to_move.from.y];
    board[to_move.from.x][to_move.from.y] = '.';
}


//function returns values of the peice on the board
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
                  exit(1);
    }
    //    cout<<"\nERROR PEICE VALUE"<<endl;
    return 0;
}    

//function returns true on attacks and false on teammate peice value
//XOR
bool Turn::Opponent(char me, char them)
{
    if(them != '.'|| me != '.')//if either one isn't a peice this is not an attack!
    {
        if((isupper(me)) != (isupper(them))) return true;
    }
    return false;
}

/*      COMMENTED OUT!!!
 *      as this was used when I was passing and copying board states for evaluations
 *
   char** Turn::Copy_Board(char**& the_board)
   {
   int i=0, j=0;
   char** temp = new char *[ROW];
   for(;i<ROW; ++i)
   temp[i] = new char [COL];
   i=0;
   for(;i<ROW; ++i)
   {   
   for(;j<COL-1; ++j)
   temp[i][j] = the_board[i][j];
   j=0;
   }
   return temp;
   }

   void Turn::Remove_Board(char**& board)
   {
   if(board)
   {
   for(int i=0;i < ROW; ++i)
   delete [] board[i];
   delete [] board;
   board = NULL;
   }
   }
   */

//method which switchs between players depending on the value already stored
void Turn::Change_Player()
{
    if(player == 1)
    {
        playing = 'B';
        player = -1;
    }
    else if( player == -1)
    {
        playing = 'W';
        player = 1;
    }
}

//removes a list of moves and resets the pointer to NULL for future evaluations
void Turn::Remove_List(Move*& the_list)
{
    if(the_list) delete [] the_list;
    the_list = NULL;
}

//Function defines END GAME state: where the player on move has NO KING
//RETURNS False if king is found and True If player has no king on board.
bool Turn::Game_Over(int this_player)
{
    if(this_player == 1)
    {
        for(int i=0; i<ROW;++i)
        {
            for(int j=0; j< COL-1; ++j)
            {
                if(board[i][j] == 'K')
                {
                    return false;
                }
            }
        }
    }
    else if(this_player == -1)
    {
        for(int i=0; i<ROW;++i)
        {
            for(int j=0; j< COL-1; ++j)
            {
                if(board[i][j] =='k')
                {
                    return false;
                }
            }
        }   
    }
    return true;
}

//this function gets the sum for each players pieces that remain on the 
//board and returns them in an order to inform the playing player of THEIR
//score!
int Turn::Board_Eval( int the_player)
{
    int w=0,b=0;
    for(int i=0; i<ROW;++i)
    {
        for(int j=0; j< COL-1; ++j)
        {
            //            cout<< i << j <<endl;
            if(board[i][j] == '.') continue;
            else
            {
                if(isupper(board[i][j])) w += Peice_Value(board[i][j]);
                else                         b += Peice_Value(board[i][j]);
            }
        }
    }
    if(the_player == 1)//whites on turn
        return (w - b);//negative Black winning, positive White winning 
    else
        return (b - w);//positive Black winning, negative White winning
}


//method used to display the board *MOSTLY for testing purposes
void Turn::Display_Board()
{
    cout<<'\n';
    for(int i=0; i<ROW; ++i)
        cout<<board[i]<<endl;
    cout<<'\n';
}

//player class constructor... NOTHING
Player::Player() {}

//method used for debugging specific situations with my program
void Player::Run()
{
    //    int list_index=0, list_max=0;
    //    list = Generate_Moves(list_index,list_max);
    //    char** temp = Copy_Board();
    //    cout<<Board_Eval(temp);
    //    Display_Moves(list,list_max);   PRIORITY LIST!!!
}

//this Function generates a move list, orders it in order of highest points
//earned to lowest points.
Move * Player::Generate_Moves(int this_player,int& list_index, int& list_max)
{
    Move * temp = new Move[MOVES];
    Move * ret_list = NULL;
    if(this_player == 1)//WHITE
    {
        for(int i=ROW-1; i >=0; --i)
        {    
            for(int j=COL-2; j>=0; --j)
            { 
                if(isupper(board[i][j]))//is a white piece
                    White_Moves(temp,list_index,i,j,board[i][j]);
            }
        }
    }
    else if(this_player == -1)//BLACK
    {
        for(int i=0; i < ROW; ++i)
        {    
            for(int j = 0; j<COL-1; ++j)
            { 
                if(board[i][j] != '.')
                {
                    if(!isupper(board[i][j]))// is a black piece
                        Black_Moves(temp,list_index,i,j,board[i][j]);
                }

            }
        }
    }
    //sort list
    if(list_index ==0) return NULL;
    list_max = list_index;
    list_index = 0;
    ret_list = new Move[list_max];
    Sort_Moves(temp,ret_list,list_index,list_max);
    delete [] ret_list;
    ret_list = new Move[list_max];
    Copy_Moves(temp,list_index,list_max,ret_list);
    delete [] temp;
    return ret_list;
}

/*                  MERGE SORT                  */

//wrapper method to sort array of moves contained within old_list[]
Move* Player::Sort_Moves(Move old_list[], Move new_list[],int& list_index,int& list_max)
{
    Copy_Moves(old_list, list_index, list_max, new_list);
    //splitmerge algorithm
    Split_Merge(new_list,list_index,list_max,old_list);
    return NULL;    
}

//function which is the work horse for Merge sort
void Player::Split_Merge(Move new_list[],int& index,int& max, Move old_list[])
{
    if(max - index <2 ) return;
    int mid = (max+index) / 2;
    Split_Merge(old_list,index,mid,new_list);
    Split_Merge(old_list,mid,max,new_list);
    Merge_Top_Down(new_list,index,mid,max,old_list);
}

//function which stors the moves in the new_list[] depending on the moves value
void Player::Merge_Top_Down(Move old_list[],int& index,int& mid,int& max,Move new_list[])
{
    int i = index, j = mid;
    for(int k=index; k<max;++k)
    {
        if(old_list[i].type != 'x' || old_list[j].type != 'x')
        {
            if(i<mid && (j>=max || old_list[i].value >= old_list[j].value))
            {
                Set_Move(new_list[k],old_list[i]);
                ++i;
            }
            else
            {
                Set_Move(new_list[k],old_list[j]);
                ++j;
            }
        }
    }
}


//function which copies one array of elements into another. 
//copy moves: invokes Set_Move
void Player::Copy_Moves(Move old_list[],int& list_index, int& list_max, Move new_list[])
{
    for(int i = list_index; i<list_max; ++i)
    {
        Set_Move(new_list[i],old_list[i]);
    }
}

//function to invoke proper peice to generate moves from based on player on move
//and peice being evaluated
void Player::White_Moves(Move*& list,int& list_index,int& x, int& y, char& peice)
{  
    char temp = peice;
    switch(temp)
    {
        case '.': break;
        case 'P': Move_W_Pawn(list,list_index,x,y,pieces[0]);
                  break;
        case 'N': Move_Knight(list,list_index,x,y,pieces[2]);
                  break;
        case 'B': Move_Bishop(list,list_index,x,y,pieces[3]);
                  break;
        case 'Q': Move_Queen(list,list_index,x,y,pieces[5]);
                  break;
        case 'K': Move_King(list,list_index,x,y,pieces[4]);
                  break;
        case 'R': Move_Rook(list,list_index,x,y,pieces[6]);
                  break;
        default:
                  cout<<"\nUNRECONGNIZED WHITE CHARACTER"<<endl;
                  exit(1);
    }
}

//function to invoke proper peice to generate moves from based on player on move
//and peice being evaluated
void Player::Black_Moves(Move*& list,int& list_index,int& x, int& y, char& peice)
{  
    char temp = peice;
    switch(temp)
    {
        case '.': break;
        case 'p': Move_B_Pawn(list,list_index,x,y,pieces[1]);
                  break;
        case 'n': Move_Knight(list,list_index,x,y,pieces[2]);
                  break;
        case 'b': Move_Bishop(list,list_index,x,y,pieces[3]);
                  break;
        case 'q': Move_Queen(list,list_index,x,y,pieces[5]);
                  break;
        case 'k': Move_King(list,list_index,x,y,pieces[4]);
                  break;
        case 'r': Move_Rook(list,list_index,x,y,pieces[6]);
                  break;
        default:
                  cout<<"\nUNRECONGNIZED BLACK CHARACTER"<<endl;
                  exit(1);
    }
}
/*********                  MOVE METHODS                        *********/
        //next 7 functions check to see that a move or an attack can be added 
        //to the move list
void Player::Move_W_Pawn(Move*& list,int& list_index,int& xpos, int& ypos,Peice & to_check)
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
                if(j == 0) //Opponent(board[xpos][ypos], board[therex][therey]))
                {
                    if(board[therex][therey] == '.')
                    {
                        to_there.Set_Point(therex,therey);
                        peicev = Peice_Value(board[therex][therey]);
                        list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                        ++list_index;
                    }
                }//possible Pawn attack
                else if(Opponent(board[xpos][ypos], board[therex][therey])&& board[therex][therey] != '.')
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

void Player::Move_B_Pawn(Move*& list,int& list_index,int& xpos, int& ypos,Peice & to_check)
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
                if( j == 0 ) 
                {
                    if(board[therex][therey] == '.')
                    {
                        to_there.Set_Point(therex,therey);
                        peicev = Peice_Value(board[therex][therey]);
                        list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                        ++list_index;
                    }
                } //possible Pawn attack
                else if(Opponent(board[xpos][ypos], board[therex][therey])) 
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

void Player::Move_Knight(Move*& list,int& list_index,int& xpos, int& ypos,Peice & to_check)
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

void Player::Move_Bishop(Move*& list,int& list_index,int& xpos, int& ypos,Peice & to_check)
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
                if(i == 0)
                {
                    if(board[therex][therey] == '.')
                    {
            
                        to_there.Set_Point(therex,therey);
                        peicev = Peice_Value(board[therex][therey]);
                        list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                        ++list_index;
                    }

                }//move for Bishop 
                else if( board[therex][therey] == '.' )
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
void Player::Move_Queen(Move*& list,int& list_index,int& xpos, int& ypos,Peice & to_check)
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
void Player::Move_King(Move*& list,int& list_index,int& xpos, int& ypos,Peice & to_check)
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
                    peicev = Peice_Value(board[therex][therey]);//DANGER!! MUST TAKE PEICE!!!  --Peice_Value(board[therex][therey]);
                    list[list_index].S_Move(to_there,from_here, peicev, board[therex][therey]);
                    ++list_index;
                    //                    break;
                }//teammate peice: dont check any further down this path
                //                   else break;
            }
        }
    }
}

void Player::Move_Rook(Move*& list,int& list_index,int& xpos, int& ypos,Peice & to_check)
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

//checks and promotes any pawn in a promotion location...
bool Player::Promotions(bool& not_pawn)
{
    if(not_pawn) not_pawn = false;
    int i=0;
    //check black side from permotions
    for(;i<COL-1;++i)
    {   //lower case char that is also a black pawn
        if(!isupper(board[5][i]) && board[5][i] == 'p')
        {   //position gets permoted
            board[5][i] = 'q';
            return true;
        }
    }
    i=0;
    for(;i<COL-1;++i)
    {   //upper case char that is also a white  pawn
        if(isupper(board[0][i]) && board[0][i] == 'P')
        {   //position gets permoted
            board[0][i] = 'Q';
            return true;
        }
    }
    //check white side permotions
    return false;
}

//method for displaying move lists for evaluation** not currently used
void Player::Display_Moves(Move*& list, int& list_max)
{
    for(int i=0; i < list_max; ++i)
    {
        cout<<"MOVE "<<i+1<<'\t';
                list[i].Display_M();
        cout<<'\n';
    }
}


