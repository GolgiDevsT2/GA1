//
//  ViewController.m
//  GA1
//
//  Created by Brian Kelly on 4/21/15.
//  Copyright (c) 2015 Golgi. All rights reserved.
//

#import "ViewController.h"
#import "GA1SvcWrapper.h"


@interface ViewController ()

@end

@implementation ViewController
@synthesize bulbButton;
@synthesize bulbOn;

-(IBAction) bulpPressed:(id)sender
{
    NSLog(@"Button Pressed");
    
    bulbButton.enabled = false;
    
    [GA1Svc sendSetLEDUsingResultHandler:^(GA1SetLEDExceptionBundle *bundle) {
        if(bundle == nil){
            NSLog(@"Success");
            bulbOn = !bulbOn;
            NSString *fname = (bulbOn ? @"bulb-on.jpg" : @"bulb-off.jpg");
            UIImage *img = [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:fname ofType:nil]];
            [bulbButton setImage:img forState:UIControlStateNormal];
            bulbButton.enabled = true;
        }
        else{
            NSLog(@"Fail");
        }
    } andDestination:@"HW" withState:(bulbOn ? 0 : 1)];
    
    
}


- (void)viewDidLoad {
    [super viewDidLoad];
    bulbOn = false;
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
