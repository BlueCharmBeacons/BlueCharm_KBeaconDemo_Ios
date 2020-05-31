//
//  ViewController.h
//  KBeaconDemo
//
//  Created by kkm on 2018/12/7.
//  Copyright © 2018 kkm. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KBeaconLib/KBeaconsMgr.h"
#import "KBeaconLib/KBeacon.h"

@interface ViewController : UIViewController <UISearchBarDelegate, UITableViewDataSource, UITableViewDelegate, KBeaconMgrDelegate, UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UIBarButtonItem *actionButton;

@property (weak, nonatomic) IBOutlet UITableView *beaconsTableView;

@property (weak, nonatomic) IBOutlet UIButton *mFilterActionButton;

@property (weak, nonatomic) IBOutlet UITextField *mFilterSummaryEdit;

@property (weak, nonatomic) IBOutlet UIButton *mRemoveSummaryButton;

@property (weak, nonatomic) IBOutlet UITextField *mFilterNameEdit;

@property (weak, nonatomic) IBOutlet UIView *mFilterView;

@property (weak, nonatomic) IBOutlet UISlider *mRssiFilterSlide;

@property (weak, nonatomic) IBOutlet UILabel *mRssiFilterLabel;

@property (weak, nonatomic) IBOutlet UIButton *mRemoveFilterNameButton;

@property (weak, nonatomic) IBOutlet UIView *mFilterSummaryView;


@end
