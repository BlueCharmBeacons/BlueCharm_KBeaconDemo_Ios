//
//  KBCfgHandler.h
//  KBeaconConfig
//
//  Created by hogen on 2019/9/10.
//  Copyright © 2019 hogen. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KBCfgBase.h"
#import "KBCfgCommon.h"
#import "KBCfgIBeacon.h"
#import "KBCfgEddyURL.h"
#import "KBCfgEddyUID.h"
#import "KBCfgSensor.h"


NS_ASSUME_NONNULL_BEGIN

@interface KBCfgHandler : NSObject

//configruation paramaters
@property (strong, readonly) NSArray* configParamaters;

//get configuration by type
-(KBCfgBase*)getConfigruationByType:(KBConfigType)type;

//init configruation fro dictornary
-(void)initConfigFromJsonDicts:(NSDictionary*) dictPara;

//update configruation from object
-(void)updateConfig:(NSArray<KBCfgBase*>*)newCfgArray;

//parse configruation objects to string
+(NSString*)objectsToJsonString:(NSArray<KBCfgBase*>*)cfgArray error:(NSError**)error;

//parse command para to string
+(NSString*)cmdParaToJsonString:(NSDictionary*)paraDicts error:(NSError**)error;

@end

NS_ASSUME_NONNULL_END
