//
//  KBCfgSensor.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/29.
//  Copyright © 2019 kkm. All rights reserved.
//

#import "KBCfgBase.h"

NS_ASSUME_NONNULL_BEGIN

#define JSON_FIELD_SENSOR_TYPE @"sensor"

#define SENSOR_TYPE_ACC_POSITION @"acc"


//beacon av type
typedef NS_ENUM(NSInteger, KBSensorType)
{
    KBSensorTypeDisable = 0x0,
    KBSensorTypeAcc = 0x1,
    KBSensorTypeHumidity = 0x2
} NS_ENUM_AVAILABLE(8_13, 8_0);

typedef NS_ENUM(NSInteger, KBSensorTriggerEvt)
{
    KBTrigEvtMotion = 0,
}NS_ENUM_AVAILABLE(8_13, 8_0);

typedef NS_ENUM(NSInteger, KBTriggerAction)
{
    KBTrigActAdvtisement = 0,
    KBTrigActAlarm,
}NS_ENUM_AVAILABLE(8_13, 8_0);


@interface KBCfgSensor : KBCfgBase

@property (strong, nonatomic) NSNumber* sensorType;

-(int) updateConfig:(NSDictionary*)dicts;

-(NSMutableDictionary*) toDictionary;

+(NSString*)getSensorTypeString:(NSNumber*) nSensorType;

@end

NS_ASSUME_NONNULL_END
