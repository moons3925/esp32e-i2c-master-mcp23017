#include "i2c_mcp23017.h"

esp_err_t i2c_mcp23017_read(uint8_t adrs, uint8_t *data)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, CMD_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, adrs, ACK_CHECK_EN);
    i2c_master_start(cmd);  // restart
    i2c_master_write_byte(cmd, CMD_READ, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, data, I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }
    return ESP_OK;
}

esp_err_t i2c_mcp23017_write(uint8_t adrs, uint8_t data)
{
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, CMD_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, adrs, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, data, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }
    return ESP_OK;
}
