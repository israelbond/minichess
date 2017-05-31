/*Israel Bond
 * MiniChess player
 * CS442
 
 File conatins move of the library files to be included as well as class 
 declarations for server class: NetProto and Novice class which is derived from
 the Player class*/
#include "Turn.h"
#include <assert.h>
#include <netdb.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <algorithm>
#include <cctype>
#include <time.h>
#include <unistd.h>
const int DEPTH = 8;
const int DRAW_D = 40;
const int T_MIN = 5;
const int T_MAX = 10;
const int QUICK_TURN = 20;

class NetProto
{
    public: 
        void startlog(void);
        FILE* netopen(char *host, int port);
        char* expectcmd(FILE *s, int fail, ...);
        void sendcmd(FILE *s, char *fmt, ...);
        char* getnet(FILE *f, char *state);
        void logmsg(char *fmt, ...);
        void logchar(char ch);
    protected:
        FILE* logfile;
        char buf[1024];


};

class Novice: public Player
{
    public:

        char* Priority();
        char* Go();
        char* ID_Wrapper();
        int Iterative_Deepening(int&);
        void Create_M(char move[]);
        void Opp_Move(char[]);
        void imcsplay(int argc, char **argv);
        int AB_NegaMax(int,int,int,int);//ABP int refereences WERE BAD!!
        int NegaMax(int,int);
        void Nega_VS_ABP();
//        void Display_Board(char**&);
    protected:
        clock_t begin, end;
        int move_index;
        NetProto plug;
        int ID_AB_NegaMax(int, int, int&, bool,int,int);
};


