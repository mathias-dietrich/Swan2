//
//  NSController+Controller.m
//  Swan
//
//  Created by Mathias Dietrich on 24.10.20.
//

#import "NSController+Controller.h"

@implementation Controller : NSController

- (IBAction)start:(id)sender{
    [view exec:CMD_START params:@"" parami:0];
}
- (IBAction)flip:(id)sender{
    [view flip];
}
- (IBAction)top:(id)sender{
    [view exec:CMD_TOP params:@"" parami:0];
}

- (IBAction)back:(id)sender{
    [view exec:CMD_BACK params:@"" parami:0];
}
- (IBAction)forward:(id)sender{
    [view exec:CMD_FORWARD params:@"" parami:0];
}
- (IBAction)stop:(id)sender{
    [view exec:CMD_STOP params:@"" parami:0];
}
- (IBAction)end:(id)sender{
    [view exec:CMD_END params:@"" parami:0];
}
- (IBAction)analyze:(id)sender{
    [view exec:CMD_ANALYZE params:@"" parami:0];
}
- (IBAction)hint:(id)sender{
    [view exec:CMD_HINT params:@"" parami:0];
}
- (IBAction)savepng:(id)sender{
    [view exec:CMD_SAVEPNG params:@"" parami:0];
}
- (IBAction)loadpng:(id)sender{
    [view exec:CMD_LOADPNG params:@"" parami:0];
}
- (IBAction)setboard:(id)sender{
    [view exec:CMD_SETBOARD params:@"" parami:0];
}
- (IBAction)resetboard:(id)sender{
    [view exec:CMD_RESETBOARD params:@"" parami:0];
}
- (IBAction)clearboard:(id)sender{
    [view exec:CMD_CLEARBOARD params:@"" parami:0];
}
- (IBAction)settings:(id)sender{
    [view exec:CMD_SETTINGS params:@"" parami:0];
}
- (IBAction)setEngineW:(id)sender{
    [view exec:CMD_SETENGINEW params:@"" parami:0];
}
- (IBAction)setEngineB:(id)sender{
    [view exec:CMD_SETENGINEB params:@"" parami:0];
}
- (IBAction)resign:(id)sender{
    [view exec:CMD_RESIGN params:@"" parami:0];
}
- (IBAction)setfen:(id)sender{
    [view exec:CMD_SETFEN params:@"" parami:0];
}

- (IBAction)setKingW:(id)sender{

}
- (IBAction)setKingB:(id)sender{

}
- (IBAction)setQueenW:(id)sender{

}
- (IBAction)setQueenB:(id)sender{

}
- (IBAction)setRookpW:(id)sender{

}
- (IBAction)setRookpB:(id)sender{

}
- (IBAction)setKnightW:(id)sender{

}
- (IBAction)setKnightB:(id)sender{

}
- (IBAction)setBishopW:(id)sender{

}
- (IBAction)setBishopB:(id)sender{

}
- (IBAction)setPawnW:(id)sender{

}
- (IBAction)setPawnB:(id)sender{

}

@end
