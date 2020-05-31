//
//  ViewController.m
//  KBeaconDemo
//
//  Created by kkm on 2018/12/7.
//  Copyright © 2018 kkm. All rights reserved.
//

#import "ViewController.h"
#import "string.h"
#import "KBeaconViewCell.h"
#import "kbeaconlib/KBeacon.h"
#import "kbeaconlib/KBeaconsMgr.h"
#import "DeviceViewController.h"
#import "kbeaconlib/KBAdvPacketIBeacon.h"
#import "KBPreferance.h"
#import "kbeaconlib/KBCfgIBeacon.h"

@interface ViewController ()
{
    NSMutableDictionary *mBeaconsDictory;
    
    NSArray* mBeaconsArray;
    
    KBeaconsMgr *mBeaconsMgr;
    
    KBPreferance* mBeaconPref;
    
    CGRect mFilterViewRect;
}

@end
@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.beaconsTableView.delegate = self;
    self.beaconsTableView.dataSource = self;

    //refresh menu
    UIRefreshControl* rc = [[UIRefreshControl alloc]init];
    rc.attributedTitle = [[NSAttributedString alloc]initWithString:@"Pull to refresh"];
    [rc addTarget:self action:@selector(refreshTableView) forControlEvents:UIControlEventValueChanged];
    self.beaconsTableView.refreshControl = rc;
    
    //add filter button
    
    //beacon list
    mBeaconsDictory = [[NSMutableDictionary alloc]initWithCapacity:50];
    
    //init kbeacon manager
    mBeaconsMgr = [KBeaconsMgr sharedBeaconManager];
    mBeaconsMgr.delegate = self;
    
    mBeaconPref = [KBPreferance sharedManager];
    
    //init for start scan
    self.actionButton.title = ACTION_START_SCAN;
    
    self.mFilterView.hidden = YES;
    self.mFilterActionButton.selected = NO;
    
    self.mFilterSummaryEdit.delegate = self;
    self.mFilterNameEdit.delegate = self;
    
    [self.mFilterNameEdit addTarget:self action:@selector(textNameFieldEditChanged:) forControlEvents:UIControlEventEditingChanged];
    
    /*
    UITapGestureRecognizer * tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(tap:)];
    [self.view addGestureRecognizer:tap];
    */

    self.mRemoveSummaryButton.hidden = YES;
    self.mRemoveFilterNameButton.hidden = YES;
    
    _beaconsTableView.separatorInset = UIEdgeInsetsZero;
    _beaconsTableView.tableFooterView = [[UIView alloc]initWithFrame:CGRectZero];
    
    /*
    self.mFilterSummaryView.layer.shadowColor = [UIColor grayColor].CGColor;
    self.mFilterSummaryView.layer.shadowOffset = CGSizeMake(0,0);
    self.mFilterSummaryView.layer.shadowOpacity = 0.5;
    self.mFilterSummaryView.layer.shadowRadius = 10.0;
    */
    
    mBeaconsArray = [[NSMutableArray alloc]init];
}

