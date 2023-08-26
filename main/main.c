// master conflict 1
/* vl53l1 Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "esp_err.h"
#include "vl53l1_api.h"
// feature 2 addeded
// now testing

// futher addition in the fature2
//git merge conflict merger feature hamzatest



#define I2C_MASTER_SCL_IO CONFIG_SCL_IO // make menuconfig
#define I2C_MASTER_SDA_IO CONFIG_SDA_IO
#define I2C_MASTER_NUM CONFIG_I2C_NUM
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0
#define I2C_MASTER_FREQ_HZ 400000

#define LED_RED_IO CONFIG_LED_RED_IO // make menuconfig
#define LED_GREEN_IO CONFIG_LED_GREEN_IO

// #define CALIBRATION_VL53L1
// #difine DEBUG_VL53L1
#define CALIBRATION_VL53L1_HEIGHT 703 // hold this height during calibration
#define STORAGE_NAMESPACE "vl53l1Data"

static const char *TAG = "vl53l1";

static void i2c_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_param_config(i2c_master_port, &conf);
    i2c_driver_install(i2c_master_port, conf.mode,
                       I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE,
                       0);
}

/*init  vl53l1 module*/
static void vl53l1_init(VL53L1_Dev_t *dev)
{
    VL53L1_UserRoi_t Roi0;
    Roi0.TopLeftX = 0; // set ROI according to requirement
    Roi0.TopLeftY = 15;
    Roi0.BotRightX = 15;
    Roi0.BotRightY = 0;
    int status = VL53L1_WaitDeviceBooted(dev);
    status = VL53L1_DataInit(dev);                                       // performs the device initialization
    status = VL53L1_StaticInit(dev);                                     // load device settings specific for a given use case.
    status = VL53L1_SetDistanceMode(dev, VL53L1_DISTANCEMODE_LONG);      // Max distance in dark:Short:136cm Medium:290cm long:360cm
    status = VL53L1_SetMeasurementTimingBudgetMicroSeconds(dev, 160000); // 140 ms is the timing budget which allows the maximum distance of 4 m (in the dark on a white chart)
    status = VL53L1_SetInterMeasurementPeriodMilliSeconds(dev, 200);     // period of time between two consecutive measurements 100ms
    status = VL53L1_SetUserROI(dev, &Roi0);                              // SET region of interest
    status = VL53L1_StartMeasurement(dev);

    if (status != VL53L1_ERROR_NONE)
    {
        ESP_LOGE(TAG, "VL53L1_StartMeasurement failed \n");
    }
    else
    {
        ESP_LOGI(TAG, "VL53L1 StartMeasurement  \n");
    }
}

void get_base_height(VL53L1_Dev_t *dev)
{
    while (1)
    {
        float heightCurrent = 0;
        int countForAvg = 5;
        float heightForAvg = 0;
        VL53L1_RangingMeasurementData_t RangingData;
        for (int i = 0; i < countForAvg;)
        {

            int status = VL53L1_WaitMeasurementDataReady(dev); // 5 HZ
            if (!status)
            {
                status = VL53L1_GetRangingMeasurementData(dev, &RangingData);
                if (status == 0)
                {
                    heightCurrent = RangingData.RangeMilliMeter / 10.0;
                    heightForAvg += heightCurrent;
                    i++;
                    ESP_LOGI(TAG, "height %3.1f \n", heightCurrent);
                }

                status = VL53L1_ClearInterruptAndStartMeasurement(dev); // clear Interrupt start next measurement
            }
        }
        ESP_LOGI(TAG, "height base = %3.1f \n", heightForAvg / countForAvg);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    VL53L1_Dev_t vl53l1_dev;
    // I2C
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_init();

    // led
    gpio_pad_select_gpio(LED_RED_IO);
    gpio_pad_select_gpio(LED_GREEN_IO);
    gpio_set_direction(LED_RED_IO, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GREEN_IO, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_RED_IO, 0);
    gpio_set_level(LED_GREEN_IO, 0);
    // xshut high
    gpio_pad_select_gpio(CONFIG_XSHUT_IO);
    gpio_set_direction(CONFIG_XSHUT_IO, GPIO_MODE_OUTPUT); //
    gpio_set_level(CONFIG_XSHUT_IO, 1);
    vTaskDelay(200 / portTICK_PERIOD_MS);

    vl53l1_dev.I2cHandle = &i2c_master_port;
    vl53l1_dev.I2cDevAddr = 0x52;
    uint8_t byteData;
    uint16_t wordData;
    VL53L1_RdByte(&vl53l1_dev, 0x010F, &byteData);
    ESP_LOGI(TAG, "VL53L1X Model_ID: %02X\n\r", byteData);
    VL53L1_RdByte(&vl53l1_dev, 0x0110, &byteData);
    ESP_LOGI(TAG, "VL53L1X Module_Type: %02X\n\r", byteData);
    VL53L1_RdWord(&vl53l1_dev, 0x010F, &wordData);
    ESP_LOGI(TAG, "VL53L1X: %02X\n\r", wordData);

    vl53l1_init(&vl53l1_dev);

    get_base_height(&vl53l1_dev); // get the height when booted as the base height
}
