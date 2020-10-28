//
//  NSObject+Facade.m
//  Swan
//
//  Created by Mathias Dietrich on 24.10.20.
//

#import "NSObject+Facade.h"
#import "Types.h"

@implementation Facade



-(void) setup{
    UI::of()->setup();
}

-(void) close{
    UI::of()->close();
}

-(void) mouseDown:(int) pos{
    UI::of()->mouseDown(pos);
}

-(void) mouseUp:(int) pos{
    UI::of()->mouseUp(pos);
}

-(void) exec:(ECmd) cmd params:(NSString *) p parami:(int)i{
    UI::of()->exec(cmd, std::string([p UTF8String]),i);
}

-(Set)getSet{
    return UI::of()->getSet();
}
@end
