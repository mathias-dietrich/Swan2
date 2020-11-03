//
//  NSView+FieldView.m
//  Swan
//
//  Created by Mathias Dietrich on 24.10.20.
//

#import "NSView+FieldView.h"

@implementation FieldView

- (void)flip{
    isFliped = !isFliped;
}

- (void)clearBg{
    btnQueenW.layer.borderWidth = 0;
    btnQueenB.layer.borderWidth = 0;
    btnKingW.layer.borderWidth = 0;
    btnKingB.layer.borderWidth = 0;
    btnRookW.layer.borderWidth = 0;
    btnRookB.layer.borderWidth = 0;
    btnBishopW.layer.borderWidth = 0;
    btnBishopB.layer.borderWidth = 0;
    btnKnightW.layer.borderWidth = 0;
    btnKnightB.layer.borderWidth = 0;
    btnPawnW.layer.borderWidth = 0;
    btnPawnB.layer.borderWidth = 0;
}

-(void) exec:(ECmd) cmd params:(NSString *) p parami:(int)i{
    switch(cmd){
        case CMD_SETFEN:
            p = [fenField stringValue];
            [self.window makeFirstResponder:nil];
            [fenField resignFirstResponder];
            break;
            
        case CMD_SETBOARD:
            setMode = !setMode;
            if(setMode){
                [self enablePieceSelection];
                 btnSetMode.layer.backgroundColor = NSColor.redColor.CGColor;
                 btnSetMode.layer.borderColor = NSColor.whiteColor.CGColor;

            }else{
                [self disablePieceSelection];
                btnSetMode.layer.backgroundColor = NSColor.knobColor.CGColor;
                btnSetMode.layer.borderColor = NSColor.knobColor.CGColor;
                [self clearBg];
            }
            break;
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
        case CMD_FINDMOVES:

            break;
            
        case CMD_SETKW:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = W_KING;
                btnKingW.layer.borderWidth = 2;
            }
            break;
            
        case CMD_SETKB:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = B_KING;
                btnKingB.layer.borderWidth = 2;
            }
            break;
            
        case CMD_SETQW:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = W_QUEEN;
                btnQueenW.layer.borderWidth = 2;
            }
            break;
            
        case CMD_SETQB:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = B_QUEEN;
                btnQueenB.layer.borderWidth = 2;
            }
            break;
            
        case CMD_SETRW:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = W_ROOK;
                btnRookW.layer.borderWidth = 2;
            }
            break;
            
        case CMD_SETRB:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = B_ROOK;
                btnRookB.layer.borderWidth = 2;
            }
            break;
            
        case CMD_SETBW:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = W_BISHOP;
                btnBishopW.layer.borderWidth = 2;
            }
            break;
            
        case CMD_SETBB:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = B_BISHOP;
                btnBishopB.layer.borderWidth = 2;
            }
            break;

        case CMD_SETNW:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = W_KNIGHT;
                btnKnightW.layer.borderWidth = 2;
            }
            break;

        case CMD_SETNB:
            [self clearBg];
            if(set.gameState!=GAME_PROMOTION){
                pieceSelected = B_KNIGHT;
                btnKnightB.layer.borderWidth = 2;
            }
            break;
            
        case CMD_SETPW:
            [self clearBg];
            pieceSelected = W_PAWN;
            btnPawnW.layer.borderWidth = 2;
            break;
            
        case CMD_SETPB:
            [self clearBg];
            pieceSelected = B_PAWN;
            btnPawnB.layer.borderWidth = 2;
            break;
    }
    [facade exec: cmd params: p parami:i];
}

- (void)mouseUp:(NSEvent *)theEvent {
    NSPoint curPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    int x = curPoint.x-BORDER;
    int y = curPoint.y-BORDER;
    int file = x/95;
    int rank =  y/95;
    int hit;
    if(isFliped){
        hit = 63 - (file + rank * 8);
    }else{
        hit = file + rank * 8 ;
    }
    [facade mouseUp: hit];
}

- (void)mouseDown:(NSEvent *)theEvent {
    NSPoint curPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    int x = curPoint.x-BORDER;
    int y = curPoint.y-BORDER;
    int file = x/95;
    int rank =  y/95;
    int hit;
    if(isFliped){
       hit = 63 - (file + rank * 8);
    }else{
       hit = file + rank * 8 ;
    }

    if(setMode){
        [facade setup: hit piece:pieceSelected];
        return;
    }
    [facade mouseDown: hit];
}

