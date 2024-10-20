#ifndef CANDRIVER_H
#define CANDRIVER_H
#include "can.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // 抽象封装 canbus 驱动操作：
    // 1. 读取 can 总线消息并广播到 nng pub
    // 2. 读取 nng pull 消息并写入 can 总线
    // 3. 支持双通道 can 设备，包括 socketcan/msi can/zlg can

    // 初始化 canbus，成功返回 true, 失败返回 false. channels 为需要使用的通道数量 1 or 2, arg1/arg2 一般为两个 channel 的比特率，socketcan 为 can 设备名称
    typedef bool (*handler_init)(int channels, const char *arg1, const char *arg2);

    // 获取某 1 channel 的 can 数据，成功返回 1, 无数据返回 0, 出错返回 -1. frame 为获取填充的 can 报文
    typedef int (*handler_recv)(int channel, struct can_frame *frame);

    // 发送某 1 channel can 数据，成功返回 1 失败返回 -1
    typedef int (*handler_send)(int channel, const struct can_frame *frame);

    // 清理 canbus 模块，channels 为打开的通道数量
    typedef void (*handler_cleanup)(int channels);

    // canbus 设备抽象提供的功能
    struct CanbusMeta
    {
        char *name;   // can 总线名称
        int channels; // 支持的 can 通道数量： 1 or 2
        handler_init do_init;
        handler_recv do_recv;
        handler_send do_send;
        handler_cleanup do_cleanup;
    };

#ifdef __cplusplus
}
#endif
#endif /* CANDRIVER_H */
