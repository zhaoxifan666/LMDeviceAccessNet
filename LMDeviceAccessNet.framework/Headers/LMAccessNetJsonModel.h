//
//  LMAccessNetJsonModel.h
//  LMDeviceAccessNet
//
//  Created by MadHeart on 2021/3/17.
//

#import <Foundation/Foundation.h>
#import <HomeKit/HomeKit.h>

#import <LMSmartConnect/LMAccessNetCategory.h>


NS_ASSUME_NONNULL_BEGIN

///SDK版本号
#define SDKVersion  @"7.0"

///网关入网引导页
#define LMAccessNetPageId_guidePage @"guidePage"

/// 设备入网引导页
#define LMAccessNetPageId_new_guidePage @"usedGuidePage"

///网关入网重置页
#define LMAccessNetPageId_resetPage @"resetPage"

///搜索设备界面
#define LMAccessNetPageId_searchDevicePage @"searchDevicePage"

///子设备绑定到网关界面（睡眠带）
#define LMAccessNetPageId_bindGatewayPage @"bindGatewayPage"

///子设备入网选择网关界面
#define LMAccessNetPageId_chooseGatewayPage @"chooseGatewayPage"

//ios 蓝牙入网步骤
#define LMAccessNetPageId_addDeviceStepPage @"addDeviceStepPage"

///选择WiFi界面
#define LMAccessNetPageId_chooseWifiPage @"chooseWifiPage"

///暂时没用
#define LMAccessNetPageId_addDeviceSuccessPage @"addDeviceSuccessPage"

//扫描二维码界面
#define LMAccessNetPageId_scanQRPage @"scanQRPage"

/// 手动输入Matter配对码页面
#define LMAccessNetPageId_manualCodePage @"manualCodePage"

/// 连接Matter设备页面
#define LMAccessNetPageId_connectMatterDevciePage @"connectMatterDevciePage"

/// 绑定Matter设备页面
#define LMAccessNetPageId_bindMatterDevicePage @"bindMatterDevicePage"

//iOS 选择设备热点wifi引导界面
#define LMAccessNetPageId_iOSChooseDeviceApPage @"iOSChooseDeviceApPage"

//添加设备过程界面
#define LMAccessNetPageId_addDeviceProPage @"addDeviceProPage"

///绑定好HomeKit界面
#define LMAccessNetPageId_addHomeKitPage @"addHomeKitPage"

///选择Homekit家庭界面
#define LMAccessNetPageId_chooseHomePage @"chooseHomePage"

///添加失败界面
#define LMAccessNetPageId_addFailPage @"addFailPage"

///摄像头二维码界面
#define LMAccessNetPageId_cameraQRPage @"cameraQRPage"

///通过HomeKit入网后绑定到Aiot界面
#define LMAccessNetPageId_bindCloudPage @"bindCloudPage"

///没有网关 添加网关界面
#define LMAccessNetPageId_addGatewayPage @"addGatewayPage"

///选择配网方式页面，旧的是在右上角切换，这里设计给了新的一套，需要单独页面
#define LMAccessNetPageId_choseConnectTypePage @"choseConnectTypePage"

/// 套装入网引导页面
#define LMAccessNetPageId_deviceKitGuidePage @"deviceKitGuidePage"

/// MagicPair扫描页面
#define LMAccessNetPageId_searchMagicPairDevicePage @"searchMagicPairDevicePage"

/// 确认Matter设备页面
#define LMAccessNetPageId_confirmMatterDevicePage @"confirmMatterDevicePage"

/// 蓝牙唤醒页面
#define LMAccessNetPageId_wakeUpBLEbroadcasPage @"wakeUpBLEBroadcastPage"

@class LMAccessNetDeviceModel;

typedef enum : NSUInteger {
    LMAccessNetTypeNone,
    LMAccessNetTypeAp_udp,
    LMAccessNetTypeHomeKit,         // 必须先入网HomeKit再绑定到云端的一种入网方式
    LMAccessNetTypeZigbee,          // 云端模式下zigbee设备入网
    LMAccessNetTypeCamera_a,        // 用于G2, G2H
    LMAccessNetTypeCamera_b,        // 用于G3, 相对（G2/G2H）生成二维码的加密方式变了
    LMAccessNetTypeEthernet,        // 用于有线入网的
    LMAccessNetTypeBle_gateway,     // 用于蓝牙网关入网的
    LMAccessNetTypeBle_zigbee,      // 用于蓝牙子设备入网的
    LMAccessNetTypeAp_tcp,          // 用于tcp入网（好博设备）
    LMAccessNetType4G,              // 用于4G设备入网
    LMAccessNetTypeHomeKit_mode,    // 纯HomeKit模式独立设备入网
    LMAccessNetTypeHomeKit_zigbee,  // 纯HomeKit模式下zigbee子设备入网到独立设备
    LMAccessNetTypeBle_doorlock,    // 门锁入网方式，目前门锁需要把入网配置的json回调出去让门锁处理
    LMAccessNetTypeBleSubDevice,    // 纯蓝牙的子设备入网
    LMAccessNetTypeMPBleSubDevice,    // magic Pair子设备入网
    LMAccessNetTypeMagicPair        //e1magic_pair
} LMAccessNetType;

