package com.windowsthermalprinter

import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.module.annotations.ReactModule

@ReactModule(name = ReactNativeWindowsThermalPrinterModule.NAME)
class ReactNativeWindowsThermalPrinterModule(reactContext: ReactApplicationContext) :
  NativeReactNativeWindowsThermalPrinterSpec(reactContext) {

  override fun getName(): String {
    return NAME
  }

  @ReactMethod
  fun getDeviceList(promise: Promise) {
    promise.reject("E_NOT_IMPLEMENTED", "getDeviceList is not implemented on Android")
  }

  @ReactMethod
  fun connectPrinter(deviceId: String, promise: Promise) {
    promise.reject("E_NOT_IMPLEMENTED", "connectPrinter is not implemented on Android")
  }

  @ReactMethod
  fun closeConn(promise: Promise) {
    promise.reject("E_NOT_IMPLEMENTED", "closeConn is not implemented on Android")
  }

  @ReactMethod
  fun printText(text: String, promise: Promise) {
    promise.reject("E_NOT_IMPLEMENTED", "printText is not implemented on Android")
  }

  @ReactMethod
  fun printBill(text: String, promise: Promise) {
    promise.reject("E_NOT_IMPLEMENTED", "printBill is not implemented on Android")
  }

  @ReactMethod
  fun printImageBase64(base64: String, width: Int?, height: Int?, promise: Promise) {
    promise.reject("E_NOT_IMPLEMENTED", "printImageBase64 is not implemented on Android")
  }

  companion object {
    const val NAME = "ReactNativeWindowsThermalPrinter"
  }
}
