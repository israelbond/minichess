/*Israel Bond
 * MiniChess player
 * CS442

 This file contains the class methods used to interact with the server and 
 derived class for player manipulations. the server code is that which was 
 provided to us by the professor and is mostly written in the C programming 
 language.*/
#include "Player.h"

/*FUNCTIONS PROVIDED ONLINE MY PROFESSORi & MODIFIED AS NEEDED
 * Commented out code is left in for convenience and to clarify what is going 
 * on*/

FILE * NetProto::netopen(char *host, int port) {
    struct hostent *hp = gethostbyname(host);
    if (!hp) {
        herror("gethostbyname");
        exit(1);
    }
    int s = socket(hp->h_addrtype, SOCK_STREAM, 0);
    if (s == -1) {
        perror("socket");
        exit(1);
    }
    char **a;
    for (a = hp->h_addr_list; *a; a++) {
        struct sockaddr_in sa;
        sa.sin_family = hp->h_addrtype;
        sa.sin_port = htons(port);
        memcpy(&sa.sin_addr, *a, hp->h_length);
        if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) != -1)
            break;
    }
    if (!*a) {
        perror("connect");
        exit(1);
    }
    FILE *f = fdopen(s, "a+");
    if (!f) {
        perror("fdopen");
        exit(1);
    }
    setlinebuf(f);
    return f;
}

//static char buf[1024];  //COMMENTED OUTSKY! already declaired in Player.h

//FILE *logfile;        //COMMENTED OUTSKY! already declaired in Player.h

void NetProto::startlog(void) {
    logfile = fopen("hyphen.log", "w");
    if (!logfile) {
        perror("logfile");
        exit(1);
    }
    setlinebuf(logfile);
}

char* NetProto::getnet(FILE *nf, char *state) {
    char *r = fgets(buf, sizeof(buf), nf);
    if (!r || strlen(r) >= sizeof(buf) - 1) {
        perror("fgets");
        fprintf(stderr, "fgets fails in state '%s'\n", state);
        exit(1);
    }
    printf("%s", r);
    if (logfile)
        fprintf(logfile, "%s", r);
    return r;
}

char* NetProto::expectcmd(FILE *s, int fail, ...) {
    char *r = fgets(buf, sizeof(buf), s);
    if (r == 0 || strlen(buf) >= sizeof(buf) - 1) {
        perror("fgets");
        exit(1);
    }
    printf("%s", buf);
    if (logfile)
        fprintf(logfile, "%s", buf);
    va_list args;
    va_start(args, fail);
    int code;
    while ((code = va_arg(args, int)) != 0) {
        assert(code > 0 && code <= 999);
        char cstr[4];
        sprintf(cstr, "%d", code);
        if (!strncmp(cstr, buf, 3)) {
            va_end(args);
            return buf;
        }
    }
    va_end(args);
    if (fail) {
        logmsg((char*)"expect: got unexpected code in '%s'", buf);
        exit(1);
    }
    return 0;
}

void NetProto::logmsg(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
    if (logfile) {
        va_start(args, fmt);
        vfprintf(logfile, fmt, args);
        va_end(args);
        fprintf(logfile, "\n");
    }
}

void NetProto::logchar(char ch) {
    putchar(ch);
    if (logfile)
        fputc(ch, logfile);
}

void NetProto::sendcmd(FILE *s, char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(s, fmt, args);
    fprintf(s, "\r\n");
    va_end(args);
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
    if (logfile) {
        va_start(args, fmt);
        vfprintf(logfile, fmt, args);
        va_end(args);
        fprintf(logfile, "\n");
    }
}

