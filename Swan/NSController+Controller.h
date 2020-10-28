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


@end

NS_ASSUME_NONNULL_END
