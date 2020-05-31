//
//  BeaconDevice.h
//  ESLConfig
//
//  Created by kkm on 2018/12/8.
//  Copyright © 2018 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreBluetooth/CBService.h>
#import "KBAdvPacketBase.h"
#import "KBAuthHandler.h"
#import "KBCfgCommon.h"
#import "KBCfgIBeacon.h"
#import "KBCfgEddyUID.h"
#import "KBCfgEddyURL.h"
#import "KBCfgSensor.h"
#import "KBException.h"


NS_ASSUME_NONNULL_BEGIN

//connect status
typedef NS_ENUM(NSInteger, KBConnState)
{
    KBStateDisconnected = 0,
    KBStateConnecting,
    KBStateDisconnecting,
    KBStateConnected
}NS_ENUM_AVAILABLE(8_13, 8_0);

//connection event
typedef NS_ENUM(NSInteger, KBConnEvtReason)
{
    KBEvtConnSuccess = 0,
    KBEvtConnTimeout,
    KBEvtConnException,
    KBEvtConnServiceNotSupport,
    KBEvtConnManualDisconnting,
    KBEvtConnAuthFail,
}NS_ENUM_AVAILABLE(8_13, 8_0);


@class KBeacon;
@protocol ConnStateDelegate<NSObject>
-(void)onConnStateChange:(KBeacon*)beacon state:(KBConnState)state evt:(KBConnEvtReason)evt;
@end

//read config data callback
typedef void (^onReadComplete)(BOOL bConfigSuccess, NSDictionary* __nullable readPara, NSError* _Nullable  error);

//action complete
typedef void (^onActionComplete)(BOOL bConfigSuccess, NSError* error);

//declare
@class KBeaconsMgr;
@class KBAdvPacketBase;

//beacon device
@interface KBeacon : NSObject<CBPeripheralDelegate, KBAuthDelegate>

@property(nonatomic,weak)id<ConnStateDelegate> delegate;

//adv information
@property (strong, readonly) NSString* mac;

@property (strong, readonly) NSString* UUIDString;

@property (assign, readonly) BOOL isConnectable;

@property (strong, readonly) NSString* name;

@property (strong, readonly) NSNumber* rssi;

@property (strong, readonly) NSNumber* batteryPercent;

//device state
@property (assign, readonly) KBConnState state;

///////////////////////////////////////
//all adv packets
@property (weak, readonly) NSArray* allAdvPackets;

//get advitisement packet by type
-(KBAdvPacketBase*)getAdvPacketByType:(KBAdvType) advType;


//////////////////////////////configuration about beacon
@property(weak, readonly)NSNumber* maxTxPower;

@property(weak, readonly)NSNumber* minTxPower;

@property (strong, readonly) NSString* model;

@property (strong, readonly) NSString* version;

@property (strong, readonly) NSNumber* capibility;

//all configruation paramaters
@property (weak, readonly) NSArray* configParamaters;

//get configruation by type
-(KBCfgBase*)getConfigruationByType:(KBConfigType)type;

//////////////////////////////////////////////
-(id) initWithUUID:(NSString*)uuidString;

-(BOOL) connect:(NSString*)password timeout:(NSUInteger)timeout;

-(void) disconnect;

//config beacon paramaters
-(void) modifyConfig:(NSArray<KBCfgBase*>*) cfgPara callback:(onActionComplete)callback;

//read config 
-(void) readConfig:(int) nConfigType callback:(onReadComplete)callback;

//send commond
-(void) sendCommand:(NSDictionary*) cmdPara callback:(onActionComplete)callback;


/////////////////////////////////////////
-(void)attach2Device:(CBPeripheral*) peripheral beaconMgr:(KBeaconsMgr*) beaconMgr;

-(BOOL) parseAdvPacket:(NSDictionary*) advData rssi:(NSNumber*)rssi;

-(void) handleCentralBLEEvent:(CBPeripheralState)nNewState;


@end

NS_ASSUME_NONNULL_END
