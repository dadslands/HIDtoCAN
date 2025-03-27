/**
 * @file hid_host.h
 * @brief HID Host Interface for ESP32-S3
 * 
 * This file contains the declarations for the HID host functionality
 * that allows for multiple HID input devices to be connected to the ESP32-S3
 * via USB.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Maximum number of HID devices that can be connected simultaneously
 */
#define MAX_HID_DEVICES 8

/**
 * @brief HID device types
 */
typedef enum {
    HID_DEVICE_UNKNOWN = 0,
    HID_DEVICE_KEYBOARD,
    HID_DEVICE_MOUSE,
    HID_DEVICE_GAMEPAD,
    HID_DEVICE_JOYSTICK,
    HID_DEVICE_GENERIC
} hid_device_type_t;

/**
 * @brief HID device information structure
 */
typedef struct {
    uint8_t device_addr;           /*!< Device address */
    uint8_t instance;              /*!< Instance number */
    hid_device_type_t device_type; /*!< Device type */
    uint16_t vid;                  /*!< Vendor ID */
    uint16_t pid;                  /*!< Product ID */
    char manufacturer[64];         /*!< Manufacturer string */
    char product[64];              /*!< Product string */
    char serial_number[64];        /*!< Serial number string */
    bool connected;                /*!< Connection status */
} hid_device_info_t;

/**
 * @brief HID keyboard event data
 */
typedef struct {
    uint8_t modifier;              /*!< Keyboard modifier keys */
    uint8_t key_code[6];           /*!< Key codes (up to 6 keys pressed simultaneously) */
} hid_keyboard_event_t;

/**
 * @brief HID mouse event data
 */
typedef struct {
    uint8_t buttons;               /*!< Mouse button state */
    int8_t x;                      /*!< X-axis movement */
    int8_t y;                      /*!< Y-axis movement */
    int8_t wheel;                  /*!< Vertical wheel movement */
    int8_t pan;                    /*!< Horizontal wheel movement */
} hid_mouse_event_t;

/**
 * @brief HID gamepad/joystick event data
 */
typedef struct {
    uint8_t buttons[4];            /*!< Button states (up to 32 buttons) */
    int8_t x;                      /*!< X-axis position */
    int8_t y;                      /*!< Y-axis position */
    int8_t z;                      /*!< Z-axis position */
    int8_t rx;                     /*!< X-axis rotation */
    int8_t ry;                     /*!< Y-axis rotation */
    int8_t rz;                     /*!< Z-axis rotation */
    int8_t slider1;                /*!< Slider 1 position */
    int8_t slider2;                /*!< Slider 2 position */
    uint8_t hat;                   /*!< Hat switch position */
} hid_gamepad_event_t;

/**
 * @brief HID generic event data
 */
typedef struct {
    uint16_t report_id;            /*!< Report ID */
    uint16_t report_size;          /*!< Report size in bytes */
    uint8_t report_data[64];       /*!< Report data */
} hid_generic_event_t;

/**
 * @brief HID event data union
 */
typedef union {
    hid_keyboard_event_t keyboard;
    hid_mouse_event_t mouse;
    hid_gamepad_event_t gamepad;
    hid_generic_event_t generic;
} hid_event_data_t;

/**
 * @brief HID event structure
 */
typedef struct {
    uint8_t device_idx;            /*!< Device index */
    hid_device_type_t device_type; /*!< Device type */
    hid_event_data_t data;         /*!< Event data */
} hid_event_t;

/**
 * @brief HID event callback function type
 */
typedef void (*hid_event_callback_t)(hid_event_t *event, void *user_ctx);

/**
 * @brief HID connection callback function type
 */
typedef void (*hid_connection_callback_t)(hid_device_info_t *device_info, bool connected, void *user_ctx);

/**
 * @brief HID host configuration structure
 */
typedef struct {
    hid_event_callback_t event_callback;           /*!< Event callback function */
    hid_connection_callback_t connection_callback; /*!< Connection callback function */
    void *user_ctx;                                /*!< User context */
} hid_host_config_t;

/**
 * @brief Initialize the HID host
 * 
 * @param config Pointer to the HID host configuration
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t hid_host_init(const hid_host_config_t *config);

/**
 * @brief Deinitialize the HID host
 * 
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t hid_host_deinit(void);

/**
 * @brief Get the number of connected HID devices
 * 
 * @param[out] num_devices Pointer to store the number of connected devices
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t hid_host_get_device_count(uint8_t *num_devices);

/**
 * @brief Get information about a connected HID device
 * 
 * @param device_idx Device index
 * @param[out] device_info Pointer to store the device information
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t hid_host_get_device_info(uint8_t device_idx, hid_device_info_t *device_info);

/**
 * @brief Set the output report for a HID device (for devices with output capabilities)
 * 
 * @param device_idx Device index
 * @param report_id Report ID
 * @param report_data Pointer to the report data
 * @param report_size Size of the report data in bytes
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t hid_host_set_output_report(uint8_t device_idx, uint8_t report_id, const uint8_t *report_data, uint16_t report_size);

#ifdef __cplusplus
}
#endif
