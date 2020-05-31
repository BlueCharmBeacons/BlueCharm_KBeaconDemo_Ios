//
//  KBeaconsMgr.h
//
//  Created by kkm on 2018/12/10.
//  Copyright © 2018 kkm. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <CoreBluetooth/CBService.h>
#import "KBUtility.h"

NS_ASSUME_NONNULL_BEGIN

#define SCAN_ERROR_BLE_NOT_ENABLE 0x2
#define SCAN_ERROR_NO_PERMISSION 0x1
#define SCAN_ERROR_UNKNOWN 0x3

//scan filter type
typedef NS_ENUM(NSInteger, BLECentralMgrState)
{
    BLEStatePowerOn = 0,
    BLEStatePowerOff,
    BLEStateUnauthorized,
    BLEStateUnknown,
} NS_ENUM_AVAILABLE(8_13, 8_0);

//scan filter type
typedef NS_ENUM(NSInteger, KBScanFilter)
{
    KBScanFilterRssi = 0,
    KBScanFilterSrvID,
} NS_ENUM_AVAILABLE(8_13, 8_0);


//declare
@class KBeacon;

/////////////////////////////
//new beacon delegation
@protocol KBeaconMgrDelegate<NSObject>

-(void)onBeaconDiscovered:(NSArray<KBeacon*>*)beacons; //found new beacon device

-(void)onCentralBleStateChange:(BLECentralMgrState)newState; //central bel state change

@end

//beacon device manager
@interface KBeaconsMgr : NSObject<CBCentralManagerDelegate>

+ (KBeaconsMgr *)sharedBeaconManager;

@property(nonatomic,weak)id<KBeaconMgrDelegate> delegate;

//all beacon device
@property(strong, readonly)NSDictionary* beacons;

//min rssi filter
@property (strong, nonatomic, readonly) NSNumber* scanMinRssiFilter;

//name filter
@property (strong, nonatomic, readonly) NSString* scanNameFilter;

//central ble state
@property (assign, readonly) BLECentralMgrState centralBLEState;

//start scan beacon device, 0x0: success; 0x1: BLE function not enable
-(int) startScanning;

//scan name filter
-(void)setScanNameFilter:(NSString*) strFilterName caseIgnore:(BOOL)caseIgnore;

//rssi filter
-(void)setScanRssiFilter:(NSNumber*) minRssi;


//stop scan beacon
-(void) stopScanning;

//check if is scanning
-(BOOL) isScanning;

//remove all beacon in list
-(void) clearBeacons;

//get central manager
-(CBCentralManager*) getBLECentralMgr;

@end

NS_ASSUME_NONNULL_END
