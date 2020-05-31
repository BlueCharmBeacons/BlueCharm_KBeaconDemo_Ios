//
//  KBAdvEddyURL.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/17.
//  Copyright © 2019 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KBAdvPacketBase.h"

NS_ASSUME_NONNULL_BEGIN

@interface KBAdvPacketEddyURL : KBAdvPacketBase

//eddy url address
@property (strong, readonly) NSString* url;

//tx power at 0 cent-meter
@property (strong, readonly) NSNumber* refTxPower;

-(BOOL) parseAdvPacket:(const NSData*) data;

//encode url address to advertisement content
+(Byte) encodeURL:(char*)urlOrg urlEnc:(char*)urlEnc;

//decode advertisement content to url address
+(int)decodeURL:(char*) urlOrg len:(int)nSrcLength urlDec:(char*) urlDec;

@end

NS_ASSUME_NONNULL_END
