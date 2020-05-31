//
//  main.m
//  KBeaconDemo
//
//  Created by kkm on 2018/12/7.
//  Copyright © 2018 kkm. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int main(int argc, char * argv[]) {
    @try {
        @autoreleasepool {
            return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
        }
    } @catch (NSException *exception) {
        NSLog(@"Stack trace:%@", [exception callStackSymbols]);
    } @finally {
        ;
    }
    
}