void Novice::imcsplay(int argc, char **argv) {
    setlinebuf(stdout);
    if (argc < 5 || argc > 7)
    {
        fprintf(stderr,"Arguments given out of bounds");
        exit(0);
    }
    char mecolor = '?';
    int megame = 0;
    switch(argv[1][0]) {
        case 'O':
            switch(argv[2][0]) {
                case 'W':
                case 'B':
                case '?':
                    mecolor = argv[2][0];
                    playing = mecolor;
                    Set_Player();
                    break;
                default:
                    fprintf(stderr,"Offered game failed");
                    exit(0);
            }
            break;
        case 'A': {
                      char ch = argv[2][0];
                      if (isdigit(ch)) {
                          megame = atoi(&argv[2][1]);
                      } else if (ch == 'W' || ch == 'B') {
                          mecolor = ch;
                          playing = mecolor;//MINE 
                          Set_Player();//sets variable for use in move gen.
                          megame = atoi(&argv[2][1]);
                      } else {
                          fprintf(stderr,"Accepted game failed");      
                          exit(0);
                      }
                      if (megame <= 0)
                      {
                          fprintf(stderr,"Incorrect input to Accept game");
                          exit(0);
                      }
                      break;
                  }
        default:
                  exit(0);
    }
    char *meuser = argv[3];
    char *mepassword = argv[4];
    char *host = (char*)"imcs.svcs.cs.pdx.edu";
    if (argc > 5)
        host = argv[5];
    int port = 3589;
    if (argc > 6) {
        port = atoi(argv[6]);
        if (port <= 0)
        {
            fprintf(stderr,"Incorrect port value");
            exit(0);
        }
    }
    FILE *nf = plug.netopen(host, port);
    setlinebuf(nf);
    plug.startlog();
    char *greeting = plug.expectcmd(nf, 1, 100, 0);
    (void) strtok(greeting, " ");
    char *pgm = strtok(0, " ");
    assert(!strcmp(pgm, "imcs"));
    char *version = strtok(0, " \r\n");
    if(strcmp(version, "2.5")) {
        fprintf(stderr, "got unexpected imcs version %s\n", version);
        exit(1);
    }
    plug.sendcmd(nf, (char*)"me %s %s", meuser,mepassword);
    (void) plug.expectcmd(nf, 1, 201, 0);
    if (megame != 0) {
        if (mecolor == '?')
            plug.sendcmd(nf, (char*)"accept %d", megame);
        else
            plug.sendcmd(nf, (char*)"accept %d %c", megame, mecolor);
        (void) plug.expectcmd(nf, 1, 105, 106, 0);
    } else {
        if (mecolor == '?')
            plug.sendcmd(nf, (char*)"offer");
        else
            plug.sendcmd(nf, (char*)"offer %c", mecolor);
        (void) plug.expectcmd(nf, 1, 103, 0);
        plug.logmsg((char*)"waiting for opponent");
        (void) plug.expectcmd(nf, 1, 105, 106, 0);
        plug.logmsg((char*)"opponent found");
    }
    /*    struct state s = s0;
          s.cureval = eval(&s);
          if (nttable > 0)
          s.curzhash = zhash(&s);
          */
    while (1) {
        int ch = fgetc(nf);
        int r = ungetc(ch, nf);
        assert(r != EOF);
        /*              if (isdigit(ch)) {
                        s = readstate(nf, 1);
                        s.cureval = eval(&s);
                        if (nttable > 0)
                        s.curzhash = zhash(&s);
                        continue;
                        }
                        */
        switch (ch) {
            case '?': {
                          char *r = plug.getnet(nf, (char*)"?");
                          char *q = strtok(r, " ");
                          assert(!strcmp(q, "?"));
                          char *tl = strtok(0, " ");
                          char *tr = strtok(0, " ");
                          assert(tl && tr);
                          char* mine = Go();//Priority();
                          //           Create_M(mine);
                          plug.sendcmd(nf,mine);
                          /*                          int t = readtimems(tl);
                                                      t = 95 * t / (100 * ((81 - s.ply) / 2));
                                                      struct move m = idnegamax(&s, t, 0);
                                                      logmsg("value %d at time %d depth %d for %s\n\n",
                                                      v0, t, d0, movestr(&m));
                                                      move(&s, &m, 0);
                                                      sendcmd(nf, "%s", movestr(&m));
                                                      printstate(&s, 1);
                                                      if (ponder)
                                                      (void) idnegamax(&s, 0, nf);
                                                      */                          continue;
                      }
            case '!':
                      assert(fgetc(nf) == '!');
                      int ch,z;
                      do
                          ch = fgetc(nf);
                      while (isspace(ch));
                      ungetc(ch, nf);
                      char move[5];
                      z=fscanf(nf,"%s",move); if(z) ;//did to get rid of warnings
                      Opp_Move(move);
                      propawn =Promotions(propawn);
                      //                      struct move m = getmove(nf, &s);
                      //                      move(&s, &m, 0);
                      continue;
            case '=':
                      (void) plug.getnet(nf, (char*)"=");
                      break;
            case 'X':
                      (void) plug.getnet(nf, (char*)"X");
                      break;
            default:
                      (void) plug.getnet(nf, (char*)"...");
                      continue;
        }
        break;
    }
    fclose(nf);
}

