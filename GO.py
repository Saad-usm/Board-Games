import numpy as np

def runGame(size):
    return

def get_Coords(string):
    pos = string.index(",")
    x = int(string[:pos])
    y = int(string[pos+1:])
    return x, y
#start up the game
class GoGame () :
    def __init__ (self, size):
        if (size == 1) or (size%2 == 0):
            raise ValueError("Wrong Size!")
        else:
            self.board = np.zeros((size, size))
            self.whoseMove = "Black"
            self.winner = False
            self.size = size
            self.pass_count = 0

    def isValidMove(self, move):
        if (move == "p"):
            return True
        x, y = get_Coords(move)
        if (self.board[x,y] != 0):
            return False
        if (x < 0) or (x > self.size) or (y < 0) or (y > self.size):
            return False
        else:
            return True

    def endGame (self) :
        blackcounter = 0
        whitecounter = 0
        for i in range(0, self.size):
            for j in range(0, self.size):
                if self.board[i, j] == 1:
                    blackcounter += 1
        for i in range(0, self.size):
            for j in range(0, self.size):
                if self.board[i, j] == 2:
                    whitecounter += 1
        if blackcounter > whitecounter:
            self.winner = "white"
        elif whitecounter < blackcounter:
            self.winner = "black"
        else:
            self.winner = "draw"

    def captureCheck(self, group):
        counter = 0
        while (counter < len(group)):
            i = group[counter]
            color = self.board[i[0], i[1]]
            if (i[0] != self.size - 1):
                if self.board[i[0] + 1, i[1]] == color:
                    if ((i[0] + 1), i[1]) not in group:
                        group.append((i[0] + 1, i[1]))
                elif self.board[i[0] + 1, i[1]] == 0:
                    return
            if (i[1] != self.size - 1):
                if self.board[i[0], i[1] + 1] == color:
                    if ((i[0]), i[1] + 1) not in group:
                        group.append((i[0], i[1] + 1))
                elif self.board[i[0], i[1] + 1] == 0:
                    return
            if (i[0] != 0):
                if self.board[i[0] - 1, i[1]] == color:
                    if ((i[0] - 1), i[1]) not in group:
                        group.append((i[0] - 1, i[1]))
                elif self.board[i[0] - 1, i[1]] == 0:
                    return

            if (i[1] != 1):
                if self.board[i[0], i[1] - 1] == color:
                    if (i[0], i[1] - 1) not in group:
                        group.append((i[0], i[1] - 1))
                elif self.board[i[0], i[1] - 1] == 0:
                    return
            counter += 1

        for i in group:
            self.board[i[0], i[1]] = 0
        return

    def move (self, move) :
            if move == "p":
                if (self.whoseMove == "Black"):
                    self.whoseMove = "White"
                else:
                    self.whoseMove = "Black"
                self.pass_count += 1
                if self.pass_count == 2:
                    endGame(self)
                return

            else:
                self.pass_count = 0
            x, y = get_Coords(move)
            if (self.whoseMove == "Black"):
                self.board[x,y] = 1
                for i in range(0, self.size):
                    for j in range(0, self.size):
                        captureCheck(self, [(i, j)])
                self.whoseMove = "White"
            else:
                self.board[x,y] = 2
                for i in range(0, self.size):
                    for j in range(0, self.size):
                        captureCheck(self, [(i, j)])
                self.whoseMove = "Black"
