/*
 * @Date: 2021-11-29 19:51:08
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2023-07-01 17:08:19
 * @FilePath: /miniEV/src/gps_bridge/src/proj4.cpp
 * @Description: Do not edit
 */

#include "gps_bridge/proj4.h"
#include <string.h>

namespace Location
{
    //Constructor
    proj::proj()
    {
        initForProj4();
    }

    //Destructor
    proj::~proj()
    {
        // 上下文对象在线程结束前，或不再使用的时候进行销毁
        proj_context_destroy(C); /* 如果是单线程也可忽略这一步 */
        proj_destroy(P);
    }

    void proj::initForProj4()
    {
        // 创建一个上下文对象，这个是非线程安全的，建议为每个线程都创建一个
        // 如果是单线程使用，可以直接使用 PJ_DEFAULT_CTX 取代C填入，而不创建C
        sour_EPSG_init = "EPSG:4326";
        des_EPSG_init = "EPSG:4526";
        C = proj_context_create();
        P = proj_create_crs_to_crs(C,
                                   sour_EPSG_init,
                                   des_EPSG_init, /* or +proj=utm +zone=32 +datum=WGS84 */
                                   NULL);
    }

    bool proj::LLtoGaus(const char *sour_EPSG, const char *des_EPSG,
                        const double Long, const double Lat, double &Easting, double &Northing)
    {
        PJ *P_for_GIS;
        PJ_COORD input, output;

        // 创建一个坐标系转换处理对象
        // 第二个参数是源坐标系，第三个参数是目标坐标系
        // 可以输入3种形式：1 EPGS编号；2 proj4 字符串；3 OGC WKT 字符串
        // 最后一个参数是一个 PJ_AREA ，用于指定 执行转换的区域 ，以便提供更精确的转换
        // NULL 表示不指定转换执行区域。
        // 可以通过 proj_area_create 来创建，然后使用 proj_area_set_bbox 来设置范围。
        if (strcmp(sour_EPSG , sour_EPSG_init) || strcmp(des_EPSG , des_EPSG_init))
        {
            *sour_EPSG_init = *sour_EPSG;
            *des_EPSG_init = *des_EPSG;
            std::cout << "The EPSG is update to: " << sour_EPSG_init << " and "<< des_EPSG_init << " !"<<std::endl; 
            P = proj_create_crs_to_crs(C,
                                    sour_EPSG_init,
                                    des_EPSG_init, /* or +proj=utm +zone=32 +datum=WGS84 */
                                    NULL);
        }
        

        if (0 == P)
        {
            fprintf(stderr, "Oops\n");
            return 1;
        }

        /* 如果您喜欢使用统一的轴顺序,不去管源坐标系和目标坐标系的顺序，
        ** 可以使用proj_normalize_for_visualization()，转换之后的PJ对象，
        ** 使用传统的GIS顺序接受输入坐标并返回输出坐标()。
        ** 
        ** 对于 PROJ 字符串定义坐标系，除非指定 +axis 参数对轴序进行修改
        ** 不然都是 先经度后纬度，先东后北 的坐标顺序
        ** 对于 EPSG 机构定义的地理坐标系，则是 先纬度后经度

        ** 统一之后，输入坐标的时候，坐标输入顺序为
        ** 1、地理坐标系，先经度后纬度
        ** 2、投影坐标系：先东（X）后北（Y）
        */
        P_for_GIS = proj_normalize_for_visualization(C, P);
        if (0 == P_for_GIS)
        {
            fprintf(stderr, "Oops\n");
            proj_destroy(P_for_GIS);
            return 1;
        }
        // std::cout << *P << std::endl;
        proj_destroy(P);
        P = P_for_GIS;
        // 下面是武汉的坐标: 东经114度北纬30度
        // 这里也可以这样 input.xy.x = 12; input.xy.y = 55;
        // 输入为经度、纬度、海拔、时间
        input = proj_coord(Long, Lat, 0, 0);

        // 转换到EPSG:4526 坐标系，PJ_FWD 是前向转换，就是从源坐标系向目标坐标系转换
        output = proj_trans(P, PJ_FWD, input);
        printf("东: %.3f, 北: %.3f\n", output.enu.e, output.enu.n);
        Easting = output.enu.e;
        Northing = output.enu.n;

        // 从 EPSG:4526 转换到 EPSG:4326，PJ_INV 是逆向转换
        // output = proj_trans(P, PJ_INV, output);
        // printf("经度: %g, 纬度: %g\n", output.lp.lam, output.lp.phi);
        // 可以使用 proj_trans_array 来一次转换批量坐标点
        // 如果转换出错，可以使用 en = proj_context_errno(C) 获取 errno
        // 然后使用 proj_errno_string(en) 获取错误消息

        // 清理使用对象

        // proj_destroy(P);

        return 0;
    }

    bool proj::GaustoLL(const char *sour_EPSG, const char *des_EPSG,
                              const double Easting, const double Northing, double &Long, double &Lat)
    {
        PJ *P, *P_for_GIS;
        PJ_COORD input, output;

        P = proj_create_crs_to_crs(C, sour_EPSG, des_EPSG, NULL);

        if (0 == P)
        {
            fprintf(stderr, "Oops\n");
            return 1;
        }

        P_for_GIS = proj_normalize_for_visualization(C, P);
        if (0 == P_for_GIS)
        {
            fprintf(stderr, "Oops\n");
            return 1;
        }
        proj_destroy(P);
        P = P_for_GIS;

        input = proj_coord(Easting, Northing, 0, 0);

        output = proj_trans(P, PJ_FWD, input);

        printf("经度: %.7f, 纬度: %.7f\n", output.lp.lam, output.lp.phi);

        // 清理使用对象
        // proj_destroy(P);

        return 0;
    }
}