/// 蓝牙广播模式
typedef NS_ENUM(NSUInteger, LMAccessNetBleBroadcastMode) {
    /// 蓝牙广播始终开启（ABM）
    LMAccessNetBleBroadcastModeAlways,
    /// 蓝牙可重新开启（CBM）
    LMAccessNetBleBroadcastModeConditional,
    /// 蓝牙入网后不可开启（LBM）
    LMAccessNetBleBroadcastModeLimited,
};

typedef enum : NSUInteger {
    //未知错误（code:-1）
    LMAccessNetErrorCodeUnexpectedError = -1,
    
    
    //入网超时\n1、仅支持2.4GHz WiFi连接，并确保手机/平板与网关处于同一Wi-Fi环境覆盖下；\n2、请检查Wi-Fi及密码是否拼写正确；
    LMAccessNetErrorCodeTimeOut = 100,
    
    
    //设备未注册\n1、请确认网关已播报“网络连接成功”语音提示，这表明网关已连接服务器，若未提示，请重置网关后再试。\n2、请确保网关所连接的路由器网络可正常连接互联网。"
    LMAccessNetErrorCodeNotRegister = 601,
    
    //设备已绑定(code:607)
    LMAccessNetErrorCodeDidBinded = 607,
    
    
    //设备模型不支持（可用于串货提醒）（code:616）
    LMAccessNetErrorCodeAreaNotSupported = 616,
    
    
    //绑定失败，请重试（code:624）需要重新绑定
    LMAccessNetErrorCodeBindFailed = 624,
    
    //设备已绑定(code:626)
    LMAccessNetErrorCodeDidBinded1 = 626,
    
    /// 网关子设备数量限制
    LMAccessNetErrorCodeSubDeviceLimit = 683,
    
    //设备不允许绑定, 该设备已绑定其他账号（cdoe:656）
    LMAccessNetErrorCodeDidBindedOnOtherAccount = 656,
    
    //SN渠道管控
    LMAccessNetErrorCodeSerialNumControl = 668,
    
    //网络不可用
    LMAccessNetErrorCodeNetworkUnexpected = 10000,
    
    //连接设备热点失败，请手动进行切换设备热点:
    LMAccessNetErrorCodeConnectDeviceAPFailed = 10002,
    
    //参数异常
    LMAccessNetErrorCodeInvalidParams = 10003,

    
    //请检查设备是否处于等待入网状态(code:10004) 发送入网信息失败
    LMAccessNetErrorCodeNotAvaliable = 10004,
    
    //参数错误，尚不支持该入网类型。请联系客服
    LMAccessNetErrorCodeErrorParams = 10005,
    
    //不支持该设备，请联系客服(code:10006)
    LMAccessNetErrorCodeUnsupportDevice = 10006,
    
    //牙连接断开，请检查设备是否处于入网状态(code:10007)
    LMAccessNetErrorCodeBlueToothBreak = 10007,
    
    
    //连接设备蓝牙失败，请检查设备是否处于入网状态(code:10008)
    LMAccessNetErrorCodeConnectBLEDeviceFailed = 10008,
    
    //维码生成失败，请重试(code:10009)
    LMAccessNetErrorCodeGernerateQRCodeFailed = 10009,
    
    //添加设备超时，请重试
    LMAccessNetErrorCodeAddDeviceTimeOut = 10010,
    
    //添加设备超时，请重试（支持5G网络）
    LMAccessNetErrorCodeAddDeviceTimeOut5G = 10015,
    
    //添加子设备超时，请重试
    LMAccessNetErrorCodeAddChildDeviceTimeOut = 10012,
    
    //切换云平台错误
    LMAccessNetErrorCodeSwitchToAiotError = 10013

} LMAccessNetErrorCode;

@interface LMAccessNetJsonModel : NSObject



///所有界面的json数据  每次选择一个设备后需要重新设置该值
@property(nonatomic, strong)NSDictionary *allPageJson;


@property(nonatomic, strong)LMAccessNetDeviceModel *device;


/// 用户选择的WiFi名称
@property(nonatomic, copy)NSString *ssid;


/// 用户输入的WiFi密码
@property(nonatomic, copy)NSString *password;

//用户设置过的bindKey;
@property(nonatomic, copy)NSString *userBindKey;

/// 重新请求到的bindKey
@property(nonatomic, copy)NSString *bindKey;


///设备入网的服务器域名
@property(nonatomic, copy)NSString *countryDomain;




///设备入网类型枚举
@property(nonatomic, assign)LMAccessNetType accessNetType;


/// 用户选择的入网流程页面Map
@property(nonatomic, strong)NSDictionary *targetAccessLink;

///zigbee3.0子设备扫码入网时的installCode;
@property(nonatomic, copy)NSString *installCode;



///用户选择入网的房间id
@property(nonatomic, copy)NSString *roomId;



///用户选择入网房间所在的家的id
@property(nonatomic, copy)NSString *homeId;



