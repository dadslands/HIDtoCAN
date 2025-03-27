# ESP32-S3 HID to Serial/CAN System

## Overview

This project implements a versatile interface device using the ESP32-S3 microcontroller that allows for multiple HID input devices (keyboards, mice, gamepads, etc.) to be connected and their inputs mapped to either serial or CAN bus outputs. The system includes a web-based configuration interface, firmware upgrade capability, and TunerStudio integration.

## Features

- **Multiple HID Device Support**: Connect and use multiple USB HID devices simultaneously
- **Flexible Input Mapping**: Map any HID input to serial or CAN bus outputs with customizable conditions
- **Web Configuration Interface**: Configure all aspects of the system through a browser
- **OTA Firmware Updates**: Update firmware through the web interface
- **TunerStudio Integration**: Compatible with TunerStudio for advanced configuration and monitoring
- **Persistent Settings**: All configurations are saved to non-volatile memory

## Hardware Requirements

- ESP32-S3-DevKitC-1-N8R8 development board
- USB HID devices (keyboards, mice, gamepads, etc.)
- CAN bus transceiver (for CAN bus functionality)
- USB power supply

## Pinout Reference

### ESP32-S3-DevKitC-1-N8R8 Pinout

| Function | GPIO Pin |
|----------|----------|
| USB D+   | GPIO 20  |
| USB D-   | GPIO 19  |
| UART0 TX | GPIO 43  |
| UART0 RX | GPIO 44  |
| UART1 TX | GPIO 17  |
| UART1 RX | GPIO 18  |
| UART2 TX | GPIO 14  |
| UART2 RX | GPIO 15  |
| CAN TX   | GPIO 4   |
| CAN RX   | GPIO 5   |
| LED      | GPIO 2   |

## Software Architecture

The system is built on the ESP-IDF framework and consists of several key components:

1. **HID Host**: Manages USB HID device connections and processes input events
2. **Serial Port**: Handles serial communication through multiple UART ports
3. **CAN Bus**: Manages CAN bus communication using the TWAI driver
4. **Input Mapping**: Maps HID inputs to serial or CAN outputs based on configurable rules
5. **Web Server**: Provides a web interface for configuration and firmware updates
6. **Firmware Update**: Handles OTA firmware updates
7. **TunerStudio**: Implements TunerStudio protocol for integration with tuning software

## Building and Flashing

### Prerequisites

- ESP-IDF v4.4 or later
- Python 3.6 or later
- Git

### Setup Development Environment

1. Install ESP-IDF following the [official guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/index.html)
2. Clone this repository:
   ```
   git clone https://github.com/your-username/esp32-hid-to-serial-can.git
   cd esp32-hid-to-serial-can
   ```

3. Configure the project:
   ```
   idf.py set-target esp32s3
   idf.py menuconfig
   ```

4. Build the project:
   ```
   idf.py build
   ```

5. Flash the firmware:
   ```
   idf.py -p (PORT) flash
   ```

## Usage

### Initial Setup

1. Power on the ESP32-S3 board
2. Connect to the WiFi network "ESP32-HID-Config" with password "password"
3. Open a web browser and navigate to http://192.168.4.1
4. Follow the on-screen instructions to configure your WiFi network

### Connecting HID Devices

1. Connect USB HID devices to the ESP32-S3 USB port
2. The system will automatically detect and initialize the devices
3. Use the web interface to configure input mappings

### Creating Input Mappings

1. Navigate to the "Mappings" section in the web interface
2. Click "Add New Mapping"
3. Select the input device, input type, and input index
4. Configure the condition for when the mapping should trigger
5. Select the output type (serial or CAN bus) and configure its parameters
6. Set the output format and any scaling or offset values
7. Click "Save" to create the mapping

### Configuring Serial Ports

1. Navigate to the "Serial Config" section in the web interface
2. Configure baud rate, data bits, stop bits, parity, and flow control for each port
3. Click "Apply" to save the configuration

### Configuring CAN Bus

1. Navigate to the "CAN Config" section in the web interface
2. Configure bit rate, mode, and message filtering options
3. Click "Apply" to save the configuration

### Updating Firmware

1. Navigate to the "Firmware" section in the web interface
2. Click "Browse" and select the new firmware binary file
3. Click "Upload & Flash" to start the update process
4. Wait for the device to reboot with the new firmware

### Using TunerStudio

1. Navigate to the "TunerStudio" section in the web interface
2. Configure the protocol type, signature, and output port
3. Download the INI file
4. Open TunerStudio and create a new project using the downloaded INI file
5. Connect to the ESP32-S3 using the configured serial port

## API Reference

The system provides a RESTful API for programmatic control:

### Devices API

- `GET /api/devices` - Get list of connected HID devices

### Mappings API

- `GET /api/mappings` - Get list of all input-output mappings
- `POST /api/mappings` - Create a new mapping
- `PUT /api/mappings/{id}` - Update an existing mapping
- `DELETE /api/mappings/{id}` - Delete a mapping
- `POST /api/mappings/save` - Save mappings to non-volatile memory
- `POST /api/mappings/load` - Load mappings from non-volatile memory
- `POST /api/mappings/reset` - Reset all mappings to default

### Serial API

- `GET /api/serial` - Get serial port configuration
- `POST /api/serial` - Update serial port configuration

### CAN API

- `GET /api/can` - Get CAN bus configuration
- `POST /api/can` - Update CAN bus configuration

### Firmware API

- `GET /api/firmware/info` - Get current firmware information
- `GET /api/firmware/status` - Get firmware update status
- `POST /api/firmware/upload` - Upload and flash new firmware

### TunerStudio API

- `GET /api/tunerstudio/config` - Get TunerStudio configuration
- `POST /api/tunerstudio/config` - Update TunerStudio configuration
- `GET /api/tunerstudio/ini` - Download TunerStudio INI file
- `POST /api/tunerstudio/ini` - Upload custom TunerStudio INI file

## Troubleshooting

### Device Not Detected

- Ensure the device is properly connected to the USB port
- Check if the device is powered on
- Try disconnecting and reconnecting the device
- Verify the device is a supported HID device

### Mapping Not Working

- Check if the device is properly detected in the "Devices" section
- Verify the input type and index are correct
- Ensure the condition is properly configured
- Check the serial or CAN bus configuration

### Web Interface Not Accessible

- Verify the ESP32-S3 is powered on
- Check if you're connected to the correct WiFi network
- Try resetting the ESP32-S3 and reconnecting

### Firmware Update Fails

- Ensure the firmware binary is valid for ESP32-S3
- Check if the ESP32-S3 has enough free space
- Try resetting the ESP32-S3 and attempting the update again

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements

- Espressif for the ESP-IDF framework
- TinyUSB library for USB HID support
- Bootstrap for the web interface
- TunerStudio for the tuning software integration
