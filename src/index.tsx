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

export function multiply(a: number, b: number): number {
  return ReactNativeWindowsThermalPrinter.multiply(a, b);
}

export function getDeviceList(): Promise<Array<string>> {
  return ReactNativeWindowsThermalPrinter.getDeviceList();
}

export function connectPrinter(deviceId: string): Promise<string> {
  return ReactNativeWindowsThermalPrinter.connectPrinter(deviceId);
}

export function closeConn(): Promise<void> {
  return ReactNativeWindowsThermalPrinter.closeConn();
}

export function printText(text: string): Promise<void> {
  return ReactNativeWindowsThermalPrinter.printText(text);
}

export function printBill(text: string): Promise<void> {
  return ReactNativeWindowsThermalPrinter.printBill(text);
}

export function printImageBase64(
  Base64: string,
  opts?: PrinterImageOptions
): Promise<void> {
  return ReactNativeWindowsThermalPrinter.printImageBase64(
    Base64,
    opts?.imageWidth,
    opts?.imageHeight
  );
}

export { COMMANDS };
