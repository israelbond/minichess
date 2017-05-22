/*Israel Bond
 * MiniChess player
 * CS442
 
    This is main() takes command line arguments to be passed to the imcs server
    for evaluation and to initialize class object components*/
#include "Player.h"

int main(int argc, char** argv)
{
    srand(time(NULL));
    Novice game;
//    game.Go();
    
   game.imcsplay(argc,argv);
    return 0;
}


