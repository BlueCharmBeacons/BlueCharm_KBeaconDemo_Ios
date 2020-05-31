#KBeacon Blue Charm Beacons IOS SDK Instruction DOC（English）

----
## 1. Introduction
**Welcome to Blue Charm Beacons' SDK library for our Blue Charm KBeacon devices on GitHub. At the time of this upload, our line of "KBeacon" devices include the BC011 Multi-Beacon and BC021 Multi-Beacon with Accelerometer, but we may add others later.** 

Herein, you can find the latest in directory:   
./kbeaconlib.framework  
And the historical version library at:  
./kbeacon_library

With this SDK, you can scan and configure Blue Charm Beacons' KBeacon devices. The SDK includes the following main classes:
* KBeaconsMgr: Global definition, responsible for scanning Blue Charm Beacons' KBeacon devices advertisement packet, and monitoring the Bluetooth status of the system;

* KBeacon: An instance of a Blue Charm Beacons' KBeacon device, KBeaconsMgr creates an instance of KBeacon while it found a physical device. Each KBeacon instance has three properties: KBAdvPacketHandler, KBAuthHandler, KBCfgHandler.

* KBAdvPacketHandler: parsing advertisement packet. This attribute is valid during the scan phase.

* KBAuthHandler: Responsible for the authentication operation with the Blue Charm Beacons' KBeacon device after the connection is established.

