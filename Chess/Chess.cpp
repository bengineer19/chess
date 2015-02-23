#include <Arduino.h>
#include <Chess.h>

Chess::Chess(){
    for(int squareLEDCol = 46; squareLEDCol < 54; squareLEDCol++){
        pinMode(squareLEDCol, OUTPUT);
        digitalWrite(squareLEDCol, LOW);
    }

    for(int pieceLEDCol = 2; pieceLEDCol < 10; pieceLEDCol++){
        pinMode(pieceLEDCol, OUTPUT);
        digitalWrite(pieceLEDCol, LOW);
    }

    for(int LEDGnd = 22; LEDGnd < 30; LEDGnd++){
        pinMode(LEDGnd, OUTPUT);
        digitalWrite(LEDGnd, HIGH);
    }

    for(detection5v = 30; detection5v < 38; detection5v++){
        pinMode(detection5v, OUTPUT);
        digitalWrite(detection5v, LOW);
    }

    for(detectionInput = 38; detectionInput < 46; detectionInput++){
        pinMode(detectionInput, INPUT);
    }
    readBoardToArray();
}

void Chess::flashStartingRows(){
    for(int i = 1; i < 70; i++){
        digitalWrite(22, LOW);
        for(activePieceLEDCol = pieceColStart; activePieceLEDCol < pieceColEnd; activePieceLEDCol++){
            digitalWrite(activePieceLEDCol, HIGH);
            delay(1);
            digitalWrite(activePieceLEDCol, LOW);
        }
        digitalWrite(22, HIGH);
    }

    for(int i = 1; i < 70; i++){
        digitalWrite(23, LOW);
        for(activePieceLEDCol = pieceColStart; activePieceLEDCol < pieceColEnd; activePieceLEDCol++){
            digitalWrite(activePieceLEDCol, HIGH);
            delay(1);
            digitalWrite(activePieceLEDCol, LOW);
        }
        digitalWrite(23, HIGH);
    }

    for(int i = 1; i < 70; i++){
        digitalWrite(28, LOW);
        for(activePieceLEDCol = pieceColStart; activePieceLEDCol < pieceColEnd; activePieceLEDCol++){
            digitalWrite(activePieceLEDCol, HIGH);
            delay(1);
            digitalWrite(activePieceLEDCol, LOW);
        }
        digitalWrite(28, HIGH);
    }

    for(int i = 1; i < 70; i++){
        digitalWrite(29, LOW);
        for(activePieceLEDCol = pieceColStart; activePieceLEDCol < pieceColEnd; activePieceLEDCol++){
            digitalWrite(activePieceLEDCol, HIGH);
            delay(1);
            digitalWrite(activePieceLEDCol, LOW);
        }
        digitalWrite(29, HIGH);
    }

}

void Chess::squareLEDs(int delayTime){
    for(activeSquareLEDCol = squareColStart; activeSquareLEDCol < squareColEnd; activeSquareLEDCol++){
        digitalWrite(activeSquareLEDCol, HIGH);
        cycleRows(delayTime);

        digitalWrite(activeSquareLEDCol, LOW);
    }
}

void Chess::pieceLEDs(int delayTime){
    for(activePieceLEDCol = pieceColStart; activePieceLEDCol < pieceColEnd; activePieceLEDCol++){
        digitalWrite(activePieceLEDCol, HIGH);
        cycleRows(delayTime);

        digitalWrite(activePieceLEDCol, LOW);
    }
}

void Chess::pieceLEDsStarting(int delayTime){
    for(activeRow = rowStart; activeRow < 24; activeRow++){
        digitalWrite(activeRow, LOW);
        cyclePieceLEDCols(delayTime);
        digitalWrite(activeRow, HIGH);
    }

    for(activeRow = 28; activeRow < rowEnd; activeRow++){
        digitalWrite(activeRow, LOW);
        cyclePieceLEDCols(delayTime);
        digitalWrite(activeRow, HIGH);
    }
}

void Chess::oneLED(int column, int row, int pause){
    digitalWrite(column + 46, HIGH);
    digitalWrite(row + 22, LOW);
    delay(pause);
    digitalWrite(column + 46, LOW);
    digitalWrite(row + 22, HIGH);
}

void Chess::cyclePieceLEDCols(int delayTime){
    for(activePieceLEDCol = pieceColStart; activePieceLEDCol < pieceColEnd; activePieceLEDCol++){
        digitalWrite(activePieceLEDCol, HIGH);
        delay(delayTime);
        digitalWrite(activePieceLEDCol, LOW);
    }
}

void Chess::cycleRows(int delayTime){
    for(activeRow = rowStart; activeRow < rowEnd; activeRow++){
        digitalWrite(activeRow, LOW);
        delay(delayTime);
        digitalWrite(activeRow, HIGH);
    }
}

void Chess::cycleRowsUp(int delayTime){
    for(activeRow = rowEnd - 1; activeRow >= rowStart; activeRow--){
        digitalWrite(activeRow, LOW);
        delay(delayTime);
        digitalWrite(activeRow, HIGH);
    }
}

