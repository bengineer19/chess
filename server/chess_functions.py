#!/usr/bin/env python
import chess

def writeFile(info):
    f = open("/var/www/latestWhiteMove.txt","a")
    f.write(info + "\n")
    f.close()

def writeBoardFENToFile(info):
    f = open("/var/www/latestBoardMove.txt","a")
    f.write(info + "\n")
    f.close()

def getFENFromFile():
    f = open("/var/www/latestWhiteMove.txt","r")
    contents = f.readlines()[len(f.readlines()) - 1]
    f.close()
    return contents

def addSpaces(message):
    message = message.replace("s", " ")
    return message

letterArray = ["a", "b", "c", "d", "e", "f", "g", "h"]

def compileMessage(message):
    #Convert letters to numbers and flip orientation by subtracting them from seven.
    #Subtract 1 from numbers to convert to zero-indexed board
    compiledMessage = str(7 - letterArray.index(message[0]))
    compiledMessage += ","
    compiledMessage += str(int(message[1]) - 1)
    compiledMessage += ";"
    compiledMessage += str(7 - letterArray.index(message[2]))
    compiledMessage += ","
    compiledMessage += str(int(message[3]) - 1)

    return compiledMessage

def getSquareNumber(x, y):
    square = letterArray[7 - int(x)] + str(int(y) + 1)
    #print square
    return chess.SQUARE_NAMES.index(square)

def generateFEN(boardMove):
    board = chess.Bitboard(getFENFromFile())

    piece = getSquareNumber(boardMove[0], boardMove[2])
    square = getSquareNumber(boardMove[4], boardMove[6])
    board.push_san(board.san(chess.Move(piece, square)))
    fen = board.fen()
    writeBoardFENToFile(fen)
    return fen
