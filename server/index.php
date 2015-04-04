<!DOCTYPE html>
<html>
<head>
    <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
    <meta content="utf-8" http-equiv="encoding">

    <title>IoT Chess Board</title>
    <link rel="icon" href="../favicon.ico" type="image/x-icon">
    <link rel="shortcut icon" href="../favicon.ico" type="image/x-icon">

    <link rel="stylesheet" href="chessboardjs/css/chessboard.css">
    <link rel="stylesheet" href="style.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
    <script src="chessboardjs/js/chessboard.js"></script>
    <script src="chessjs/chess.js"></script>
</head>

<body>
    <h1>IoT Chess Board</h1>
    <div id="sideMenu">
        <h3>Navigation</h3>

        <div id="history">
            <input type="button" onclick="goBack();" value="<-">
            <input type="button" onclick="current(false);" value="Current">
            <input type="button" onclick="goForwards();" value="->">
        </div>
        <br>
        <table>
            <tr>
                <td><strong>Move:</strong></td>
                <td id="move"></td>
            </tr>
            <tr>
                <td><strong>Turn:</strong></td>
                <td id="turn"></td>
            </tr>
        </table>
        <br>
        <h3>Board</h3>
        <!--<div>
            <input type="button" id="connect" onclick="connect();" value="Check board connection">
        </div>
        <br>
        <br>-->
        <div id="boardOptions">
            <input type="button" onclick="newGame();" value="New Game">
            <br><br>
            <input type="button" onclick="flip();" value="Flip Board">
        </div>

        <!--<input type="button" onclick="printHistory();" value="Print History">-->
    </div>

    <div id="board"></div>
    <script src="script.js"></script>

</body>
</html>
