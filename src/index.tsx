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

export const WinPrinter = {
  init(): void {},
  getDeviceList(): Promise<Array<string>> {
    return ReactNativeWindowsThermalPrinter.getDeviceList();
  },
  connectPrinter(deviceId: string): Promise<string> {
    return ReactNativeWindowsThermalPrinter.connectPrinter(deviceId);
  },
  closeConn(): Promise<void> {
    return ReactNativeWindowsThermalPrinter.closeConn();
  },
  printText(text: string, opts?: any): Promise<void> {
    return ReactNativeWindowsThermalPrinter.printText(text);
  },
  printBill(text: string, opts?: any): Promise<void> {
    return ReactNativeWindowsThermalPrinter.printBill(text);
  },
  printImage(imgUrl: string, opts?: PrinterImageOptions): void {
    throw new Error("printImage() not implemented yet.");
  },
  printImageBase64(Base64: string, opts?: PrinterImageOptions): Promise<void> {
    return ReactNativeWindowsThermalPrinter.printImageBase64(Base64, opts?.imageWidth, opts?.imageHeight);
  },
  printRaw(text: string): void {
    throw new Error("printRaw() not implemented yet.");
  },
  printColumnsText(texts: string[], columnWidth: number[], columnAlignment: any, columnStyle: string[], opts?: any): void {
    throw new Error("printColumnsText() not implemented yet.");
  },
}

export { COMMANDS };
