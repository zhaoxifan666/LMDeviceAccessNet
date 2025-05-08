//
//  LMDeviceAccessNetMsgCenter.h
//  LMDeviceAccessNet
//
//  Created by MadHeart on 2021/3/19.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <LMFramework/LMFramework.h>
#import <HomeKit/HomeKit.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const kLMSkipAccessNetGuidePageNotificationName;

@interface LMAccessNetUISDK : NSObject

+ (instancetype)sharedInstance;

//通过magic Pair deeplink打开
@property(nonatomic, assign)BOOL openByMpDeepLink;

/// 入网时传递的网关Id，如果不为空时，会跳过选择网关页面
@property(nonatomic, copy) NSString *gatewayId;

/// 入网完成之后是否需要回调到RN页面
@property (nonatomic, assign) BOOL needGoBackWhenAccessFinish;

//设备不支持入网配置化回调
@property(nonatomic, copy)void (^notSupportConfigAccessNet)(NSDictionary *deviceDic);

//入网配置化json回调
@property(nonatomic, copy)void (^accessNetViewConfigJson)(NSDictionary *jsonDic);

/// 用户引导回调
@property (nonatomic, copy) void (^accessNetUserGuideCallBack)(NSDictionary *json);

/// Matter失败页跳转Matter FAQ相关H5
@property (nonatomic, copy) void (^accessMatterFAQCallBack)(void);


@property(nonatomic, copy)void (^accessNetCallBack)(id response, NSError *error, __kindof UIViewController *controller);

/// 隐私协议回调
@property(nonatomic, copy)void (^privacyCallBack)(NSString *url,  void (^__nullable actionCallBack)(BOOL  showAgain));

- (void)launchMagicPair;

///处理弹窗遮挡问题
- (void)hasOtherAlertWindow:(BOOL)hasOther;


/// 设置家庭id, 用于当前家庭的信息获取
/// @param homeId NSString
- (void)setAccessNetHomeId:(NSString *)homeId;


/// 设置设备入网bindkey（如果需要SDK中自请求 可以不用设置该参数）
/// @param bindKey NSString
- (void)setAccessNetBindKey:(NSString *)bindKey;


/// 设置入网基本信息
/// @param homeId 家庭Id
/// @param bindKey bindKey 如果需要SDK中自请求 可以不传此参数
- (void)setAccessNetHomeId:(NSString *)homeId bindKey:(NSString *)bindKey;


/// 是否只使用Apple HomeKit模式入网，不会接入私有云, 默认为NO
/// @param flag YES or NO
- (void)setOnlyUseHomeKitMode:(BOOL)flag;


/// 使用Apple Homekit模式入网，需要选择入网的apple homeJ家庭
/// @param home HMHome instance
- (void)setAccessNetAppleHome:(HMHome *)home;



/// 设置入网UI图片的基础url
/// @param url 设置入网
- (void)setAccessNetImgBaseUrl:(NSString *)url;

/// 获取入网UI图片的基础url
- (NSString *)getAccessNetImgBaseUrl;

/// 获取内部SDK版本号
- (NSString *)getSDKVersion;

/// 获取某个设备配置的json数据
/// @param model 设备model值/pid值
/// @param sdkVersion 当前sdk版本
/// @param configVersion json配置的版本
/// @param completion 结果回调
- (void)requestJsonDataWithDeviceModel:(NSString *)model sdkVersion:(NSString * _Nullable)sdkVersion configVersion:(NSString * _Nullable)configVersion completion:(void (^)(id  _Nonnull response, NSError * _Nonnull error))completion;

/// 开始进入入网流程
/// @param pageData 设备入网配置的json数据，通过私有云获取
- (void)startAccessNetWithPageData:(NSDictionary *)pageData;

/// 进入已经支持入网的设备列表界面
- (void)pushSupportedDeviceListPage:(NSString*)gatewayId;

/// 打开扫码页面
- (void)openScanQRCodePage:(NSString *)gatewayId;

- (void)goToUpdateWifiPage:(NSString *)did model:(NSString *)model;

- (void)goToSwitchThreadPage:(NSString*)did;

/// 获取设备配置json数据，成功后直接进入入网流程
/// @param model 设备model值/pid值
/// @param sdkVersion 当前sdk版本
/// @param configVersion json配置的版本
/// @param completion 结果回调，有错误表示获取设备配置json数据失败，或者数据错误
- (void)rqeuestJsonAndStartAccessNetWithModel:(NSString *)model sdkVersion:(NSString * _Nullable)sdkVersion configVersion:(NSString * _Nullable)configVersion completion:(void (^)(NSError *error))completion;

/// 获取设备配置json数据，成功后直接进入入网流程
/// @param model 设备model值/pid值
/// @param gatewayId 网关Id，如果传递此值，那么会直接跳过选择网关页面
/// @param sdkVersion 当前sdk版本
/// @param configVersion json配置的版本
/// @param needGoBackWhenAccessFinish 入网结束后是否需要回到入网前的页面
/// @param completion 结果回调，有错误表示获取设备配置json数据失败，或者数据错误
- (void)requestJsonAndStartAccessNetWithModel:(NSString *)model
                                    gatewayId:(NSString *)gatewayId
                                   sdkVersion:(NSString * _Nullable)sdkVersion
                                configVersion:(NSString * _Nullable)configVersion
                   needGoBackWhenAccessFinish:(BOOL)needGoBackWhenAccessFinish
                                   completion:(void (^)(NSError *error))completion;

