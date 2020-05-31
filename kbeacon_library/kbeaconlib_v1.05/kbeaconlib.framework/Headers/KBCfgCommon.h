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

#define MIN_TLM_INTERVAL 2
#define MAX_TLM_INTERVAL 100

#define JSON_FIELD_BEACON_MODLE @"modle"
#define JSON_FIELD_BEACON_VER @"ver"
#define JSON_FIELD_DEV_NAME @"devName"
#define JSON_FIELD_ADV_PERIOD @"advPrd"
#define JSON_FIELD_TLM_ADV_INTERVAL @"tlmItvl"

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

//trigger capibility
@property (strong, readonly) NSNumber* trigCapibility;

//supported max tx power
@property (strong, readonly) NSNumber* maxTxPower;

//supported min tx power
@property (strong, readonly) NSNumber* minTxPower;

//device model
@property (strong, readonly) NSString* model;

//device firmware version
@property (strong, readonly) NSString* version;

//adv type string
@property (strong, readonly)NSString* advTypeString;

////////////////////can be configruation able///////////////////////
//tx power
@property (strong, nonatomic) NSNumber* txPower;

//referance rx power at 1 meters
@property (strong, nonatomic) NSNumber* refPower1Meters;

//advertisement period
@property (strong, nonatomic) NSNumber* advPeriod;

//device name
@property (strong, nonatomic) NSString* name;

//beacon type (iBeacon, Eddy TLM/UID/ etc.,)
@property (strong, nonatomic) NSNumber* advType;

//device password, the password length must >= 8 bytes and <= 16 bytes
//Be sure to remember your new password, you won’t be able to connect to the device if you forget the password.
@property (strong, nonatomic) NSString* password;

//beacon always advertisement if it has battery
//If autoAdvAfterPowerOn set to enable, the device will not allowed power off.
//If autoAdvAfterPowerOn set to disable, the beacon will power off if long press button for 5 seconds.
@property (strong, nonatomic) NSNumber* autoAdvAfterPowerOn;

//is beacon advertisement can be connectable
//Warning: if the app set the KBeacon to un-connectable, the app can not connect to it if it does not has button.
//If the device has button, the device can enter connect-able advertisement for 60 seconds when click on the button
@property (strong, nonatomic) NSNumber* advConnectable;

//eddystone TLM advertisement interval
@property (strong, nonatomic) NSNumber* tlmAdvInterval;

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
