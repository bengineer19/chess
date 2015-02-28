#ifndef Chess_h
#define Chess_h

#include "Arduino.h"

class Chess{
    public:
        Chess();
        bool boardState [8][8];
        int liftedPiece[2] = {0,0}; //liftedPiece must be equal to placedPiece for waitForMove() to run
        int placedPiece[2] = {0,0};
        bool moveWasACapture;

        void pieceLEDs(int delayTime);
        void pieceLEDsStarting(int delayTime);
        void squareLEDs(int delayTime);
        void flashStartingRows();
        void oneLED(int column, int row, int pause);

        void movePiece(int piece[2], int square[2]);
        void readBoardToArray();
        void printBoardState();
        void waitForMove();
    private:
        int activeRow, activeSquareLEDCol, activePieceLEDCol;
        int detection5v, detectionInput;

        int squareColStart = 46; //Min = 46
        int squareColEnd = 54; //Max = 53
        int pieceColStart = 2; //Min = 2
        int pieceColEnd = 10; //Max = 9
        int rowStart = 22; //Min = 22
        int rowEnd = 30; //Max = 29

        void cycleRows(int delayTime);
        void cycleRowsUp(int delayTime);
        void cyclePieceLEDCols(int delayTime);
        void flashPieceUntilMoved(int piece[2]);
        void flashSquareUntilPlaced(int square[2]);
        void flashUntilCaptured(int square[2]);
        bool pieceIsPresent(int column, int row);
        void LEDGndsLOW();
        void LEDGndsHIGH();
        void checkForShorts(int delayTime);
        bool pieceHasBeenLifted();
        bool pieceHasBeenPlaced();
        bool liftedOrCaptured();
};

#endif
