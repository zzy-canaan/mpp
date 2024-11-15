#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "k_connector_comm.h"
#include "k_connector_ioctl.h"
#include "k_vo_comm.h"
#include "mpi_connector_api.h"

#define pr_debug(...) // printf(__VA_ARGS__)
#define pr_info(...) // printf(__VA_ARGS__)
#define pr_warn(...) // printf(__VA_ARGS__)
#define pr_err(...) printf(__VA_ARGS__)

k_connector_info connector_info_list[] = {
#if defined (CONFIG_MPP_ENABLE_DSI_DEBUGGER)
    {
        .connector_name = "debugger",
        .type = DSI_DEBUGGER_DEVICE,
    },
#endif
    {
        "hx8399",
        0,
        0,
        BACKGROUND_BLACK_COLOR,
        11,
        7,
        K_DSI_4LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 15, 295, 0x17, 0x96 },
        { 74250, 445500, 1160, 1080, 20, 20, 40, 2134, 1920, 5, 8, 206 },
        HX8377_V2_MIPI_4LAN_1080X1920_30FPS,
    },
    {
        "lt9611",
        0,
        0,
        BACKGROUND_BLACK_COLOR,
        10,
        0,
        K_DSI_4LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        LT9611_MIPI_ADAPT_RESOLUTION,
    },
    {
        "lt9611",
        0,
        0,
        BACKGROUND_BLACK_COLOR,
        10,
        3,
        K_DSI_4LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 15, 295, 0x09, 0x96 },
        { 148500, 891000, 2200, 1920, 44, 148, 88, 1125, 1080, 5, 4, 36 },
        LT9611_MIPI_4LAN_1920X1080_60FPS,
    },
    {
        "lt9611",
        0,
        0,
        BACKGROUND_BLACK_COLOR,
        10,
        3,
        K_DSI_4LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 15, 295, 0x09, 0x96 },
        { 148500, 891000, 2200, 1920, 44, 148, 88, 1125, 1080, 5, 4, 36 },
        LT9611_MIPI_4LAN_1920X1080_30FPS,
    },
    // {
    //     "lt9611",
    //     0,
    //     0,
    //     BACKGROUND_BLACK_COLOR,
    //     10,
    //     7,
    //     K_DSI_4LAN,
    //     K_BURST_MODE,
    //     K_VO_LP_MODE,
    //     { 15, 295, 0x19, 0x96 },
    //     { 74250, 445500, 2200, 1920, 44, 148, 88, 1125, 1080, 5, 4, 36 },
    //     LT9611_MIPI_4LAN_1920X1080_30FPS,
    // },
    {
        "lt9611",
        0,
        0,
        BACKGROUND_BLACK_COLOR,
        9,
        7,
        K_DSI_4LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 15, 295, 0x19, 0x96 },
        { 74250, 445500, 1616, 1280, 40, 220, 76, 765, 720, 5, 4, 36 },
        LT9611_MIPI_4LAN_1280X720_60FPS,
    },
    {
        "lt9611",
        0,
        0,
        BACKGROUND_BLACK_COLOR,
        9,
        7,
        K_DSI_4LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 15, 295, 0x19, 0x96 },
        { 74250, 445500, 1940, 1280, 40, 220, 400, 765, 720, 5, 4, 36 },
        LT9611_MIPI_4LAN_1280X720_50FPS,
    },
    {
        "lt9611",
        0,
        0,
        BACKGROUND_BLACK_COLOR,
        9,
        7,
        K_DSI_4LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 15, 295, 0x19, 0x96 },
        { 74250, 445500, 3232, 1280, 40, 220, 1692, 765, 720, 5, 4, 36 },
        LT9611_MIPI_4LAN_1280X720_30FPS,
    },
    {
        "lt9611",
        0,
        0,
        BACKGROUND_BLACK_COLOR,
        9,
        23,
        K_DSI_4LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 15, 394, 0x39, 0x96 },
        { 24750, 148500, 800, 640, 96, 48, 16, 525, 480, 5, 4, 36 },
        LT9611_MIPI_4LAN_640X480_60FPS,
    },
    // {
    //     "st7701",
    //     0,
    //     0,
    //     BACKGROUND_BLACK_COLOR,
    //     10,
    //     24,
    //     K_DSI_2LAN,
    //     K_BURST_MODE,
    //     K_VO_LP_MODE,
    //     { 10, 259, 0x27, 0x84 },
    //     { 23760, 285120, 660, 480, 10, 20, 150, 1200, 800, 10, 20, 370 },
    //     ST7701_V1_MIPI_2LAN_480X800_30FPS,
    // },
