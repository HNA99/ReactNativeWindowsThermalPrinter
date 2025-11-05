import React, { useEffect, useState } from 'react';
import {
  Text,
  View,
  StyleSheet,
  Button,
  Pressable,
  ScrollView,
} from 'react-native';
import {
  multiply,
  getDeviceList,
  connectPrinter,
  closeConn,
  COMMANDS,
  PrinterWidth,
  printText,
  printBill,
  printImageBase64,
} from 'react-native-windows-thermal-printer';

export default function App() {
  const [result, setResult] = useState<number>(0);
  const [devices, setDevices] = useState<string[]>([]);
  const [selectedDevice, setSelectedDevice] = useState<string>('');
  const [isConnected, setIsConnected] = useState<Boolean>(false);

  const PoweredByPOSpeyBlack =
    'data:image/png;base64,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';

  const loadData = async () => {
    try {
      const mult = multiply(Math.round(Math.random() * 10), 7);
      setResult(mult);

      const deviceList = await getDeviceList();
      setDevices(deviceList);
      setSelectedDevice('');
    } catch (error) {
      console.error('Error fetching devices:', error);
      setDevices([]);
    }
  };

  useEffect(() => {
    loadData();
  }, []);

  const handleConnect = async () => {
    if (!selectedDevice) {
      console.log('Please select a printer.');
      return;
    }
    console.log('Connecting to printer:', selectedDevice);
    const printer = await connectPrinter(selectedDevice);
    console.log('Connected to printer:', printer);
    setIsConnected(true);
  };

  const handleDisconnect = async () => {
    console.log('Disconnecting printer:', selectedDevice);
    await closeConn();
    setIsConnected(false);
  };

  const handlePrintText = async () => {
    const charactersPerLine = 42;

    const BOLD_ON = COMMANDS.TEXT_FORMAT.TXT_BOLD_ON;
    const BOLD_OFF = COMMANDS.TEXT_FORMAT.TXT_BOLD_OFF;
    const CENTER = COMMANDS.TEXT_FORMAT.TXT_ALIGN_CT;
    const HR3 = '-'.repeat(charactersPerLine);

    let execCommands = '';
    execCommands += `${CENTER}${BOLD_ON}Test${BOLD_OFF}\n`;
    execCommands += `${CENTER}${HR3}\n`;
    execCommands += `${BOLD_ON}Billed To:${BOLD_OFF} Test\n`;
    await printText(execCommands);
  };

  const handlePrintBill = async () => {
    const charactersPerLine = 42;

    const BOLD_ON = COMMANDS.TEXT_FORMAT.TXT_BOLD_ON;
    const BOLD_OFF = COMMANDS.TEXT_FORMAT.TXT_BOLD_OFF;
    const CENTER = COMMANDS.TEXT_FORMAT.TXT_ALIGN_CT;
    const HR3 = '-'.repeat(charactersPerLine);

    let execCommands = '';
    execCommands += `${CENTER}${BOLD_ON}Test${BOLD_OFF}\n`;
    execCommands += `${CENTER}${HR3}\n`;
    execCommands += `${BOLD_ON}Billed To:${BOLD_OFF} Test\n`;
    await printBill(execCommands);
  };

  const handlePrintImageBase64 = async () => {
    await printImageBase64(
      PoweredByPOSpeyBlack.replace(
        /^data:image\/[a-zA-Z]+;base64,/,
        ''
      ).replace(/(\r\n|\n|\r)/gm, '')
    );
  };

  return (
    <View style={styles.container}>
      <Text style={styles.header}>Result: {result}</Text>

      <View style={styles.row}>
        <View style={styles.dropdownContainer}>
          <ScrollView style={styles.scroll}>
            {devices.length > 0 ? (
              devices.map((dev, index) => (
                <Pressable
                  key={index}
                  style={[
                    styles.item,
                    selectedDevice === dev && styles.selectedItem,
                  ]}
                  onPress={() => setSelectedDevice(dev)}
                >
                  <Text
                    style={[
                      styles.itemText,
                      selectedDevice === dev && styles.selectedText,
                    ]}
                  >
                    {dev}
                  </Text>
                </Pressable>
              ))
            ) : (
              <Text style={styles.noDevice}>No printers found</Text>
            )}
          </ScrollView>
        </View>

        {isConnected ? (
          <>
            <Button title="Print Text" onPress={handlePrintText} />
            <Button title="Print Bill" onPress={handlePrintBill} />
            <Button
              title="Print Image Base64"
              onPress={handlePrintImageBase64}
            />
            <Button title="Disconnect Printer" onPress={handleDisconnect} />
          </>
        ) : (
          <Button title="Connect Printer" onPress={handleConnect} />
        )}
      </View>

      <View style={styles.refreshContainer}>
        <Button title="Refresh" onPress={loadData} />
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20,
    alignItems: 'center',
    justifyContent: 'center',
  },
  header: {
    marginBottom: 20,
    fontSize: 18,
  },
  row: {
    flexDirection: 'row',
    alignItems: 'center',
  },
  dropdownContainer: {
    flex: 1,
    marginRight: 10,
    borderWidth: 1,
    borderColor: '#ccc',
    borderRadius: 6,
    height: 150,
  },
  scroll: {
    width: 250,
  },
  item: {
    padding: 10,
  },
  selectedItem: {
    backgroundColor: '#0078D4',
  },
  itemText: {
    fontSize: 16,
  },
  selectedText: {
    color: '#fff',
  },
  noDevice: {
    padding: 10,
    color: '#888',
    textAlign: 'center',
  },
  refreshContainer: {
    marginTop: 20,
  },
});
