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
#include "EngineWrapper.h"
#include "Board.h"
#import "Game.h"

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
       
        newGame();
        vEngine = new VEngine();
        vEngine->listener = this;
        vEngine->init("/Users/mdietric/Swan2/engines/stockfish");
        engineWrapper = new EngineWrapper();
        

    }
    
    void close(){
        vEngine->close();
        engineWrapper->close();
        delete vEngine;
        delete engineWrapper;
        delete board;
    }
    
    void clearToFields(){
        for(int i=0;i<64;i++){
            toFields[i] = -1;
        }
        nextToField = 0;
    }
    
    void flipColor(){
        if(board->sideToMove==WHITE){
            board->sideToMove=BLACK;
        }else{
            board->sideToMove=WHITE;
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
    
    int timeWMsec;
    int timeBMsec;
    
  //  Set set;
    EEntryState entryState = ES_NONE;
    
    VEngine * vEngine;
    EngineWrapper * engineWrapper;
    TBoard * board;
    bool runClock = false;
    Game game;
    Ply ply;
    bool isCheck;
    int toFields[64];
    int fromField;
};

#endif /* UI_hpp */
