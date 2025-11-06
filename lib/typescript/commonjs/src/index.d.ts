import { COMMANDS } from './utils/printer-commands';
export declare enum PrinterWidth {
    '58mm' = 58,
    '80mm' = 80
}
export interface PrinterImageOptions {
    imageWidth?: number;
    imageHeight?: number;
}
export interface IWINPrinter {
    device_id: string;
    device_name: string;
}
export declare const WinPrinter: {
    init(): void;
    getDeviceList(): Promise<Array<IWINPrinter>>;
    connectPrinter(deviceId: string): Promise<string>;
    closeConn(): Promise<void>;
    printText(text: string, _opts?: any): Promise<void>;
    printBill(text: string, _opts?: any): Promise<void>;
    printImage(_imgUrl: string, _opts?: PrinterImageOptions): void;
    printImageBase64(Base64: string, opts?: PrinterImageOptions): Promise<void>;
    printRaw(_text: string): void;
    printColumnsText(_texts: string[], _columnWidth: number[], _columnAlignment: any, _columnStyle: string[], _opts?: any): void;
};
export { COMMANDS };
//# sourceMappingURL=index.d.ts.map