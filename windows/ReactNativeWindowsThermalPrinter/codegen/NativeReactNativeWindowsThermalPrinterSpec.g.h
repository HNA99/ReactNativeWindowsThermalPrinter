
/*
 * This file is auto-generated from a NativeModule spec file in js.
 *
 * This is a C++ Spec class that should be used with MakeTurboModuleProvider to register native modules
 * in a way that also verifies at compile time that the native module matches the interface required
 * by the TurboModule JS spec.
 */
#pragma once
// clang-format off


#include <NativeModules.h>
#include <tuple>

namespace ReactNativeWindowsThermalPrinterCodegen {

struct ReactNativeWindowsThermalPrinterSpec : winrt::Microsoft::ReactNative::TurboModuleSpec {
  static constexpr auto methods = std::tuple{
      Method<void(Promise<std::vector<std::string>>) noexcept>{0, L"getDeviceList"},
      Method<void(std::string, Promise<std::string>) noexcept>{1, L"connectPrinter"},
      Method<void(Promise<void>) noexcept>{2, L"closeConn"},
      Method<void(std::string, Promise<void>) noexcept>{3, L"printText"},
      Method<void(std::string, Promise<void>) noexcept>{4, L"printBill"},
      Method<void(std::string, std::optional<double>, std::optional<double>, Promise<void>) noexcept>{5, L"printImageBase64"},
  };

  template <class TModule>
  static constexpr void ValidateModule() noexcept {
    constexpr auto methodCheckResults = CheckMethods<TModule, ReactNativeWindowsThermalPrinterSpec>();

    REACT_SHOW_METHOD_SPEC_ERRORS(
          0,
          "getDeviceList",
          "    REACT_METHOD(getDeviceList) void getDeviceList(::React::ReactPromise<std::vector<std::string>> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(getDeviceList) static void getDeviceList(::React::ReactPromise<std::vector<std::string>> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          1,
          "connectPrinter",
          "    REACT_METHOD(connectPrinter) void connectPrinter(std::string deviceId, ::React::ReactPromise<std::string> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(connectPrinter) static void connectPrinter(std::string deviceId, ::React::ReactPromise<std::string> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          2,
          "closeConn",
          "    REACT_METHOD(closeConn) void closeConn(::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(closeConn) static void closeConn(::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          3,
          "printText",
          "    REACT_METHOD(printText) void printText(std::string text, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(printText) static void printText(std::string text, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          4,
          "printBill",
          "    REACT_METHOD(printBill) void printBill(std::string text, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(printBill) static void printBill(std::string text, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n");
    REACT_SHOW_METHOD_SPEC_ERRORS(
          5,
          "printImageBase64",
          "    REACT_METHOD(printImageBase64) void printImageBase64(std::string Base64, std::optional<double> width, std::optional<double> height, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n"
          "    REACT_METHOD(printImageBase64) static void printImageBase64(std::string Base64, std::optional<double> width, std::optional<double> height, ::React::ReactPromise<void> &&result) noexcept { /* implementation */ }\n");
  }
};

} // namespace ReactNativeWindowsThermalPrinterCodegen
