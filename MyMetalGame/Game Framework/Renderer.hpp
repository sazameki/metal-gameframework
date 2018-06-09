//
//  Renderer.hpp
//  MyMetalGame
//
//  Created by numata on 2018/06/05.
//  Copyright (c) 2018 Satoshi Numata. All rights reserved.
//

#import <MetalKit/MetalKit.h>
#include "Color.hpp"
#include "BlendMode.hpp"


@interface Renderer : NSObject <MTKViewDelegate>

-(nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)view;

@end

