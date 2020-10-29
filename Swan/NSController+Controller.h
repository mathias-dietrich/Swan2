//
//  NSController+Controller.h
//  Swan
//
//  Created by Mathias Dietrich on 24.10.20.
//

#import <Cocoa/Cocoa.h>
#import "NSView+FieldView.h"

NS_ASSUME_NONNULL_BEGIN

@interface Controller: NSController{
    
    IBOutlet  FieldView * view;
}

- (IBAction)flip:(id)sender;
- (IBAction)top:(id)sender;
- (IBAction)back:(id)sender;
- (IBAction)forward:(id)sender;
- (IBAction)stop:(id)sender;
- (IBAction)end:(id)sender;
- (IBAction)analyze:(id)sender;
- (IBAction)hint:(id)sender;
- (IBAction)savepng:(id)sender;
- (IBAction)loadpng:(id)sender;
- (IBAction)setboard:(id)sender;
- (IBAction)resetboard:(id)sender;
- (IBAction)clearboard:(id)sender;
- (IBAction)settings:(id)sender;
- (IBAction)setEngineW:(id)sender;
- (IBAction)setEngineB:(id)sender;
- (IBAction)resign:(id)sender;
- (IBAction)setfen:(id)sender;
- (IBAction)start:(id)sender;

- (IBAction)setKingW:(id)sender;
- (IBAction)setKingB:(id)sender;
- (IBAction)setQueenW:(id)sender;
- (IBAction)setQueenB:(id)sender;
- (IBAction)setRookpW:(id)sender;
- (IBAction)setRookpB:(id)sender;
- (IBAction)setKnightW:(id)sender;
- (IBAction)setKnightB:(id)sender;
- (IBAction)setBishopW:(id)sender;
- (IBAction)setBishopB:(id)sender;
- (IBAction)setPawnW:(id)sender;
- (IBAction)setPawnB:(id)sender;

- (void)call:(NSString*)b;

@end

NS_ASSUME_NONNULL_END
