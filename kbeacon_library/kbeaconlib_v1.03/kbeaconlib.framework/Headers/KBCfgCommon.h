//
//  KBCfgCommon.h
//  KBeaconConfig
//
//  Created by hogen on 2019/8/25.
//  Copyright © 2019 hogen. All rights reserved.
//

#import "KBCfgBase.h"

NS_ASSUME_NONNULL_BEGIN

#define KB_CAPIBILITY_KEY 0x1
#define KB_CAPIBILITY_BEEP 0x2
#define KB_CAPIBILITY_ACC 0x4
#define KB_CAPIBILITY_TEMP 0x8
#define KB_CAPIBILITY_HUMIDITY 0x10
#define KB_CAPIBILITY_EDDY 0x20

#define JSON_FIELD_BEACON_MODLE @"modle"
#define JSON_FIELD_BEACON_VER @"ver"
#define JSON_FIELD_DEV_NAME @"devName"
#define JSON_FIELD_ADV_PERIOD @"advPrd"
#define JSON_FIELD_TX_PWR @"txPwr"
#define JSON_FIELD_MIN_TX_PWR @"minPwr"
#define JSON_FIELD_MAX_TX_PWR @"maxPwr"

#define JSON_FIELD_BASIC_CAPIBILITY @"bCap"
#define JSON_FIELD_TRIG_CAPIBILITY @"trCap"

#define JSON_FIELD_PWD @"pwd"
#define JSON_FIELD_MEA_PWR @"meaPwr"

#define JSON_FIELD_BEACON_TYPE @"type"

#define JSON_FIELD_ADV_FLAG @"advFlag"

@interface KBCfgCommon : KBCfgBase

//basic capiblity
@property (strong, readonly) NSNumber* basicCapibility;

@property (strong, readonly) NSNumber* trigCapibility;

@property (strong, readonly) NSNumber* actionCapibility;

@property (strong, readonly) NSNumber* maxTxPower;

@property (strong, readonly) NSNumber* minTxPower;

@property (strong, readonly) NSString* model;

@property (strong, readonly) NSString* version;

@property (strong, readonly)NSString* advTypeString;

////////////////////can be configruation able///////////////////////
@property (strong, nonatomic) NSNumber* txPower;

@property (strong, nonatomic) NSNumber* refPower1Meters;

@property (strong, nonatomic) NSNumber* advPeriod;

@property (strong, nonatomic) NSString* password;

@property (strong, nonatomic) NSString* name;

@property (strong, nonatomic) NSNumber* advType; //beacon type (iBeacon, Eddy TLM/UID/ etc.,)

@property (strong, nonatomic) NSNumber* autoAdvAfterPowerOn; //beacon automatic start advertisement after powen on

@property (strong, nonatomic) NSNumber* advConnectable; //is beacon can be connectable

////////////////////////method
-(int) updateConfig:(NSDictionary*)dicts;

-(NSMutableDictionary*) toDictionary;

//get adv type stirng
+(NSString*) getAdvTypeString:(NSNumber*)nAdvType;

//is the device support iBeacon
-(BOOL) isSupportIBeacon;

//is the device support URL
-(BOOL) isSupportEddyURL;

//is the device support TLM
-(BOOL)isSupportEddyTLM;

//is the device support UID
-(BOOL) isSupportEddyUID;

//support kb sensor
-(BOOL) isSupportKBSensor;

//is support button
-(BOOL) isSupportButton;

//is support beep
-(BOOL) isSupportBeep;

//is support acc sensor
-(BOOL) isSupportAccSensor;

//is support humidity sensor
-(BOOL) isSupportHumiditySensor;

@end

NS_ASSUME_NONNULL_END
