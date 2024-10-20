#include "candriver.h"
#include "controlcan.h" //for usbcan ii+
//#include "zcan.h"  //for usbcanfd 200U
// #include "ulog.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define CAN_RECEIVE_BUF_SIZE 10

// device type
static int DEVICE_TYPE = 4;  //DEVICE_TYPE = VCI_USBCAN2 //4
//static int DEVICE_TYPE = 33;  //DEVICE_TYPE = VCI_USBCANFD 200U //33
static int DEVICE_INDEX = 0;

static void get_baudrate(const char *str, int *para0, int *para1)
{
    if (str == NULL)
    {
        str = "250k";
    }
    if (str)
    {
        if (strcasecmp(str, "125k") == 0)
        {
            *para0 = 0x03;
            *para1 = 0x1C;
            printf("bitrate = 125k");
        }
        else if (strcasecmp(str, "250k") == 0)
        {
            *para0 = 0x01;
            *para1 = 0x1C;
            printf("bitrate = 250k");
        }
        else if (strcasecmp(str, "500k") == 0)
        {
            *para0 = 0x00;
            *para1 = 0x1C;
            printf("bitrate = 500k");
        }
        else if (strcasecmp(str, "1000k") == 0)
        {
            *para0 = 0x00;
            *para1 = 0x14;
            printf("bitrate = 1000k");
        }
        else
        {
            printf("unsupport bitrate='%s', using default = 250k", str);
            *para0 = 0x01;
            *para1 = 0x1C;
        }
    }
}

static bool local_init(int channels, const char *arg1, const char *arg2)
{
    printf("open zlg canbus device: type=%d index=%d.\n", DEVICE_TYPE, DEVICE_INDEX);
    // 如果失败，则尝试关闭1次再打开
    if (!VCI_OpenDevice(DEVICE_TYPE, DEVICE_INDEX, 0))
    {
        printf("VCI_OpenDevice error.\n");
        VCI_CloseDevice(DEVICE_TYPE, DEVICE_INDEX); //段错误 (核心已转储)
        if (!VCI_OpenDevice(DEVICE_TYPE, DEVICE_INDEX, 0))
        {
            printf("VCI_OpenDevice error again, exit.\n");
            VCI_CloseDevice(DEVICE_TYPE, DEVICE_INDEX); //段错误 (核心已转储)
            return false;
        }
    }
    else
    {
        printf("VCI_OpenDevice succeeded.\n");
    }
    // config every channel
    for (int i = 0; i < channels; i++)
    {
    #if 1  //for usbcan ii
        VCI_INIT_CONFIG config = {0};
        config.AccCode = 0;
        config.AccMask = 0xFFFFFFFF;
        config.Reserved = 0;
        config.Filter = 1;
        config.Mode = 0;
        int time0 = 0;
        int time1 = 0;
        // get_baudrate(bitsstr[i], &time0, &time1);
        config.Timing0 = 0x00;
        config.Timing1 = 0x1C;
    #else //for usbcanfd200U
        ZCAN_INIT config = {0};
        config.clk = 60000000; // clock: 60M
        config.mode = 0;
        config.aset.tseg1 = 103; // 500k
        config.aset.tseg2 = 14;
        config.aset.sjw = 3;
        config.aset.smp = 0;
        config.aset.brp = 0;
        config.dset.tseg1 = 14; // 500k
        config.dset.tseg2 = 3;
        config.dset.sjw = 3;
        config.dset.smp = 0;
        config.dset.brp = 5;
    #endif
        // init
        int stat = VCI_InitCAN(DEVICE_TYPE, DEVICE_INDEX, i, &config);
        if (stat <= 0)
        {
            printf("VCI_InitCAN error, channel=%d", i);
            VCI_CloseDevice(DEVICE_TYPE, DEVICE_INDEX);
            return false;
        }
        // reset
        stat = VCI_ResetCAN(DEVICE_TYPE, DEVICE_INDEX, i);
        if (stat <= 0)
        {
            printf("VCI_ResetCAN error, channel=%d", i);
            VCI_CloseDevice(DEVICE_TYPE, DEVICE_INDEX);
            return false;
        }
        // start
        stat = VCI_StartCAN(DEVICE_TYPE, DEVICE_INDEX, i);
        if (stat <= 0)
        {
            printf("VCI_StartCAN error, channel=%d", i);
            VCI_CloseDevice(DEVICE_TYPE, DEVICE_INDEX);
            return false;
        }
    }

    return true;
}