#if defined (CONFIG_BOARD_K230_CANMV_LCKFB)
    {
        "st7701",
        .screen_test_mode = 0,
        .dsi_test_mode = 0,
        .bg_color = BACKGROUND_BLACK_COLOR,
        .intr_line = 10, // 1024 lines
        .pixclk_div = 17,
        .lan_num = K_DSI_2LAN,
        .work_mode = K_BURST_MODE,
        .cmd_mode = K_VO_LP_MODE,
        .phy_attr = {
            .n = 3,
            .m = 64,
            .voc = 0x1f, // 0b00011111
            .hs_freq = 0x80 | 0x13, // 0b10010011
        },
        .resolution = {
            .pclk = 33000, // 33000 * 1000 / (480 + 8 + 32 + 32) / (800 + 10 + 140 + 150) = 54.35 fps
            .phyclk = 396000,
            .htotal = (480 + 8 + 32 + 32), // 552
            .hdisplay = 480,
            .hsync_len = 8,
            .hback_porch = 32,
            .hfront_porch = 32,
            .vtotal = (800 + 10 + 140 + 150), // 1100
            .vdisplay = 800,
            .vsync_len = 10,
            .vback_porch = 150,
            .vfront_porch = 140,
        },
        ST7701_V1_MIPI_2LAN_480X800_30FPS,
    },
#else
    {
        // this configure is generated by tools.
        .connector_name = "st7701",
        .screen_test_mode = 0,
        .dsi_test_mode = 0,
        .bg_color = BACKGROUND_BLACK_COLOR,
        .intr_line = 10, // 1024 lines
        .pixclk_div = 21,
        .lan_num = K_DSI_2LAN,
        .work_mode = K_BURST_MODE,
        .cmd_mode = K_VO_LP_MODE,
        .phy_attr = {
            .n = 3,
            .m = 52,
            .voc = 0x1f, // 0b00011111
            .hs_freq = 0x80 | 0x22, // 0b10100010
        },
        .resolution = {
            .pclk = 27000, // 27000 * 1000 / (480 + 2 + 16 + 50) / (800 + 180 + 60 + 60) = 44.79 fps
            .phyclk = 324000,
            .htotal = (480 + 2 + 16 + 50), // 548
            .hdisplay = 480,
            .hsync_len = 2,
            .hback_porch = 16,
            .hfront_porch = 50,
            .vtotal = (800 + 180 + 60 + 60), // 1100
            .vdisplay = 800,
            .vsync_len = 60,
            .vback_porch = 180,
            .vfront_porch = 60,
        },
        .type = ST7701_V1_MIPI_2LAN_480X800_30FPS,
    },
#endif

    {
        "st7701",
        0,
        0,
        BACKGROUND_PINK_COLOR,
        10,
        24,
        K_DSI_2LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 10, 259, 0x27, 0x84 },
        { 23760, 285120, 660, 480, 10, 20, 150, 1200, 854, 10, 20, 316 },
        ST7701_V1_MIPI_2LAN_480X854_30FPS,
    },
#if defined (CONFIG_BOARD_K230D_CANMV_ATK_DNK230D)
    {
        .connector_name = "st7701",
        .screen_test_mode = 0,
        .dsi_test_mode = 0,
        .bg_color = BACKGROUND_BLACK_COLOR,
        .intr_line = 9,
        .pixclk_div = 24,
        .lan_num = K_DSI_2LAN,
        .work_mode = K_BURST_MODE,
        .cmd_mode = K_VO_LP_MODE,
        .phy_attr = {
            .n = 11,
            .m = 278,
            .voc = 0x27,
            .hs_freq = 0x84,
        },
        .resolution = {
            .pclk = 23760,
            .phyclk = 285120,
            .htotal = 625,
            .hdisplay = 480,
            .hsync_len = 6,
            .hback_porch = 6,
            .hfront_porch = 133,
            .vtotal = 686,
            .vdisplay = 640,
            .vsync_len = 6,
            .vback_porch = 14,
            .vfront_porch = 26,
        },
        .type = ST7701_V1_MIPI_2LAN_480X640_30FPS,
    },