// Main refresh timer
- (void)_timerFired:(NSTimer *)timer {
    set = [facade getSet];
    NSResponder *firstResponder = [[NSApp keyWindow] firstResponder];
    if ([firstResponder isKindOfClass:[NSText class]] && [(id)firstResponder delegate] == fenField) {
        [fenField setBackgroundColor: NSColor.systemYellowColor];
    }else{
        [fenField setStringValue: [NSString stringWithCString:set.fen.c_str() encoding:[NSString defaultCStringEncoding]]];
        [fenField setBackgroundColor: NSColor.clearColor];
    }
    [timeW setStringValue: [NSString stringWithCString:set.timeW.c_str() encoding:[NSString defaultCStringEncoding]]];
    [timeB setStringValue: [NSString stringWithCString:set.timeB.c_str() encoding:[NSString defaultCStringEncoding]]];
    
    NSColor * c =  set.whiteToMove ? NSColor.whiteColor : NSColor.blackColor;
    [colorWell setColor:c];
    
    [pngView setString: [NSString stringWithCString:set.pngDescription.c_str() encoding:[NSString defaultCStringEncoding]]];
    
    if(set.gameState == GAME_PROMOTION && set.whiteToMove){
        [ self enableWhitePromotion];
    }
    if(set.gameState == GAME_PROMOTION && !set.whiteToMove){
        [ self enableBlackPromotion];
    }
    [self setNeedsDisplay:YES];
}

-(void)initalize{
    facade = [Facade alloc];
    [facade setup];
    
    NSSize size = NSMakeSize(77,77);
    BORDER = 20;
    myColor = [NSColor colorWithCalibratedRed:0.4 green:0.4 blue:0.9 alpha:0.7f];
    wBishop = [self imageResize:[NSImage imageNamed:@"Chess_blt60"] newSize:size];
    wRook = [self imageResize:[NSImage imageNamed:@"Chess_rlt60"] newSize:size];
    WKnight = [self imageResize:[NSImage imageNamed:@"Chess_nlt60"] newSize:size];
    wKing = [self imageResize:[NSImage imageNamed:@"Chess_klt60"] newSize:size];
    wQueen = [self imageResize:[NSImage imageNamed:@"Chess_qlt60"] newSize:size];
    wPawn = [self imageResize:[NSImage imageNamed:@"Chess_plt60"] newSize:size];

    bBishop = [self imageResize:[NSImage imageNamed:@"Chess_bdt60"] newSize:size];
    bRook = [self imageResize:[NSImage imageNamed:@"Chess_rdt60"] newSize:size];
    bKnight = [self imageResize:[NSImage imageNamed:@"Chess_ndt60"] newSize:size];
    bKing = [self imageResize:[NSImage imageNamed:@"Chess_kdt60"] newSize:size];
    bQueen = [self imageResize:[NSImage imageNamed:@"Chess_qdt60"] newSize:size];
    bPawn = [self imageResize:[NSImage imageNamed:@"Chess_pdt60"] newSize:size];
    
    self->drpEngine0.delegate = self;
    self->drpEngine1.delegate = self;
    self->drpGame.delegate = self;

    attributes = [NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:@"Helvetica" size:17], NSFontAttributeName,[NSColor blackColor], NSForegroundColorAttributeName, nil];
    attributesSmall = [NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:@"Helvetica" size:13], NSFontAttributeName,[NSColor grayColor], NSForegroundColorAttributeName, nil];
   
    _timer = [NSTimer scheduledTimerWithTimeInterval:0.1f target:self selector:@selector(_timerFired:) userInfo:nil repeats:YES];
}

