#include "pch.h"
#include "ReactNativeWindowsThermalPrinter.h"
#include <winrt/Windows.Devices.PointOfService.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace Windows::Devices::PointOfService;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Storage::Streams;
using namespace Windows::Graphics::Imaging;
using namespace Windows::Security::Cryptography;

namespace winrt::ReactNativeWindowsThermalPrinter
{

  void ReactNativeWindowsThermalPrinter::Initialize(React::ReactContext const& reactContext) noexcept {
    m_context = reactContext;
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

      auto caps = printer.Capabilities();

      if (caps.Receipt().IsBitmapSupported())
      {
        OutputDebugString(L"[ThermalPrinter] Bitmap printing is supported.\n");
      }
      else
      {
        OutputDebugString(L"[ThermalPrinter] Bitmap printing NOT supported.\n");
      }

      // Try to claim printer
      ClaimedPosPrinter claimedPrinter = co_await printer.ClaimPrinterAsync();

      if (claimedPrinter == nullptr)
      {
        OutputDebugString(L"[ThermalPrinter] Could not claim printer\n");
        promise.Reject("Could not claim printer");
        co_return;
      }

      m_claimedPrinter = claimedPrinter;

      OutputDebugString(L"[ThermalPrinter] Printer claimed successfully\n");

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

  winrt::fire_and_forget ReactNativeWindowsThermalPrinter::closeConn(
    React::ReactPromise<void> promise) noexcept
  {
    try
    {
      OutputDebugString(L"[ThermalPrinter] closeConn called\n");

      if (m_claimedPrinter == nullptr)
      {
        OutputDebugString(L"[ThermalPrinter] Claimed printer not found\n");
        promise.Reject("Could not find claimed printer");
        co_return;
      }

      // Release the printer claim
      m_claimedPrinter.Close();
      OutputDebugString(L"[ThermalPrinter] Printer claim released\n");

      m_claimedPrinter = nullptr;
      promise.Resolve();

      OutputDebugString(L"[ThermalPrinter] Printer Closed\n");
    }
    catch (std::exception const& ex)
    {
      std::string errorMsg = "[ThermalPrinter] Exception: " + std::string(ex.what()) + "\n";
      OutputDebugStringA(errorMsg.c_str());

      promise.Reject(ex.what());
    }
  }

  winrt::fire_and_forget ReactNativeWindowsThermalPrinter::printText(
    std::string text, 
    React::ReactPromise<void> promise) noexcept
  {
    try
    {
      OutputDebugString(L"[ThermalPrinter] printText called\n");


      if (m_claimedPrinter == nullptr)
      {
        OutputDebugString(L"[ThermalPrinter] Claimed printer not found\n");
        promise.Reject("Could not find claimed printer");
        co_return;
      }

      if (!m_claimedPrinter.IsEnabled())
      {
        OutputDebugString(L"[ThermalPrinter] Claimed printer is not enabled\n");
        bool IsEnabled = co_await m_claimedPrinter.EnableAsync();

        if(!IsEnabled){
          OutputDebugString(L"[ThermalPrinter] Failed to enable claimed printer\n");
          promise.Reject("Could not enable claimed printer");
          co_return;
        }
      }

      // Create a print job
      ReceiptPrintJob job = m_claimedPrinter.Receipt().CreateJob();

      // Print text
      job.Print(winrt::to_hstring(text));

      // // Send the job to printer
      bool success = co_await job.ExecuteAsync();

      if (success)
      {
        OutputDebugString(L"[ThermalPrinter] Printing complete.\n");
      }
      else
      {
        auto receipt = m_claimedPrinter.Receipt();
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

      promise.Resolve();
      OutputDebugString(L"[ThermalPrinter] Print job executed\n");
    }
    catch (std::exception const& ex)
    {
      std::string errorMsg = "[ThermalPrinter] Exception: " + std::string(ex.what()) + "\n";
      OutputDebugStringA(errorMsg.c_str());

      promise.Reject(ex.what());
    }
  }

  winrt::fire_and_forget ReactNativeWindowsThermalPrinter::printBill(
    std::string text, 
    React::ReactPromise<void> promise) noexcept
  {
    try
    {
      OutputDebugString(L"[ThermalPrinter] printBill called\n");


      if (m_claimedPrinter == nullptr)
      {
        OutputDebugString(L"[ThermalPrinter] Claimed printer not found\n");
        promise.Reject("Could not find claimed printer");
        co_return;
      }

      if (!m_claimedPrinter.IsEnabled())
      {
        OutputDebugString(L"[ThermalPrinter] Claimed printer is not enabled\n");
        bool IsEnabled = co_await m_claimedPrinter.EnableAsync();

        if(!IsEnabled){
          OutputDebugString(L"[ThermalPrinter] Failed to enable claimed printer\n");
          promise.Reject("Could not enable claimed printer");
          co_return;
        }
      }

      // Create a print job
      ReceiptPrintJob job = m_claimedPrinter.Receipt().CreateJob();

      // Print text
      job.Print(winrt::to_hstring(text));

      //Cut Paper
      job.CutPaper();

      // // Send the job to printer
      bool success = co_await job.ExecuteAsync();

      if (success)
      {
        OutputDebugString(L"[ThermalPrinter] Printing complete.\n");
      }
      else
      {
        auto receipt = m_claimedPrinter.Receipt();
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

      promise.Resolve();
      OutputDebugString(L"[ThermalPrinter] Print job executed\n");
    }
    catch (std::exception const& ex)
    {
      std::string errorMsg = "[ThermalPrinter] Exception: " + std::string(ex.what()) + "\n";
      OutputDebugStringA(errorMsg.c_str());

      promise.Reject(ex.what());
    }
  }

   // Base64 decoding utility
  std::vector<uint8_t> Base64Decode(const std::string& base64) {
    static constexpr unsigned char base64_table[65] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[base64_table[i]] = i;

    std::vector<uint8_t> output;
    int val = 0, valb = -8;
    for (unsigned char c : base64) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            output.push_back(uint8_t((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return output;
  }

  winrt::Windows::Foundation::IAsyncOperation<BitmapFrame> SoftwareBitmapFromBase64(
  const std::string& base64,
  std::optional<double> width,
  std::optional<double> height)
  {
    OutputDebugString(L"[ThermalPrinter] Starting decode\n");
    std::vector<uint8_t> imageBytes = Base64Decode(base64);
    OutputDebugString(L"[ThermalPrinter] Decode done\n");

    std::wstring msg = L"[ThermalPrinter] Bytes to write: " + std::to_wstring(imageBytes.size()) + L"\n";
    OutputDebugString(msg.c_str());

    // Create stream and output stream
    InMemoryRandomAccessStream stream;
    IOutputStream outputStream = stream.GetOutputStreamAt(0);

    {
        DataWriter writer(outputStream);
        writer.WriteBytes(imageBytes);
        OutputDebugString(L"[ThermalPrinter] Bytes written\n");

        writer.StoreAsync().get();
        OutputDebugString(L"[ThermalPrinter] StoreAsync done\n");

        writer.FlushAsync().get();
        OutputDebugString(L"[ThermalPrinter] Flush done\n");

        writer.DetachStream(); // important: detach before destruction
    }

    stream.Seek(0);
    OutputDebugString(L"[ThermalPrinter] Stream done\n");

    auto decoder = co_await BitmapDecoder::CreateAsync(stream);
    OutputDebugString(L"[ThermalPrinter] Decoder created\n");

    SoftwareBitmap softwareBitmap = co_await decoder.GetSoftwareBitmapAsync(
      BitmapPixelFormat::Bgra8,
      BitmapAlphaMode::Premultiplied);

    wchar_t buffer[256];
    swprintf_s(buffer, L"[ThermalPrinter] Decoded bitmap - Width: %d, Height: %d, PixelFormat: %d\n",
      softwareBitmap.PixelWidth(), softwareBitmap.PixelHeight(), (int)softwareBitmap.BitmapPixelFormat());
    OutputDebugString(buffer);


    if (width.has_value() && height.has_value())
    {
      wchar_t buf[128];
      swprintf_s(buf, L"[ThermalPrinter] Scaling requested - Target: %.0f x %.0f\n", *width, *height);
      OutputDebugString(buf);

      BitmapTransform transform;
      transform.ScaledWidth(static_cast<uint32_t>(*width));
      transform.ScaledHeight(static_cast<uint32_t>(*height));

      softwareBitmap = co_await decoder.GetSoftwareBitmapAsync(
        BitmapPixelFormat::Bgra8,
        BitmapAlphaMode::Premultiplied,
        transform,
        ExifOrientationMode::RespectExifOrientation,
        ColorManagementMode::DoNotColorManage);
    }

    InMemoryRandomAccessStream printStream;
    auto encoder = co_await BitmapEncoder::CreateAsync(BitmapEncoder::BmpEncoderId(), printStream);
    encoder.SetSoftwareBitmap(softwareBitmap);
    co_await encoder.FlushAsync();

    // MUST rewind before decoding
    printStream.Seek(0);
    auto printDecoder = co_await BitmapDecoder::CreateAsync(printStream);
    auto frame = co_await printDecoder.GetFrameAsync(0);



    co_return frame;
  }


  winrt::fire_and_forget ReactNativeWindowsThermalPrinter::printImageBase64(
    std::string base64Image,
    std::optional<double> width,
    std::optional<double> height,
    React::ReactPromise<void> promise) noexcept
  {
    try
    {
      OutputDebugString(L"[ThermalPrinter] printImageBase64 called\n");

      if (m_claimedPrinter == nullptr)
      {
        OutputDebugString(L"[ThermalPrinter] Claimed printer not found\n");
        promise.Reject("Could not find claimed printer");
        co_return;
      }

      if (!m_claimedPrinter.IsEnabled())
      {
        OutputDebugString(L"[ThermalPrinter] Claimed printer is not enabled\n");
        bool IsEnabled = co_await m_claimedPrinter.EnableAsync();

        if (!IsEnabled) {
          OutputDebugString(L"[ThermalPrinter] Failed to enable claimed printer\n");
          promise.Reject("Could not enable claimed printer");
          co_return;
        }
      }

      // Create bitmap
      auto bitmap = co_await SoftwareBitmapFromBase64(base64Image, width, height);

      auto bitmap2 = co_await bitmap.GetSoftwareBitmapAsync();
      auto width = bitmap2.PixelWidth();
      auto height = bitmap2.PixelHeight();
      auto format = bitmap2.BitmapPixelFormat();

      std::wstring msg = L"[ThermalPrinter] BitmapFrame created - Width: " +
          std::to_wstring(width) + L", Height: " +
          std::to_wstring(height) + L", Format: " +
          std::to_wstring(static_cast<int>(format)) + L"\n";

      OutputDebugString(msg.c_str());

      // Create a print job
      ReceiptPrintJob job = m_claimedPrinter.Receipt().CreateJob();

      // Print image
      job.PrintBitmap(bitmap, PosPrinterAlignment::Center);

      // Send the job to printer
      bool success = co_await job.ExecuteAsync();

      if (success)
      {
        OutputDebugString(L"[ThermalPrinter] Printing complete.\n");
      }
      else
      {
        std::wstring reason = L"Unknown";      
        auto receipt = m_claimedPrinter.Receipt();

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

      promise.Resolve();
      OutputDebugString(L"[ThermalPrinter] Print job executed\n");
    }
    catch (std::exception const& ex)
    {
      std::string errorMsg = "[ThermalPrinter] Exception: " + std::string(ex.what()) + "\n";
      OutputDebugStringA(errorMsg.c_str());

      promise.Reject(ex.what());
    }
  }
} // namespace winrt::ReactNativeWindowsThermalPrinter
