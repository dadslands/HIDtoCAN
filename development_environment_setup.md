# ESP32-S3 Development Environment Setup Guide

This document outlines the setup process for the ESP32-S3 development environment required for our HID to Serial/CAN project.

## Development Environment Options

There are two main approaches to setting up the ESP32-S3 development environment:

1. **ESP-IDF (Espressif IoT Development Framework)** - The official development framework from Espressif
2. **Arduino IDE with ESP32 board support** - A simpler alternative for some use cases

For this project, we'll primarily use **ESP-IDF** as it provides the most comprehensive support for all the required functionality, particularly the TinyUSB stack for HID device handling.

## ESP-IDF Setup Options

ESP-IDF can be set up in several ways:

1. **IDE-based installation**:
   - VSCode Extension (recommended)
   - Eclipse Plugin

2. **Manual installation**:
   - Windows Installer
   - Linux and macOS manual setup

## Recommended Setup: VSCode with ESP-IDF Extension

For this project, we recommend using Visual Studio Code with the ESP-IDF extension for the following reasons:
- Integrated development environment with code completion and debugging
- Simplified ESP-IDF setup and management
- Built-in terminal for command execution
- Git integration for version control
- Support for all required ESP32-S3 features

### VSCode + ESP-IDF Extension Setup Steps

1. Download and install [Visual Studio Code](https://code.visualstudio.com/)

2. Install ESP-IDF system prerequisites:
   - For Windows: No additional prerequisites
   - For MacOS and Linux: Follow the [prerequisites guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/linux-macos-setup.html)

3. Install the ESP-IDF Extension in VSCode:
   - Open VSCode
   - Go to Extensions view (Ctrl+Shift+X or Cmd+Shift+X)
   - Search for "ESP-IDF Extension"
   - Install the extension

4. Configure the ESP-IDF Extension:
   - Click the Espressif icon in the Activity bar
   - Select "Configure ESP-IDF Extension"
   - Choose "Express" setup
   - Select a download server (Github or Espressif)
   - Choose an ESP-IDF version (recommend v5.2.5 or newer)
   - Set the ESP-IDF Tools path (default is ~/.espressif on Linux/macOS or %USERPROFILE%\.espressif on Windows)
   - Follow the setup wizard to complete the installation

## Alternative Setup: Manual ESP-IDF Installation

If you prefer a manual setup without VSCode, follow these steps:

1. Install prerequisites:
   - For Windows: [Windows Installer Guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/windows-setup.html)
   - For Linux/macOS: [Linux and macOS Setup Guide](https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/get-started/linux-macos-setup.html)

2. Get ESP-IDF:
   ```bash
   mkdir -p ~/esp
   cd ~/esp
   git clone -b v5.2.5 --recursive https://github.com/espressif/esp-idf.git
   ```

3. Set up the tools:
   ```bash
   cd ~/esp/esp-idf
   ./install.sh esp32s3
   ```

4. Set up the environment variables:
   ```bash
   . ~/esp/esp-idf/export.sh
   ```

## Required ESP-IDF Components

For this project, we'll need to add the following ESP-IDF components:

1. **TinyUSB**: For USB HID device support
   ```bash
   idf.py add-dependency "espressif/esp_tinyusb"
   ```

2. **ESP-TWAI**: For CAN bus functionality
   ```bash
   idf.py add-dependency "espressif/esp_twai"
   ```

3. **ESP-HTTP-Server**: For web server functionality
   ```bash
   idf.py add-dependency "espressif/esp_http_server"
   ```

## Verifying the Setup

To verify that your ESP-IDF environment is set up correctly:

1. Create a new project:
   ```bash
   cd ~/esp
   cp -r $IDF_PATH/examples/get-started/hello_world my_project
   cd my_project
   ```

2. Configure the project for ESP32-S3:
   ```bash
   idf.py set-target esp32s3
   idf.py menuconfig
   ```

3. Build, flash, and monitor:
   ```bash
   idf.py build
   idf.py -p (PORT) flash monitor
   ```

## Next Steps

After setting up the development environment, we'll proceed with:
1. Developing the HID input handling firmware
2. Implementing serial and CAN bus output functionality
3. Creating the input-to-output mapping system
4. Developing the web interface for configuration
5. Implementing the firmware upgrade mechanism
6. Creating TunerStudio integration
