//
//  LMAccessNetDeviceListViewController.h
//  LMDeviceAccessNet
//
//  Created by MadHeart on 2021/3/31.
//

#import <LMFramework/LMFramework.h>

@class LMAccessNetCategoryDevice;
@interface LMAccessNetDeviceListViewController : LMBaseViewController

- (instancetype)initWithGatewayId:(NSString*)gatewayId;

+ (void)handleAccessNetWithDevice:(LMAccessNetCategoryDevice *)device;

@end