- (void)drawRect:(NSRect)dirtyRect {
    if(!isInit){
        isInit = true;
       [self initalize];
    }
    
    // Fields
    bool flip = true;
   for(int x=0; x < 8; ++x){
       for(int y=0; y < 8; ++y){
           if(flip){
               [myColor set];
           }else{
               [[NSColor whiteColor] set];
           }
           flip = !flip;
           CGRect rectangle = CGRectMake(BORDER + x * 95, BORDER + y * 95, 95, 95);
           NSRectFill( rectangle);
           
           int no = y*8+x;
           if(isFliped){
               no = 63-no;
           }
           NSString *ss = [NSString stringWithFormat:@"%i",no];
           NSAttributedString * currentText=[[NSAttributedString alloc] initWithString:ss attributes: attributesSmall];
           [currentText drawAtPoint:NSMakePoint(23 + x * 95, 20 + y * 95)];
       }
       flip = !flip;
   }

  // Files A - H
  [[NSColor blackColor] set];
   for(int i =0; i < 8;i++){
       int file = i;
       if(isFliped){
           file = 7-file;
       }
       char c = (char) file + 65;
       NSString *s = [NSString stringWithFormat:@"%c", c];
       NSAttributedString * currentText=[[NSAttributedString alloc] initWithString:s attributes: attributes];
       [currentText drawAtPoint:NSMakePoint(59+i*95  , 0)];
       [currentText drawAtPoint:NSMakePoint(59+i*95  , 780)];
   }
    
    // Ranks 1 - 8
   for(int i =0; i < 8;i++){
       int rank = i;
       if(isFliped){
           rank = 7-rank;
       }
       char c = (char) rank + 49;
       NSString *s = [NSString stringWithFormat:@"%c", c];
       NSAttributedString * currentText=[[NSAttributedString alloc] initWithString:s attributes: attributes];
       [currentText drawAtPoint:NSMakePoint(5, 59+i*95)];
       [currentText drawAtPoint:NSMakePoint(785,59+i*95 )];
   }
    
    // Active Fields
        int aField = set.fromField;
        if(aField > -1){
            if(isFliped){
                aField = 63-aField;
            }
            int x = aField % 8;
            int y = aField / 8;
            int xPos = 27 + x * 95;
            int yPos = 27 + y * 95;
            NSRect rect = NSMakeRect(xPos, yPos, 80, 80);
            NSBezierPath* circlePath = [NSBezierPath bezierPath];
            [circlePath appendBezierPathWithOvalInRect: rect];
            [[NSColor yellowColor] setStroke];
            [[NSColor yellowColor] setFill];
            [circlePath stroke];
            [circlePath fill];
        }
        
        for(int i=0;i<64;i++){
            if(set.toFields[i]>-1){
                int aField = set.toFields[i];
                if(isFliped){
                    aField = 63-aField;
                }
                int x = aField % 8;
                int y = aField / 8;
                int xPos = 27 + x * 95;
                int yPos = 27 + y * 95;
                NSRect rect = NSMakeRect(xPos, yPos, 80, 80);
                NSBezierPath* circlePath = [NSBezierPath bezierPath];
                [circlePath appendBezierPathWithOvalInRect: rect];
                [[NSColor orangeColor] setStroke];
                [[NSColor orangeColor] setFill];
                [circlePath stroke];
                [circlePath fill];
            }
            
            if(set.lastFrom == i){
                int aField = set.lastFrom;
                if(isFliped){
                    aField = 63-aField;
                }
                int x = aField % 8;
                int y = aField / 8;
                int xPos = BORDER + x * 95;
                int yPos = BORDER + y * 95;
                NSRect rect = NSMakeRect(xPos, yPos, 95, 95);
                NSBezierPath* circlePath = [NSBezierPath bezierPath];
                [circlePath appendBezierPathWithRect: rect];
                [[NSColor blueColor] setStroke];
                [circlePath stroke];
            }
            
            if(set.lastTo == i){
                int aField = set.lastTo;
                if(isFliped){
                    aField = 63-aField;
                }
                int x = aField % 8;
                int y = aField / 8;
                int xPos = BORDER + x * 95;
                int yPos = BORDER + y * 95;
                NSRect rect = NSMakeRect(xPos, yPos, 95, 95);
                NSBezierPath* circlePath = [NSBezierPath bezierPath];
                [circlePath appendBezierPathWithRect: rect];
                [[NSColor blueColor] setStroke];
                [circlePath stroke];
            }
        }
    
    for(int i =0;i<64;++i){
        int p = i;
        if(isFliped){
            p = 63-p;
        }
        
        int x = p % 8;
        int y = p / 8;
        int xPos = 27 + x * 95;
        int yPos = 29 + y * 95;
        
        switch(set.s[i]){
  
            case EMPTY:
                continue;
                
            case W_KING:
                [wKing drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case W_QUEEN:
                [wQueen drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case W_ROOK:
                [wRook drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case W_KNIGHT:
                [WKnight drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case W_BISHOP:
                [wBishop drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case W_PAWN:
                [wPawn drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case B_KING:
                [bKing drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case B_QUEEN:
                [bQueen drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case B_ROOK:
                [bRook drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case B_KNIGHT:
                [bKnight drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case B_BISHOP:
                [bBishop drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;
            case B_PAWN:
                [bPawn drawAtPoint:NSMakePoint(xPos,yPos) fromRect:CGRectMake(0, 0, 90, 90) operation:NSCompositeSourceOver fraction:1.0];
                break;

            default:
                break;
        }
    }
}

- (NSImage *)imageResize:(NSImage*)anImage newSize:(NSSize)newSize {
    NSImage *sourceImage = anImage;

    // Report an error if the source isn't a valid image
    if (![sourceImage isValid]){
        NSLog(@"Invalid Image");
    } else {
        NSImage *smallImage = [[NSImage alloc] initWithSize: newSize];
        [smallImage lockFocus];
        [sourceImage setSize: newSize];
        [[NSGraphicsContext currentContext] setImageInterpolation:NSImageInterpolationHigh];
        [sourceImage drawAtPoint:NSZeroPoint fromRect:CGRectMake(0, 0, newSize.width, newSize.height) operation:NSCompositeCopy fraction:1.0];
        [smallImage unlockFocus];
        return smallImage;
    }
    return nil;
}

- (void)disablePieceSelection{
    [btnKingW setEnabled: NO];
    [btnQueenW setEnabled: NO];
    [btnRookW setEnabled: NO];
    [btnBishopW setEnabled: NO];
    [btnKnightW setEnabled: NO];
    [btnPawnW setEnabled: NO];

    [btnKingB setEnabled: NO];
    [btnQueenB setEnabled: NO];
    [btnRookB setEnabled: NO];
    [btnBishopB setEnabled: NO];
    [btnKnightB setEnabled: NO];
    [btnPawnB setEnabled: NO];
}
- (void)enablePieceSelection{
    [btnKingW setEnabled: YES];
    [btnQueenW setEnabled: YES];
    [btnRookW setEnabled: YES];
    [btnBishopW setEnabled: YES];
    [btnKnightW setEnabled: YES];
    [btnPawnW setEnabled: YES];

    [btnKingB setEnabled: YES];
    [btnQueenB setEnabled: YES];
    [btnRookB setEnabled: YES];
    [btnBishopB setEnabled: YES];
    [btnKnightB setEnabled: YES];
    [btnPawnB setEnabled: YES];
}
- (void)enableWhitePromotion{
    [btnQueenW setEnabled: YES];
    [btnRookW setEnabled: YES];
    [btnBishopW setEnabled: YES];
    [btnKnightW setEnabled: YES];
}
- (void)enableBlackPromotion{
    [btnQueenB setEnabled: YES];
    [btnRookB setEnabled: YES];
    [btnBishopB setEnabled: YES];
    [btnKnightB setEnabled: YES];
}

-(void)comboBoxSelectionDidChange:(NSNotification *)notification{
    if ([notification object] == drpEngine0) {
        NSString *engineName = [drpEngine0 objectValueOfSelectedItem];
        [facade exec:CMD_SETENGINEW params: engineName parami:0];
   }
   else if ([notification object] == drpEngine1) {
       NSString *engineName = [drpEngine1 objectValueOfSelectedItem];
       [facade exec:CMD_SETENGINEB params: engineName parami:0];
   }
   else if ([notification object] == drpBook0) {
       NSString *book = [drpBook0 objectValueOfSelectedItem];
       [facade exec:CMD_SETBOOK0 params: book parami:0];
   }
   else if ([notification object] == drpBook1) {
       NSString *book = [drpBook1 objectValueOfSelectedItem];
       [facade exec:CMD_SETBOOK1 params: book parami:0];
   }
}
@end
