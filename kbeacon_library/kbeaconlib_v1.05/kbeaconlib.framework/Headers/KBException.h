//
//  KBException.h
//  KBeaconConfig
//
//  Created by hogen on 2019/10/3.
//  Copyright © 2019 hogen. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, KBErrorCode)
{
    KBEvtCfgBusy = 0x1,
    KBEvtCfgFailed = 0x2,
    KBEvtCfgTimeout = 0x3,
    KBEvtCfgInputInvalid = 0x4,
    KBEvtCfgReadNull = 0x5,
    KBEvtCfgStateError = 0x6,
    KBEvtCfgNoParameters = 0x7,
    KBEvtCfgNotSupport = 0x8
}NS_ENUM_AVAILABLE(8_13, 8_0);

@interface KBException : NSException

@property (assign, readonly) NSInteger errorCode;
    
-(id) init:(NSInteger)code info:(NSString*)info;

@end

NS_ASSUME_NONNULL_END