void Chess::movePiece(int piece[], int square[]){
    flashPieceUntilMoved(piece);
    //Check if a piece is already present on the square, ie if the move is a capture
    delay(150); //To prevent shorting of rows as piece is pulled out
    if(pieceIsPresent(square[0], square[1])){
        //move is a capture
        flashUntilCaptured(square);
    }
    else{
        //move is not a capture
        flashSquareUntilPlaced(square);
    }
}

void Chess::flashPieceUntilMoved(int piece[]){
    while(pieceIsPresent(piece[0], piece[1])){
        unsigned long currentTime = millis();

        digitalWrite(piece[0] + 2, HIGH);
        digitalWrite(piece[1] + 22, LOW);

        while(currentTime + 125 > millis() && pieceIsPresent(piece[0], piece[1])){
        }

        digitalWrite(piece[0] + 2, LOW);
        digitalWrite(piece[1] + 22, HIGH);

        while(currentTime + 250 > millis() && pieceIsPresent(piece[0], piece[1])){
        }
    }
}

void Chess::flashSquareUntilPlaced(int square[]){
    while(pieceIsPresent(square[0], square[1]) == false){
        unsigned long currentTime = millis();

        digitalWrite(square[0] + 46, HIGH);
        digitalWrite(square[1] + 22, LOW);

        while(currentTime + 125 > millis() && pieceIsPresent(square[0], square[1]) == false){
        }

        digitalWrite(square[0] + 46, LOW);
        digitalWrite(square[1] + 22, HIGH);

        while(currentTime + 250 > millis() && pieceIsPresent(square[0], square[1]) == false){
        }
    }
}

void Chess::flashUntilCaptured(int square[]){
    flashPieceUntilMoved(square);
    delay(150); //To prevent shorting of rows as piece is pulled out
    flashSquareUntilPlaced(square);
}

bool Chess::pieceIsPresent(int column, int row){
    digitalWrite(column + 30, HIGH);
    if(digitalRead(row + 38) == HIGH){
        digitalWrite(column + 30, LOW);
        return true;
    }
    else{
        digitalWrite(column + 30, LOW);
        return false;
    }
}

void Chess::readBoardToArray(){
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(pieceIsPresent(x, y)){
                boardState[y][x] = true;
            }
            else{
                boardState[y][x] = false;
            }
        }
    }
}

void Chess::printBoardState(){
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Serial.print(boardState[y][x]);
            Serial.print(" ");
        }
        Serial.println();
    }
    Serial.println();
}

void Chess::waitForMove(){
    readBoardToArray();

    while(!pieceHasBeenLifted()){}

    //To prevent LED Gnds shorting with detection lines and ghosting pieces
    LEDGndsLOW();

    //while(!pieceHasBeenPlaced() && !pieceHasBeenCaptured()){}
    while(!liftedOrCaptured()){}

    //Turn LED Gnds back on
    LEDGndsHIGH();

    checkForShorts(65);
}

bool Chess::pieceHasBeenLifted(){
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if(boardState[y][x] == true && pieceIsPresent(x,y) == false){
                liftedPiece[0] = x;
                liftedPiece[1] = y;
                //Serial.println("lifted");
                delay(250);
                readBoardToArray();
                return true;
            }
        }
    }
    return false;
}

void Chess::checkForShorts(int delayTime){
    digitalWrite(46, HIGH);
    cycleRows(delayTime);
    cycleRowsUp(delayTime);
    digitalWrite(46, LOW);
}

void Chess::LEDGndsLOW(){
    for(int LEDGnd = 22; LEDGnd < 30; LEDGnd++){
        digitalWrite(LEDGnd, LOW);
    }
}

void Chess::LEDGndsHIGH(){
    for(int LEDGnd = 22; LEDGnd < 30; LEDGnd++){
        digitalWrite(LEDGnd, HIGH);
    }
}


bool Chess::liftedOrCaptured(){
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(boardState[y][x] == false && pieceIsPresent(x,y)){
                //If the piece is placed
                placedPiece[0] = x;
                placedPiece[1] = y;
                moveWasACapture = false;
                delay(250); //To prevent readBoardToArray being called while the piece is being placed
                readBoardToArray();
                return true;
            }
            if(boardState[y][x] == true && pieceIsPresent(x,y) == false){
                //If another piece is lifted, ie a capture
                moveWasACapture = true;
                delay(250); //To prevent readBoardToArray being called while the piece is being placed
                readBoardToArray();
                while(!pieceHasBeenPlaced()){}
                //Depends on whether the user lifted the capturing or captured piece first
                if(placedPiece[0] == liftedPiece[0] && placedPiece[1] == liftedPiece[1]){
                    liftedPiece[0] = x;
                    liftedPiece[1] = y;
                }
                readBoardToArray();
                return true;
            }
        }
    }
    return false;
}

bool Chess::pieceHasBeenPlaced(){

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if(boardState[y][x] == false && pieceIsPresent(x,y)){
                placedPiece[0] = x;
                placedPiece[1] = y;
                delay(250); //To prevent readBoardToArray being called while the piece is being lifted
                readBoardToArray();
                return true;
            }
        }
    }
    return false;
}
