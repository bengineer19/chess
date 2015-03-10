game = new Chess();

var from, to;

var onDrop = function(source, target, piece, newPos, oldPos, orientation) {

    // see if the move is legal
    var move = game.move({
        from: source,
        to: target,
        promotion: 'q'
    });

    // illegal move
    if (move === null) return 'snapback';

    //console.log(game.moves())
    console.log("-----User Move-----");
    console.log("Source: " + source);
    console.log("Target: " + target);
    window.currentFEN = game.fen();
    console.log(window.currentFEN);

    var bareFEN = window.currentFEN.substring(0, window.currentFEN.indexOf(" "));
    console.log(bareFEN);
    board.position(bareFEN);
    //Loads chess.js FEN onto chessboard.js board, neccesary for castling.

    window.currentFEN = window.currentFEN.split("/").join("s");
    window.currentFEN = window.currentFEN.split(" ").join("u");
    console.log(window.currentFEN);
    from = source;
    to = target;

    ajaxFunction("process.php?data=" + from + to + "&fen=" + window.currentFEN);
};

function recoverGameData(){
    ajaxFunction("latestBoardMove.txt");
}

var cfg = {
    draggable: true,
    position: 'start',
    onDrop: onDrop,
    //orientation: "black",
    sparePieces: false
};
var board = new ChessBoard('board', cfg);

function ajaxFunction(message){
    var ajaxRequest;

    try{
            // Opera 8.0+, Firefox, Safari
            ajaxRequest = new XMLHttpRequest();
    } catch (e){
            // Internet Explorer Browsers
            try{
                    ajaxRequest = new ActiveXObject("Msxml2.XMLHTTP");
            } catch (e) {
                    try{
                            ajaxRequest = new ActiveXObject("Microsoft.XMLHTTP");
                    } catch (e){
                            // Something went wrong
                            alert("Your browser broke!");
                            return false;
                    }
            }
    }
    ajaxRequest.onreadystatechange = function(){
            if(ajaxRequest.readyState == 4 && message != "latestBoardMove.txt"){
                console.log("-----Opponent move-----")
                console.log("Response: ");
                console.log(ajaxRequest.responseText);
                window.currentFEN = ajaxRequest.responseText.substring(0, (ajaxRequest.responseText.length - 1));
                //Remove mystery space from end of ajax response
                console.log(window.currentFEN);

                if(window.currentFEN.substring(0, 5) == "Error"){
                    alert("Something went wrong on the other end! \n Click Recover to return to a safe state in the game.");
                    return false;
                }

                var bareFEN = window.currentFEN.substring(0, window.currentFEN.indexOf(" "));
                console.log(bareFEN);
                game.load(window.currentFEN);
                board.position(bareFEN);
            }
            else if(ajaxRequest.readyState == 4 && message == "latestBoardMove.txt"){
                console.log("Response: ");
                console.log(ajaxRequest.responseText);
                window.currentFEN = ajaxRequest.responseText;
                var bareFEN = window.currentFEN.substring(0, window.currentFEN.indexOf(" "));
                console.log(bareFEN);
                game.load(window.currentFEN);
                board.position(bareFEN);
            }
    }
    ajaxRequest.open("GET", message, true); //Swap out slashes becasue of them being parsed in URL
    ajaxRequest.send(null);
}


