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

        std::string id = winrt::to_string(device.Id());
        std::string name = winrt::to_string(device.Name());
        OutputDebugStringA(("[ThermalPrinter] Found printer: " + name + "\n").c_str());
        OutputDebugStringA(("[ThermalPrinter] ID: " + id + "\n").c_str());
        printers.push_back(id);
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

  winrt::fire_and_forget ReactNativeWindowsThermalPrinter::connectPrinter(
    std::string deviceId,
    React::ReactPromise<std::string> promise) noexcept
{
  try
  {
    OutputDebugString(L"[ThermalPrinter] connectPrinter called\n");

    // Convert std::string to hstring for WinRT
    hstring hDeviceId = winrt::to_hstring(deviceId);

    // Await the async call properly
    PosPrinter printer = co_await PosPrinter::FromIdAsync(hDeviceId);    

    if (printer == nullptr)
    {
      OutputDebugString(L"[ThermalPrinter] Printer not found\n");
      promise.Reject("Printer not found");
      co_return;
    }

    OutputDebugString(L"[ThermalPrinter] Printer found\n");

    // Try to claim printer
    ClaimedPosPrinter claimedPrinter = co_await printer.ClaimPrinterAsync();

    if (claimedPrinter == nullptr)
    {
      OutputDebugString(L"[ThermalPrinter] Could not claim printer\n");
      promise.Reject("Could not claim printer");
      co_return;
    }

    OutputDebugString(L"[ThermalPrinter] Printer claimed successfully\n");

    if (!claimedPrinter.IsEnabled())
    {
      OutputDebugString(L"[ThermalPrinter] Claimed printer is not enabled\n");
      co_await claimedPrinter.EnableAsync();
    }

    // Create a print job
    ReceiptPrintJob job = claimedPrinter.Receipt().CreateJob();

    // Print a simple line
    job.PrintLine(L"Hello from ReactNative Windows Thermal Printer!");
    job.PrintLine(L"------------------------------");
    job.PrintLine(L"POS Print Test Completed.");
    job.CutPaper();

    // Send the job to printer
    bool success = co_await job.ExecuteAsync();

    if (success)
    {
      OutputDebugString(L"[ThermalPrinter] Printing complete.\n");
    }
    else
    {
      auto receipt = claimedPrinter.Receipt();
      std::wstring reason;

      if (receipt.IsCartridgeEmpty())
      {
        reason = L"Printer is out of ink. Please replace cartridge.";
      }
      else if (receipt.IsCartridgeRemoved())
      {
        reason = L"Printer cartridge is missing. Please replace cartridge.";
      }
      else if (receipt.IsCoverOpen())
      {
        reason = L"Printer cover is open. Please close it.";
      }
      else if (receipt.IsHeadCleaning())
      {
        reason = L"Printer is currently cleaning the cartridge. Please wait until cleaning has completed.";
      }
      else if (receipt.IsPaperEmpty())
      {
        reason = L"Printer is out of paper. Please insert a new roll.";
      }
      else
      {
        reason = L"Unable to print.";
      }

      std::wstring msg = L"[ThermalPrinter] Print failed: " + reason + L"\n";
      OutputDebugString(msg.c_str());

      std::string err = winrt::to_string(reason);

      promise.Reject(err.c_str());
      co_return;
    }

    OutputDebugString(L"[ThermalPrinter] Print job executed\n");

    // Release the printer claim
    claimedPrinter.Close();
    OutputDebugString(L"[ThermalPrinter] Printer claim released\n");

    // Successfully connected
    std::string printerId = winrt::to_string(printer.DeviceId());
    promise.Resolve(printerId);

    OutputDebugString(L"[ThermalPrinter] Printer Connected\n");
  }
  catch (std::exception const& ex)
  {
    std::string errorMsg = "[ThermalPrinter] Exception: " + std::string(ex.what()) + "\n";
    OutputDebugStringA(errorMsg.c_str());

    promise.Reject(ex.what());
  }
}


} // namespace winrt::ReactNativeWindowsThermalPrinter
