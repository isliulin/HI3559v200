/**
* Copyright (C), 2017-2018, Hisilicon Tech. Co., Ltd.
* All rights reserved.
*
* @file    sensor_interface_cfg_params.c
* @brief   sensor dev interface config params:
* one type interface config params must be choiced at global var "user_dev_attr"
* @author  HiMobileCam NDK develop team
* @date    2018/2/7
*/

#include "mpi_vi.h"
#include "mpi_isp.h"
#include "hi_sns_ctrl.h"
#include "sensor_comm.h"
#include "sensor_interface_cfg_params.h"
#include "../include/sensor_interface_cfg_adapt.h"

static const HI_MAPI_MIPI_INTF_S g_Sensor_MipiIntfCfg[] =
{
    /*config 4k@30fps*/
    {
        .img_rect =
        {
            .x = 0,
            .y = 0,
            .width = 3840,
            .height = 2160
        },
        .stSnsSize =
        {
            .u32Width = 3840,
            .u32Height = 2160
        },
        .mipi_attr =
        {
            .input_data_type = DATA_TYPE_RAW_10BIT,
            .wdr_mode = HI_MIPI_WDR_MODE_NONE,
        },
    },
    /*config 12M@30fps*/
    {
        .img_rect =
        {
            .x = 0,
            .y = 0,
            .width = 4000,
            .height = 3000
        },
        .stSnsSize =
        {
            .u32Width = 4000,
            .u32Height = 3000
        },
        .mipi_attr =
        {
            .input_data_type = DATA_TYPE_RAW_10BIT,
            .wdr_mode = HI_MIPI_WDR_MODE_NONE,
        },
    },

    /*config 1080p@120fps*/
    {
        .img_rect =
        {
            .x = 0,
            .y = 0,
            .width = 1920,
            .height = 1080
        },
        .stSnsSize =
        {
            .u32Width = 1920,
            .u32Height = 1080
        },
        .mipi_attr =
        {
            .input_data_type = DATA_TYPE_RAW_10BIT,
            .wdr_mode = HI_MIPI_WDR_MODE_NONE,
        },
    },

    /*config 720P@240fps*/
    {
        .img_rect =
        {
            .x = 0,
            .y = 0,
            .width = 1280,
            .height = 720
        },
        .stSnsSize =
        {
            .u32Width = 1280,
            .u32Height = 720
        },
        .mipi_attr =
        {
            .input_data_type = DATA_TYPE_RAW_10BIT,
            .wdr_mode = HI_MIPI_WDR_MODE_NONE,
        },
    },
};

/*width and height must align with 4 bytes*/
static const HI_MAPI_SENSOR_MODE_S g_Sensor_Mode[] =
{
    /*SENSOR_MODE_4K_30FPS  frameRate:[1.0-30]*/
    {
        .s32Width = 3840,
        .s32Height = 2160,
        .u8SnsMode = 0,
        .enWdrMode = WDR_MODE_NONE,
        .f32SnsMaxFrameRate = 30.0f
    },
    /*SENSOR_MODE 12M@30FPS  frameRate:[1.0-20]*/
    {
        .s32Width = 4000,
        .s32Height = 3000,
        .u8SnsMode = 0,
        .enWdrMode = WDR_MODE_NONE,
        .f32SnsMaxFrameRate = 30.0f
    },
    /*SENSOR_MODE 1080p@120FPS  frameRate:[1.0-90]*/
    {
        .s32Width = 1920,
        .s32Height = 1080,
        .u8SnsMode = 0,
        .enWdrMode = WDR_MODE_NONE,
        .f32SnsMaxFrameRate = 120.0f
    },
    /*SENSOR_MODE 720p@240FPS  frameRate:[1.0-240]*/
    {
        .s32Width = 1280,
        .s32Height = 720,
        .u8SnsMode = 0,
        .enWdrMode = WDR_MODE_NONE,
        .f32SnsMaxFrameRate = 240.0f
    },
};

/*final interface here*/
static HI_MAPI_COMBO_DEV_ATTR_S g_Sensor_Cfg =
{
    /*config SENSOR */
    .pSensorObj = &stSnsOv12870Obj,
    .s32SensorType = OV12870,
    .input_mode = INPUT_MODE_MIPI,
    .data_rate = MIPI_DATA_RATE_X1,
    .stSensorInputAttr =
    {
        .enBayerFormat = BAYER_BGGR,
        .enSensorCommBusType = HI_SENSOR_COMMBUS_TYPE_I2C,
    },

    .stSensorMode =
    {
        .s32SensorModeCnt = sizeof(g_Sensor_Mode) / sizeof(HI_MAPI_SENSOR_MODE_S),
        .pSensorMode = g_Sensor_Mode,
        .pstIntf = g_Sensor_MipiIntfCfg
    },

    .aLaneId =
    {
#if defined  CFG_LANE_DIVIDE_MODE_0
        /*mipi_dev0*/
        {
            {  0,  1,  2,  3}, /*4K@30FPS*/
            {  0,  1,  2,  3}, /*12M@30FPS*/
            {  0,  1,  2,  3}, /*1080p@90FPS*/
            {  0,  1,  2,  3}, /*720p@120FPS*/
        },

        /*No mipi_dev1*/
        {
            {}, {}, {}, {},

        }
#elif defined  CFG_LANE_DIVIDE_MODE_1
        /*mipi_dev0*/
        {
            {  0,  2,  -1,  -1}, /*4K@30FPS*/
            {  0,  2,  -1,  -1}, /*12M@30FPS*/
            {  0,  2,  -1,  -1}, /*1080p@120FPS*/
            {  0,  2,  -1,  -1}, /*720p@120FPS*/
        },

        /*mipi_dev1*/
        {
            {  1,  3,  -1,  -1}, /*4K@30FPS*/
            {  1,  3,  -1,  -1}, /*12M@30FPS*/
            {  1,  3,  -1,  -1}, /*1080p@120FPS*/
            {  1,  3,  -1,  -1}, /*720p@120FPS*/
        }
#endif
    },
};

HI_U32 SensorOV12870Init(void)
{
    return MAPI_SENSOR_Register((HI_MAPI_COMBO_DEV_ATTR_S*)&g_Sensor_Cfg);
}
