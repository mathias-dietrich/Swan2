//
//  NSObject+Facade.h
//  Swan
//
//  Created by Mathias Dietrich on 24.10.20.
//

#import <Foundation/Foundation.h>
#include "Types.h"
#include "UI.h"

NS_ASSUME_NONNULL_BEGIN

@interface Facade : NSObject

-(void) setup;
-(void) close;

-(Set)getSet;
-(void) exec:(ECmd) cmd params:(NSString *) p parami:(int)i;

-(void) mouseDown:(int) pos;
-(void) mouseUp:(int) pos;

@end

NS_ASSUME_NONNULL_END
