//
//  KBCfgTrigger.h
//  KBeacon
//
//  Created by hogen on 2020/2/8.
//  Copyright © 2020 hogen. All rights reserved.
//

#import "KBCfgBase.h"

NS_ASSUME_NONNULL_BEGIN

//trigger type
typedef NS_ENUM(NSInteger, KBTriggerType)
{
    KBTriggerTypeMotion = 0x1,   //motion trigger
    KBTriggerTypeButton = 0x2    //button click trigger
}NS_ENUM_AVAILABLE(8_13, 8_0);

//trigger action option
typedef NS_ENUM(NSInteger, KBTriggerAction)
{
    KBTriggerActionOff = 0x0,     //disable trigger
    KBTriggerActionAdv = 0x1,     //enable advertisment when trigger event happened
    KBTriggerActionAlert = 0x2,   //enable alert when trigger event happened
    KBTriggerActionRecord = 0x4
}NS_ENUM_AVAILABLE(8_13, 8_0);

//button trigger para
typedef NS_ENUM(NSInteger, KBTriggerBtnPara)
{
    KBTriggerBtnHold = 0x1,
    KBTriggerBtnSingleClick = 0x2,
    KBTriggerBtnDoubleClick = 0x4,
    KBTriggerBtnTripleClick = 0x8
}NS_ENUM_AVAILABLE(8_13, 8_0);

//trigger advertisement mode
typedef NS_ENUM(NSInteger, KBTriggerAdvMode)
{
    KBTriggerAdvOnlyMode = 0x0,    //only advertisement when trigger event happened
    KBTriggerAdv2AliveMode = 0x1  //always advertisement
}NS_ENUM_AVAILABLE(8_13, 8_0);
#define KBTriggerAdvIntervalDefault 400

//trigger key
#define JSON_FIELD_TRIGGER_OBJS @"trObj"
#define JSON_FIELD_TRIGGER_TYPE @"trType"
#define JSON_FIELD_TRIGGER_ACTION @"trAct"
#define JSON_FIELD_TRIGGER_PARA @"trPara"
#define JSON_FIELD_TRIGGER_ADV_MODE @"trAMode"
#define JSON_FIELD_TRIGGER_ADV_TYPE @"trAType"
#define JSON_FIELD_TRIGGER_ADV_TIME  @"trATm"
#define JSON_FIELD_TRIGGER_ADV_INTERVAL @"trAPrd"

@interface KBCfgTrigger : KBCfgBase

//trigger type, defined in KBTriggerType
@property (strong, nonatomic) NSNumber* triggerType;

//trigger action, defined in KBTriggerAction
@property (strong, nonatomic) NSNumber* triggerAction;

//trigger parameters
@property (strong, nonatomic) NSNumber* triggerPara;

//trigger advertisement, defined in KBTriggerAdvMode
@property (strong, nonatomic) NSNumber* triggerAdvMode;

//advertisement type when trigger event happened
@property (strong, nonatomic) NSNumber* triggerAdvType;

//advertisement duration when trigger event happened
@property (strong, nonatomic) NSNumber* triggerAdvTime;

//advertisement interval when trigger event happened
@property (strong, nonatomic) NSNumber* triggerAdvInterval;

-(int) updateConfig:(NSDictionary*)dicts;

-(NSMutableDictionary*) toDictionary;

@end

NS_ASSUME_NONNULL_END
