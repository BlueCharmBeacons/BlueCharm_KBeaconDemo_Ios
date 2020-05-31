//
//  KBAdvPacketSensor.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/22.
//  Copyright © 2019 kkm. All rights reserved.
//

#import "KBAdvPacketBase.h"

NS_ASSUME_NONNULL_BEGIN

@interface KBAccSensorValue : NSObject
@property (strong) NSNumber* xAis;
@property (strong) NSNumber* yAis;
@property (strong) NSNumber* zAis;
@end

@interface KBAdvPacketSensor : KBAdvPacketBase

@property (strong, readonly) KBAccSensorValue* accSensor;

@property (assign, readonly) NSNumber* temperature;

@property (assign, readonly) NSNumber* humidity;

@property (assign, readonly) NSNumber* version;

@property (assign, readonly) NSNumber* batteryLevel;

-(BOOL) parseAdvPacket:(const NSData*) data;

@end

NS_ASSUME_NONNULL_END
