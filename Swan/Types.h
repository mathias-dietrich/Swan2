//
//  Types.hpp
//  Swan
//
//  Created by Mathias Dietrich on 24.10.20.
//

#ifndef Types_hpp
#define Types_hpp

#include <stdio.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

typedef long long TBitBoard;
typedef long long int64;

enum Color {
    WHITE = 0,
    BLACK = 1,
    NO_COLOR,
    COLOR_NB = 2
};

enum MoveType {
  NORMAL,
  PROMOTION = 1 << 14,
  ENPASSANT = 2 << 14,
  CASTLING  = 3 << 14
};

enum File {
  FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NB
};

enum Rank {
  RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NB
};

enum Square : int{
  SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
  SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
  SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
  SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
  SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
  SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
  SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
  SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
  SQ_NONE,
  SQUARE_NB = 64
};

enum Direction : int {
  NORTH =  8,
  EAST  =  1,
  SOUTH = -NORTH,
  WEST  = -EAST,

  NORTH_EAST = NORTH + EAST,
  SOUTH_EAST = SOUTH + EAST,
  SOUTH_WEST = SOUTH + WEST,
  NORTH_WEST = NORTH + WEST
};

inline File getFile(char x){
    return (File)(int) (x - 97);
}

enum EngineState {
  GETLEGAL, FINDMOVE, USERFROM, USERTO, MATE, PAT, RESIGN, STOPPED
};

struct Set{
    int s[64];
    int fromField;
    int toFields[64];
    int timeWMsec;
    int timeBMsec;
    bool whiteToMove;
    
};
// Piece Identifiers
enum EPiece {EMPTY,W_PAWN,W_KNIGHT,W_BISHOP,W_ROOK,W_QUEEN,W_KING, B_PAWN,B_KNIGHT,B_BISHOP,B_ROOK,B_QUEEN,B_KING,INVALID};


enum ECmd{CMD_TOP, CMD_BACK, CMD_FORWARD, CMD_STOP, CMD_END, CMD_ANALYZE, CMD_HINT, CMD_SAVEPNG, CMD_LOADPNG, CMD_START, CMD_SETBOARD, CMD_RESETBOARD,CMD_CLEARBOARD, CMD_SETTINGS,CMD_SETENGINEW,CMD_SETENGINEB, CMD_RESIGN,CMD_SETFEN, CMD_FINDMOVES};

enum EEntryState{ES_FROMDOWN, ES_FROMUP, ES_TODOWN, ES_TOUP, ES_NONE};

enum EReply{ES_MOVESAVAILABLE};

inline string posFromInt(int pos){
    int rank = pos / 8 + 1;
    int file = pos % 8;
    char c = (char)file +97;
    return c +  to_string(rank);
}


struct Ply{
    int from;
    int to;
    string str;
    string strDisplay;
};

inline Rank getRank(char x){
    return (Rank)(int) (x - 49);
}

inline Square getPosFromStr(string pos){
    int p = (tolower(pos[0]) - 97) + 8 *  (pos[1]-49);
    return (Square)p;
}

inline Square make_square(File f, Rank r) {
  return Square(int(f) | (int(r) << 3));
}

#endif /* Types_hpp */