/// 获取设备配置json数据，成功后直接进入入网流程
/// @param model 设备model值/pid值
/// @param gatewayId 网关Id，如果传递此值，那么会直接跳过选择网关页面
/// @param sdkVersion 当前sdk版本
/// @param configVersion json配置的版本
/// @param needGoBackWhenAccessFinish 入网结束后是否需要回到入网前的页面
/// @param magicPaicCode magicPaic码
/// @param completion 结果回调，有错误表示获取设备配置json数据失败，或者数据错误
- (void)requestJsonAndStartAccessNetWithModel:(NSString *)model
                                    gatewayId:(NSString *)gatewayId
                                   sdkVersion:(NSString * _Nullable)sdkVersion
                                configVersion:(NSString * _Nullable)configVersion
                   needGoBackWhenAccessFinish:(BOOL)needGoBackWhenAccessFinish
                                magicPaicCode:(NSString *)magicPaicCode
                                   completion:(void (^)(NSError *error))completion;

/// 判断一个HomeKit设备是否需要切换平台，并弹出窗口引导切换
/// @param accessory  新添加到HomeKit的设备
/// @param switchCompletion 回调，isSwitch - yes 切换  - no 不切换
- (BOOL)showSwitchPlatformAlert:(HMAccessory *)accessory switchCompletion:(void (^)(BOOL isSwitch, NSError *error))switchCompletion;

/// 入网解密接口
/// @param encodeText 密文
/// @param completion 解密后的数据
- (void)requestQRDecryptWithEncodeText:(NSString *)encodeText completion:(void(^)(NSDictionary *result, NSError *error))completion;

/// 回到入网前的页面
- (void)popToPreAccessNetPage;

- (void)getLocalNetWorkAuthority:(void(^)(BOOL enable))competion;

#pragma mark - MagicPair
/// Magic Pair 入网页面
/// @param link 链接
- (void)openMPPage:(NSString*)link;

/// 查询homekit或者是matter Payload
/// @param homeKit YES查询homekit，NO查询matter payload。
/// @param did did
/// @param completion 回调
- (void)mdnsQueryHomekitOrMatterPayLoad:(BOOL)homeKit withDid:(NSString*)did completion:(void (^)(NSError* error,NSInteger bind, NSString* qrCode,NSString*digitalPairingCode))completion;

- (void)sendFactoryResetWithDid:(NSString*)did completion:(void(^)(NSError *error))completion;

- (void)removeHomeKitPairingWithDid:(NSString*)did completion:(void(^)(NSError *error))completion;

- (void)sendDeviceToStartHomekitWithDid:(NSString*)did completion:(void(^)(NSError *error))completion;

///切换zigbee的网关
- (void)goToSwitchZigbeeGatewayWithDid:(NSString*)did;

/// 扫描蓝牙设备
- (void)scanDeviceAndShow ;

- (void)stopScan;

#pragma mark - Matter
/// 是否支持Matter
- (BOOL)isSupportMatter;

/// 是否是支持的Matter配对码
- (BOOL)isSupportMatterSetupPayload:(NSString *)setupPayload;

/// 绑定Matter
- (void)bindMatterWithDid:(NSString *)did
             setupPayload:(NSString *)setupPayload
        presentController:(UIViewController *)presentController
               completion:(void(^)(NSError *error))completion;

/// 销毁单例（SDK内部已自管理，生命周期和SDK的vc一样）, 宿主工程酌情使用
+ (void)destory;

#pragma mark - MagicPair & Matter

/// 打开Matter设备配对窗口
/// - Parameters:
///   - did: 设备did
///   - completion: 回调
- (void)openMatterCommissioningWindowWithDid:(NSString *)did completion:(void (^)(NSError *error))completion;

/// 移除MatterFabric
/// - Parameters:
///   - did: 设备did
///   - vendorId: 厂商Id，传0时移除所有生态
///   - completion: 回调
- (void)removeMatterFabricWithDid:(NSString *)did vendorId:(NSInteger)vendorId completion:(void (^)(NSError * _Nullable))completion;

/// 发送重启命令
/// - Parameters:
///   - did: 设备did
///   - completion: 回调
- (void)sendRestartWithDid:(NSString *)did completion:(void (^)(NSError * _Nullable error))completion;

/// 查询已绑定生态信息
/// - Parameters:
///   - did: 设备did
///   - completion: 回调
- (void)queryBoundEcosystemWithDid:(NSString *)did completion:(void (^)(NSError * _Nullable error, NSInteger value))completion;
        
/// 查询已连接的MatterFabric
/// - Parameters:
///   - did: 设备did
///   - completion: 回调
- (void)queryConnectedMatterFabricsWithDid:(NSString *)did completion:(void (^)(NSError * _Nullable error, NSArray *fabrics))completion;

/// 获取MagicPair设备的MatterPayload
/// - Parameter did: 设备did
- (void)queryMatterPayloadWithDid:(NSString *)did completion:(void (^)(NSError *error, NSString *qrCode, NSString *digitalPairingCode))completion;

/// 打开连接AqaraMatter生态页面
/// - Parameters:
///   - did: 设备did
///   - setupPayload: 配对码
///   - completion: 回调
- (void)openConnectAqaraMatterEcosystemGuidePageWithDid:(NSString *)did
                                           setupPayload:(NSString *)setupPayload
                                             completion:(void (^)(NSError * _Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
