//
//  KBAdvPacketEddyTLM.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/17.
//  Copyright © 2019 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KBAdvPacketBase.h"

NS_ASSUME_NONNULL_BEGIN

@interface TLMElapseTime: NSObject
@property (assign) int days;
@property (assign) int hours;
@property (assign) int minutes;
@property (assign) int second;
@end

@interface KBAdvPacketEddyTLM : KBAdvPacketBase

//battery level, uint is mV (not percent)
@property (strong, readonly) NSNumber* batteryLevel;

@property (strong, readonly) NSNumber* temperature;

@property (strong, readonly) NSNumber* advCount;

@property (strong, readonly) NSNumber* secCount;

@property (strong, readonly) NSNumber* tlmType;



-(BOOL) parseAdvPacket:(const NSData*) data;

-(TLMElapseTime*) getElapseTime;


@end

NS_ASSUME_NONNULL_END