* KBCfgHandler：Responsible for configuring parameters related to Blue Charm Beacons' KBeacon devices
![avatar](https://github.com/BlueCharmBeacons/BlueCharm_KBeaconDemo_Android/blob/master/kbeacon_class_arc.png?raw=true)

**Scanning Stage**

in this stage, KBeaconsMgr will scan and parse the advertisement packet about KBeacon devices, and it will create "KBeacon" instance for every founded devices, developers can get all advertisements data by its allAdvPackets or getAdvPacketByType function.

**Connection Stage**

After a KBeacon connected, developer can make some changes of the device by modifyConfig.


## 2. IOS demo
To make your development easier, we have an IOS demos in GitHub. They are:  
* KBeaconDemo_Ios: The app can scan KBeacon devices and configure iBeacon related parameters.


## 3. Import SDK to project
### 3.1 Prepare
Development environment:  
min IOS Version 10.0

### 3.2 Import SDK
1. Add the kbeaconlib.framework into your project. As shown below:  
![avatar](https://github.com/BlueCharmBeacons/BlueCharm_KBeaconDemo_Ios/blob/master/addlibrary.png?raw=true)

2. Add the Bluetooth permissions declare in your project plist file (Target->Info). As follows:  
* Privacy - Bluetooth Always Usage Description
* Privacy - Bluetooth Peripheral Usage Description


## 4. How to use SDK
### 4.1 Scanning device
1. Initialize KBeaconMgr instance in Activity, also your application should implementation the KBeaconMgr's KBeaconMgrDelegate.

```objective-c
- (void)viewDidLoad {
    //other code...
  //init kbeacon manager
  mBeaconsMgr = [KBeaconsMgr sharedBeaconManager];
  mBeaconsMgr.delegate = self;
    //other code...  
}  
```

2. Implementation KBeaconMgrDelegate   

```objective-c
-(void)onBeaconDiscovered:(NSArray<KBeacon*>*)beacons
{
  //found device
}
-(void)onCentralBleStateChange:(BLECentralMgrState)newState
{
    if (newState == BLEStatePowerOn)
    {
        //the app can start scan in this case
        NSLog(@"central ble state power on");
    }
}
```

3. Start scanning  
After app startup, the BLE state was set to unknown, so the app should wait a few milliseconds before start scanning.

```objective-c
  int nStartScan = [mBeaconsMgr startScanning];
  if (nStartScan == 0)
  {
      NSLog(@"start scan success");
      self.actionButton.title = ACTION_STOP_SCAN;
  }
  else if (nStartScan == SCAN_ERROR_BLE_NOT_ENABLE) {
      [self showMsgDlog:@"error" message:@"BLE function is not enable"];

  }
  else if (nStartScan == SCAN_ERROR_NO_PERMISSION) {
      [self showMsgDlog:@"error" message:@"BLE scanning has no location permission"];
  }
  else
  {
      [self showMsgDlog:@"error" message:@"BLE scanning unknown error"];
  }
```

4. Implementation KBeaconMgr delegate to get scanning result

```objective-c
-(void)onBeaconDiscovered:(NSArray<KBeacon*>*)beacons
{
    KBeacon* pBeacon = nil;
    for (int i = 0; i < beacons.count; i++)
    {
        pBeacon = [beacons objectAtIndex:i];

        //get common data
        //device can be connectable ?
        cell.connectableLabel.text = [NSString stringWithFormat:@"Conn:%@", pBeacons.isConnectable ? @"yes":@"no"];

        //mac
        if (pBeacons.mac != nil)
        {
            cell.macLabel.text = [NSString stringWithFormat:@"mac:%@", pBeacons.mac];
        }

        //battery percent
        if (pBeacons.batteryPercent != nil)
        {
           cell.voltageLabel.text = [NSString stringWithFormat:@"Batt:%@", [pBeacons.batteryPercent stringValue]];
        }

        //device name
        if (pBeacons.name != nil){
            cell.deviceNameLabel.text = pBeacons.name;
        }else{
            cell.deviceNameLabel.text = @"N/A";
        }

        //rssi
        if (pBeacons.rssi != nil)
        {
            cell.rssiLabel.text = [NSString stringWithFormat:@"rssi:%@", [pBeacons.rssi stringValue]];
        }

        //filter iBeacon packet
        KBAdvPacketIBeacon* piBeaconAdvPacket = (KBAdvPacketIBeacon*)[pBeacons getAdvPacketByType:KBAdvTypeIBeacon];
        if (piBeaconAdvPacket != nil)
        {
            //because IOS app can not get UUID from advertisement, so we try to get uuid from configruation database, the UUID will only avaiable when device ever conneced
            KBCfgIBeacon* pIBeaconCfg = (KBCfgIBeacon*)[pBeacons getConfigruationByType:KBConfigTypeIBeacon];
            if (pIBeaconCfg != nil)
            {
                cell.uuidLabel.text = [NSString stringWithFormat:@"major:%@",
                                       pIBeaconCfg.uuid];
            }

            //get majorID from advertisement packet
            //notify: this is not standard iBeacon protocol, we get major ID from KKM private
            //scan response message
            if (piBeaconAdvPacket.majorID != nil)
            {
                cell.majorLabel.text = [NSString stringWithFormat:@"major:%@",[piBeaconAdvPacket.majorID stringValue]];
            }

            //get majorID from advertisement packet
            //notify: this is not standard iBeacon protocol, we get minor ID from KKM private
            //scan response message
            if (piBeaconAdvPacket.minorID != nil)
            {
                cell.minorLabel.text = [NSString stringWithFormat:@"minor:%@",[piBeaconAdvPacket.minorID stringValue]];
            }
        }
    }

    mBeaconsArray = [mBeaconsDictory allValues];
    [_beaconsTableView reloadData];
}
```

4. Clean scanning result and stop scanning  
After start scanning, The KBeaconMgr will buffer all found KBeacon device. If the app want to remove all buffered KBeacon device, the app can:  

```objective-c
[mBeaconsMgr clearBeacons];
```

If the app wants to stop scanning:
```objective-c
[mBeaconsMgr stopScanning];
```

### 4.2 Connect to device
 1. If the app wants to change the device parameters, then it need connect to the device.
 ```objective-c
 self.beacon.delegate = self;
[self.beacon connect:password timeout:20];
 ```
* Password: device password, the default password is 0000000000000000
* timeout: max connection time, unit is second.

2. the app should implementation the KBeacon's delegate for get connection status:
 ```objective-c
 -(void)onConnStateChange:(KBeacon*)beacon state:(KBConnState)state evt:(KBConnEvtReason)evt;
 {
     if (state == KBStateConnecting)
     {
         self.txtBeaconStatus.text = @"Connecting to device";
     }
     else if (state == KBStateConnected)
     {
         self.txtBeaconStatus.text = @"Device connected";

         [self updateDeviceToView];
     }
     else if (state == KBStateDisconnected)
     {
         self.txtBeaconStatus.text = @"Device disconnected";
         if (evt == KBEvtConnAuthFail)
         {
             NSLog(@"auth failed");
             [self showPasswordInputDlg];
         }
     }

     [self updateActionButton];
 }
 ```

3. Disconnect from the device.
 ```objective-c
[self.beacon disconnect];
 ```

### 4.3 Configure parameters
#### 4.3.1 Advertisement type
KBeacon can support broadcasting multiple type advertisement packets in parallel.  
For example, advertisement period was set to 500ms. Advertisement type was set to “iBeacon + URL + UID + KSensor”, then the device will send advertisement packet like follow.   

|Time(MS)|0|500|1000|1500|2000|2500|3000|3500
|----|----|----|----|----|----|----|----|----
|`Adv type`|KSensor|UID|iBeacon|URL|KSensor|UID|iBeacon|URL


If the advertisement type contains TLM and other types, the KBeacon will send 1 TLM advertisement every 10 advertisement packets by default configuration.
For example: advertisement period was set to 500ms. Advertisement type was set to “URL + TLM”, then the advertisement packet is like follow

|Time|0|500|1000|1500|2000|2500|3000|3500|4000|4500|5000
|----|----|----|----|----|----|----|----|----|----|----|----
|`Adv type`|URL|URL|URL|URL|URL|URL|URL|URL|URL|TLM|URL


**Notify:**  
  For the advertisement period, Apple has some suggestions that make the device more easily discovered by IOS phones. (The suggest value was: 152.5 ms; 211.25 ms; 318.75 ms; 417.5 ms; 546.25 ms; 760 ms; 852.5 ms; 1022.5 ms; 1285 ms). For more information, please refer to Section 3.5 in "Bluetooth Accessory Design Guidelines for Apple Products". The document link: https://developer.apple.com/accessories/Accessory-Design-Guidelines.pdf.


#### 4.3.2 Get device parameters
After the app connect to KBeacon success. The KBeacon will automatically read current parameters from physical device. so the app can update UI and show the parameters to user after connection setup.  
 ```objective-c
 -(void)onConnStateChange:(KBeacon*)beacon state:(KBConnState)state evt:(KBConnEvtReason)evt;
 {
     if (state == KBStateConnected)
     {
         [self updateDeviceToView];
     }
 }

//update device's configuration to UI
-(void)updateDeviceToView
{
    KBCfgCommon* pCommonCfg = (KBCfgCommon*)[self.beacon getConfigruationByType:KBConfigTypeCommon];
    if (pCommonCfg != nil)
    {
        NSLog(@"support iBeacon:%@", [pCommonCfg isSupportIBeacon]?@"1":@"0");
        NSLog(@"support eddy url:%@", [pCommonCfg isSupportEddyURL]?@"1":@"0");
        NSLog(@"support eddy tlm:%@", [pCommonCfg isSupportEddyTLM]?@"1":@"0");
        NSLog(@"support eddy uid:%@", [pCommonCfg isSupportEddyUID]?@"1":@"0");
        NSLog(@"support ksensor:%@", [pCommonCfg isSupportKBSensor]?@"1":@"0");
        NSLog(@"support has button:%@", [pCommonCfg isSupportButton]?@"1":@"0");
        NSLog(@"support beep:%@", [pCommonCfg isSupportBeep]?@"1":@"0");
        NSLog(@"support accleration:%@", [pCommonCfg isSupportAccSensor]?@"1":@"0");
        NSLog(@"support humidify:%@", [pCommonCfg isSupportHumiditySensor]?@"1":@"0");
        NSLog(@"support max tx power:%d", [pCommonCfg.maxTxPower intValue]);
        NSLog(@"support min tx power:%d", [pCommonCfg.minTxPower intValue]);

        self.labelBeaconType.text = pCommonCfg.advTypeString;
        self.txtName.text = pCommonCfg.name;
        self.labelModel.text = pCommonCfg.model;
        self.labelVersion.text = pCommonCfg.version;
        self.txtTxPower.text = [pCommonCfg.txPower stringValue];
        self.txtAdvPeriod.text = [pCommonCfg.advPeriod stringValue];

        KBCfgIBeacon* pIBeacon = (KBCfgIBeacon*)[self.beacon getConfigruationByType:KBConfigTypeIBeacon];
        if (pIBeacon != nil)
        {
            self.txtBeaconUUID.text = pIBeacon.uuid;
            self.txtBeaconMajor.text = [pIBeacon.majorID stringValue];
            self.txtBeaconMinor.text = [pIBeacon.minorID stringValue];
        }
    }
}
 ```

#### 4.3.3 Update advertisement parameters
After app connects to device success, the app can update parameters of KBeacon device.

##### 4.3.3.1 Update common advertisement parameters
The app can modify the basic parameters of KBeacon through the KBCfgCommon class. The KBCfgCommon has follow parameters:

* name: device name, the device name must <= 18 character.

* advType: beacon type, can be setting to iBeacon, KSesnor, Eddy TLM/UID/ etc.,

* advPeriod: advertisement period, the value can be set to 100~10000ms.

* txPower: advertisement TX power, unit is dBm.

* autoAdvAfterPowerOn: if autoAdvAfterPowerOn was setting to true, the beacon always advertisement if it has battery. If this value was setting to false, the beacon will power off if long press button for 5 seconds.

* tlmAdvInterval: eddystone TLM advertisement interval. the default value is 10. The KBeacon will send 1 TLM advertisement every 10 advertisement packets.

* refPower1Meters: the rx power at 1 meters.

* advConnectable: is beacon advertisement can be connectable.  
**Warning:**   
   If the KBeacon was set to un-connectable, the app cannot connect to it again. If the device has button, the device can re-enter connectable advertisement for 60 seconds when single click on the button

* password: device password, the password length must >= 8 character and <= 16 character.  
 **Warning:**   
 Be sure to remember the new password, you won’t be able to connect to the device if you forget the new password.

Example: Update common parameters
```objective-c
-(void)updateKBeaconCommonPara
{
    if (_beacon.state != KBStateConnected)
    {
        NSLog(@"beacon not connected");
        return;
    }

    KBCfgCommon* pCommonPara = [[KBCfgCommon alloc]init];

    //change the device name
    pCommonPara.name = @"MyBeacon";

    //change the tx power
    pCommonPara.txPower = [NSNumber numberWithInt:-4];

    //change advertisement period
    pCommonPara.advPeriod = [NSNumber numberWithFloat:1000.0];

    //set the device to un-connectable.
    //Warning: if the app set the KBeacon to un-connectable, the app cannot connect to it if it does not have button.
    //If the device has button, the device can enter connect-able advertisement for 60 seconds when click on the button
    pCommonPara.advConnectable = [NSNumber numberWithBool:NO];

    //set device to always power on
    //the autoAdvAfterPowerOn is enable, the device will not allowed power off by long press button
    pCommonPara.autoAdvAfterPowerOn = [NSNumber numberWithBool:YES];

    //update password.
    //Warnning: Be sure to remember the new password, you won’t be able to connect to the device if you forget it.
    //pCommonPara.password = @"123456789";

    //start configruation
    NSArray* configParas = @[pCommonPara];
    [_beacon modifyConfig:configParas callback:^(BOOL bCfgRslt, NSError* error)
     {
         if (bCfgRslt)
         {
             [self showDialogMsg: @"Success" message: @"config beacon success"];
         }
         else if (error != nil)
         {
             [self showDialogMsg:@"Failed" message:[NSString stringWithFormat:@"config error:%@",error.localizedDescription]];
         }
     }];
}
```

##### 4.3.3.2 Update iBeacon parameters
The app can modify the iBeacon parameters of KBeacon through the KBCfgIBeacon class. The KBCfgIBeacon has follow parameters:
uuid: iBeacon uuid
majorID: iBeacon major ID
minorID: iBeacon minor ID

example: setting the KBeacon to broadcasting iBeacon
```objective-c
//example: update KBeacon to iBeacon
-(void)updateKBeaconToIBeacon
{
    if (_beacon.state != KBStateConnected)
    {
        NSLog(@"beacon not connected");
        return;
    }

    KBCfgIBeacon* pIBeaconCfg = [[KBCfgIBeacon alloc]init];
    KBCfgCommon* pCommonCfg = [[KBCfgCommon alloc]init];

    //update beacon type to hybid iBeacon/TLM
    pCommonCfg.advType = [NSNumber numberWithInt: KBAdvTypeIBeacon];

    //update iBeacon parameters
    pIBeaconCfg.uuid = @"E2C56DB5-DFFB-48D2-B060-D0F5A71096E0";
    pIBeaconCfg.majorID = [NSNumber numberWithInt: 6454];
    pIBeaconCfg.minorID = [NSNumber numberWithInt: 1458];

    //start configruation
    NSArray* configParas = @[pCommonCfg, pIBeaconCfg];
    [_beacon modifyConfig:configParas callback:^(BOOL bCfgRslt, NSError* error)
     {
         if (bCfgRslt)
         {
             [self showDialogMsg: @"Success" message: @"config beacon success"];
         }
         else if (error != nil)
         {
             [self showDialogMsg:@"Failed" message:[NSString stringWithFormat:@"config error:%@",error.localizedDescription]];
         }
     }];
}

//example: update KBeacon to hybrid iBeacon/EddyTLM
//sometimes we need KBeacon broadcasting both iBeacon and TLM packet (battery level, Temperature, power on times, etc., )
-(void)updateKBeaconToIBeaconAndTLM
{
    if (_beacon.state != KBStateConnected)
    {
        NSLog(@"beacon not connected");
        return;
    }

    KBCfgIBeacon* pIBeaconCfg = [[KBCfgIBeacon alloc]init];
    KBCfgCommon* pCommonCfg = [[KBCfgCommon alloc]init];

    //update beacon type to hybid iBeacon/TLM
    pCommonCfg.advType = [NSNumber numberWithInt: KBAdvTypeIBeacon | KBAdvTypeEddyTLM];

    //updatet KBeacon send TLM packet every 8 advertisement packets
    pCommonCfg.tlmAdvInterval = [NSNumber numberWithInt:8];

    //update iBeacon parameters
    pIBeaconCfg.uuid = @"E2C56DB5-DFFB-48D2-B060-D0F5A71096E0";
    pIBeaconCfg.majorID = [NSNumber numberWithInt: 6454];
    pIBeaconCfg.minorID = [NSNumber numberWithInt: 1458];

    //start configruation
    NSArray* configParas = @[pCommonCfg, pIBeaconCfg];
    [_beacon modifyConfig:configParas callback:^(BOOL bCfgRslt, NSError* error)
     {
         if (bCfgRslt)
         {
             [self showDialogMsg: @"Success" message: @"config beacon success"];
         }
         else if (error != nil)
         {
             [self showDialogMsg:@"Failed" message:[NSString stringWithFormat:@"config error:%@",error.localizedDescription]];
         }
     }];
}
```

##### 4.3.3.3 Update Eddystone parameters
The app can modify the eddystone parameters of KBeacon by the KBCfgEddyURL and KBCfgEddyUID class.  
The KBCfgEddyURL has follow parameters:
* url: eddystone URL address

The KBCfgEddyUID has follow parameters:
* nid: namespace id about UID. It is 10 bytes length hex string value.
* sid: instance id about UID. It is 6 bytes length hex string value.

```objective-c
//example: update KBeacon to Eddy URL
-(void)updateKBeaconToEddyURL
{
    if (_beacon.state != KBStateConnected)
    {
        NSLog(@"beacon not connected");
        return;
    }

    KBCfgCommon* pCommonPara = [[KBCfgCommon alloc]init];
    KBCfgEddyURL* pEddyUrlPara = [[KBCfgEddyURL alloc]init];

    //set beacon type to URL
    pCommonPara.advType = [NSNumber numberWithInt: KBAdvTypeEddyURL];

    //set address to google
    pEddyUrlPara.url = @"https://www.google.com/";

    //start configruation
    NSArray* configParas = @[pCommonPara, pEddyUrlPara];
    [_beacon modifyConfig:configParas callback:^(BOOL bCfgRslt, NSError* error)
     {
         if (bCfgRslt)
         {
             [self showDialogMsg: @"Success" message: @"config beacon success"];
         }
         else if (error != nil)
         {
             [self showDialogMsg:@"Failed" message:[NSString stringWithFormat:@"config error:%@",error.localizedDescription]];
         }
     }];
}

//example: update KBeacon to UID
-(void)updateKBeaconToEddyUID
{
    if (_beacon.state != KBStateConnected)
    {
        NSLog(@"beacon not connected");
        return;
    }

    KBCfgCommon* pCommonPara = [[KBCfgCommon alloc]init];
    KBCfgEddyUID* pEddyUIDPara = [[KBCfgEddyUID alloc]init];

    //set beacon type to UID
    pCommonPara.advType = [NSNumber numberWithInt:  KBAdvTypeEddyUID];

    //update UID para
    pEddyUIDPara.nid = @"0x00010203040506070809";
    pEddyUIDPara.sid = @"0x010203040506";

    //start configruation
    NSArray* configParas = @[pCommonPara, pEddyUIDPara];
    [_beacon modifyConfig:configParas callback:^(BOOL bCfgRslt, NSError* error)
     {
         if (bCfgRslt)
         {
             [self showDialogMsg: @"Success" message: @"config beacon success"];
         }
         else if (error != nil)
         {
             [self showDialogMsg:@"Failed" message:[NSString stringWithFormat:@"config error:%@",error.localizedDescription]];
         }
     }];
}
```

##### 4.3.3.4 Check if parameters are changed
Sometimes the app needs to configure multiple advertisement parameters at the same time.  
We recommend that the app should check whether the parameter was changed. The app doesn’t need to send the parameters if it’s value were not changed. Reducing the parameters will reduce the modification time.

Example: checking if the parameters was changed, then send new parameters to device.
```objective-c
-(void)updateViewToDevice
{
    if (_beacon.state != KBStateConnected)
    {
        NSLog(@"beacon not connected");
        return;
    }

    KBCfgIBeacon* pIBeaconCfg = [[KBCfgIBeacon alloc]init];
    KBCfgCommon* pCommonCfg = [[KBCfgCommon alloc]init];

    @try {

        //set beacon type to iBeacon
        pCommonCfg.advType = [NSNumber numberWithInt: KBAdvTypeIBeacon];

        //device name
        if (_txtName.tag == TXT_DATA_MODIFIED)
        {
            pCommonCfg.name = _txtName.text;
        }

        //tx power
        if (_txtTxPower.tag == TXT_DATA_MODIFIED)
        {
            int nTxPower = [_txtTxPower.text intValue];

            if (nTxPower > [_beacon.maxTxPower intValue]
                || nTxPower < [_beacon.minTxPower intValue])
            {
                [self showDialogMsg:@"error" message: @"Tx power is invalid"];
                return;
            }

            pCommonCfg.txPower = [NSNumber numberWithInt:nTxPower];
        }

        //set adv period
        if (_txtAdvPeriod.tag == TXT_DATA_MODIFIED)
        {
            if ([_txtAdvPeriod.text floatValue] < 100.0
                || [_txtAdvPeriod.text floatValue] > 10000.0)
            {
                [self showDialogMsg:@"error" message: @"adv period is invalid"];
                return;
            }

            pCommonCfg.advPeriod = [NSNumber numberWithFloat:[_txtAdvPeriod.text floatValue]];
        }

        //modify ibeacon uuid
        if (_txtBeaconUUID.tag == TXT_DATA_MODIFIED)
        {
            if (![KBUtility isUUIDString:_txtBeaconUUID.text])
            {
                [self showDialogMsg:@"error" message: @"UUID data length invalid"];
                return;
            }

            pIBeaconCfg.uuid = _txtBeaconUUID.text;
        }

        //modify ibeacon major id
        if (_txtBeaconMajor.tag == TXT_DATA_MODIFIED)
        {
            if ([_txtBeaconMajor.text intValue] > 65535)
            {
                [self showDialogMsg:@"error" message: @"major id data invalid"];
                return;
            }
            pIBeaconCfg.majorID = [NSNumber numberWithInt:[_txtBeaconMajor.text intValue]];
        }

        //modify ibeacon minor
        if (_txtBeaconMinor.tag == TXT_DATA_MODIFIED)
        {
            if ([_txtBeaconMinor.text intValue] > 65535)
            {
                [self showDialogMsg:@"error" message: @"minor id data invalid"];
                return;
            }
            pIBeaconCfg.minorID = [NSNumber numberWithInt:[_txtBeaconMinor.text intValue]];
        }
    }
    @catch (KBException *exception)
    {
        NSString* errorInfo = [NSString stringWithFormat:@"input parameters invalid:%ld",
                               (long)exception.errorCode];
        [self showDialogMsg: @"error" message: errorInfo];
        return;
    }


    NSArray* configParas = @[pCommonCfg, pIBeaconCfg];

    //start configruation
    [_beacon modifyConfig:configParas callback:^(BOOL bCfgRslt, NSError* error)
     {
         if (bCfgRslt)
         {
             [self showDialogMsg: @"Success" message: @"config beacon success"];
         }
         else if (error != nil)
         {
             if (error.code == KBEvtCfgBusy)
             {
                 NSLog(@"Config busy, please make sure other configruation complete");
             }
             else if (error.code == KBEvtCfgTimeout)
             {
                 NSLog(@"Config timeout");
             }
             [self showDialogMsg:@"Failed" message:[NSString stringWithFormat:@"config error:%@",error.localizedDescription]];
         }
     }];
}
```

#### 4.3.4 Update trigger parameters
 For some KBeacon device that has motion or push button. The app can set advertisement trigger and the device will advertise when the trigger condition is met. The trigger advertisement has follow parameters:
 * Trigger advertisement Mode: There are two modes of trigger advertisement. One mode is to broadcast only when the trigger is satisfied. The other mode is always broadcasting, and the content of advertisement packet will change when the trigger conditions are met.

 *    Trigger parameters: For motion trigger, the parameters are acceleration sensitivity. For button trigger, you can set different trigger event (single click, double click, etc.,).

 *    Trigger advertisement type: The advertisement packet type when trigger event happened. it can be set to iBeacon, Eddystone or KSensor advertisement.

 *    Trigger advertisement duration: The advertisement duration when trigger event happened.

 *    Trigger advertisement interval: The Bluetooth advertisement interval for trigger advertisement.

 Example 1:  
  &nbsp;&nbsp;Trigger adv mode: setting to broadcast only on trigger event happened  
  &nbsp;&nbsp;Trigger adv type: iBeacon  
  &nbsp;&nbsp;Trigger adv duration: 30 seconds  
    &nbsp;&nbsp;Trigger adv interval: 300ms  
    ![avatar](https://github.com/kkmhogen/KBeaconDemo_Android/blob/master/only_adv_when_trigger.png?raw=true)

 Example 2:  
    &nbsp;For some scenario, we need to continuously monitor the KBeacon to ensure that the device was alive, so we set the trigger advertisement mode to always advertisement.   
    &nbsp;We set an larger advertisement interval during alive advertisement and a short advertisement interval when trigger event happened, so we can achieve a balance between power consumption and triggers advertisement be easily detected.  
   &nbsp;&nbsp;Trigger adv mode: set to Always advertisement  
   &nbsp;&nbsp;Trigger adv type: iBeacon  
   &nbsp;&nbsp;Trigger adv duration: 30 seconds  
      &nbsp;&nbsp;Trigger adv interval: 300ms  
     &nbsp;&nbsp;Always adv interval: 2000ms
     ![avatar](https://github.com/kkmhogen/KBeaconDemo_Android/blob/master/always_adv_with_trigger.png?raw=true)

**Notify:**  
      The SDK will not automatically read trigger configuration after connection setup complete. So the app need read the trigger configuration manual if the app needed. Please reference 4.3.4.1 code for read trigger parameters from device.  

#### 4.3.4.1 Push button trigger
The push button trigger feature is used in some hospitals, nursing homes and other scenarios. When the user encounters some emergency event, they can click the button and the KBeacon device will start broadcast.
The app can configure single click, double-click, triple-click, long-press the button trigger, or a combination.

**Notify:**  
* By KBeacon's default setting, long press button used to power on and off. Clicking button used to force the KBeacon enter connectable broadcast advertisement. So when you enable the long-press button trigger, the long-press power off function will be disabled. When you turn on the single/double/triple click trigger, the function of clicking to enter connectable broadcast state will also be disabled. After you disable button trigger, the default function about long press or click button will take effect again.
* iBeacon UUID for single click trigger = Always iBeacon UUID + 0x5
* iBeacon UUID for single double trigger = Always iBeacon UUID + 0x6
* iBeacon UUID for single triple trigger = Always iBeacon UUID + 0x7
* iBeacon UUID for single long press trigger = Always iBeacon UUID + 0x8

1. Enable or button trigger feature.

```objective-c
-(void)enableButtonTrigger
{
    if (self.beacon.state != KBStateConnected){
        return;
    }

    //check if device can support button trigger capibility
    if (([self.beacon.triggerCapibility intValue] & KBTriggerTypeButton) == 0)
    {
        return;
    }

    KBCfgTrigger* btnTriggerPara = [[KBCfgTrigger alloc]init];

    //set trigger type
    btnTriggerPara.triggerType = [NSNumber numberWithInt: KBTriggerTypeButton];

    //set trigger advertisement enable
    btnTriggerPara.triggerAction = [NSNumber numberWithInt: KBTriggerActionAdv];

    //set trigger adv mode to adv only on trigger
    btnTriggerPara.triggerAdvMode = [NSNumber numberWithInt:KBTriggerAdvOnlyMode];

    //set trigger button para
    btnTriggerPara.triggerPara = [NSNumber numberWithInt: (KBTriggerBtnSingleClick | KBTriggerBtnDoubleClick)];

    //set trigger adv type
    btnTriggerPara.triggerAdvType = [NSNumber numberWithInt:KBAdvTypeIBeacon];

    //set trigger adv duration to 20 seconds
    btnTriggerPara.triggerAdvTime = [NSNumber numberWithInt: 20];

    //set the trigger adv interval to 500ms
    btnTriggerPara.triggerAdvInterval = [NSNumber numberWithFloat: 500];

    [self.beacon modifyTriggerConfig:btnTriggerPara callback:^(BOOL bConfigSuccess, NSError * _Nonnull error) {
        if (bConfigSuccess)
        {
            NSLog(@"modify btn trigger success");
        }
        else
        {
            NSLog(@"modify btn trigger fail:%ld", (long)error.code);
        }
    }];
}
```

2. The app can disable the button trigger

```objective-c
//disable button trigger
-(void)disableButtonTrigger
{
    if (self.beacon.state != KBStateConnected){
        return;
    }

    //check if device can support button trigger capibility
    if (([self.beacon.triggerCapibility intValue] & KBTriggerTypeButton) == 0)
    {
        return;
    }

    KBCfgTrigger* btnTriggerPara = [[KBCfgTrigger alloc]init];

    //set trigger type
    btnTriggerPara.triggerType = [NSNumber numberWithInt: KBTriggerTypeButton];

    //set trigger advertisement enable
    btnTriggerPara.triggerAction = [NSNumber numberWithInt: KBTriggerActionOff];

    [self.beacon modifyTriggerConfig:btnTriggerPara callback:^(BOOL bConfigSuccess, NSError * _Nonnull error) {
        if (bConfigSuccess)
        {
            NSLog(@"modify btn trigger success");
        }
        else
        {
            NSLog(@"modify btn trigger fail:%ld", (long)error.code);
        }
    }];
}
```

3. The app can read the button current trigger parameters from KBeacon by follow code  

```objective-c
 //read button trigger information
-(void)readButtonTriggerPara
{
    if (self.beacon.state != KBStateConnected){
        return;
    }

    //check if device can support button trigger capibility
    if (([self.beacon.triggerCapibility intValue] & KBTriggerTypeButton) == 0)
    {
        return;
    }

    [self.beacon readTriggerConfig:KBTriggerTypeButton callback:^(BOOL bConfigSuccess, NSDictionary * _Nullable readPara, NSError * _Nullable error)
        {
        if (bConfigSuccess)
        {
            NSArray* btnTriggerCfg = [readPara objectForKey:@"trObj"];
            if (btnTriggerCfg != nil)
            {
                KBCfgTrigger* btnCfg = [btnTriggerCfg objectAtIndex:0];
                NSLog(@"trigger type:%d", [btnCfg.triggerType intValue]);
                if ([btnCfg.triggerAction intValue] > 0)
                {
                    //button enable mask
                    int nButtonEnableInfo = [btnCfg.triggerPara intValue];
                    if ((nButtonEnableInfo & KBTriggerBtnSingleClick) > 0)
                    {
                        NSLog(@"Enable single click trigger");
                    }
                    if ((nButtonEnableInfo & KBTriggerBtnDoubleClick) > 0)
                    {
                        NSLog(@"Enable double click trigger");
                    }
                    if ((nButtonEnableInfo & KBTriggerBtnHold) > 0)
                    {
                        NSLog(@"Enable hold press trigger");
                    }

                    //button trigger adv mode
                    if ([btnCfg.triggerAdvMode intValue] == KBTriggerAdvOnlyMode)
                    {
                        NSLog(@"device only advertisement when trigger event happened");
                    }
                    else if ([btnCfg.triggerAdvMode intValue] == KBTriggerAdv2AliveMode)
                    {
                        NSLog(@"device will always advertisement, but the uuid is difference when trigger event happened");
                    }

                    //button trigger adv type
                    NSLog(@"Button trigger adv type:%d", [btnCfg.triggerAdvType intValue]);

                    //button trigger adv duration, unit is sec
                    NSLog(@"Button trigger adv duration:%dsec", [btnCfg.triggerAdvTime intValue]);

                    //button trigger adv interval, unit is ms
                    NSLog(@"Button trigger adv interval:%gms", [btnCfg.triggerAdvInterval floatValue]);
                }
                else
                {
                    NSLog(@"Button trigger disable");
                }
            }
        }
        else
        {
            NSLog(@"Button trigger failed, %ld", (long)error.code);
        }
    }];
}

 ```

#### 4.3.4.2 Motion trigger
The KBeacon can start broadcasting when it detects motion. Also the app can setting the sensitivity of motion detection.  

**Notify:**  
* iBeacon UUID for motion trigger = Always iBeacon UUID + 0x1
* When the KBeacon enable the motion trigger, the Acc feature(X, Y, and Z axis detected function) in the KSensor broadcast will be disabled.

Enabling motion trigger is similar to push button trigger, which will not be described in detail here.
1. Enable or button trigger feature.  

```objective-c
-(void)enableMotionTrigger
{
    ... same as push button trigger

    //check if device can support motion trigger capibility
    if (([self.beacon.triggerCapibility intValue] & KBTriggerTypeMotion) == 0)
    {
        return;
    }

    ... same as push button trigger

    //set trigger type
    btnTriggerPara.triggerType = [NSNumber numberWithInt: KBTriggerTypeMotion];

    //set motion trigger sensitivity, the valid range is 2~31. The unit is 16mg.
    btnTriggerPara.triggerPara = [NSNumber numberWithInt: 3];

    ... same as push button trigger
}
```

#### 4.3.5 Send command to device
After app connects to device success, the app can send command to device.  
All command messages between app and KBeacon are JSON format. Our SDK provide Hash Map to encapsulate these JSON message.

#### 4.3.5.1 Ring device
 Some Blue Charm Beacons KBeacon devices have a buzzer function. The app can ring device. for ring command, it has 5 parameters:
 * msg: msg type is 'ring'
 * ringTime: unit is ms. The KBeacon will start flash/alert for 'ringTime' milliseconds  when receive this command.
 * ringType: 0x0:led flash only; 0x1:beep alert only; 0x2 both led flash and beep;
 * ledOn: optional parameters, unit is ms. The LED will flash at interval (ledOn + ledOff).  This parameters is valid when ringType setting to 0x0 or 0x2.
 * ledOff: optional parameters, unit is ms. the LED will flash at interval (ledOn + ledOff).  This parameters is valid when ringType setting to 0x0 or 0x2.

```objective-c
-(void) ringDevice
{
    if (self.beacon.state != KBStateConnected){
        return;
    }

    NSMutableDictionary* paraDicts = [[NSMutableDictionary alloc]init];

    [paraDicts setValue:@"ring" forKey:@"msg"];

    //ring times, unit is ms
    [paraDicts setValue:[NSNumber numberWithInt:20000] forKey:@"ringTime"];

    //0x0:led flash only; 0x1:beep alert only; 0x2 led flash and beep alert;
    [paraDicts setValue:[NSNumber numberWithInt:2] forKey:@"ringType"];

    //led flash on time. valid when ringType set to 0x0 or 0x2
    [paraDicts setValue:[NSNumber numberWithInt:200] forKey:@"ledOn"];

    //led flash off time. valid when ringType set to 0x0 or 0x2
    [paraDicts setValue:[NSNumber numberWithInt:1800] forKey:@"ledOff"];

    [self.beacon sendCommand:paraDicts callback:^(BOOL bConfigSuccess, NSError * _Nonnull error)
    {
        if (bConfigSuccess)
        {
            NSLog(@"send ring command to device success");
        }
        else
        {
            NSLog(@"send ring command to device failed");
        }
    }];
}
```
#### 4.3.5.2 Reset configuration to default
 The app can use follow command to reset all configurations to default.
 * msg: message type is 'reset'

```objective-c
//set parameter to default
-(void)resetParametersToDefault
{
    if (self.beacon.state != KBStateConnected){
        return;
    }

    NSMutableDictionary* paraDicts = [[NSMutableDictionary alloc]init];
    [paraDicts setValue:@"reset" forKey:@"msg"];
    [self.beacon sendCommand:paraDicts callback:^(BOOL bConfigSuccess, NSError * _Nonnull error)
    {
        if (bConfigSuccess)
        {
            //disconnect with device to make sure the parameters to take effect
            [self.beacon disconnect];
            NSLog(@"send reset command to device success");
        }
        else
        {
            NSLog(@"send reset command to device failed");
        }
    }];
}
```
#### 4.3.6 Error cause in configuration/command
 App may get errors during the configuration. The KBErrorCode has follow values.
 * KBEvtCfgNoParameters: parameters is null
 * KBEvtCfgBusy : device is busy, please make sure last configuration operation has complete
 * KBEvtCfgFailed: device return failed.
 * KBEvtCfgTimeout: configuration timeout
 * KBEvtCfgInputInvalid: input parameters data not in valid range
 * KBEvtCfgStateError: device is not in connected state
 * KBEvtCfgNotSupport: device does not support the parameters

 ```objective-c
{
    ...another code

    //start configuration
    [_beacon modifyConfig:configParas callback:^(BOOL bCfgRslt, NSError* error)
    {
       if (bCfgRslt)
       {
           [self showDialogMsg: @"Success" message: @"config beacon success"];
       }
       else if (error != nil)
       {
           if (error.code == KBEvtCfgBusy)
           {
               NSLog(@"Config busy, please make sure other configruation complete");
           }
           else if (error.code == KBEvtCfgTimeout)
           {
               NSLog(@"Config timeout");
           }
           ...other code
       }
    }];
}
 ```

## 5. Change log
* 2020.3.1 v1.21 change the advertisement period from integer to float.
* 2020.1.11 v1.2 add trigger function.
* 2019.10.11 v1.1 add KSesnor function.
* 2019.4.1 v1.0 first version.
