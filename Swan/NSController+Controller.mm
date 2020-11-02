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
    [view exec:CMD_SETKW params:@"" parami:0];
}
- (IBAction)setKingB:(id)sender{
    [view exec:CMD_SETKB params:@"" parami:0];
}
- (IBAction)setQueenW:(id)sender{
    [view exec:CMD_SETQW params:@"" parami:0];
}
- (IBAction)setQueenB:(id)sender{
    [view exec:CMD_SETQB params:@"" parami:0];
}
- (IBAction)setRookpW:(id)sender{
    [view exec:CMD_SETRW params:@"" parami:0];
}
- (IBAction)setRookpB:(id)sender{
    [view exec:CMD_SETRB params:@"" parami:0];
}
- (IBAction)setKnightW:(id)sender{
    [view exec:CMD_SETNW params:@"" parami:0];
}
- (IBAction)setKnightB:(id)sender{
    [view exec:CMD_SETNB params:@"" parami:0];
}
- (IBAction)setBishopW:(id)sender{
    [view exec:CMD_SETBW params:@"" parami:0];
}
- (IBAction)setBishopB:(id)sender{
    [view exec:CMD_SETBB params:@"" parami:0];
}
- (IBAction)setPawnW:(id)sender{
    [view exec:CMD_SETPW params:@"" parami:0];
}
- (IBAction)setPawnB:(id)sender{
    [view exec:CMD_SETPB params:@"" parami:0];
}

@end
