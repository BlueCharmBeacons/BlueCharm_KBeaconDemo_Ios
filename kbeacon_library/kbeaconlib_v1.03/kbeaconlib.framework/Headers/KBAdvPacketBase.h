//
//  KBeaconAdvertisement.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/17.
//  Copyright © 2019 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KBUtility.h"

NS_ASSUME_NONNULL_BEGIN

//beacon av type
typedef NS_ENUM(NSInteger, KBAdvType)
{
    KBAdvTypeSensor = 0x1,
    KBAdvTypeEddyUID = 0x2,
    KBAdvTypeIBeacon = 0x4,
    KBAdvTypeEddyTLM = 0x8,
    KBAdvTypeEddyURL = 0x10,
    KBAdvTypeInvalid = 0x80,
} NS_ENUM_AVAILABLE(8_13, 8_0);

#define KBAdvTypeSensorString  @"KSensor"
#define KBAdvTypeEddyUIDString  @"UID"
#define KBAdvTypeIBeaconString  @"iBeacon"
#define KBAdvTypeEddyTLMString  @"TLM"
#define KBAdvTypeEddyURLString  @"URL"
#define KBAdvTypeInvalidString  @"invalid"


@interface KBAdvPacketBase : NSObject

@property (strong, readonly) NSString* name;

@property (strong, readonly) NSNumber* rssi;

@property (assign, readonly) NSNumber* connectable;

@property (assign, nonatomic, readonly) NSTimeInterval lastReceiveTime;

-(BOOL) parseAdvPacket:(const NSData*) data;

@property (assign, readonly) KBAdvType advType;

//update common info
-(void) updateBasicInfo:(NSString*)name rssi:(NSNumber*)rssi connectable:(NSNumber*)isConnect;

@end

NS_ASSUME_NONNULL_END
