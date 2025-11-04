#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen/NativeReactNativeWindowsThermalPrinterDataTypes.g.h")
  #include "codegen/NativeReactNativeWindowsThermalPrinterDataTypes.g.h"
#endif
#include "codegen/NativeReactNativeWindowsThermalPrinterSpec.g.h"

#include "NativeModules.h"

namespace winrt::ReactNativeWindowsThermalPrinter
{

// See https://microsoft.github.io/react-native-windows/docs/native-platform for help writing native modules

REACT_MODULE(ReactNativeWindowsThermalPrinter)
struct ReactNativeWindowsThermalPrinter
{
  using ModuleSpec = ReactNativeWindowsThermalPrinterCodegen::ReactNativeWindowsThermalPrinterSpec;

  REACT_INIT(Initialize)
  void Initialize(React::ReactContext const &reactContext) noexcept;

  REACT_SYNC_METHOD(multiply)
  double multiply(double a, double b) noexcept;

  REACT_METHOD(getDeviceList)
  winrt::fire_and_forget getDeviceList(React::ReactPromise<std::vector<std::string>> promise) noexcept;

  REACT_METHOD(connectPrinter)
  winrt::fire_and_forget connectPrinter(std::string deviceId, React::ReactPromise<std::string> promise) noexcept;

private:
  React::ReactContext m_context;
};

} // namespace winrt::ReactNativeWindowsThermalPrinter
