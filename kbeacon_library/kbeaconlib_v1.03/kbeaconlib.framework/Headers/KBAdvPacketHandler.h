//
//  KBAdvPacketHandler.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/22.
//  Copyright © 2019 kkm. All rights reserved.
//

#import "KBAdvPacketBase.h"

NS_ASSUME_NONNULL_BEGIN

@interface KBAdvPacketHandler : NSObject

//get adv packet by type
-(KBAdvPacketBase*)getAdvPacket:(KBAdvType) advType;

@property (strong, readonly) NSNumber* batteryPercent;


//beacon all received adv packets
@property (strong, readonly) NSArray* advPackets;

-(BOOL) parseAdvPacket:(NSDictionary*) advData rssi:(NSNumber*)rssi;

@end

NS_ASSUME_NONNULL_END
