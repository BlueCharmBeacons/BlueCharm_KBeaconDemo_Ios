//
//  KBAdvEddyUID.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/17.
//  Copyright © 2019 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KBAdvPacketBase.h"

NS_ASSUME_NONNULL_BEGIN

@interface KBAdvPacketEddyUID : KBAdvPacketBase

//eddy nid
@property (strong, readonly) NSString* nid;

//eddy sid
@property (strong, readonly) NSString* sid;

//tx power at 0 cent-meter
@property (strong, readonly) NSNumber* refTxPower;

-(BOOL) parseAdvPacket:(const NSData*) data;

@end

NS_ASSUME_NONNULL_END
