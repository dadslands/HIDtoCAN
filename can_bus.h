#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CAN bus mode
 */
typedef enum {
    CAN_MODE_NORMAL = 0,     /*!< Normal mode */
    CAN_MODE_LISTEN_ONLY,    /*!< Listen-only mode (no transmission) */
    CAN_MODE_LOOPBACK        /*!< Loopback mode (for testing) */
} can_mode_t;

/**
 * @brief CAN bus configuration structure
 */
typedef struct {
    uint8_t port_num;        /*!< CAN port number (0-1) */
    uint32_t bitrate;        /*!< Bit rate in bits per second */
    can_mode_t mode;         /*!< CAN mode */
    int8_t tx_pin;           /*!< TX pin number (-1 for default) */
    int8_t rx_pin;           /*!< RX pin number (-1 for default) */
    bool accept_all;         /*!< Accept all messages (no filtering) */
    uint16_t rx_queue_size;  /*!< RX queue size */
    uint16_t tx_queue_size;  /*!< TX queue size */
} can_bus_config_t;

/**
 * @brief CAN message structure
 */
typedef struct {
    uint32_t id;             /*!< Message ID */
    bool extended;           /*!< Extended ID flag */
    bool rtr;                /*!< Remote transmission request flag */
    uint8_t dlc;             /*!< Data length code (0-8) */
    uint8_t data[8];         /*!< Message data */
} can_message_t;

/**
 * @brief Initialize CAN bus
 * 
 * @param config Pointer to CAN bus configuration
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_init(const can_bus_config_t *config);

/**
 * @brief Deinitialize CAN bus
 * 
 * @param port_num CAN port number
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_deinit(uint8_t port_num);

/**
 * @brief Start CAN bus
 * 
 * @param port_num CAN port number
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_start(uint8_t port_num);

/**
 * @brief Stop CAN bus
 * 
 * @param port_num CAN port number
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_stop(uint8_t port_num);

/**
 * @brief Send CAN message
 * 
 * @param port_num CAN port number
 * @param message Pointer to CAN message
 * @param timeout_ms Timeout in milliseconds
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_send(uint8_t port_num, const can_message_t *message, uint32_t timeout_ms);

/**
 * @brief Receive CAN message
 * 
 * @param port_num CAN port number
 * @param message Pointer to store received CAN message
 * @param timeout_ms Timeout in milliseconds
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_receive(uint8_t port_num, can_message_t *message, uint32_t timeout_ms);

/**
 * @brief Add CAN message filter
 * 
 * @param port_num CAN port number
 * @param id Message ID to filter
 * @param mask ID mask (bits set to 1 are compared)
 * @param extended Extended ID flag
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_add_filter(uint8_t port_num, uint32_t id, uint32_t mask, bool extended);

/**
 * @brief Remove all CAN message filters
 * 
 * @param port_num CAN port number
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_clear_filters(uint8_t port_num);

/**
 * @brief Check if CAN bus is initialized
 * 
 * @param port_num CAN port number
 * @param[out] initialized Pointer to store initialization status
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_is_initialized(uint8_t port_num, bool *initialized);

/**
 * @brief Get CAN bus status
 * 
 * @param port_num CAN port number
 * @param[out] tx_error_counter Pointer to store TX error counter
 * @param[out] rx_error_counter Pointer to store RX error counter
 * @param[out] bus_off Pointer to store bus-off status
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_get_status(uint8_t port_num, uint8_t *tx_error_counter, uint8_t *rx_error_counter, bool *bus_off);

/**
 * @brief Reset CAN bus after bus-off condition
 * 
 * @param port_num CAN port number
 * @return esp_err_t ESP_OK on success, error code otherwise
 */
esp_err_t can_reset_bus(uint8_t port_num);

#ifdef __cplusplus
}
#endif
