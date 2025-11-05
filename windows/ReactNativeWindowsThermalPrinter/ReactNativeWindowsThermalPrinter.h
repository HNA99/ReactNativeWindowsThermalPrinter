#pragma once

#include "pch.h"
#include "resource.h"

#if __has_include("codegen/NativeReactNativeWindowsThermalPrinterDataTypes.g.h")
  #include "codegen/NativeReactNativeWindowsThermalPrinterDataTypes.g.h"
#endif
#include "codegen/NativeReactNativeWindowsThermalPrinterSpec.g.h"

#include "NativeModules.h"
#include <winrt/Windows.Devices.PointOfService.h>

using namespace winrt;
using namespace Windows::Devices::PointOfService;

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

    REACT_METHOD(closeConn)
      winrt::fire_and_forget closeConn(React::ReactPromise<void> promise) noexcept;

    REACT_METHOD(printText)
      winrt::fire_and_forget printText(std::string text, React::ReactPromise<void> promise) noexcept;

    REACT_METHOD(printBill)
      winrt::fire_and_forget printBill(std::string text, React::ReactPromise<void> promise) noexcept;

    REACT_METHOD(printImageBase64)
      winrt::fire_and_forget printImageBase64(std::string base64Image, std::optional<double> width, std::optional<double> height, React::ReactPromise<void> promise) noexcept;

    private:
      React::ReactContext m_context;
      ClaimedPosPrinter m_claimedPrinter{ nullptr };
  };

} // namespace winrt::ReactNativeWindowsThermalPrinter
