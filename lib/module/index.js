"use strict";

import ReactNativeWindowsThermalPrinter from './NativeReactNativeWindowsThermalPrinter';
import { COMMANDS } from "./utils/printer-commands.js";
export const WinPrinter = {
  init() {},
  getDeviceList() {
    return ReactNativeWindowsThermalPrinter.getDeviceList();
  },
  connectPrinter(deviceId) {
    return ReactNativeWindowsThermalPrinter.connectPrinter(deviceId);
  },
  closeConn() {
    return ReactNativeWindowsThermalPrinter.closeConn();
  },
  printText(text, _opts) {
    return ReactNativeWindowsThermalPrinter.printText(text);
  },
  printBill(text, _opts) {
    return ReactNativeWindowsThermalPrinter.printBill(text);
  },
  printImage(_imgUrl, _opts) {
    throw new Error('printImage() not implemented yet.');
  },
  printImageBase64(Base64, opts) {
    return ReactNativeWindowsThermalPrinter.printImageBase64(Base64, opts?.imageWidth, opts?.imageHeight);
  },
  printRaw(_text) {
    throw new Error('printRaw() not implemented yet.');
  },
  printColumnsText(_texts, _columnWidth, _columnAlignment, _columnStyle, _opts) {
    throw new Error('printColumnsText() not implemented yet.');
  }
};
export { COMMANDS };
//# sourceMappingURL=index.js.map