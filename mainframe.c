#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
int max(int* currenttable, int length) {
    int currentmax = -100;
    int i = 0;
    for (i=0;i<length;i++) {
        if (*(currenttable + i) > currentmax) {
            currentmax = *(currenttable + i);
        }
    } return currentmax;
}

int min(int* currenttable, int length) {
    int currentmin = 100;
    int i = 0;
    for (i=0;i<length;i++) {
        if (*(currenttable + i) < currentmin) {
            currentmin = *(currenttable + i);
        }
    } return currentmin;
}

void addtheturnplayer1(int v,char** currenttable)
{
    *(currenttable + v - 1) = "X";

}

void addtheturnplayer2(int v,char** currenttable)
{
    *(currenttable + v - 1) =  "O";
}

char** makethetable() {
    char** currenttable;
    currenttable = (char**)malloc(9 * sizeof(char*));
    return currenttable;
}

int tester(int v, char** currenttable) {
    if ((*(currenttable + v - 1) == "X")
        ||  (*(currenttable + v - 1) ==  "O")) {
        return 0;
    } else {
        return 1;
    }
}

int testwin(char* mark,char** currenttable) {
    int i, j;
    int xcounter;
    for (i = 0; i < 7; i += 3) {
        xcounter = 0;
        for (j = 0; j < 3; j++) {
            if (*(currenttable + j + i) == mark) {
                xcounter++;
            }
        }
        if (xcounter == 3) {
            //printf("1");

            return 1;
        } }
    xcounter = 0;
    for (i = 0; i < 3; i++) {
        xcounter = 0;
        for (j = 0; j < 7; j += 3) {
            if (*(currenttable + j + i) == mark) {
                xcounter++;
            }
        }
        if (xcounter == 3) {
            //printf("2");

            return 1;

        }
    }
    xcounter = 0;
    for (j = 0; j < 9; j += 4) {
        if (*(currenttable + j) == mark) {
            xcounter++;
        }
    }
    if (xcounter == 3) {
        //printf("3");

        return 1;
    }
    xcounter = 0;
    for (j = 2; j < 7; j += 2) {
        if (*(currenttable + j) == mark) {
            xcounter++;

        }
    }
    if (xcounter == 3) {
        //printf("4");

        return 1;

    }

    return 0;
}

void printboard(char** currenttable) {
    int o, j;
    for (j=0;j<7;j+=3) {
        for (o=0;o<3;o++) {
            if ((*(currenttable + j + o) == "X")
                ||  (*(currenttable + j + o) ==  "O")) {
                printf("%s", *(currenttable + o + j));
            }
            else {
                printf("%d",(o+j+1));
            }
        }
        printf("\n");
    }
}

void printcands(int* inttable) {
    int j;
    for (j=0;j<9;j+=1) {
        printf("%i",(inttable[j]));
    }
    printf("\n");

}

int testtie(char** currenttable) {
    int i, xcounter = 0;
    for (i=0;i<9;i++) {
        if (*(currenttable + i) == "X" ||
            *(currenttable + i) == "O") {
            xcounter++;
        } }
    if (xcounter == 9) {
        return 1;
    } else {
        return 0;
    }
}

int* findcandidates(char** currenttable,int numberofcand) {
    int* temptable;
    temptable = (int*)malloc(numberofcand * sizeof(int));
    int i;
    int counter = -1;
    for (i=0;i<9;i++) {
        if (!(*(currenttable + i) == "X") &&
            !(*(currenttable + i) == "O")) {
            //printf("%d",i);
            counter++;
            temptable[counter] = i + 1;
        } }
    return temptable;
}

int numberofcandidates(char** currenttable) {
    int i;
    int counter = 0;
    for (i=0;i<9;i++) {
        if (!(*(currenttable + i) == "X") &&
            !(*(currenttable + i) == "O")) {
            counter++;
        } }
    return counter;
}


int minilist(char** currenttable,int* listofempties, int lengthofempties, int stateofgame) {
    int i, j;
    int* temporarylist1;
    int* temporarylist2;
    if (stateofgame == 1) {
        temporarylist1 = (int*)malloc(lengthofempties * sizeof(int));
        for (i=0;i<lengthofempties;i++) {
            *(currenttable+(listofempties[i])-1) = "O";
            temporarylist1[i] = minimax(currenttable,2);
            *(currenttable+(listofempties[i])-1) = "-";
        }
        return (max(temporarylist1,lengthofempties));
    } else if (stateofgame == 2) {
        temporarylist2 = (int*)malloc(lengthofempties * sizeof(int));
        for (j=0;j<lengthofempties;j++) {
            *(currenttable+(listofempties[j])-1) = "X";
            temporarylist2[j] = minimax(currenttable,1);
            *(currenttable+(listofempties[j])-1) = "-";
        } return (min(temporarylist2,lengthofempties));
    } }

int minimax(char** currenttable,int player) {
    int number = numberofcandidates(currenttable);
    int* listofcan = findcandidates(currenttable, number);
    if (testwin("X",currenttable) == 1) {
        return -10;
    } else if (testwin("O",currenttable) == 1) {
        return 10; }
    else if (testtie(currenttable) == 1) {
        return 0;  }
    else {
        if (player == 1) {
            minilist(currenttable, listofcan , number, 1);
            //return 0;
        }
        else {
            minilist(currenttable, listofcan,
                     number, 2); } } }


int computerturn(char** currenttable) {
    int* toplevelcandidates;
    int numberofc, i, j = 0;
    numberofc = numberofcandidates(currenttable);
    int* listofvalues = (int*)malloc(numberofc * sizeof(int));

    toplevelcandidates = findcandidates(currenttable, numberofc);

    for (i=0;i<numberofc;i++) {

        *(currenttable + toplevelcandidates[i]-1) = "O";
        *(listofvalues + i) = minimax(currenttable,2);
        *(currenttable + toplevelcandidates[i]-1) = "";
    }

    int maxscore = max(listofvalues, numberofc);
    for (j=0;j<numberofc;j++) {
        if (*(listofvalues + j) == maxscore) {
            return *(toplevelcandidates + j);
        }
    } }

int main()
{
    int counter = 0;
    int turn;
    turn = 0;
    int b, h;
    char** currenttable = makethetable();
    //addtheturnplayer1(1,currenttable);
    //addtheturnplayer1(3,currenttable);
    //addtheturnplayer2(4,currenttable);
    //addtheturnplayer2(7,currenttable);



    while(1) {
        if (turn == 0) {
            printboard(currenttable);

            while (1) {
                printf("Player 1 enter your turn:");
                scanf("%d", &b);
                if (tester(b,currenttable) == 1) {
                    break; }
            }
            addtheturnplayer1(b,currenttable);
            if ((testwin("X",currenttable)) == 1) {
                printboard(currenttable);

                printf("Player 1 wins!");
                break;
            }
            else {
                turn = 1;
            } }
        else if (turn == 1) {
            h = computerturn(currenttable);
            printf("%i\n",h);
            addtheturnplayer2(h,currenttable);
            if ((testwin("O",currenttable)) == 1) {
                printboard(currenttable);

                printf("Player 2 wins!");
                break;
            }
            else {
                turn = 0;
            }
        }
        counter++;
        if (counter == 9) {
            printboard(currenttable);

            printf("game is over, you tied");
            break;
        }
    }
}