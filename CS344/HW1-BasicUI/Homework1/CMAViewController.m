//
//  CMAViewController.m
//  Homework1
//
//  Created by Cohen Adair on 9/5/14.
//  Copyright (c) 2014 Cohen Adair. All rights reserved.
//

#import "CMAViewController.h"

@interface CMAViewController ()

@property (weak, nonatomic) IBOutlet UILabel *labelText;

@end

@implementation CMAViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)clicked:(id)sender {
    if ([self.labelText.text isEqual: @"Goodbye"])
        self.labelText.text = @"Hello";
    else if ([self.labelText.text isEqual: @"Hello"])
        self.labelText.text = @"Goodbye";
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
