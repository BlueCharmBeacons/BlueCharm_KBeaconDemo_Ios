//
//  KBAdvPacketIBeacon.h
//  KBAdvPacketIBeacon
//
//  Created by kkm on 2019/7/17.
//  Copyright © 2019 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KBAdvPacketBase.h"

NS_ASSUME_NONNULL_BEGIN

@interface KBAdvPacketIBeacon : KBAdvPacketBase

//notify: this is not standard iBeacon protocol, we get major ID from KKM private
//scan response message
@property (strong, readonly) NSNumber* majorID;

//get majorID from advertisement packet
//notify: this is not standard iBeacon protocol, we get minor ID from KKM private
//scan response message
@property (strong, readonly) NSNumber* minorID;

@property (strong, readonly) NSString* uuid;

@property (strong, readonly) NSNumber* refTxPower;

-(BOOL) parseAdvPacket:(const NSData*) data;

@end

NS_ASSUME_NONNULL_END
