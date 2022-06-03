#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

#include "i2c_mcp23017.h"

static const char TAG[] = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Initializing bus I2C0...");
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf = {   // (1)ピン設定用の構造体
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_DISABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_DISABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_param_config(i2c_master_port, &conf);   // (2)初期化する
    i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);    // (3)ドライバーのインストール

    esp_err_t ret;
    ret = i2c_mcp23017_write(IOCON, IOCON_COMMAND);    // IOCONの設定
    ESP_ERROR_CHECK(ret);
    ret = i2c_mcp23017_write(IODIRA, IO_ALL_OUTPUT);   // GPIOA方向レジスタの設定
    ESP_ERROR_CHECK(ret);
    ret = i2c_mcp23017_write(IODIRB, IO_INPUT_D7_ONLY);    // GPIOB方向レジスタの設定
    ESP_ERROR_CHECK(ret);
    ret = i2c_mcp23017_write(GPPUB, IO_PULLUP_D7_ONLY);    // GIPOBプルアップレジスタの設定
    ESP_ERROR_CHECK(ret);

    uint8_t ex = 0;
    uint8_t input_data;

    // GPIOA: オール出力, GPIOB: D7だけが入力、それ以外は出力
    // GPIOA: 定期的にGPIOA0ビットを反転させてLチカする
    // GPIOB:は D7をレジスタ設定でプルアップしておき、GNDに落とすとD7がLになりGPIOB0でLEDを点灯させる

    i2c_mcp23017_write(GPIOB, 1);

    while (1) {
        vTaskDelay(100);
        i2c_mcp23017_write(GPIOA, ex & 1); // GPIOA0でLチカ
        ret = i2c_mcp23017_read(GPIOB, &input_data);
        if (input_data & 0x80)
        {
           i2c_mcp23017_write(GPIOB, 1); // GPIOB0で消灯
        }
        else
        {
           i2c_mcp23017_write(GPIOB, 0); // GPIOB0で点灯
        }
        ex++;
    }
}

