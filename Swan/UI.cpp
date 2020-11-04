//
//  UI.cpp
//  Swan
//
//  Created by Mathias Dietrich on 28.10.20.
//

#include "UI.h"

 UI * UI::instance;

/*
 Listening to the UCI Engines =====================================================================
 */
void UI::listen(EReply c, string s){
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    switch(c){
        case ES_ENGINE0:
        case ES_ENGINE1:
        {
            std::string delimiter = "/n";
            std::stringstream ss(s);
             std::string to;
               while(std::getline(ss,to,'\n')){
                   if (to.rfind("bestmove", 0) == 0) {
                       string movestr = to.substr (9,5);
                       int from  = getPosFromStr(movestr.substr (0,2));
                       int to  = getPosFromStr(movestr.substr (2,2));
                       string promo = movestr.substr (5,1);
                       move(from,to, promo);
                       return;
                   }
                   if (to.rfind("info", 0) == 0) {
                       cout << to << endl;
                       continue;
                   }
               }
            break;
        }
            
        case ES_MATE:
        {
            bool haveMoves = false;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                if(token.length() > 3){
                    haveMoves = true;
                    break;
                }
                s.erase(0, pos + delimiter.length());
            }
            // no moves - in check? ============================================
            if(haveMoves){
                if(isCheck){
                    // Check if Mate;
                    ply.strDisplay += "+";
                }
                game.plies.push_back(ply);
                
                // Next move - ============================================
                if(board->sideToMove == WHITE){
                    if(engineName0 == "Player"){
                        return;
                    }
                    engine0->findMove(board->getFen(board), ES_ENGINE0);
                }else{
                    if(engineName1 == "Player"){
                        return;
                    }
                    engine1->findMove(board->getFen(board), ES_ENGINE1);
                }
                return;
            }
            
            // no moves - Game END ============================================
            runClock = false;
            if(isCheck){
                ply.strDisplay += "++";
                game.plies.push_back(ply);
                if(board->sideToMove == BLACK){
                    game.result = "1-0";
                    game.gameState = GAME_MATE;
                }else{
                    game.result = "0-1";
                    game.gameState = GAME_MATE;
                }
                return;
            }
            game.result = "1/2-1/2";
            game.gameState = GAME_PAT;
            break;
        }
            
        case ES_MOVESAVAILABLE:
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                std::cout << token << std::endl;
                if(from == getPosFromStr(token.substr(0, 2))){
                    toFields[nextToField] = getPosFromStr(token.substr(2, 2));
                    nextToField++;
                }
                s.erase(0, pos + delimiter.length());
            }
            break;
            
        case ES_CHECK:
            isCheck = false;
            int kingPos = -1;
            if(board->sideToMove==BLACK){
                for(int i =0;i<64;i++){
                    if(W_KING == board->squares[i]){
                        kingPos = i;
                        break;
                    }
                }
            }else{
                for(int i =0;i<64;i++){
                    if(B_KING == board->squares[i]){
                        kingPos = i;
                        break;
                    }
                }
            }
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                if(token.length() > 3){
                    if(kingPos == getPosFromStr(token.substr(2, 2))){
                        isCheck = true;
                    }
                }
                s.erase(0, pos + delimiter.length());
            }
            
            flipColor();
            if(board->sideToMove == WHITE){
                board->halfmove++;
            }
            
            vEngine->getLegalMoves(board->getFen(board),ES_MATE);
            break;
    }
}

/*
 Mouse Down Event =====================================================================
 */
void UI::mouseDown(int pos){
    switch(entryState){
        case ES_PROMOTION:
            return;
            
        case ES_FROMDOWN:
            to = pos;
            entryState = ES_TODOWN;
            break;

        case ES_FROMUP:
            if(from == pos){
                fromField = -1;
                entryState = ES_NONE;
                clearToFields();
            }
            break;
            
        case ES_TODOWN:
            for(int i=0;i<64;i++){
                if(pos == toFields[i]){
                    entryState = ES_NONE;
                    clearToFields();
                    fromField = -1;
                    move(from, pos, " ");
                    return;
                }
            }
            entryState = ES_NONE;
            clearToFields();
            fromField = -1;
            break;
            
        case ES_TOUP:
            break;
            
        case ES_NONE:
            if(board->squares[pos] == EMPTY){
                return;
            }
            if(board->sideToMove == WHITE && board->squares[pos]  > 6){
                return;
            }
            if(board->sideToMove == BLACK && board->squares[pos]  < 7){
                return;
            }
            from = pos;
            fromField = pos;
            entryState = ES_FROMDOWN;
            break;
    }
}

