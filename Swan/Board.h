//
//  Board.h
//  Swan
//
//  Created by Mathias Dietrich on 20.09.20.
//

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <boost/algorithm/string.hpp>

#include "Types.h"
#include "Global.h"

using namespace std;

/*******************************************************************
 TBoard : a powerfull class that represents the actual board
 this class is responsible for legal move generation and move
 execution
 *******************************************************************/
class TBoard
{
public:
    
    TBoard(){
        
    }
    
    ~TBoard(){
        
    }
    
    int64 hash;
    int lastTriggerEvent;// ply whith pawn move or capture
    int castelingRights = 1+2+4+8;
    bool inCheck;
    int repetitions;
    Square enPassentSquare = SQ_NONE;
    
    // Holds the piece information per square
    EPiece squares[SQ_H8+2];
    
    // Bit Boards for Pieces
    TBitBoard pcs[B_KING+2];
    TBitBoard emptySquares;
    TBitBoard occupiedSquares;
    TBitBoard pcsOfColor[BLACK+1];
    
    Color sideToMove = WHITE;
    int currentPly;
    
    Square findKingSquare(Color color){
        for(int i=0;i<64;i++){
            if(color==WHITE && squares[i] == W_KING){
                return (Square)i;
            }
            if(color==BLACK && squares[i] == B_KING){
                return (Square)i;
            }
        }
        return SQ_NONE;
    }

    int rule50 = 0;
    int halfmove =0;

    void move(string move){
        Square from = getPosFromStr(move.substr(0,2));
        Square to = getPosFromStr(move.substr(2,2));
        squares[to] =  squares[from];
        squares[from] = EMPTY;
    }
    string getPGNCode(EPiece piece){
        if(piece == W_PAWN  || piece == B_PAWN ){
            return "";
        }
        string l = getPieceLetter(piece);
        l = boost::to_upper_copy<std::string>(l);
        return l;
    }
    
    string getPieceLetter(EPiece piece){
        switch(piece){
            case B_PAWN:
                return "p" ;
                
            case W_PAWN:
                return "P";
                
            case B_ROOK:
                return "r";
                
            case W_ROOK:
                return "R";

            case B_KNIGHT:
                return "n";
                
            case W_KNIGHT:
                return "N";

            case B_BISHOP:
                return "b";

            case W_BISHOP:
                return "B";
 
            case B_QUEEN:
                return "q";

            case W_QUEEN:
                return"Q";

            case B_KING:
                return"K";

            case W_KING:
                return "K";

            default:
                return " ";
        }
    }
    
    void print(){
        myfile << "  A B C D E F G H" << endl;
        for(int i=8; i>0; --i){
            myfile  << i;
            myfile  << " ";
            for(int x=0; x<8; ++x){
                Square sq = (Square) (((i-1) * 8) + x);
                myfile << getPieceLetter(squares[sq]) << " ";
            }
            myfile  << i << endl;
        }
        myfile << "  A B C D E F G H" << endl;
    }
    
    string getFen(TBoard * board){
           string fen = "";
           int count = 0;
           
           for(int y=7; y>-1; y--){
               for(int x=0; x < 8; x++){
                   
                   int field = board->squares[x  + y * 8];
                   
                   if(field!=0 && count >0){
                       fen += std::to_string(count);
                       count = 0;
                   }
                   
                   switch(field){
                           
                       case W_PAWN:
                           fen += "P";
                           break;
                           
                       case W_ROOK:
                           fen += "R";
                           break;
                           
                       case W_KNIGHT:
                           fen += "N";
                           break;
                           
                       case W_BISHOP:
                           fen += "B";
                           break;
                           
                       case W_QUEEN:
                           fen += "Q";
                           break;
                           
                       case W_KING:
                           fen += "K";
                           break;
                           
                       case B_PAWN:
                           fen += "p";
                           break;
                           
                       case B_ROOK:
                           fen += "r";
                           break;
                           
                       case B_KNIGHT:
                           fen += "n";
                           break;
                           
                       case B_BISHOP:
                           fen += "b";
                           break;
                           
                       case B_QUEEN:
                           fen += "q";
                           break;
                           
                       case B_KING:
                           fen += "k";
                           break;
                           
                       case 0:
                           count++;
                           break;
                   }
               }
               if(y>-1 && count >0){
                   fen += std::to_string(count);
                   count = 0;
               }
               if(y>0){
                   fen += "/";
               }
           }
           fen += " ";
        if(board->sideToMove == WHITE){
               fen += "w";
           }else{
               fen += "b";
           }
           fen += " ";
        
           if(board->castelingRights == 0){
               fen += "-";
           }
           if(board->castelingRights & 1){
               fen += "K";
           }
           if(board->castelingRights & 2){
               fen += "Q";
           }
           if(board->castelingRights & 4){
               fen += "k";
           }
           if(board->castelingRights & 8){
               fen += "q";
           }
           
           fen += " ";
           string temp("abcdefgh");
           stringstream ss;
           
           if(board->enPassentSquare != SQ_NONE){
               int r = (board->enPassentSquare - 8) % 8;
               int f = (board->enPassentSquare - 8) / 8;
               ss << temp.at(r)  << to_string(f*8);
               fen += ss.str();
           }else{
               fen += "-";
           }
           fen += " ";
           fen += std::to_string(board->rule50);
           fen += " ";
           fen += std::to_string(board->halfmove);
           return fen;
       }
    
    int setFEN(string aFEN)
    {
        unsigned int i,j;
        int sq;
        char letter;
        int aRank,aFile;

        std::stringstream ss(aFEN);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> strList(begin, end);
 
        // Empty the board quares
        for (sq=SQ_A1;sq <= SQ_H8;sq++) squares[sq] = EMPTY;
        // read the board - translate each loop idx into a square
        j = 1; i = 0;
        while ((j<=64) && (i<=strList[0].length()))
        {
            letter = strList[0].at(i);
            i++;
            aFile = 1+((j-1) % 8);
            aRank = 8-((j-1) / 8);
            sq = (Square) (((aRank-1)*8) + (aFile - 1));
            switch (letter)
            {
                case 'p' : squares[sq] = B_PAWN; break;
                case 'r' : squares[sq] = B_ROOK; break;
                case 'n' : squares[sq] = B_KNIGHT; break;
                case 'b' : squares[sq] = B_BISHOP; break;
                case 'q' : squares[sq] = B_QUEEN; break;
                case 'k' : squares[sq] = B_KING; break;
                case 'P' : squares[sq] = W_PAWN; break;
                case 'R' : squares[sq] = W_ROOK; break;
                case 'N' : squares[sq] = W_KNIGHT; break;
                case 'B' : squares[sq] = W_BISHOP; break;
                case 'Q' : squares[sq] = W_QUEEN; break;
                case 'K' : squares[sq] = W_KING; break;
                case '/' : j--; break;
                case '1' : break;
                case '2' : j++; break;
                case '3' : j+=2; break;
                case '4' : j+=3; break;
                case '5' : j+=4; break;
                case '6' : j+=5; break;
                case '7' : j+=6; break;
                case '8' : j+=7; break;
                default: return -1;
            }
            j++;
        }
        string color = strList[1];
        if (color == "w"){
            sideToMove = WHITE;
        }else{
            sideToMove = BLACK;
        }
        
        // TODO
        string castling = strList[2];
        string enPasse = strList[3];
        
        if(enPasse != "-"){
            enPassentSquare = (Square)std::stoi(enPasse);
        }

        rule50 = stoi(strList[4]);
        halfmove = stoi(strList[5]);
        return 0;
    }
        
private:

};

