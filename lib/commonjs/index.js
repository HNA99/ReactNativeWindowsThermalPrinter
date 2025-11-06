"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
Object.defineProperty(exports, "COMMANDS", {
  enumerable: true,
  get: function () {
    return _printerCommands.COMMANDS;
  }
});
exports.WinPrinter = void 0;
var _NativeReactNativeWindowsThermalPrinter = _interopRequireDefault(require("./NativeReactNativeWindowsThermalPrinter"));
var _printerCommands = require("./utils/printer-commands.js");
function _interopRequireDefault(e) { return e && e.__esModule ? e : { default: e }; }
const WinPrinter = exports.WinPrinter = {
  init() {},
  async getDeviceList() {
    const list = await _NativeReactNativeWindowsThermalPrinter.default.getDeviceList();
    return list?.map(item => ({
      device_id: item.device_id ?? '',
      // store the string from results
      device_name: item.device_name ?? '' // store the string from results
    })) ?? [];
  },
  connectPrinter(deviceId) {
    return _NativeReactNativeWindowsThermalPrinter.default.connectPrinter(deviceId);
  },
  closeConn() {
    return _NativeReactNativeWindowsThermalPrinter.default.closeConn();
  },
  printText(text, _opts) {
    return _NativeReactNativeWindowsThermalPrinter.default.printText(text);
  },
  printBill(text, _opts) {
    return _NativeReactNativeWindowsThermalPrinter.default.printBill(text);
  },
  printImage(_imgUrl, _opts) {
    throw new Error('printImage() not implemented yet.');
  },
  printImageBase64(Base64, opts) {
    return _NativeReactNativeWindowsThermalPrinter.default.printImageBase64(Base64, opts?.imageWidth, opts?.imageHeight);
  },
  printRaw(_text) {
    throw new Error('printRaw() not implemented yet.');
  },
  printColumnsText(_texts, _columnWidth, _columnAlignment, _columnStyle, _opts) {
    throw new Error('printColumnsText() not implemented yet.');
  }
};
//# sourceMappingURL=index.js.map