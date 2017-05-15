#include "Player.h"


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
    logfile = fopen("minime2.log", "w");
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
    switch(argv[2][0]) {
        case 'O':
            switch(argv[2][1]) {
                case 'W':
                case 'B':
                case '?':
                    mecolor = argv[2][1];
                    break;
                default:
                    fprintf(stderr,"Offered game failed");
                    exit(0);
            }
            break;
        case 'A': {
                      char ch = argv[2][1];
                      if (isdigit(ch)) {
                          megame = atoi(&argv[2][1]);
                      } else if (ch == 'W' || ch == 'B') {
                          mecolor = ch;
                          megame = atoi(&argv[2][2]);
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
        if (isdigit(ch)) {
//            s = readstate(nf, 1);
//            s.cureval = eval(&s);
//            if (nttable > 0)
//                s.curzhash = zhash(&s);
            continue;
        }
        switch (ch) {
            case '?': {
                          char *r = plug.getnet(nf, (char*)"?");
                          char *q = strtok(r, " ");
                          assert(!strcmp(q, "?"));
                          char *tl = strtok(0, " ");
                          char *tr = strtok(0, " ");
                          assert(tl && tr);
//                          int t = readtimems(tl);
//                          t = 95 * t / (100 * ((81 - s.ply) / 2));
//                          struct move m = idnegamax(&s, t, 0);
//                          logmsg("value %d at time %d depth %d for %s\n\n",
//                                  v0, t, d0, movestr(&m));
//                          move(&s, &m, 0);
//                          sendcmd(nf, "%s", movestr(&m));
//                          printstate(&s, 1);
//                          if (ponder)
//                              (void) idnegamax(&s, 0, nf);
                          continue;
                      }
            case '!':
                      assert(fgetc(nf) == '!');
                      int ch;
                      do
                          ch = fgetc(nf);
                      while (isspace(ch));
                      ungetc(ch, nf);
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

void Novice::Go()
{  
    int list_index=0, list_max=0, depth=4,cost=0;
    list = Generate_Moves(list_index,list_max);
    char** this_board = Copy_Board(board);
    cost = NegaMax(this_board,depth);
    cout<<cost<<endl; 
//    char** temp = Copy_Board();
    //    Display_Moves(list,list_max);   PRIORITY LIST!!!
}

int Novice::NegaMax(char**& the_board,int depth)
{   //has no king on board or depth is 0 
    if(depth == 0 || Game_Over(the_board)) return Board_Eval(the_board);

    int list_max=0,list_index=0,val=-1,max_val=-1;
    char ** new_board = NULL;
    //legal moves
    Move * list = Generate_Moves(list_index,list_max);
    //no moves 
    if(!list) return Board_Eval(the_board);
    //create new board with move
    new_board = Moved(the_board,list[0]);
    Display_Board(new_board);
    Change_Player();
    max_val = - NegaMax(new_board,depth-1);
    for(int i=1; i<list_max;++i)
    {
        new_board = Moved(the_board,list[i]);
        Change_Player();
        val = - NegaMax(new_board,depth-1);
        max_val = max(max_val,val);
    }
    delete [] list;
    list = NULL;
    Remove_Board(new_board);
    return max_val;
}
