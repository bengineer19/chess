#include <Arduino.h>
#include <ChessSerial.h>

//update this whole file and its functions

ChessSerial::ChessSerial(){
}

void ChessSerial::begin(){
    Serial.begin(9600);
}

void ChessSerial::sendMove(String information){
    bool acknowledged = false;
    while(acknowledged == false){
        if(Serial.available()){
            message = getMessage();
            if(message == "s"){
                Serial.println(information);
                Serial.flush();
            }
            else if(message == "1"){
                acknowledged = true;
            }
        }

    }
}

String ChessSerial::waitForMessage(){
    message = "not message2";
    message2 = "not message";

    while(message != message2 || message == "timeout"){
        Serial.println("s");
        Serial.flush();
        message = getMessage();
        Serial.println("s");
        Serial.flush();
        message2 = getMessage();
    }
    Serial.println("1");
    //Serial.println(message);
    Serial.flush();
    return message;
}

String ChessSerial::getMessage(){
    String incomingMessage;
    int timeout = millis() + 500;
    while(millis() < timeout){
        delay(10); //Reading bytes from and the state of the Serial buffer requires a delay
        if(Serial.available()){
            delay(10); //Reading bytes from and the state of the Serial buffer requires a delay
            incomingMessage = "";
            while(Serial.available()){
                character = Serial.read();
                incomingMessage.concat(character);
                delay(10); //Reading bytes from and the state of the Serial buffer requires a delay
            }
            return incomingMessage;
        }
    }
    return "timeout";
}