/*
 Mouse UP Event =====================================================================
 */
void UI::mouseUp(int pos){
    switch(entryState){
        case ES_FROMDOWN:
            if(pos==from){
                entryState = ES_TODOWN;
                string fen = board->getFen(board);
                clearToFields();
                exec(CMD_FINDMOVES, fen, pos);
                return;
            }
            entryState = ES_NONE;
            clearToFields();
            break;
        case ES_FROMUP:
            
            break;
        case ES_TODOWN:
            if(pos==to){
                clearToFields();
                return;
            }
            entryState = ES_NONE;
            clearToFields();
            break;
        case ES_TOUP:
            
            break;
        case ES_NONE:
            break;
    }
}

/*
 Making a move =====================================================================
 */
void UI::move(int from, int to, string promo){
    bool r50 = true;
    
    Square f = (Square)from;
    Square t = (Square)to;
    
    // Ply
    EPiece p = board->squares[from];
    ply.from = from;
    ply.to = to;
    ply.str = posFromInt(from)+posFromInt(to);
    ply.strDisplay =  board->getPGNCode(p) + posFromInt(from)+posFromInt(to);
    
    if(p == W_PAWN){
        r50 = false;
    }
    if(p == B_PAWN){
        r50 = false;
    }
    bool wCastlingS = board->castelingRights & 1;
    bool wCastlingL = board->castelingRights & 2;
    bool bCastlingS = board->castelingRights & 4;
    bool bCastlingL = board->castelingRights & 8;
    
    if(p==W_KING){
        wCastlingS = false;
        wCastlingL = false;
    }
   
    if(p==B_KING){
        bCastlingS = false;
        bCastlingL = false;
    }
    if(p==W_ROOK && from==SQ_A1){
        wCastlingL = false;
    }
    if(p==W_ROOK && from==SQ_H1){
        wCastlingS = false;
    }
    if(p==B_ROOK && from==SQ_A8){
        bCastlingL = false;
    }
    if(p==B_ROOK && from==SQ_H8){
        bCastlingS = false;
    }
    
    // Make Move
    board->gameState = GAME_RUNNING;
    
    // capture?
    if(board->squares[to]!=EMPTY){
        r50 = false;
    }
    board->squares[to] = p;
    board->squares[from] = EMPTY;
    
    // Promotion
    if(promo != " "){
        if("q" == promo){
            if(board->sideToMove == WHITE){
                board->squares[from] = W_QUEEN;
            }else{
                board->squares[from] = B_QUEEN;
            }
        }
        if("r"==promo){
            if(board->sideToMove == WHITE){
                board->squares[from] = W_ROOK;
            }else{
                board->squares[from] = B_ROOK;
            }
        }
        if("n"==promo){
            if(board->sideToMove == WHITE){
                board->squares[from] = W_KNIGHT;
            }else{
                board->squares[from] = B_KNIGHT;
            }
        }
        if("b"==promo){
            if(board->sideToMove == WHITE){
                board->squares[from] = W_BISHOP;
            }else{
                board->squares[from] = B_BISHOP;
            }
        }
    }

    // En passe hit
    if(board->enPassentSquare != SQ_NONE && ((Square)to) == board->enPassentSquare){
        if(p==W_PAWN){
            board->squares[to-8] = EMPTY;
        }
        if(p==B_PAWN){
            board->squares[to+8] = EMPTY;
        }
    }
        
    // En passe h
    board->enPassentSquare = SQ_NONE;
    if(p==W_PAWN && to == from + 16){
        board->enPassentSquare = (Square) (to - 8);
    }
    if(p==B_PAWN && to == from - 16){
        board->enPassentSquare = (Square) (to + 8);
    }
    
    // Castling
    if( p == W_KING && f == SQ_E1 && t == SQ_G1){
        board->squares[SQ_H1] = EMPTY;
        board->squares[SQ_F1] = W_ROOK;
        wCastlingS = false;
        wCastlingL = false;
        ply.strDisplay = "o-o";
    }
    if( p == W_KING && f == SQ_E1 && t == SQ_C1){
        board->squares[SQ_A1] = EMPTY;
        board->squares[SQ_D1] = W_ROOK;
        wCastlingL = false;
        wCastlingS = false;
        ply.strDisplay = "o-o-o";
    }
    if( p == B_KING && f == SQ_E8 && t == SQ_G8){
        board->squares[SQ_H8] = EMPTY;
        board->squares[SQ_F8] = B_ROOK;
        bCastlingS = false;
        bCastlingL = false;
        ply.strDisplay = "o-o";
    }
    if( p == B_KING && f == SQ_E8 && t == SQ_C8){
        board->squares[SQ_A8] = EMPTY;
        board->squares[SQ_D8] = B_ROOK;
        bCastlingL = false;
        bCastlingS = false;
        ply.strDisplay = "o-o-o";
    }
    board->castelingRights = 0;
    if(wCastlingS)board->castelingRights += 1;
    if(wCastlingL)board->castelingRights += 2;
    if(bCastlingS)board->castelingRights += 4;
    if(bCastlingL)board->castelingRights += 8;
    
    // Promotion
    if(board->sideToMove == WHITE ){
        if(p==W_PAWN &&  to> 55){
            entryState = ES_PROMOTION;
            board->gameState = GAME_PROMOTION;
            return;
        }
    }else{
        if(p==B_PAWN && to < 8){
            entryState = ES_PROMOTION;
            board->gameState = GAME_PROMOTION;
            return;
        }
    }
    
    lastTo = to;
    lastFrom = from;
    if(r50){
        board->rule50++;
    }else{
        board->rule50 = 0;
    }
    // Check if King in check;
    vEngine->getLegalMoves(board->getFen(board),ES_CHECK);
}

