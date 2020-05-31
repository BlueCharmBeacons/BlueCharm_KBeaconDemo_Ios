//
//  AppDelegate.m
//  KBeaconDemo
//
//  Created by kkm on 2018/12/7.
//  Copyright © 2018 kkm. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()

@end

#define App_Bar_Color [UIColor colorWithRed:42/255.0 green:42/255.0 blue:42/255.0 alpha:1.0]
#define App_Text_Color [UIColor whiteColor]


@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;

    
    // Navigation bar styling
  //  [[UINavigationBar appearance] setBarStyle:UIStatusBarStyleDefault];
    //[[UINavigationBar appearance] setTranslucent:NO];
    //[[UINavigationBar appearance] setTintColor:App_Text_Color];
    //[[UINavigationBar appearance] setBarTintColor:App_Bar_Color];
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
