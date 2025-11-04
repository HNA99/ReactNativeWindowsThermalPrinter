import ReactNativeWindowsThermalPrinter from './NativeReactNativeWindowsThermalPrinter';

export function multiply(a: number, b: number): number {
  return ReactNativeWindowsThermalPrinter.multiply(a, b);
}

export function getDeviceList(): Promise<Array<string>> {
  return ReactNativeWindowsThermalPrinter.getDeviceList();
}

export function connectPrinter(deviceId: string): Promise<string> {
  return ReactNativeWindowsThermalPrinter.connectPrinter(deviceId);
}