/*
 Returning the Set to the UI =====================================================================
 */
Set UI::getSet(){
    Set set;
    
    // Clock  -----------------------------------
    if(runClock){
        if(board->sideToMove == WHITE){
            timeWMsec--;
        }else{
            timeBMsec--;
        }
    }
    int secWall = timeWMsec/10;
    int secBall = timeBMsec/10;
    int minW = secWall / 60;
    int secW = secWall - minW * 60;
    int minB = secBall / 60;
    int secB = secBall - minB * 60;
    string secWs = to_string(secW);
    string secBs = to_string(secB);
    
    if(secWs.length() == 1){
        secWs = "0" + secWs;
    }
    if(secBs.length() == 1){
        secBs = "0" + secBs;
    }
    set.timeW = to_string(minW)  + ":" + secWs;
    set.timeB = to_string(minB)  + ":" + secBs;
    // End Clock -----------------------------------
    
    if(timeWMsec<=0){
        runClock = false;
        game.result = "0-1";
        game.gameState = GAME_TIMEOUT;
    }
    if(timeBMsec<=0){
        runClock = false;
        game.result = "1-0";
        game.gameState = GAME_TIMEOUT;
    }
    set.pngDescription = game.getDescription();
    for(int i=0;i<64;++i){
        set.s[i] = board->squares[i];
        set.toFields[i] = toFields[i] ;
        set.fromField = fromField;
    }
    set.whiteToMove = board->sideToMove == WHITE;
    set.fen = board->getFen(board);
    set.gameState = board->gameState;
    set.lastTo = lastTo;
    set.lastFrom = lastFrom;
    return set;
}


/*
Handing Commands from the UI  =====================================================================
 */
