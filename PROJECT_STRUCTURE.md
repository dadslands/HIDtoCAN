# ESP32-S3 HID to Serial/CAN Project Structure

This document provides an overview of the project structure and files.

## Directory Structure

```
esp32_project/
├── firmware/
│   └── hid_handler/
│       ├── include/
│       │   ├── hid_host.h
│       │   ├── input_mapping.h
│       │   ├── serial_port.h
│       │   ├── can_bus.h
│       │   ├── web_server.h
│       │   ├── firmware_update.h
│       │   └── tunerstudio.h
│       ├── hid_host.c
│       ├── input_mapping.c
│       ├── serial_port.c
│       ├── can_bus.c
│       ├── web_server.c
│       ├── firmware_update.c
│       ├── firmware_api.c
│       ├── tunerstudio.c
│       ├── tunerstudio_api.c
│       └── web/
│           ├── index.html
│           ├── css/
│           │   └── styles.css
│           └── js/
│               └── app.js
├── web/
│   └── (deployment files)
├── docs/
│   ├── README.md
│   └── TEST_PLAN.md
├── research/
│   └── esp32s3_capabilities.md
└── setup/
    └── development_environment_setup.md
```

## Core Components

### HID Input Handling
- `hid_host.h/c`: Manages USB HID device connections and processes input events

### Output Interfaces
- `serial_port.h/c`: Handles serial communication through multiple UART ports
- `can_bus.h/c`: Manages CAN bus communication using the TWAI driver

### Mapping System
- `input_mapping.h/c`: Maps HID inputs to serial or CAN outputs based on configurable rules

### Web Interface
- `web_server.h/c`: Core web server functionality
- `web/index.html`: Main HTML interface
- `web/css/styles.css`: CSS styling for the web interface
- `web/js/app.js`: JavaScript for the web interface

### Firmware Update
- `firmware_update.h/c`: Core firmware update functionality
- `firmware_api.c`: Web API endpoints for firmware updates

### TunerStudio Integration
- `tunerstudio.h/c`: Core TunerStudio protocol implementation
- `tunerstudio_api.c`: Web API endpoints for TunerStudio configuration

### Documentation
- `docs/README.md`: Main project documentation
- `docs/TEST_PLAN.md`: Comprehensive test plan
- `research/esp32s3_capabilities.md`: Research on ESP32-S3 capabilities
- `setup/development_environment_setup.md`: Development environment setup guide

## Build System

The project uses the ESP-IDF build system. To build the project:

1. Set up the ESP-IDF environment
2. Navigate to the project directory
3. Run `idf.py build`
4. Flash with `idf.py -p (PORT) flash`

## Web Interface Structure

The web interface is organized into several sections:

1. Dashboard: Overview of system status and connected devices
2. Mappings: Configure input-output mappings
3. Serial Config: Configure serial port parameters
4. CAN Config: Configure CAN bus parameters
5. Firmware: Update firmware
6. TunerStudio: Configure TunerStudio integration

## API Endpoints

The system provides RESTful API endpoints for all functionality:

- `/api/devices`: HID device management
- `/api/mappings`: Input-output mapping configuration
- `/api/serial`: Serial port configuration
- `/api/can`: CAN bus configuration
- `/api/firmware`: Firmware update management
- `/api/tunerstudio`: TunerStudio integration configuration

## Next Steps

1. Implement unit tests for each component
2. Add support for more HID device types
3. Enhance the web interface with additional features
4. Optimize performance for high-frequency inputs
5. Add support for wireless connectivity options
