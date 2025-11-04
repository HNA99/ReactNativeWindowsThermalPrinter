import type { TurboModule } from 'react-native';
import { TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  multiply(a: number, b: number): number;
  getDeviceList(): Promise<Array<string>>;
  connectPrinter(deviceId: string): Promise<string>;
}

export default TurboModuleRegistry.getEnforcing<Spec>(
  'ReactNativeWindowsThermalPrinter'
);
