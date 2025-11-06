#import "ReactNativeWindowsThermalPrinter.h"

@implementation ReactNativeWindowsThermalPrinter
RCT_EXPORT_MODULE()

RCT_REMAP_METHOD(getDeviceList,
                 getDeviceListWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
  reject(@"E_NOT_IMPLEMENTED", @"getDeviceList is not implemented on iOS", nil);
}

RCT_REMAP_METHOD(connectPrinter,
                 connectPrinterWithDeviceId:(NSString *)deviceId
                 resolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
  reject(@"E_NOT_IMPLEMENTED", @"connectPrinter is not implemented on iOS", nil);
}

RCT_REMAP_METHOD(closeConn,
                 closeConnWithResolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
  reject(@"E_NOT_IMPLEMENTED", @"closeConn is not implemented on iOS", nil);
}

RCT_REMAP_METHOD(printText,
                 printTextWithText:(NSString *)text
                 resolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
  reject(@"E_NOT_IMPLEMENTED", @"printText is not implemented on iOS", nil);
}

RCT_REMAP_METHOD(printBill,
                 printBillWithText:(NSString *)text
                 resolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
  reject(@"E_NOT_IMPLEMENTED", @"printBill is not implemented on iOS", nil);
}

RCT_REMAP_METHOD(printImageBase64,
                 printImageBase64WithBase64:(NSString *)base64
                 width:(nullable NSNumber *)width
                 height:(nullable NSNumber *)height
                 resolver:(RCTPromiseResolveBlock)resolve
                 rejecter:(RCTPromiseRejectBlock)reject)
{
  reject(@"E_NOT_IMPLEMENTED", @"printImageBase64 is not implemented on iOS", nil);
}

- (std::shared_ptr<facebook::react::TurboModule>)getTurboModule:
(const facebook::react::ObjCTurboModule::InitParams &)params
{
  return std::make_shared<facebook::react::NativeReactNativeWindowsThermalPrinterSpecJSI>(params);
}

@end
