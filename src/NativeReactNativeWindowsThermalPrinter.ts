import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface PrinterOptions {
  beep?: boolean;
  cut?: boolean;
  tailingLine?: boolean;
  encoding?: string;
}

export interface Spec extends TurboModule {
  multiply(a: number, b: number): number;
  getDeviceList(): Promise<Array<string>>;
  connectPrinter(deviceId: string): Promise<string>;
  closeConn(): Promise<void>;
  printText(text: string): Promise<void>;
  printBill(text: string): Promise<void>;
  printImageBase64(Base64: string, width: number | undefined, height: number | undefined): Promise<void>;
}

export default TurboModuleRegistry.getEnforcing<Spec>(
  'ReactNativeWindowsThermalPrinter'
);
