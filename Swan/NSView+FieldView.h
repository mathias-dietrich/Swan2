//
//  NSView+FieldView.h
//  Swan
//
//  Created by Mathias Dietrich on 24.10.20.
//

#import <Cocoa/Cocoa.h>
#include <stdio.h>

#include "Types.h"
#import "NSObject+Facade.h"

NS_ASSUME_NONNULL_BEGIN

@interface FieldView : NSView <NSComboBoxDelegate>{
    
    IBOutlet NSComboBox * drpEngine0;
    IBOutlet NSComboBox * drpEngine1;
    IBOutlet NSComboBox * drpGame;
    
    IBOutlet NSButton * btnKingW;
    IBOutlet NSButton * btnQueenW;
    IBOutlet NSButton * btnRookW;
    IBOutlet NSButton * btnBishopW;
    IBOutlet NSButton * btnKnightW;
    IBOutlet NSButton * btnPawnW;
    
    IBOutlet NSButton * btnKingB;
    IBOutlet NSButton * btnQueenB;
    IBOutlet NSButton * btnRookB;
    IBOutlet NSButton * btnBishopB;
    IBOutlet NSButton * btnKnightB;
    IBOutlet NSButton * btnPawnB;
    
    IBOutlet  NSTextField * fenField;
    IBOutlet  NSTextField * timeW;
    IBOutlet  NSTextField * timeB;
    IBOutlet  NSColorWell * colorWell;
    
    IBOutlet  NSTextView * pngView;
    
    NSTimer * _timer;
    NSImage *wBishop;
    NSImage *wRook;
    NSImage *WKnight;
    NSImage *wKing;
    NSImage *wQueen;
    NSImage *wPawn;

    NSImage *bBishop;
    NSImage *bRook;
    NSImage *bKnight;
    NSImage *bKing;
    NSImage *bQueen;
    NSImage *bPawn;
    
    bool isInit;
    bool isFliped;
    NSColor *myColor;
    int BORDER;
    NSDictionary *attributes;
    NSDictionary *attributesSmall;
    
    Facade * facade;
    
    Set set;
}

- (void)flip;
- (void)initalize;
- (NSImage *)imageResize:(NSImage*)anImage newSize:(NSSize)newSize;
- (void)drawRect:(NSRect)dirtyRect;
- (void) exec:(ECmd) cmd param:(NSString *) p;

- (void)disablePieceSelection;
- (void)enablePieceSelection;
- (void)enableWhitePromotion;
- (void)enableBlackPromotion;

- (void)comboBoxSelectionDidChange:(NSNotification *)notification;
@end


NS_ASSUME_NONNULL_END
