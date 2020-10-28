//
//  UI.cpp
//  Swan
//
//  Created by Mathias Dietrich on 28.10.20.
//

#include "UI.h"

 UI * UI::instance;

void UI::listen(EReply c, int params[]){
    switch(c){

    }
}

void UI::listen(EReply c, string s){
    switch(c){
        case ES_MOVESAVAILABLE:
            cout << s << endl;
            std::string delimiter = ",";
            size_t pos = 0;
            std::string token;
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                std::cout << token << std::endl;
                if(from == getPosFromStr(token.substr(0, 2))){
                    set.toFields[nextToField] = getPosFromStr(token.substr(2, 2));
                    nextToField++;
                }
                s.erase(0, pos + delimiter.length());
            }
            break;
    }
}

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

void UI::mouseDown(int pos){
    switch(entryState){
        case ES_FROMDOWN:
            to = pos;
            entryState = ES_TODOWN;
            break;

        case ES_FROMUP:
            if(from == pos){
                set.fromField = -1;
                entryState = ES_NONE;
                clearToFields();
            }
            break;
            
        case ES_TODOWN:
            for(int i=0;i<64;i++){
                if(pos == set.toFields[i]){
                    entryState = ES_NONE;
                    clearToFields();
                    set.fromField = -1;
                    
                    // Make Move
                    EPiece p = board->squares[from];
                    board->squares[pos] = p;
                    board->squares[from] = EMPTY;
                    
                    // Castling
                    Square f = (Square)from;
                    Square t = (Square)pos;
                    bool wCastlingS = board->castelingRights & 1;
                    bool wCastlingL = board->castelingRights & 2;
                    bool bCastlingS = board->castelingRights & 4;
                    bool bCastlingL = board->castelingRights & 8;
                    if( p == W_KING && f == SQ_E1 && t == SQ_G1){
                        board->squares[SQ_H1] = EMPTY;
                        board->squares[SQ_F1] = W_ROOK;
                        wCastlingS = false;
                        wCastlingL = false;
                    }
                    if( p == W_KING && f == SQ_E1 && t == SQ_C1){
                        board->squares[SQ_A1] = EMPTY;
                        board->squares[SQ_D1] = W_ROOK;
                        wCastlingL = false;
                        wCastlingS = false;
                    }
                    if( p == B_KING && f == SQ_E8 && t == SQ_G8){
                        board->squares[SQ_H8] = EMPTY;
                        board->squares[SQ_F8] = B_ROOK;
                        bCastlingS = false;
                        bCastlingL = false;
                    }
                    if( p == B_KING && f == SQ_E8 && t == SQ_G8){
                        board->squares[SQ_A8] = EMPTY;
                        board->squares[SQ_D8] = B_ROOK;
                        bCastlingL = false;
                        bCastlingS = false;
                    }
                    board->castelingRights = 0;
                    if(wCastlingS)board->castelingRights += 1;
                    if(wCastlingL)board->castelingRights += 2;
                    if(bCastlingS)board->castelingRights += 4;
                    if(bCastlingL)board->castelingRights += 8;
                    for(int i=0; i < 64; i++){
                        set.s[i] = board->squares[i];
                    }
                    flipColor();
                    if(board->sideToMove == WHITE){
                        board->halfmove++;
                    }
                    set.fen = board->getFen(board);
                    return;
                }
            }
            entryState = ES_NONE;
            clearToFields();
            set.fromField = -1;
            break;
            
        case ES_TOUP:
            break;
            
        case ES_NONE:
            if(set.s[pos] == EMPTY){
                return;
            }
            if(set.whiteToMove && set.s[pos]  > 6){
                return;
            }
            if(!set.whiteToMove && set.s[pos]  < 7  ){
                return;
            }
            from = pos;
            set.fromField = pos;
            entryState = ES_FROMDOWN;
            break;
    }
}

Set UI::getSet(){
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
    return set;
}

void UI::newGame(){
    for(int i=0; i < 64; i++){
        set.s[i] = EMPTY;
        set.toFields[i] = -1;
    }
    set.fromField = -1;

    set.s[0] = W_ROOK;
    set.s[1] = W_KNIGHT;
    set.s[2] = W_BISHOP;
    set.s[3] = W_QUEEN;
    set.s[4] = W_KING;
    set.s[5] = W_BISHOP;
    set.s[6] = W_KNIGHT;
    
    set.s[7] = W_ROOK;
    set.s[8] = W_PAWN;
    set.s[9] = W_PAWN;
    set.s[10] = W_PAWN;
    set.s[11] = W_PAWN;
    set.s[12] = W_PAWN;
    set.s[13] = W_PAWN;
    set.s[14] = W_PAWN;
    set.s[15] = W_PAWN;
    
    set.s[48] = B_PAWN;
    set.s[49] = B_PAWN;
    set.s[50] = B_PAWN;
    set.s[51] = B_PAWN;
    set.s[52] = B_PAWN;
    set.s[53] = B_PAWN;
    set.s[54] = B_PAWN;
    set.s[55] = B_PAWN;
    
    set.s[56] = B_ROOK;
    set.s[57] = B_KNIGHT;
    set.s[58] = B_BISHOP;
    set.s[59] = B_QUEEN;
    set.s[60] = B_KING;
    set.s[61] = B_BISHOP;
    set.s[62] = B_KNIGHT;
    set.s[63] = B_ROOK;
}

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
            runClock = true;
            break;
            
        case CMD_SETBOARD:
            
            break;
        case CMD_RESETBOARD:
            
            break;
        case CMD_CLEARBOARD:
            
            break;
        case CMD_SETTINGS:
            
            break;
        case CMD_SETENGINEW:
            
            break;
        case CMD_SETENGINEB:
            
            break;
        case CMD_RESIGN:
            
            break;
        case CMD_SETFEN:
            
            break;
        case CMD_FINDMOVES:
            runClock = true;
            vEngine->getLegalMoves(s);
            break;
    }
}
