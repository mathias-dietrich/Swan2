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

@interface FieldView : NSView{
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
}

- (void)flip;
- (void)initalize;
- (NSImage *)imageResize:(NSImage*)anImage newSize:(NSSize)newSize;
- (void)drawRect:(NSRect)dirtyRect;
- (void) exec:(ECmd) cmd param:(NSString *) p;

@end


NS_ASSUME_NONNULL_END
