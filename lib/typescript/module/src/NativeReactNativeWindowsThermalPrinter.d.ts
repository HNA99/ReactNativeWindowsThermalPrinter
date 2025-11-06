import type { TurboModule } from 'react-native';
export interface PrinterOptions {
    beep?: boolean;
    cut?: boolean;
    tailingLine?: boolean;
    encoding?: string;
}
export interface Spec extends TurboModule {
    getDeviceList(): Promise<Array<Record<string, string>>>;
    connectPrinter(deviceId: string): Promise<string>;
    closeConn(): Promise<void>;
    printText(text: string): Promise<void>;
    printBill(text: string): Promise<void>;
    printImageBase64(Base64: string, width: number | undefined, height: number | undefined): Promise<void>;
}
declare const _default: Spec;
export default _default;
//# sourceMappingURL=NativeReactNativeWindowsThermalPrinter.d.ts.map