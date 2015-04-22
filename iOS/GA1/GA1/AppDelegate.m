//
//  AppDelegate.m
//  GA1
//
//  Created by Brian Kelly on 4/21/15.
//  Copyright (c) 2015 Golgi. All rights reserved.
//

#import "AppDelegate.h"
#import "GA1SvcWrapper.h"
#import "libGolgi.h"
#import "GOLGI_KEYS.h"


@interface AppDelegate ()

@end

@implementation AppDelegate

+ (NSString *)getInstanceId
{
    return @"iOS";
}


// GOLGI
//********************************* Registration ***************************
//
// Setup handling of inbound SendMessage methods and then Register with Golgi
//
- (void)doGolgiRegistration
{
    //
    // Do this before registration because on registering, there may be messages queued
    // up for us that would arrive and be rejected because there is no handler in place
    //
    
    // [TapTelegraphSvc registerSendMessageRequestReceiver:self];
    
    //
    // and now do the main registration with the service
    //
    NSLog(@"Registering with golgiId: '%@'", [AppDelegate getInstanceId]);
    
    
    
    NSString *instanceId = [AppDelegate getInstanceId];
    
    if(instanceId.length > 0){
        [Golgi registerWithDevId:GOLGI_DEV_KEY
                           appId:GOLGI_APP_KEY
                          instId:instanceId
                andResultHandler:^(NSString *errorText) {
                    if(errorText != nil){
                        NSLog(@"Golgi Registration: FAIL => '%@'", errorText);
                    }
                    else{
                        NSLog(@"Golgi Registration: PASS");
                    }
                }];
    }
}


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    {extern void enableOMNLogging(); enableOMNLogging();}

    if(launchOptions != nil) {
        // Launched from push notification
        NSDictionary *d = [launchOptions objectForKey:UIApplicationLaunchOptionsRemoteNotificationKey];
        if(d != nil){
            //
            // Ok, launched into the background, setup Golgi
            //
            
            /*
             UILocalNotification* localNotification = [[UILocalNotification alloc] init];
             localNotification.alertBody = @"Launching into BG";
             [[UIApplication sharedApplication] cancelAllLocalNotifications];
             [[UIApplication sharedApplication] scheduleLocalNotification:localNotification];
             */
            
            [Golgi enteringBackground];
            [Golgi useEphemeralConnection];
        }
    }
    
    [self doGolgiRegistration];

    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    
    
    //
    // GOLGI: Tell the framework that we are going into the background
    //
    NSLog(@"applicationDidEnterBackground()");
    [Golgi enteringBackground];
    [Golgi useEphemeralConnection];
    NSLog(@"applicationDidEnterBackground() complete");
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    
    //
    // GOLGI: Tell the framework that we are active again
    //
    
    NSLog(@"applicationDidBecomeActive()");
    [Golgi enteringForeground];
    [Golgi usePersistentConnection];
    

}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
