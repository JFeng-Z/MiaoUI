#include "Button.h"
#include "string.h"
#include "driver/uart.h"

const uart_port_t uart_num = UART_NUM_0;

void Button_Init(void)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
        .rx_flow_ctrl_thresh = 122,
    };
    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
    // Setup UART buffered IO with event queue
    const int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
    // Write data to UART.
    char* test_str = "Hello World!\n";
    uart_write_bytes(uart_num, (const char*)test_str, strlen(test_str));
}

UI_ACTION Button_Scan(void)
{
    // Read data from UART.
    uint8_t data;
    int length = 1;
    ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*)&length));
    length = uart_read_bytes(uart_num, &data, length, 100);
    switch (data)
    {
    case UI_ACTION_UP:
        return UI_ACTION_UP;
    case UI_ACTION_DOWN:
        return UI_ACTION_DOWN;
    case UI_ACTION_ENTER:
        return UI_ACTION_ENTER;
    default:
        break;
    }
    return UI_ACTION_NONE;
}