//
//  KBCfgEddyUID.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/28.
//  Copyright © 2019 kkm. All rights reserved.
//

#import "KBCfgBase.h"

NS_ASSUME_NONNULL_BEGIN

#define JSON_FIELD_EDDY_UID_NID @"nid"
#define JSON_FIELD_EDDY_UID_SID @"sid"

@interface KBCfgEddyUID : KBCfgBase

@property (strong, nonatomic) NSString* nid;

@property (strong, nonatomic) NSString* sid;

-(int) updateConfig:(NSDictionary*)dicts;

-(NSMutableDictionary*) toDictionary;

@end

NS_ASSUME_NONNULL_END