#else
    {
        .connector_name = "st7701",
        .screen_test_mode = 0,
        .dsi_test_mode = 0,
        .bg_color = BACKGROUND_BLACK_COLOR,
        .intr_line = 10, // 1024 lines
        .pixclk_div = 23,
        .lan_num = K_DSI_2LAN,
        .work_mode = K_BURST_MODE,
        .cmd_mode = K_VO_LP_MODE,
        .phy_attr = {
            .n = 3,
            .m = 97,
            .voc = 0x27, // 0b00100111
            .hs_freq = 0x80 | 0x02, // 0b10000010
        },
        .resolution = {
            .pclk = 24750, // 24750 * 1000 / (480 + 6 + 10 + 20) / (640 + 30 + 60 + 300) = 46.57 fps
            .phyclk = 297000,
            .htotal = (480 + 6 + 10 + 20), // 516
            .hdisplay = 480,
            .hsync_len = 6,
            .hback_porch = 10,
            .hfront_porch = 20,
            .vtotal = (640 + 30 + 60 + 300), // 1030
            .vdisplay = 640,
            .vsync_len = 30,
            .vback_porch = 60,
            .vfront_porch = 300,
        },
        .type = ST7701_V1_MIPI_2LAN_480X640_30FPS,
    },
#endif
    {
        "ili9806",
        0,
        0,
        BACKGROUND_PINK_COLOR,
        9,
        14,
        K_DSI_2LAN,
        K_NON_BURST_MODE_WITH_PULSES,
        K_VO_LP_MODE,
        { 4, 97, 0x19, 0x96 },
        { 39600, 475200, 714, 480, 50, 100, 84, 895, 800, 15, 40, 40 },
        ILI9806_MIPI_2LAN_480X800_30FPS,
    },
    {
        "virtdev",
        0,
        0,
        BACKGROUND_BLACK_COLOR,
        7,
        0,
        K_DSI_4LAN,
        K_BURST_MODE,
        K_VO_LP_MODE,
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        VIRTUAL_DISPLAY_DEVICE,
    },
    {
        .connector_name = NULL,
    }
};

k_s32 kd_mpi_get_connector_info(k_connector_type connector_type, k_connector_info* connector_info)
{
    if (!connector_info) {
        pr_err("%s, connector_info is null\n", __func__);
        return K_ERR_VO_NULL_PTR;
    }

#if defined (CONFIG_MPP_ENABLE_DSI_DEBUGGER)
    if(DSI_DEBUGGER_DEVICE == connector_type) {
        kd_mpi_connector_parse_setting(connector_info_list);
    }
#endif // CONFIG_MPP_ENABLE_DSI_DEBUGGER

    for (k_s32 i = 0; i < sizeof(connector_info_list) / sizeof(k_connector_info); i++) {
        if (connector_type == connector_info_list[i].type) {
            memcpy(connector_info, &connector_info_list[i], sizeof(k_connector_info));
            return 0;
        }
    }
    return K_ERR_UNEXIST;
}

