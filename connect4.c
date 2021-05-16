///////////////////////////////////////////////////////////////////////////// 
// INTEGRITY STATEMENT (v3)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement:a
// https://student.cs.uwaterloo.ca/~cs136/current/assignments/integrity.shtml
/////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with: 
 
// none 
//  
// Name: Saad Usman 
// login ID: s7usman 
///////////////////////////////////////////////////////////////////////////// 

#include "trace-2d.h"
#include <assert.h>
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THESE CONSTANTS
const int INVALID_GAME = -1;
const int TIE = 1;
const int MAX_BOARD_SIZE = 1024;
/////////////////////////////////////////////////////////////////////////////

// checkvalid(gameboard, move, width, height) given a gameboard
// and move will determine whether that move was valid for the
// given situation of the game
// requires: 2 < width, height
//           width x height <= MAX_BOARD_SIZE
// effects: returns a 0 for a valid move, 1 for invalid

int checkvalid(int* gameboard, int move, int width, int height) {
    assert(gameboard);
    assert((2 < width) && (2 < height));
    assert((width*height) < MAX_BOARD_SIZE);
    if ((move > (width-1)) || (move < 0)) {
        return 1;
    } else {
        for (int i=move;i<=((width*height)-(width-
                                            move));i+=width) {
            if (gameboard[i] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

// checkwin(gameboard, width, height, length, player) given a 
// a gameboard will determine whether of a certain length
// has been formed by the player
// requires: 2 < width, height
//           width x height <= MAX_BOARD_SIZE
//           2 < length < max(width, height)
// effects: returns a game state

int checkwin(int* gameboard, int width, int height, int length, int player) {
    assert(gameboard);
    assert((2 < width) && (2 < height));
    assert((width*height) < MAX_BOARD_SIZE);
    assert((2 < length) && (length <= width) && (length <=
                                                 height));
  
    int counter = 0;
    for (int j=0;j<=(((height-1)*width)+1);j+=width) {
        for (int k = 0; k <= (width - length); k++) {
            for (int i = j + k; i < (length + k + j); i++) {
                if (gameboard[i] == player) {
                    //printf("%d %d\n", i, counter);
                    counter++;
                }
                if (counter == length) {
                    //printf("1");
                    return 1;
                }
            }
            counter = 0;
        }
    }
    counter = 0;
    for (int j=0;j<width;j++) {
        for (int k = 0; k < (width * (height - length+1)); k += 
             width) {
            for (int i = k + j; i <= ((width * (length - 1)) +
                                      k + j); i += width) {
                if (gameboard[i] == player) {
                    counter++;
                }
                if (counter == length) {
                    //printf("2");
                    return 1;
                }
            }
            counter = 0;
        }
    }
    counter = 0;
    for (int j=0;j<width;j++) {
        for (int k=0;k<((width*height)-(width*length)-
                        (j*width)+2);k+=(1+width)) {
            for (int i = j+k; i < ((width*length)+1+k); i+=
                                  (1+width)) {
                if (gameboard[i] == player) {
                    counter++;
                }
                if (counter == length) {
                    //printf("3");
                    return 1;
                }
                if (((i - (width - 1)) % width) == 0) {
                    break;
                }
            }
            counter = 0;
        }
    }
    counter = 0;
    for (int j=0;j<height;j++) {
        for (int k=0;k<(width*height-(j*(width-1)));k+=
             (1+width)) {
            for (int i = (j*width)+k; i < ((width*length)+k+
                                           (j*width)); i+=
                                                               
                 (1+width)) {
                //printf("%d\n", k);
                if (gameboard[i] == player) {
                    counter++;
                }
                if (counter == length) {
                    //printf("4");
                    return 1;
                }
                if (((i - (width - 1)) % width) == 0) {
                    break;
                }
            }
            counter = 0;
        }
    }
    counter = 0;
    for (int j=(width-1);j>0;j--) {
        for (int k=0;k<((((height-length)*width)+length));k+=    
             (width-1)) {
            for (int i = j+k; i < (((width*length)-length+k) + 
                                   1);
                 i+=(width-1)) {
                //printf("%d %d %d\n", i, j, k);
                if (gameboard[i] == player) {
                    counter++;
                }
                if (counter == length) {
                    //printf("5");
                    return 1;
                }
                if ((i % width) == 0) {
                    break;
               }
            }
            counter = 0;
        }
    }
    counter = 0;
    for (int j=(width-1);j<=(width*height);j+=width) {
        for (int k=0;k<(((height-length)*width)+length); k+=
             (width-1)) {
            for (int i = j+k; i < (((width*length)-
                                    length+k)+1);
                 i+=(width-1)) {
                if (gameboard[i] == player) {
                    counter++;
                }
                if (counter == length) {
                    //printf("6");
                    return 1;
                }
                if ((i % width) == 0) {
                    break;
                }
            }
            counter = 0;
        }
    }
    return 0;
}

// changer(gameboard, move, width, height, player) changes
//   the state of the gameboard given a move and player 
//   executing that move
// requires: 2 < width, height
//           width x height <= MAX_BOARD_SIZE
// effects: mutates gameboard

void changer(int* gameboard, int move, int width, int height, int player) {
    assert(gameboard);
    assert((2 < width) && (2 < height));
    assert((width*height) < MAX_BOARD_SIZE);
    for (int i=move;i<=((width*height)-move);i+=width) {
        if (gameboard[i] == 0) {
            gameboard[i] = player;
            break;
        }
    }
}


int connect_analysis(const int moves[], int width, int height, int length) {
    assert(moves);
    assert((2 < width) && (2 < height));
    assert((width*height) < MAX_BOARD_SIZE);
    assert((2 < length) && (length <= width) && (length <= 
                                                height)); 
    int counter = 0;
    int gameboard[1024] = {0};
    while (1) {
        if (checkvalid(gameboard, moves[counter], width, 
                       height)) {
            return INVALID_GAME;
        }
        if ((counter % 2) == 0) {
            changer(gameboard, moves[counter], width, height, 
                    1);
            if (checkwin(gameboard, width, height, length, 1)) 
            {
                return counter+1;
            }
        } else {
            changer(gameboard, moves[counter], width, height, 
                    -1);
            if (checkwin(gameboard, width, height, length, -1)) 
            {
                return -(counter+1);
            }
        }
        counter += 1;
        if (counter == (width*height)) {
            return TIE;
        }
    }
}