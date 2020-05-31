//
//  KBCfgEddyURL.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/28.
//  Copyright © 2019 kkm. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "KBCfgBase.h"

NS_ASSUME_NONNULL_BEGIN

#define JSON_FIELD_EDDY_URL_ADDR @"url"

@interface KBCfgEddyURL : KBCfgBase

@property (strong, nonatomic) NSString* url;

-(int) updateConfig:(NSDictionary*)dicts;

-(NSMutableDictionary*) toDictionary;

@end

NS_ASSUME_NONNULL_END
