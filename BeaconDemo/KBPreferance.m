//
//  KBPreferance.m
//
//  Created by kkm on 2019/4/24.
//  Copyright © 2019 kkm. All rights reserved.
//

#import "KBPreferance.h"

#define MIN_RSSI_FILTER_KEY @"minRssi"
#define BEACON_PWD_KEY_PREFX @"beaconPwd"


@implementation KBPreferance
{
    NSUserDefaults* mUserPref;
}


+ (instancetype )sharedManager
{
    static KBPreferance * sharedMgr = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{
        sharedMgr = [[self alloc] init];
    });
    return sharedMgr;
}

-(id) init
{
    self = [super init];
    
    mUserPref = [NSUserDefaults standardUserDefaults];
    
    return self;
}

//rssi filter
-(NSNumber*) rssiFilter
{
    NSNumber* minRssi = [NSNumber numberWithInteger:-100];
    if ([mUserPref valueForKey:MIN_RSSI_FILTER_KEY]){
        minRssi = [mUserPref objectForKey:MIN_RSSI_FILTER_KEY];
    }
    
    return minRssi;
}

//set rssi filter
-(void)setrssiFilter:(NSNumber*)minRssi
{
    [mUserPref setObject: minRssi forKey:MIN_RSSI_FILTER_KEY];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

//save beacon password
-(void) saveBeaconPassword:(NSString*)identify pwd:(NSString*)pwd
{
    NSString* keyTemp = [identify lowercaseString];
    
    [mUserPref setObject: pwd forKey:[NSString stringWithFormat:@"%@%@",BEACON_PWD_KEY_PREFX, keyTemp]];
    [[NSUserDefaults standardUserDefaults] synchronize];
}


//get beacon password
 -(NSString*) getBeaconPassword:(NSString*)identify
{
    NSString* strPassword = DEFAULT_PASSWORD;
    
    NSString* keyTemp = [identify lowercaseString];
    NSString* strKey = [NSString stringWithFormat:@"%@%@",BEACON_PWD_KEY_PREFX, keyTemp];
    if ([mUserPref stringForKey:strKey] != nil)
    {
        strPassword = [mUserPref stringForKey:strKey];
    }
    
    return strPassword;
}

@end
