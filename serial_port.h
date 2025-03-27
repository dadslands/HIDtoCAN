#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Serial port configuration structure
 */
typedef struct {
    uint8_t port_num;        /*!< Serial port number (0-2) */
    uint32_t baud_rate;      /*!< Baud rate */
    uint8_t data_bits;       /*!< Data bits (5-8) */
    uint8_t stop_bits;       /*!< Stop bits (1-2) */
    uint8_t parity;          /*!< Parity (0=none, 1=odd, 2=even) */
    uint8_t flow_control;    /*!< Flow control (0=none, 1=RTS/CTS, 2=XON/XOFF) */
    int8_t tx_pin;           /*!< TX pin number (-1 for default) */
    int8_t rx_pin;           /*!< RX pin number (-1 for default) */
    int8_t rts_pin;          /*!< RTS pin number (-1 for default) */
    int8_t cts_pin;          /*!< CTS pin number (-1 for default) */
    uint16_t rx_buffer_size; /*!< RX buffer size in bytes */
    uint16_t tx_buffer_size; /*!< TX buffer size in bytes */
} serial_port_config_t;

/**
 * @brief Initialize serial port
 * 
 * @param config Pointer to serial port configuration
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t serial_init(const serial_port_config_t *config);

/**
 * @brief Deinitialize serial port
 * 
 * @param port_num Serial port number
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t serial_deinit(uint8_t port_num);

/**
 * @brief Send data over serial port
 * 
 * @param port_num Serial port number
 * @param data Pointer to data buffer
 * @param len Length of data in bytes
 * @param timeout_ms Timeout in milliseconds
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t serial_send(uint8_t port_num, const uint8_t *data, size_t len, uint32_t timeout_ms);

/**
 * @brief Receive data from serial port
 * 
 * @param port_num Serial port number
 * @param data Pointer to data buffer
 * @param len Maximum length of data to receive
 * @param[out] bytes_read Pointer to store number of bytes read
 * @param timeout_ms Timeout in milliseconds
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t serial_receive(uint8_t port_num, uint8_t *data, size_t len, size_t *bytes_read, uint32_t timeout_ms);

/**
 * @brief Flush serial port transmit buffer
 * 
 * @param port_num Serial port number
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t serial_flush_tx(uint8_t port_num);

/**
 * @brief Flush serial port receive buffer
 * 
 * @param port_num Serial port number
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t serial_flush_rx(uint8_t port_num);

/**
 * @brief Check if serial port is initialized
 * 
 * @param port_num Serial port number
 * @param[out] initialized Pointer to store initialization status
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t serial_is_initialized(uint8_t port_num, bool *initialized);

/**
 * @brief Get available bytes in receive buffer
 * 
 * @param port_num Serial port number
 * @param[out] available Pointer to store number of available bytes
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t serial_available(uint8_t port_num, size_t *available);

#ifdef __cplusplus
}
#endif
