//
//  KBPreferance.h
//
//  Created by kkm on 2019/4/24.
//  Copyright © 2019 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>

//default password for kbeacon, 16 ascii 0
#define DEFAULT_PASSWORD @"0000000000000000"

NS_ASSUME_NONNULL_BEGIN
@interface KBPreferance : NSObject

+ (instancetype )sharedManager;

//min rssi filter
@property (nonatomic, strong) NSNumber* rssiFilter;

//get beacon password
-(NSString*) getBeaconPassword:(NSString*)identify;

//save beacon password
-(void) saveBeaconPassword:(NSString*)identify pwd:(NSString*)pwd;


@end



NS_ASSUME_NONNULL_END
