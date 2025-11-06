import ReactNativeWindowsThermalPrinter from './NativeReactNativeWindowsThermalPrinter';
import { COMMANDS } from './utils/printer-commands';

export declare enum PrinterWidth {
  '58mm' = 58,
  '80mm' = 80,
}

export interface PrinterImageOptions {
  imageWidth?: number;
  imageHeight?: number;
}

export interface IWINPrinter {
  device_id: string;
  device_name: string;
}

export const WinPrinter = {
  init(): void {},
  async getDeviceList(): Promise<Array<IWINPrinter>> {
    const list = await ReactNativeWindowsThermalPrinter.getDeviceList();
    return (
      list?.map((item) => ({
        device_id: item.device_id ?? '', // store the string from results
        device_name: item.device_name ?? '', // store the string from results
      })) ?? []
    );
  },
  connectPrinter(deviceId: string): Promise<string> {
    return ReactNativeWindowsThermalPrinter.connectPrinter(deviceId);
  },
  closeConn(): Promise<void> {
    return ReactNativeWindowsThermalPrinter.closeConn();
  },
  printText(text: string, _opts?: any): Promise<void> {
    return ReactNativeWindowsThermalPrinter.printText(text);
  },
  printBill(text: string, _opts?: any): Promise<void> {
    return ReactNativeWindowsThermalPrinter.printBill(text);
  },
  printImage(_imgUrl: string, _opts?: PrinterImageOptions): void {
    throw new Error('printImage() not implemented yet.');
  },
  printImageBase64(Base64: string, opts?: PrinterImageOptions): Promise<void> {
    return ReactNativeWindowsThermalPrinter.printImageBase64(
      Base64,
      opts?.imageWidth,
      opts?.imageHeight
    );
  },
  printRaw(_text: string): void {
    throw new Error('printRaw() not implemented yet.');
  },
  printColumnsText(
    _texts: string[],
    _columnWidth: number[],
    _columnAlignment: any,
    _columnStyle: string[],
    _opts?: any
  ): void {
    throw new Error('printColumnsText() not implemented yet.');
  },
};

export { COMMANDS };
