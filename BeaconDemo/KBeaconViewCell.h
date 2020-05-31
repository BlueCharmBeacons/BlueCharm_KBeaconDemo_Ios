//
//  KBeaconViewCell.h
//  KBeaconDemo
//
//  Created by kkm on 2018/12/8.
//  Copyright © 2018 kkm. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KBeaconLib/KBeacon.h"

NS_ASSUME_NONNULL_BEGIN

@interface KBeaconViewCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *deviceNameLabel;

@property (weak, nonatomic) IBOutlet UILabel *rssiLabel;

@property (weak, nonatomic) IBOutlet UILabel *voltageLabel;

@property (weak, nonatomic) IBOutlet UILabel *connectableLabel;

@property (weak, nonatomic) IBOutlet UILabel *macLabel;

@property (weak, nonatomic) IBOutlet UILabel *uuidLabel;

@property (weak, nonatomic) IBOutlet UILabel *majorLabel;

@property (weak, nonatomic) IBOutlet UILabel *minorLabel;

@property (weak, nonatomic) KBeacon *beacon;

@end

NS_ASSUME_NONNULL_END
