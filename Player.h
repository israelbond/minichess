#include "Turn.h"
#include <assert.h>
#include <netdb.h>
//#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <algorithm>
#include <cctype>
#include <time.h>
#include <unistd.h>
const int DEPTH = 6;
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

        void Create_M(char move[]);
        void Opp_Move(char[]);
        void imcsplay(int argc, char **argv);
        int AB_NegaMax(int,int,int,int);//ABP refereences could be BAD
        int NegaMax(int,int);
//        void Display_Board(char**&);
    protected:
        int move_index;
        NetProto plug;
};