static int local_recv(int channel, struct can_frame *out_frame)
{
#if 1  //for usbcan ii
    VCI_CAN_OBJ candata_buff[CAN_RECEIVE_BUF_SIZE] = {0};
    int stat = VCI_Receive(DEVICE_TYPE, DEVICE_INDEX, channel, &candata_buff, CAN_RECEIVE_BUF_SIZE, 1);
    //printf("%d\n",stat);
    if (stat > 0)
    {
        for (size_t j = 0; j < stat; j++)
        {
            CAN_SET_ID(&out_frame[j], candata_buff[j].ID);
            if (candata_buff[j].ExternFlag)
            {
                CAN_SET_EFF(&out_frame[j]);
            }
            if (candata_buff[j].RemoteFlag)
            {
                CAN_SET_RTR(&out_frame[j]);
            }
            out_frame[j].can_dlc = candata_buff[j].DataLen;
            for (int i = 0; i < candata_buff[j].DataLen; i++)
            {
                out_frame[j].data[i] = candata_buff[j].Data[i];
            }
        }
        return stat;
    }
#else //for usbcanfd200U
    ZCAN_20_MSG candata = {0};
    int stat = VCI_Receive(DEVICE_TYPE, DEVICE_INDEX, channel, &candata, 1, 10);
    //printf("%d\n",stat);
    if (stat > 0)
    {
        struct can_frame frame = {0};
        CAN_SET_ID(&frame, candata.hdr.id);
        if (candata.hdr.inf.sef)
        {
            CAN_SET_EFF(&frame);
        }
        if (candata.hdr.inf.sdf)
        {
            CAN_SET_RTR(&frame);
        }
        frame.can_dlc = candata.hdr.len;
        for (int i = 0; i < candata.hdr.len; i++)
        {
            frame.data[i] = candata.dat[i];
        }
        *out_frame = frame;
        return 1;
    }
#endif
    return 0;
}

static int local_send(int channel, const struct can_frame *frame)
{
#if 1  //for usbcan ii
    VCI_CAN_OBJ data;
    data.SendType = 0;
    data.ID = CAN_GET_ID(frame);
    data.DataLen = frame->can_dlc;
    data.RemoteFlag = CAN_IS_RTR(frame);
    data.ExternFlag = CAN_IS_EFF(frame);
    memcpy(data.Data, frame->data, frame->can_dlc);
#else //for usbcanfd200U
    ZCAN_20_MSG data;
    data.hdr.inf.txm = ZCAN_TX_NORM;
    data.hdr.inf.fmt = 0;
    data.hdr.id = CAN_GET_ID(frame);
    data.hdr.len = frame->can_dlc;
    data.hdr.inf.sdf = CAN_IS_RTR(frame);
    data.hdr.inf.sef = CAN_IS_EFF(frame);
    memcpy(data.dat, frame->data, frame->can_dlc);
#endif
    int stat = VCI_Transmit(DEVICE_TYPE, DEVICE_INDEX, channel, &data, 1);
    if (stat < 0)
    {
        printf("ch%d VCI_Transmit error", channel);
        return -1;
    }
    else
    {
        return 1;
    }
}

static void local_cleanup(int channels)
{
    VCI_CloseDevice(DEVICE_TYPE, DEVICE_INDEX);
}

struct CanbusMeta CANBUS_ZLG = {
    .name = "ZLG",
    .channels = 2,
    .do_init = local_init,
    .do_recv = local_recv,
    .do_send = local_send,
    .do_cleanup = local_cleanup,
};

struct CanbusMeta *CANBUS_META = &CANBUS_ZLG;
