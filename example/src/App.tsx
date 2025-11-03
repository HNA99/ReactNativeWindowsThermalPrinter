import { useEffect, useState } from 'react';
import { Text, View, StyleSheet } from 'react-native';
import { multiply, getDeviceList } from 'react-native-windows-thermal-printer';

export default function App() {
  const [result, setResult] = useState<number>(0);
  const [devices, setDevices] = useState<string>('Loading...');

  useEffect(() => {
    // Run once on mount
    const loadData = async () => {
      try {
        const mult = multiply(3, 7);
        setResult(mult);

        const deviceList = await getDeviceList();
        // Convert array of objects into readable string
        setDevices(JSON.stringify(deviceList));
      } catch (error) {
        console.error('Error fetching devices:', error);
        setDevices('Error fetching devices');
      }
    };

    loadData();
  }, []);

  return (
    <View style={styles.container}>
      <Text>Result: {result}</Text>
      <Text>Devices: {devices}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
