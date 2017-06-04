/*Israel Bond
 * MiniChess player
 * CS442
 
    This is main() takes command line arguments to be passed to the imcs server
    for evaluation and to initialize class object components*/
#include "Player.h"

void timing(void);

int main(int argc, char** argv)
{
    Novice game;
   game.imcsplay(argc,argv);
    return 0;
/*------------   USED FOR TESTING PURPOSES   ----------------------*/
//    game.Go();
//    game.Priority();
//    game.Nega_VS_ABP(); 
//    game.ID_VS_AB_Nega();
//    timing();

}

//testing out implemented timeing running function
void timing()
{

    srand(time(NULL));
    clock_t t1,t2;
    t1=clock();
    t2=t1;
    while((t2/CLOCKS_PER_SEC - t1/CLOCKS_PER_SEC)<1)
        t2=clock();
    printf("Took %ld ticks to wait one second.\n",t2-t1);
    printf("this value should be the same as CLOCKS_PER_SEC which is %ld.\n",CLOCKS_PER_SEC);
 
}

