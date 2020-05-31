//
//  DeviceViewController.h
//  KBeaconDemo
//
//  Created by kkm on 2018/12/9.
//  Copyright © 2018 kkm. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "kbeaconlib/KBeacon.h"

NS_ASSUME_NONNULL_BEGIN

@interface DeviceViewController : UIViewController<ConnStateDelegate, UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UIBarButtonItem *actionConnect;

@property (weak, nonatomic) IBOutlet UILabel *labelModel;

@property (weak, nonatomic) IBOutlet UILabel *labelVersion;

@property (weak, nonatomic) IBOutlet UITextField *txtName;

@property (weak, nonatomic) IBOutlet UITextField *txtTxPower;

@property (weak, nonatomic) IBOutlet UITextField *txtAdvPeriod;

@property (weak, nonatomic) IBOutlet UITextField *txtBeaconUUID;

@property (weak, nonatomic) IBOutlet UITextField *txtBeaconMajor;

@property (weak, nonatomic) IBOutlet UITextField *txtBeaconMinor;

@property (weak, nonatomic) IBOutlet UITextView *txtBeaconStatus;

@property (weak, nonatomic) IBOutlet UILabel *labelBeaconType;

@property (weak, nonatomic) IBOutlet UIButton *mDownCfgBtn;

@property (weak, nonatomic) IBOutlet UIButton *mBtnConfigTest;

@property (weak, nonatomic) KBeacon* beacon;

@end

NS_ASSUME_NONNULL_END
