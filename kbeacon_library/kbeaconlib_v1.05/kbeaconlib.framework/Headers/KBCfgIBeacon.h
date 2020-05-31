//
//  KBIBeaconCfg.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/28.
//  Copyright © 2019 kkm. All rights reserved.
//

#import "KBCfgBase.h"

NS_ASSUME_NONNULL_BEGIN

#define JSON_FIELD_IBEACON_UUID @"uuid"
#define JSON_FIELD_IBEACON_MAJORID @"majorID"
#define JSON_FIELD_IBEACON_MINORID @"minorID"

@interface KBCfgIBeacon : KBCfgBase

@property (strong, nonatomic) NSNumber* majorID;

@property (strong, nonatomic) NSNumber* minorID;

@property (strong, nonatomic) NSString* uuid;

-(int) updateConfig:(NSDictionary*)dicts;

-(NSMutableDictionary*) toDictionary;

@end

NS_ASSUME_NONNULL_END
