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

-(void) exec:(ECmd) cmd params:(NSString *) p parami:(int)i{
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
    [facade mouseDown: hit];
}

// Main refresh timer
- (void)_timerFired:(NSTimer *)timer {
    set = [facade getSet];
    [fenField setStringValue: [NSString stringWithCString:set.fen.c_str() encoding:[NSString defaultCStringEncoding]]];
    [timeW setStringValue: [NSString stringWithCString:set.timeW.c_str() encoding:[NSString defaultCStringEncoding]]];
    [timeB setStringValue: [NSString stringWithCString:set.timeB.c_str() encoding:[NSString defaultCStringEncoding]]];
    
    NSColor * c =  set.whiteToMove ? NSColor.whiteColor : NSColor.blackColor;
    [colorWell setColor:c];
    [pngView setString: [NSString stringWithCString:set.pngDescription.c_str() encoding:[NSString defaultCStringEncoding]]];
    
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
@end
