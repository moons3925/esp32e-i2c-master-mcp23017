#include "driver/i2c.h"

#define I2C_MASTER_NUM 0
#define I2C_MASTER_SDA_IO 2
#define I2C_MASTER_SCL_IO 0
#define I2C_MASTER_FREQ_HZ 400000   // 400kHz

#define CMD_WRITE 0x40  // A0,A1,A2=GNDに接続した場合のハードウェアアドレス
#define CMD_READ (CMD_WRITE | 1)

// BANKビットの値によってレジスタアドレスがかわる
// BANK=0時のレジスタアドレス

#define IOCON 0x0a      // コンフィグレーションレジスタ
#define IODIRA 0x00     // IO方向レジスタA
#define IODIRB 0x01     // IO方向レジスタB
#define GPINTENA 0x04      // 状態変化割り込み　制御レジスタA
#define GPINTENB 0x05      // 状態変化割り込み　制御レジスタB
#define DEFVALA 0x06      // 状態変化割り込み用　規定値レジスタA
#define DEFVALB 0x07      // 状態変化割り込み用　規定値レジスタB
#define INTCONA 0x08      // 状態変化割り込み用　比較指定レジスタA
#define INTCONB 0x09      // 状態変化割り込み用　比較指定レジスタB
#define GPPUA 0x0c      // プルアップレジスタA
#define GPPUB 0x0d      // プルアップレジスタB
#define INTFA 0x0e      // フラグレジスタA
#define INTFB 0x0f      // フラグレジスタB
#define INTCAPA 0x10      // 割り込みキャプチャレジスタA
#define INTCAPB 0x11      // 割り込みキャプチャレジスタB
#define GPIOA 0x12      // ポートレジスタA
#define GPIOB 0x13      // ポートレジスタB

#define IO_ALL_OUTPUT 0x00  // 方向レジスタへの全ビット出力設定値
#define IO_ALL_INPUT 0xff   // 方向レジスタへの全ビット入力設定値
#define IO_INPUT_D7_ONLY 0x80   // 方向レジスタへの入出力設定値（D7のみ入力でそれ以外は出力）
#define IO_PULLUP_D7_ONLY 0x80  // プルアップレジスタへの設定値（D7のみプルアップする）
#define IO_INTERRUPT_D7_ONLY 0x80  // 状態変化割り込みレジスタへの設定値（D7変化で割り込み）
#define IO_COMPARE_D7 0x80

#define IOCON_COMMAND 0x28 // シーケンシャルにしない、ハードウェアアドレス有効

//#define _I2C_NUMBER(num) I2C_NUM_##num
//#define I2C_NUMBER(num) _I2C_NUMBER(num)

#define I2C_MASTER_TX_BUF_DISABLE 0  /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0  /*!< I2C master doesn't need buffer */

#define ACK_CHECK_EN 0x1     /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0    /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0          /*!< I2C ack value */
#define NACK_VAL 0x1         /*!< I2C nack value */

esp_err_t i2c_mcp23017_read(uint8_t adrs, uint8_t *data);
esp_err_t i2c_mcp23017_write(uint8_t adrs, uint8_t data);