k_s32 kd_mpi_connector_adapt_resolution(k_connector_type type, k_connector_negotiated_data* negotiated_data)
{
    k_u32 ret = 0;
    k_s32 connector_fd;
    k_connector_type connector_type;
    k_connector_info connector_info;

    // step 1
    // read HDMI monitor EDID and negotiate the resolution
    memset(&connector_info, 0, sizeof(k_connector_info));
    connector_type = type;
    ret = kd_mpi_get_connector_info(connector_type, &connector_info);
    if (ret) {
        printf("%s get connector info failed for connector_type %d\n", __func__, connector_type);
        return ret;
    }

    connector_fd = kd_mpi_connector_open(connector_info.connector_name);
    if (connector_fd < 0) {
        printf("%s connector open %s failed \n", __func__, connector_info.connector_name);
        return K_ERR_VO_NOTREADY;
    }
    kd_mpi_connector_get_negotiated_data(connector_fd, negotiated_data);
    kd_mpi_connector_close(connector_fd);

    // step 2
    // according to the negotiated resolution and then set the prefered resolution
    memset(&connector_info, 0, sizeof(k_connector_info));
    connector_type = negotiated_data->negotiated_types[0];
    ret = kd_mpi_get_connector_info(connector_type, &connector_info);
    if (ret) {
        printf("%s get connector info failed for connector_type %d\n", __func__, connector_type);
        return ret;
    }

    connector_fd = kd_mpi_connector_open(connector_info.connector_name);
    if (connector_fd < 0) {
        printf("%s connector open %s failed \n", __func__, connector_info.connector_name);
        return K_ERR_VO_NOTREADY;
    }
    kd_mpi_connector_power_set(connector_fd, 1);
    kd_mpi_connector_init(connector_fd, connector_info);

    return 0;
}

k_s32 kd_mpi_connector_open(const char* connector_name)
{
    k_s32 fd = 0;
    char dev_name[52];

    if (!connector_name) {
        pr_err("%s, sensor_name is null\n", __func__);
        return -K_ERR_VO_NULL_PTR;
    }

    snprintf(dev_name, sizeof(dev_name), "/dev/connector_%s", connector_name);
    fd = open(dev_name, O_RDWR);
    if (fd < 0) {
        pr_err("%s, failed(%d).\n", __func__, fd);
        return -K_ERR_VO_NOTREADY;
    }
    return fd;
}

k_s32 kd_mpi_connector_close(k_s32 fd)
{
    close(fd);
}

k_s32 kd_mpi_connector_power_set(k_s32 fd, k_bool on)
{
    k_s32 ret;

    ret = ioctl(fd, KD_IOC_CONNECTOR_S_POWER, &on);
    if (ret != 0) {
        pr_err("%s, error(%d)\n", __func__, ret);
        return K_ERR_VO_NOT_SUPPORT;
    }

    return ret;
}

k_s32 kd_mpi_connector_id_get(k_s32 fd, k_u32* sensor_id)
{
    k_s32 ret;

    if (!sensor_id) {
        pr_err("%s, sensor_id is null\n", __func__);
        return K_ERR_VO_NULL_PTR;
    }

    ret = ioctl(fd, KD_IOC_CONNECTOR_G_ID, sensor_id);
    if (ret != 0) {
        pr_err("%s, error(%d)\n", __func__, ret);
        return K_ERR_VO_NOT_SUPPORT;
    }

    return ret;
}

k_s32 kd_mpi_connector_init(k_s32 fd, k_connector_info info)
{
    k_s32 ret;

    ret = ioctl(fd, KD_IOC_CONNECTOR_S_INIT, info);
    if (ret != 0) {
        pr_err("%s, error(%d)\n", __func__, ret);
        return K_ERR_VO_NOT_SUPPORT;
    }

    return ret;
}

k_s32 kd_mpi_connector_get_negotiated_data(k_s32 fd, k_connector_negotiated_data* negotiated_data)
{
    k_s32 ret;

    ret = ioctl(fd, KD_IOC_CONNECTOR_G_NEG_DATA, negotiated_data);
    if (ret == -1) {
        pr_err("%s, error(%d)\n", __func__, ret);
        return K_ERR_VO_NOT_SUPPORT;
    }

    return ret;
}

k_s32 kd_mpi_connector_set_mirror(k_s32 fd, k_connector_mirror mirror)
{
    k_s32 ret;

    ret = ioctl(fd, KD_IOC_CONNECTOR_S_MIRROR, &mirror);
    if (ret != 0) {
        pr_err("%s, error(%d)\n", __func__, ret);
        return K_ERR_VO_NOT_SUPPORT;
    }

    return ret;
}
