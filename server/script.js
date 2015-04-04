$(document).ready(function(){
    current(true);
});

game = new Chess();

var onDrop = function(source, target, piece, newPos, oldPos, orientation) {

    // see if the move is legal
    var move = game.move({
        from: source,
        to: target,
        promotion: 'q'
    });

    // illegal move
    if (move === null) return 'snapback';

    console.log("-----User Move-----");
    console.log("Source: " + source);
    console.log("Target: " + target);
    var currentFEN = game.fen();
    console.log(currentFEN);

    if((source == "e1" && target == "c1") || (source == "e1" && target == "g1")){
        //If move was a castle
        var bareFEN = currentFEN.substring(0, currentFEN.indexOf(" "));
        console.log(bareFEN);
        board.position(bareFEN);
        //Loads chess.js FEN onto chessboard.js board
    }

    var noSpacesFEN = currentFEN.split(" ").join("s");
    console.log(currentFEN);

    sendToChessboard("process.php?data=" + source + target + "&fen=" + noSpacesFEN);
    document.getElementById("turn").innerHTML = " Black";
    updateHistory(currentFEN);
};

var cfg = {
    draggable: true,
    position: 'start',
    onDrop: onDrop,
    //orientation: "black",
    sparePieces: false
};

var board = new ChessBoard('board', cfg);

function sendToChessboard(message){
    var ajaxRequest;

    try{
            ajaxRequest = new XMLHttpRequest();
    } catch (e){
            // Internet Explorer Browsers
            try{
                    ajaxRequest = new ActiveXObject("Msxml2.XMLHTTP");
            } catch (e) {
                    try{
                            ajaxRequest = new ActiveXObject("Microsoft.XMLHTTP");
                    } catch (e){
                            alert("Your browser broke!");
                            return false;
                    }
            }
    }
    ajaxRequest.onreadystatechange = function(){
        if(ajaxRequest.readyState == 4){
            console.log("-----Opponent move-----")
            console.log("Response: ");
            console.log(ajaxRequest.responseText);
            currentFEN = ajaxRequest.responseText.substring(0, (ajaxRequest.responseText.length - 1));
            //Remove mystery space from end of ajax response
            console.log(currentFEN);

            if(currentFEN.substring(0, 5) == "Error"){
                alert("Something went wrong on the other end! \n Click Recover to return to a safe state in the game.");
                return false;
            }
            if(currentFEN == ""){
                alert("The server could not process your response, please try again.");
                return false;
            }

            loadGame(currentFEN);
            updateHistory(currentFEN);
        }
    }
    ajaxRequest.open("GET", message, true); //Swap out slashes becasue of them being parsed in URL
    ajaxRequest.send(null);
}

function loadGame(fullFEN){
    var bareFEN = fullFEN.substring(0, fullFEN.indexOf(" "));
    game.load(fullFEN); //Loads full FEN into chess.js engine
    board.position(bareFEN); //Displays game in chessboard.js

    displayMoveInfo(fullFEN);
}

function displayMoveInfo(fullFEN){
    var move = fullFEN.substring((fullFEN.length - 1), fullFEN.length);
    document.getElementById("move").innerHTML = move;

    var turn = fullFEN.substring((fullFEN.indexOf(" ") + 1), (fullFEN.indexOf(" ") + 2));
    if(turn == "w"){
        turn = " White"
    }
    else{
        turn = " Black";
    }
    document.getElementById("turn").innerHTML = turn;
}

function newGame(){
    var FENHistory = ["rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"]//Starting FEN
    localStorage["FENHistory"] = JSON.stringify(FENHistory);
    loadGame("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    console.log("Board cleared");
}

function current(calledOnPageLoad){
    var FENHistory = JSON.parse(localStorage["FENHistory"]);
    var latestFEN = FENHistory[(FENHistory.length - 1)];
    var turn = latestFEN.substring((latestFEN.indexOf(" ") + 1), (latestFEN.indexOf(" ") + 2));
    if(calledOnPageLoad == true && turn == "b"){//Roll back to white's turn because if loaded on page refresh ajax response won't be recieved
        latestFEN = FENHistory[(FENHistory.length - 2)];
        FENHistory.splice(-1, 1); //Where to splice from, how many to splice
        localStorage["FENHistory"] = JSON.stringify(FENHistory);
    }
    loadGame(latestFEN);
}

function updateHistory(updateData){
    var FENHistory = JSON.parse(localStorage["FENHistory"]);
    FENHistory.push(updateData);
    localStorage["FENHistory"] = JSON.stringify(FENHistory);
}

function printHistory(){
    console.log("----- History -----");
    var FENHistory = JSON.parse(localStorage["FENHistory"]);
    for(var i = 0; i < FENHistory.length; i++){
        console.log(FENHistory[i]);
    }
    console.log("-------------------");
}

function goBack(){
    var FENHistory = JSON.parse(localStorage["FENHistory"]);
    var currentlyDisplayedFEN = game.fen();
    for(var i = (FENHistory.length - 1); i >= 0; i--){
        if(FENHistory[i] == currentlyDisplayedFEN){
            var currentPositionIndexInHistory = i;
        }
    }//Gets index of currently displayed FEN in FENHistory

    if(currentPositionIndexInHistory == 0){
        return false;
    }
    var oneFENBack = FENHistory[currentPositionIndexInHistory - 1];
    loadGame(oneFENBack);
}

function goForwards(){
    var FENHistory = JSON.parse(localStorage["FENHistory"]);
    var currentlyDisplayedFEN = game.fen();
    for(var i = (FENHistory.length - 1); i >= 0; i--){
        if(FENHistory[i] == currentlyDisplayedFEN){
            var currentPositionIndexInHistory = i;
        }
    }//Gets index of currently displayed FEN in FENHistory

    if(currentPositionIndexInHistory == (FENHistory.length - 1)){
        return false;
    }
    var oneFENForward = FENHistory[currentPositionIndexInHistory + 1];
    loadGame(oneFENForward);
}

function flip(){
    if(cfg.orientation == "white"){
        cfg.orientation = "black";
    }
    else{
        cfg.orientation = "white";
    }

    board = new ChessBoard('board', cfg);
    current(false);
}
