#ifndef ChessSerial_h
#define ChessSerial_h

#include "Arduino.h"

class ChessSerial{
    public:
        ChessSerial();
        void sendMove(String information);
        void begin();
        String waitForMessage();
        String getMessage();
    private:
        char character;
        String message, message2;
};

#endif
