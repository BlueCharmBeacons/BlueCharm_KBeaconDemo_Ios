//
//  KBAuthHandler.h
//  KBeaconConfig
//
//  Created by kkm on 2019/7/28.
//  Copyright © 2019 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, KBAuthResult)
{
    KBAuthFailed,
    KBAuthSuccess,
}NS_ENUM_AVAILABLE(8_13, 8_0);

//auth delegation
@protocol KBAuthDelegate<NSObject>

-(void)authStateChange:(KBAuthResult)authRslt;

-(void)writeAuthData:(NSData*)data;
@end


@interface KBAuthHandler : NSObject

@property(nonatomic,weak)id<KBAuthDelegate> delegate;

@property(strong, readonly) NSNumber* mtuSize;

//send auth request
-(BOOL) authSendMd5Request:(NSString*)macAddress password:(NSString*)password;

//handle auth response
-(void) authHandleResponse:(Byte*)byRcvNtfValue lenght:(int)authDataLen;

@end

NS_ASSUME_NONNULL_END