-(void)toggleEditFilterView
{
    if (self.mFilterActionButton.selected)
    {
        self.mFilterView.hidden = YES;
        [self.mFilterNameEdit resignFirstResponder];
        
        [mBeaconsDictory removeAllObjects];
        mBeaconsArray = nil;
        
        [self.beaconsTableView reloadData];
        
        [self updateFilterSummary];
    }
    else
    {
        [self.mFilterNameEdit becomeFirstResponder];
        
        self.mFilterView.hidden = NO;
        [self.view bringSubviewToFront:self.mFilterView];
    }
    
    self.mFilterActionButton.selected = !self.mFilterActionButton.selected;
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
    if (textField == self.mFilterSummaryEdit)
    {
        [self toggleEditFilterView];
        return NO;
    }
    else
    {
        return YES;
    }
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{    
    [self toggleEditFilterView];
    
    return YES;
}

-(void)updateFilterSummary
{
    NSString* strTextFilter = self.mFilterNameEdit.text;
    
    if (self.mRssiFilterSlide.value != self.mRssiFilterSlide.minimumValue)
    {
        if (self.mFilterNameEdit.text.length > 1)
        {
            strTextFilter = [NSString stringWithFormat:@"%@;", strTextFilter];
        }
        
        strTextFilter = [NSString stringWithFormat:@"%@%ddBm",
                         strTextFilter,
                         (int)self.mRssiFilterSlide.value];
    }
    
    [self.mFilterSummaryEdit setText:strTextFilter];
    if (self.mFilterSummaryEdit.text.length > 1)
    {
        self.mRemoveSummaryButton.hidden = NO;
    }
    else
    {
        self.mRemoveSummaryButton.hidden = YES;
    }
}

- (void)textNameFieldEditChanged:(UITextField *)textField
{
    [mBeaconsMgr setScanNameFilter: self.mFilterNameEdit.text caseIgnore:YES];
    if (self.mFilterNameEdit.text.length > 1)
    {
        self.mRemoveFilterNameButton.hidden = NO;
    }
    else
    {
        self.mRemoveFilterNameButton.hidden = YES;
    }
}

- (IBAction)onEditFilter:(id)sender {
    [self toggleEditFilterView];
}

- (IBAction)onRssiFilterValueChange:(id)sender
{
    [mBeaconsMgr setScanRssiFilter:[NSNumber numberWithInt: (int)self.mRssiFilterSlide.value]];
    self.mRssiFilterLabel.text = [mBeaconsMgr.scanMinRssiFilter stringValue];
}

- (IBAction)onRemoveAllFilter:(id)sender {
    self.mFilterNameEdit.text = @"";
    self.mRssiFilterSlide.value = self.mRssiFilterSlide.minimumValue;
    
    [self updateFilterSummary];
}

- (IBAction)onRemoveNameFilter:(id)sender {
    self.mFilterNameEdit.text = @"";
}


- (IBAction)onClickActionItem:(id)sender {
    
    if ([self.actionButton.title isEqualToString:ACTION_START_SCAN])
    {
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
    }
    else
    {
        [mBeaconsMgr stopScanning];
        self.actionButton.title = ACTION_START_SCAN;
    }
}


-(void)onBeaconDiscovered:(NSArray<KBeacon*>*)beacons
{
    KBeacon* pBeacon = nil;
    for (int i = 0; i < beacons.count; i++)
    {
        pBeacon = [beacons objectAtIndex:i];
        
        [mBeaconsDictory setObject:pBeacon forKey:pBeacon.UUIDString];
        
        /*
         //filter iBeacon packet
        if ([pBeacon getAdvPacketByType:KBAdvTypeIBeacon] > 0)
        {
            [mBeaconsDictory setObject:pBeacon forKey:pBeacon.UUIDString];
        }*/
    }
    
    mBeaconsArray = [mBeaconsDictory allValues];
    [_beaconsTableView reloadData];
}

-(void)onCentralBleStateChange:(BLECentralMgrState)newState
{
    if (newState == BLEStatePowerOn)
    {
        //the app can start scan in this case
        NSLog(@"central ble state power on");
    }
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    //auto matic start scan
    if ([self.actionButton.title isEqualToString:ACTION_STOP_SCAN])
    {
        [mBeaconsMgr startScanning];
    }
}

- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    
    if ([self.actionButton.title isEqualToString:ACTION_STOP_SCAN])
    {
        [mBeaconsMgr stopScanning];
    }
}


- (void) refreshTableView
{
    if (self.beaconsTableView.refreshControl.refreshing)
    {
        self.beaconsTableView.refreshControl.attributedTitle = [[NSAttributedString alloc]initWithString:ACTION_REFRESHING];
        
        [self performSelector:@selector(clearBeaconDevice) withObject:nil afterDelay:1];
    }
}

-(void) clearBeaconDevice
{
    [self.beaconsTableView.refreshControl endRefreshing];
    
    self.beaconsTableView.refreshControl.attributedTitle = [[NSAttributedString alloc]initWithString:PUSH_TO_RELEASE];
    
    [mBeaconsMgr clearBeacons];
    
    [mBeaconsDictory removeAllObjects];
    mBeaconsArray = nil;
    
    [self.beaconsTableView reloadData];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 5;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return mBeaconsArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row > mBeaconsArray.count)
    {
        return nil;
    }
    
    static NSString * cellIdentifier = @"BeaconViewCellIdentify";
    KBeaconViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (cell == nil)
    {
        return nil;
    }
    
    KBeacon* pBeacons = [mBeaconsArray objectAtIndex: indexPath.row];
    if (pBeacons == nil)
    {
        return nil;
    }
    
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
    
    KBAdvPacketIBeacon* piBeaconAdvPacket = (KBAdvPacketIBeacon*)[pBeacons getAdvPacketByType:KBAdvTypeIBeacon];
    if (piBeaconAdvPacket != nil)
    {
        //because IOS app can not get UUID from advertisement, so we try to get uuid from configruation database, the UUID only avaiable when device connected
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
    
    cell.beacon = pBeacons;
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if([segue.identifier isEqualToString:@"sceShowDeviceDetail"])
    {
        DeviceViewController *deviceController = segue.destinationViewController;
        KBeaconViewCell *cell = (KBeaconViewCell *)[self.beaconsTableView cellForRowAtIndexPath:[self.beaconsTableView indexPathForSelectedRow]];
        deviceController.beacon = cell.beacon;
    }
}

-(void)showMsgDlog:(NSString*)strTitle message:(NSString*)message
{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:ERR_TITLE message:ERR_BLE_FUNC_OFF preferredStyle:UIAlertControllerStyleAlert];
      UIAlertAction *OkAction = [UIAlertAction actionWithTitle:DLG_OK style:UIAlertActionStyleDestructive handler:nil];
      [alertController addAction:OkAction];
      [self presentViewController:alertController animated:YES completion:nil];
}

@end
