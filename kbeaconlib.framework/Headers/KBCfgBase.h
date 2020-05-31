//
//  KBAdvCfg.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/28.
//  Copyright © 2019 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KBUtility.h"

NS_ASSUME_NONNULL_BEGIN

#define JSON_MSG_TYPE_KEY @"msg"
#define JSON_MSG_TYPE_CFG @"cfg"
#define JSON_MSG_TYPE_GET_PARA @"getPara"
#define JSON_MSG_CFG_SUBTYPE @"stype"



#define MAX_NAME_LENGTH 18

//config adv type
typedef NS_ENUM(NSInteger, KBConfigType)
{
    KBConfigTypeCommon = 0x20,
    KBConfigTypeIBeacon = 0x4,
    KBConfigTypeEddyURL = 0x10,
    KBConfigTypeEddyUID = 0x2,
    KBConfigTypeSensor = 0x1,
    KBConfigTypeTrigger = 0x40,
    KBConfigTypeInvalid = 255,
}NS_ENUM_AVAILABLE(8_13, 8_0);


@interface KBCfgBase : NSObject

@property (nonatomic, assign, readonly)KBConfigType cfgParaType;

-(int) updateConfig:(NSDictionary*)dicts;

-(NSMutableDictionary*) toDictionary;

@end

NS_ASSUME_NONNULL_END
