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
} from 'react-native-windows-thermal-printer';

export default function App() {
  const [result, setResult] = useState<number>(0);
  const [devices, setDevices] = useState<string[]>([]);
  const [selectedDevice, setSelectedDevice] = useState<string>('');

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

        <Button title="Connect Printer" onPress={handleConnect} />
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
