//
//  AppDelegate.mm
//  MyMetalGame
//
//  Created by numata on 2018/06/05.
//  Copyright (c) 2018 Satoshi Numata. All rights reserved.
//

#import "AppDelegate.hpp"
#import "Globals.hpp"
#import <os/log.h>


static AppDelegate*   sInstance = nil;


@interface AppDelegate ()

@end


@implementation AppDelegate

+ (AppDelegate *)sharedInstance
{
    return sInstance;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    sInstance = self;

    NSView *metalView = (__bridge NSView *)__gMTKView;
    [metalView.window makeKeyWindow];
    [metalView.window makeFirstResponder:metalView];
}

- (void)applicationWillTerminate:(NSNotification *)aNotification
{
    // Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}

@end

