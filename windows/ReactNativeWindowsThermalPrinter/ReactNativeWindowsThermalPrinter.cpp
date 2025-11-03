#include "pch.h"
#include "ReactNativeWindowsThermalPrinter.h"
#include <winrt/Windows.Devices.PointOfService.h>
#include <winrt/Windows.Devices.Enumeration.h>

using namespace winrt;
using namespace Windows::Devices::PointOfService;
using namespace Windows::Devices::Enumeration;

namespace winrt::ReactNativeWindowsThermalPrinter
{

  void ReactNativeWindowsThermalPrinter::Initialize(React::ReactContext const& reactContext) noexcept {
    m_context = reactContext;
  }

  double ReactNativeWindowsThermalPrinter::multiply(double a, double b) noexcept {
    return a * b;
  }

  winrt::fire_and_forget ReactNativeWindowsThermalPrinter::getDeviceList(
    React::ReactPromise<std::vector<std::string>> promise) noexcept
  {
    try
    {
      OutputDebugString(L"[ThermalPrinter] getDeviceList called\n");

      std::vector<std::string> printers;

      hstring selector = PosPrinter::GetDeviceSelector();
      OutputDebugString(L"[ThermalPrinter] Device selector obtained\n");

      // Await async device enumeration
      DeviceInformationCollection deviceCollection = co_await DeviceInformation::FindAllAsync(selector);
      OutputDebugString(L"[ThermalPrinter] Device collection obtained\n");

      for (DeviceInformation const& device : deviceCollection)
      {
        std::string name = winrt::to_string(device.Name());
        printers.push_back(name);

        std::string debugMsg = "[ThermalPrinter] Found printer: " + name + "\n";
        OutputDebugStringA(debugMsg.c_str()); // std::string version
      }

      OutputDebugString(L"[ThermalPrinter] Resolving promise with printer list\n");
      promise.Resolve(std::move(printers));
    }
    catch (std::exception const& ex)
    {
      std::string errorMsg = "[ThermalPrinter] Exception: " + std::string(ex.what()) + "\n";
      OutputDebugStringA(errorMsg.c_str());

      promise.Reject(ex.what());
    }
  }

} // namespace winrt::ReactNativeWindowsThermalPrinter
