#include "Turn.h"
#include <assert.h>
#include <netdb.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <algorithm>
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
        void Go();
        void imcsplay(int argc, char **argv);
        int NegaMax(char**&,int); 
    protected:
        NetProto plug;
};