/*                    MY CLASS IMPLEMENTATIONS                        */

//Method converts string of characters into coortinates to be stored
//in a Move object
void Novice::Create_M(char move[])
{
    Move me;
    me.from.y = (move[0] - 'a');   
    me.from.x = (54 - (int)move[1]); 
    me.to.y = (move[3] - 'a');
    me.to.x = (54 - (int)move[4]);
    Server_Dis(me);
}

//function turns string to move for opponent & passes move off to be added 
//to the board
void Novice::Opp_Move(char move[])
{
    Move theirs;
    theirs.from.y = (move[0] - 'a');   
    theirs.from.x = (54 - (int)move[1]); 
    theirs.to.y = (move[3] - 'a');
    theirs.to.x = (54 - (int)move[4]);
    Make_Move(theirs);
}

//method makes my implementation play with a sorted move list which randomly
//selects a choice from possible moves
char* Novice::Priority()//modifyed to produce random play
{
    bool queen=false;
    int list_index=0, list_max=0, this_player = player;
    if(list) Remove_List(list); //get rid of old move list
    list = Generate_Moves(this_player,list_index,list_max); 
    //added random play functionality
    list_index = rand() % list_max;
    Make_Move(list[list_index]);//makes single move worth the most points
    queen = Promotions(queen);
    //    if(queen) cout<<"PROMOTED!"<<endl;
    char * str = list[list_index].Make_string();
    //    cout<<str<<endl;
    delete [] list;
    list=NULL;
    ++turn_count;
    return str;
}

void Novice::Nega_VS_ABP()
{
    char* abp =NULL, * nega =NULL;
    int abp_cost=0, nega_cost=0, a=-100,b=100,list_index=0, list_max=0, this_player = player;
    int depth=DEPTH;
    //ABP
    Display_Board();
    list = Generate_Moves(this_player,list_index,list_max);
    //    Display_Moves(list,list_max);
    //   cout<<list_index<<" "<< list_max<<endl;
    abp_cost = AB_NegaMax(this_player,depth,a,b);//NegaMax(this_player,depth); if(cost) ;
    if(list)
    {
        list[move_index].Display_M();//.Make_string();
        cout<<endl;
        cout<<" "<<move_index<<endl;
    }
    move_index =0;
    cout<<endl;
    nega_cost = NegaMax(this_player,depth);
    if(list)
    {
        list[move_index].Display_M();//.Make_string();
        cout<<endl;
        cout<<" "<<move_index<<endl;
    }
    //    fprintf(stdout, "NEGA: %s cost: %d\t ABP: %s cost: %d\n", nega,nega_cost,abp,abp_cost);

    //    Make_Move(list[move_index]);
    //    queen = Promotions(queen);
    //    delete [] list;
    //    list=NULL;
    //    ++turn_count;
    //    return temp;


}

