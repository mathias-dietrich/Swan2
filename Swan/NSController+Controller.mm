//
//  NSController+Controller.m
//  Swan
//
//  Created by Mathias Dietrich on 24.10.20.
//

#import "NSController+Controller.h"

@implementation Controller : NSController


- (IBAction)start:(id)sender{
    [view exec:CMD_START param:@""];
}
- (IBAction)flip:(id)sender{
    [view flip];
}
- (IBAction)top:(id)sender{
    [view exec:CMD_TOP param:@""];
}

- (IBAction)back:(id)sender{
    [view exec:CMD_BACK param:@""];
}
- (IBAction)forward:(id)sender{
    [view exec:CMD_FORWARD param:@""];
}
- (IBAction)stop:(id)sender{
    [view exec:CMD_STOP param:@""];
}
- (IBAction)end:(id)sender{
    [view exec:CMD_END param:@""];
}
- (IBAction)analyze:(id)sender{
    [view exec:CMD_ANALYZE param:@""];
}
- (IBAction)hint:(id)sender{
    [view exec:CMD_HINT param:@""];
}
- (IBAction)savepng:(id)sender{
    [view exec:CMD_SAVEPNG param:@""];
}
- (IBAction)loadpng:(id)sender{
    [view exec:CMD_LOADPNG param:@""];
}
- (IBAction)setboard:(id)sender{
    [view exec:CMD_SETBOARD param:@""];
}
- (IBAction)resetboard:(id)sender{
    [view exec:CMD_RESETBOARD param:@""];
}
- (IBAction)clearboard:(id)sender{
    [view exec:CMD_CLEARBOARD param:@""];
}
- (IBAction)settings:(id)sender{
    [view exec:CMD_SETTINGS param:@""];
}
- (IBAction)setEngineW:(id)sender{
    [view exec:CMD_SETENGINEW param:@""];
}
- (IBAction)setEngineB:(id)sender{
    [view exec:CMD_SETENGINEB param:@""];
}
- (IBAction)resign:(id)sender{
    [view exec:CMD_RESIGN param:@""];
}
- (IBAction)setfen:(id)sender{
    [view exec:CMD_SETFEN param:@""];
}
@end