void UI::exec(ECmd cmd, string s, int p){
    switch(cmd){
        case CMD_TOP:
            break;
            
        case CMD_BACK:
            break;
            
        case CMD_FORWARD:
            break;
            
        case CMD_STOP:
            break;
            
        case CMD_END:
            break;
            
        case CMD_ANALYZE:
            break;
            
        case CMD_HINT:
            break;
            
        case CMD_SAVEPNG:
            break;
            
        case CMD_LOADPNG:
            break;
            
        case CMD_START:
            newGame();
            if(engineName0!="Player"){
                engine0->findMove(board->getFen(board), ES_ENGINE0);
            }
            break;
            
        case CMD_SETBOARD:
            break;
            
        case CMD_RESETBOARD:
            board->resetBoard();
            break;
            
        case CMD_CLEARBOARD:
            for(int i=0;i<64;++i){
                board->squares[i] = EMPTY;
            }
            break;
            
        case CMD_SETTINGS:
            break;
            
        case CMD_SETENGINEW:
            if(engineName0 != s && s!= "Player"){
                engine0->init(config.engineRoot + s);
            }
            engineName0 = s;
            game.whitePlayer = "[" + s + "]";
            break;
            
        case CMD_SETENGINEB:
            if(engineName1 != s && s!= "Player"){
                engine1->init(config.engineRoot + s);
            }
            engineName1 = s;
            game.blackPlayer = "[" + s + "]";
            break;
            
        case CMD_SETBOOK0:
            bookeName0 = s;
            break;
            
        case CMD_SETBOOK1:
            bookeName1 = s;
            break;
            
        case CMD_RESIGN:
            runClock = false;
            break;
            
        case CMD_SETFEN:
        {
            string prevFen = board->getFen(board);
            try{
                board->setFEN(s);
            }
            catch(...){
                board->setFEN(prevFen);
            }
            break;
        }
        case CMD_FINDMOVES:
            runClock = true;
            vEngine->getLegalMoves(s,ES_MOVESAVAILABLE);
            break;

        // Promotions
        case CMD_SETQB:
            if(board->gameState == GAME_PROMOTION){
                board->squares[ply.to] = B_QUEEN;
                board->gameState = GAME_RUNNING;
                entryState = ES_NONE;
                ply.strDisplay+="Q";
                vEngine->getLegalMoves(board->getFen(board),ES_CHECK);
            }
            break;
        case CMD_SETRB:
            if(board->gameState == GAME_PROMOTION){
                board->squares[ply.to] = B_ROOK;
                board->gameState = GAME_RUNNING;
                entryState = ES_NONE;
                ply.strDisplay+="R";
                vEngine->getLegalMoves(board->getFen(board),ES_CHECK);
            }
            break;
        case CMD_SETNB:
            if(board->gameState == GAME_PROMOTION){
                board->squares[ply.to] = B_KNIGHT;
                board->gameState = GAME_RUNNING;
                entryState = ES_NONE;
                ply.strDisplay+="N";
                vEngine->getLegalMoves(board->getFen(board),ES_CHECK);
            }
            break;
        case CMD_SETBB:
            if(board->gameState == GAME_PROMOTION){
                board->squares[ply.to] = B_BISHOP;
                board->gameState = GAME_RUNNING;
                entryState = ES_NONE;
                ply.strDisplay+="B";
                vEngine->getLegalMoves(board->getFen(board),ES_CHECK);
            }
            break;
        case CMD_SETQW:
            if(board->gameState == GAME_PROMOTION){
                board->squares[ply.to] = W_QUEEN;
                board->gameState = GAME_RUNNING;
                entryState = ES_NONE;
                ply.strDisplay+="Q";
                vEngine->getLegalMoves(board->getFen(board),ES_CHECK);
            }
            break;
        case CMD_SETRW:
            if(board->gameState == GAME_PROMOTION){
                board->squares[ply.to] = W_ROOK;
                board->gameState = GAME_RUNNING;
                entryState = ES_NONE;
                ply.strDisplay+="R";
                vEngine->getLegalMoves(board->getFen(board),ES_CHECK);
            }
            break;
        case CMD_SETNW:
            if(board->gameState == GAME_PROMOTION){
                board->squares[ply.to] = W_KNIGHT;
                board->gameState = GAME_RUNNING;
                entryState = ES_NONE;
                ply.strDisplay+="N";
                vEngine->getLegalMoves(board->getFen(board),ES_CHECK);
            }
            break;
        case CMD_SETBW:
            if(board->gameState == GAME_PROMOTION){
                board->squares[ply.to] = W_BISHOP;
                board->gameState = GAME_RUNNING;
                entryState = ES_NONE;
                ply.strDisplay+="B";
                vEngine->getLegalMoves(board->getFen(board),ES_CHECK);
            }
            break;
        case CMD_SETKW:
            break;
        case CMD_SETKB:
            break;
        case CMD_SETPW:
            break;
        case CMD_SETPB:
            break;
    }
}

/*
 new Game  =====================================================================
 */
void UI::newGame(){
    runClock = false;
    
    // TODO add differet Time Sets
    timeWMsec = 3000;
    timeBMsec = 3000;
    board->setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    board->castelingRights = 15;
    for(int i=0;i<64;++i){
        toFields[i] = -1;
    }
    fromField = -1;
    game.gameState = GAME_NONE;
    game.plies.clear();
    lastTo = -1;
}