//method for implementing the Negamax function with & without alpha beta pruning
char * Novice::Go()
{  
    char* temp =NULL; bool queen=false;
    // a & b set to the value the king is worth...
    int cost=0, a=-1,b=1,list_index=0, list_max=0, this_player = player;
    int depth=DEPTH;
    Display_Board();
    list = Generate_Moves(this_player,list_index,list_max);
    cost = AB_NegaMax(this_player,depth,a,b);//NegaMax(this_player,depth); if(cost) ;
    temp =  list[move_index].Make_string();
    Make_Move(list[move_index]);
    queen = Promotions(queen);
    delete [] list;
    list=NULL;
    ++turn_count;
    return temp;
}

//NegaMax implemented WITHOUT Alpha Beta Pruning -- 90%+ completed NEEDS
//MORE TESTING
int Novice::NegaMax(int this_player,int depth)
{ 
    //if players king is gone or depth is reached: ->return board value
    if(depth == 0 || Game_Over(this_player)) return Board_Eval(this_player);
    int i=0,maxi=0,val_p=0, val=0, holdi=0; bool queen=false;

    //generate ordered move list(greatest }to{ lowest)  
    Move* the_list = Generate_Moves(this_player,i,maxi);
    //no list
    if(!the_list) return Board_Eval(this_player);
    Make_Move(the_list[0]);
    queen = Promotions(queen);
    val_p = -(NegaMax( -this_player, depth - 1));
    Unmove(queen,the_list[0]); 
    queen =false;
    i=1;
    for(;i<maxi;++i)
{
    Make_Move(the_list[i]);
    queen = Promotions(queen);
    val = -(NegaMax( - this_player,depth - 1));
    Unmove(queen,the_list[i]);
    queen =false;
    if(val_p<val)
    {
        val_p = val;
        if(depth == DEPTH) holdi = i;
    }
    else
        val_p = max(val_p,val);
}
if(depth == DEPTH) move_index = holdi;
delete []the_list;
the_list = NULL;
return val_p;
}

//NegaMax WITH Alpha Beta Pruning... i had to bail on this as time was running
//out and I had to figure out what was going wrong... NEEDS MORE TESTING
int Novice::AB_NegaMax(int this_player,int depth,int alpha,int beta)
{
    //has no king on board or depth is 0 
    if(depth == 0 || Game_Over(this_player)) return Board_Eval(this_player); 
    bool queen = false;//used to validate promotions
    int  i=0, hold_val=0,maxi=0,val=-1,max_val=-1;
    //legal moves
    Move * the_list = Generate_Moves(this_player,i,maxi);
    //no moves 
    if(!the_list) return Board_Eval(this_player);
    //Make a move
    Make_Move(the_list[0]);
    queen = Promotions(queen);
    //recursive call
    max_val = -(AB_NegaMax(-this_player,depth-1, -beta, -alpha));
    //unmake move
    Unmove(queen,the_list[0]);
    //reset queen variable
    queen = false;
    i=1;
    if(max_val > beta) 
    {
        delete [] the_list;
        the_list = NULL;
        if(depth == DEPTH)   move_index = 0;
        return max_val;//ALPHA BETA PRUN
    }
    alpha = max(alpha,max_val);//ABP

    for(; i<maxi;++i)
    {
        //make move
        Make_Move(the_list[i]);
        queen = Promotions(queen);
        //recursive call
        val = -(AB_NegaMax(-this_player,depth-1, -beta, -alpha));
        //unmake move
        Unmove(queen,the_list[i]);
        queen= false;
        if(val >= beta)//ABP   
        {
            delete [] the_list;
            the_list = NULL;
            if(depth == DEPTH) move_index = i;
            return val;
        }

        //if last move was better than first move 
        if(max_val < val)//get value for most current equivilant move
        {
            max_val = val;
            if(depth == DEPTH)
                hold_val = i;
        }
        else
            max_val = max(max_val,val);
        alpha = max(alpha,val);
    }
    delete [] the_list;
    the_list = NULL;
    if(depth == DEPTH) move_index = hold_val;//sets class move index to make move.
    return max_val;
}