@property(nonatomic, copy)NSString *iconBaseUrl;

//入网结果
@property(nonatomic)id accessNetResult;

///用户选择的设备入网信息（主要用于子设备入网时所能入网的网关列表）
@property(nonatomic, strong, nullable)LMAccessNetCategoryDevice  *targetAccessNetDevice;

///设备入网错误，由客户端定义，然后根据json中错误码找到错误描述
@property(nonatomic, strong)NSError *bindError;

//发现设备的iP地址（以太网发现）
@property(nonatomic, copy)NSString *targetDeviceIP;

//发现设备的端口地址（以太网发现）
@property(nonatomic)int targetDevicePort;

//是否只用HomeKit模式入网，只是用HomeKit入网，就不需要接入私有云
@property(nonatomic, assign)BOOL isOnlyHomeKitMode;

/// 使用Apple Homekit模式入网，需要选择入网的apple home家庭
@property(nonatomic, strong)HMHome *appleHome;


//homekit模式下 子设备入网时用户选择的HomeKit设备
@property(nonatomic, strong)HMAccessory *targetAccessory;

+ (instancetype)sharedInstance;


+ (void)destory;

/// 根据设备模型值生成对应的设备图片地址
/// @param model 设备模型值
- (NSString *)iconUrlWithModel:(NSString *)model;

/// 根据pageId获取对应界面的json数据并转换为NSDictionary对象
/// @param pageId 页面pageId
- (NSDictionary *)getDataWithPageId:(NSString *)pageId;


/// 根据当前页面id获取下一个页面ID，如果当前页面id是空的 则返回第一个（开始）页面ID
/// @param pageId 当前页面Id
- (NSString *)getNextPageIdWithCurrentPageId:(NSString *)pageId;

/// 根据当前页面获取要返回的页面id
/// @param pageId 为“”时表示正常返回
- (NSString *)getPrePageIdWithCurrentPageId:(NSString *)pageId;


/// 根据页面id获取对应vc类名
/// @param pageId 当前页面Id
- (NSString *)getViewControllerClassNameWithPageId:(NSString *)pageId;



/// 判断当前页面后时候还有其他入网流程界面
/// 用于一个入网流程结束界面（比如：摄像机入网私有云后，还要继续入网HomeKit平台）
/// @param pageId 当前页面pageId
- (BOOL)hasNextPageOrProcessPageWithCurrentPageId:(NSString *)pageId;


/// 获取切换入网模式后的切换提示文案
/// @param type 入网类型
- (NSString *)getSwithModeTipWithType:(LMAccessNetType)type;


/// 获取入网类型的标题
/// @param modeString 入网类型string文本
- (NSString *)getAccessNetTypeTitleWithModeString:(NSString *)modeString;
@end


///设备的通用model

@interface LMAccessNetDeviceModel : NSObject
/// 是否支持Apple Homekit
@property(nonatomic, assign)BOOL homeKit;


/// 入网后是否需要绑定到私有云（AiOT）
@property(nonatomic, assign)BOOL needbindGateway;


///设备名称
@property(nonatomic, copy)NSString *deviceName;


///设备的model值
@property(nonatomic, copy)NSString *model;


///入网超时时间（一般为网关的入网超时时间）, 也用作子设备入网超时时间（根据所入网关取网关规定的开启子设备入网时间）
@property(nonatomic, assign)NSInteger accessTimeout;


///特殊设备识别时的modelId
@property(nonatomic, copy)NSString *modelId;


///特殊设备识别时的modelId数组，这里是相同设备入网逻辑的合并到这里
@property(nonatomic, copy)NSArray *modelIdGroup;

@property (nonatomic, copy) NSArray *modelGroup;

///特殊设备识别的商品ID
@property(nonatomic, copy)NSString *pId;


///设备生成的WiFi热点前缀列表
@property(nonatomic, strong)NSArray *wifiPrefix;


///设备的入网方式(不再使用)
//@property(nonatomic, strong)NSArray *accessMode;


///是否支持5GHz网络
@property(nonatomic, assign)BOOL support5G;


///设备入网跳转逻辑
@property(nonatomic, strong)NSArray *iOSAccessLink;


@property(nonatomic, strong)NSArray *androidAccessLink;

/// 设备入网错误码字典
@property(nonatomic, strong)NSDictionary *errorCode;


///设备的mac地址（一些设备可通过扫码获取到mac地址）
@property(nonatomic, copy)NSString *macAddress;

///设备入网的密钥 （一些设备可通过扫码获取到 比如4G蜂助手）
@property(nonatomic, copy)NSString *cipherText;

/// 解密的秘文
@property(nonatomic, copy)NSString *decodeText;

@property(nonatomic, copy)NSString *blePeripheralId;

@property(nonatomic, copy)NSString *bleCBServiceId;

@property(nonatomic, copy)NSString *bleCBWriteCharId;

@property(nonatomic, copy)NSString *bleCBReadCharId;

/// 蓝牙广播模式
@property (nonatomic, assign) LMAccessNetBleBroadcastMode bleBroadcastMode;

@end

NS_ASSUME_NONNULL_END
