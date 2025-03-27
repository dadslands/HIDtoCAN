#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Maximum number of output mappings per HID device
 */
#define MAX_MAPPINGS_PER_DEVICE 16

/**
 * @brief Output types for HID input mapping
 */
typedef enum {
    OUTPUT_TYPE_SERIAL = 0,  /*!< Serial output */
    OUTPUT_TYPE_CANBUS       /*!< CAN bus output */
} output_type_t;

/**
 * @brief HID input types that can be mapped
 */
typedef enum {
    INPUT_TYPE_KEYBOARD_KEY = 0,     /*!< Keyboard key press */
    INPUT_TYPE_KEYBOARD_MODIFIER,    /*!< Keyboard modifier (shift, ctrl, etc.) */
    INPUT_TYPE_MOUSE_BUTTON,         /*!< Mouse button press */
    INPUT_TYPE_MOUSE_MOVEMENT_X,     /*!< Mouse X-axis movement */
    INPUT_TYPE_MOUSE_MOVEMENT_Y,     /*!< Mouse Y-axis movement */
    INPUT_TYPE_MOUSE_WHEEL,          /*!< Mouse wheel movement */
    INPUT_TYPE_GAMEPAD_BUTTON,       /*!< Gamepad button press */
    INPUT_TYPE_GAMEPAD_AXIS,         /*!< Gamepad axis movement */
    INPUT_TYPE_GAMEPAD_HAT,          /*!< Gamepad hat switch */
    INPUT_TYPE_GENERIC_REPORT        /*!< Generic HID report data */
} input_type_t;

/**
 * @brief Mapping condition types
 */
typedef enum {
    CONDITION_EQUALS = 0,    /*!< Input value equals specified value */
    CONDITION_NOT_EQUALS,    /*!< Input value does not equal specified value */
    CONDITION_GREATER_THAN,  /*!< Input value is greater than specified value */
    CONDITION_LESS_THAN,     /*!< Input value is less than specified value */
    CONDITION_CHANGED,       /*!< Input value has changed from previous value */
    CONDITION_ALWAYS         /*!< Always trigger (no condition) */
} condition_type_t;

/**
 * @brief Input mapping condition structure
 */
typedef struct {
    condition_type_t type;   /*!< Condition type */
    int32_t value;           /*!< Value to compare against (if applicable) */
} mapping_condition_t;

/**
 * @brief Serial output configuration
 */
typedef struct {
    uint8_t port;            /*!< Serial port number */
    uint32_t baud_rate;      /*!< Baud rate */
    uint8_t data_bits;       /*!< Data bits (5-8) */
    uint8_t stop_bits;       /*!< Stop bits (1-2) */
    uint8_t parity;          /*!< Parity (0=none, 1=odd, 2=even) */
    uint8_t flow_control;    /*!< Flow control (0=none, 1=RTS/CTS, 2=XON/XOFF) */
} serial_config_t;

/**
 * @brief CAN bus output configuration
 */
typedef struct {
    uint8_t port;            /*!< CAN bus port number */
    uint32_t bitrate;        /*!< Bit rate */
    bool extended_id;        /*!< Use extended ID format */
} canbus_config_t;

/**
 * @brief Output configuration union
 */
typedef union {
    serial_config_t serial;  /*!< Serial output configuration */
    canbus_config_t canbus;  /*!< CAN bus output configuration */
} output_config_t;

/**
 * @brief Output data format types
 */
typedef enum {
    FORMAT_RAW = 0,          /*!< Raw binary data */
    FORMAT_HEX,              /*!< Hexadecimal string */
    FORMAT_DECIMAL,          /*!< Decimal string */
    FORMAT_ASCII,            /*!< ASCII string */
    FORMAT_CUSTOM            /*!< Custom format (defined by format string) */
} output_format_t;

/**
 * @brief HID input to output mapping structure
 */
typedef struct {
    bool enabled;                    /*!< Mapping enabled flag */
    uint8_t device_idx;              /*!< HID device index */
    input_type_t input_type;         /*!< Input type */
    uint8_t input_index;             /*!< Input index (e.g., key code, button number, axis index) */
    mapping_condition_t condition;   /*!< Mapping condition */
    output_type_t output_type;       /*!< Output type */
    output_config_t output_config;   /*!< Output configuration */
    output_format_t output_format;   /*!< Output data format */
    char format_string[32];          /*!< Format string for custom format */
    uint32_t can_id;                 /*!< CAN message ID (for CAN bus output) */
    uint8_t can_dlc;                 /*!< CAN data length code (for CAN bus output) */
    uint8_t output_data[8];          /*!< Fixed output data (can include placeholders) */
    uint8_t output_data_len;         /*!< Length of fixed output data */
    int32_t scale_factor;            /*!< Scale factor for input value (fixed-point with 2 decimal places) */
    int32_t offset;                  /*!< Offset for input value */
    uint32_t min_interval_ms;        /*!< Minimum interval between outputs (ms) */
    uint32_t last_output_time;       /*!< Timestamp of last output (internal use) */
    int32_t last_input_value;        /*!< Last input value (internal use) */
} input_mapping_t;

/**
 * @brief Initialize the input-output mapping system
 * 
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_init(void);

/**
 * @brief Deinitialize the input-output mapping system
 * 
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_deinit(void);

/**
 * @brief Add a new input-output mapping
 * 
 * @param mapping Pointer to the mapping configuration
 * @param[out] mapping_idx Pointer to store the mapping index
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_add(const input_mapping_t *mapping, uint16_t *mapping_idx);

/**
 * @brief Update an existing input-output mapping
 * 
 * @param mapping_idx Mapping index
 * @param mapping Pointer to the new mapping configuration
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_update(uint16_t mapping_idx, const input_mapping_t *mapping);

/**
 * @brief Remove an input-output mapping
 * 
 * @param mapping_idx Mapping index
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_remove(uint16_t mapping_idx);

/**
 * @brief Get an input-output mapping
 * 
 * @param mapping_idx Mapping index
 * @param[out] mapping Pointer to store the mapping configuration
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_get(uint16_t mapping_idx, input_mapping_t *mapping);

/**
 * @brief Get the number of active mappings
 * 
 * @param[out] count Pointer to store the number of mappings
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_get_count(uint16_t *count);

/**
 * @brief Process HID input event and generate outputs according to mappings
 * 
 * @param event Pointer to the HID event
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_process_event(const hid_event_t *event);

/**
 * @brief Save mappings to non-volatile storage
 * 
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_save(void);

/**
 * @brief Load mappings from non-volatile storage
 * 
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_load(void);

/**
 * @brief Reset all mappings to default values
 * 
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t mapping_reset(void);

#ifdef __cplusplus
}
#endif
