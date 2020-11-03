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
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <boost/algorithm/string.hpp>

#include "Types.h"
#include "Listener.h"

#include "VEngine.h"
#include "EngineWrapper.h"
#include "Board.h"
#import "Game.h"
#import "Config.h"

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
        vEngine->init(config.engineRoot + "stockfish");
        
        engine0 = new EngineWrapper();
        engine0->listener = this;
        engine0->init(config.engineRoot + "stockfish");
        
        engine1 = new EngineWrapper();
        engine1->listener = this;
        engine1->init(config.engineRoot + "stockfish");
    }
    
    void setup(int field, EPiece piece){
        if(board->squares[field] != EMPTY){
            board->squares[field] = EMPTY;
        }else{
            board->squares[field] = piece;
        }
    }
    
    void close(){
        vEngine->close();
        engine0->close();
        engine1->close();
        delete vEngine;
        delete engine0;
        delete engine1;
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
    Config config;
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
    EngineWrapper * engine0;
    EngineWrapper * engine1;
    string engineName0 = "Player";
    string engineName1 = "stockfish";
    
    string bookeName0 = "No Book";
    string bookeName1 = "No Book";
    
    TBoard * board;
    bool runClock = false;
    Game game;
   
    Ply ply;
    bool isCheck;
    int toFields[64];
    int fromField;
    int lastTo = -1;
    int lastFrom = -1;
    
    void go(int from, int to, string promo);
};

#endif /* UI_hpp */
