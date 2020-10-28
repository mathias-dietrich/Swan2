//
//  UI.hpp
//  Swan
//
//  Created by Mathias Dietrich on 28.10.20.
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>
#include <iostream>

#include "Types.h"
#include "Listener.h"

#include "VEngine.h"
#include "Board.h"

using namespace std;

class UI : Listener{
public:
    static UI * of(){
        if(instance == 0){
            instance = new UI();
        }
       return instance;
   }
    UI(UI const&) = delete;
    void operator=(UI const&) = delete;
    
    void mouseUp(int pos);
    void mouseDown(int pos);
    Set getSet();
    void exec(ECmd cmd, string s, int p);
    void listen(EReply c, int params[]);
    void listen(EReply c, string s);
    
    void setup(){
        board = new TBoard();
        board->setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        newGame();
        vEngine = new VEngine();
        vEngine->listener = this;
        vEngine->init("/Users/mdietric/Swan2/engines/stockfish");
        set.whiteToMove = true;
    }
    
    void close(){
        vEngine->close();
        delete vEngine;
        delete board;
    }
    
    void clearToFields(){
        for(int i=0;i<64;i++){
            set.toFields[i] = -1;
        }
        nextToField = 0;
    }
    
    void flipColor(){
        if(board->sideToMove==WHITE){
            board->sideToMove=BLACK;
            set.whiteToMove=false;
        }else{
            board->sideToMove=WHITE;
            set.whiteToMove=true;
        }
    }
    
private:
    static UI * instance;
    UI() {}
    void newGame();
    
    int from = -1;
    int to = -1;
    int nextToField = 0;
    bool fromSelected;
    bool fromSelectedConfirmed;
    bool toSelected;
    
    Set set;
    EEntryState entryState = ES_NONE;
    
    VEngine * vEngine;
    TBoard * board;
};

#endif /* UI_hpp */