#!/usr/bin/env python

import serial, sys, datetime, time, chess
from chess_functions import *

s = serial.Serial("/dev/ttyACM0", 9600)
time.sleep(2) #Lets the arduino serial port get set up

#board = chess.Bitboard()

def waitForMessage():
    message = "not message2"
    message2 = "not message"
    while message != message2 or message == "timeout":
        s.write("s")
        message = getMessage()
        s.write("s")
        message2 = getMessage()
    s.write("1")
    time.sleep(1)
    message = message[:message.find("\\")] #strips "\r\n" Arduino formmating off the end
    #return repr(message)
    return message

def getMessage():
    startTime = datetime.datetime.now()
    difference = 0
    while difference < 500:
        if(s.inWaiting() > 0):
            #print "Serial!"
            return s.readline()
        currentTime = datetime.datetime.now()
        difference = int((currentTime - startTime).total_seconds() * 1000)
    #print "timeout"
    return "timeout"


def sendMove(information):
    acknowledged = False
    while not acknowledged:
        while not s.inWaiting():
            continue
        message = s.readline()
        #print repr(message)
        if message == "s\r\n":
            s.write(information)
        elif message == "1\r\n":
            #print "Acknowledged"
            acknowledged = True
    return True

def handleData():
    sendMove(compileMessage(sys.argv[1]))
    writeFile(addSpaces(sys.argv[2]))
    time.sleep(1)
    print generateFEN(waitForMessage())

moveOk = False
count = 0

while not moveOk:
    try:
        handleData()
        sendMove("ok")
        moveOk = True

    except Exception as e:
        sendMove("error")
        #print "Error"
        #print e
        count += 1
        if count == 3:
            print "Error: " + e
            moveOk = True #It's not, but we have to break outta the loop

