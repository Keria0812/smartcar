#ifndef _PROJ4_H
#define _PROJ4_H

/*
 * @Date: 2021-11-29 19:41:30
 * @LastEditors: jinxiaoxin235
 * @LastEditTime: 2023-06-27 16:08:17
 * @FilePath: /miniEV/src/gps_bridge/include/gps_bridge/proj4.h
 * @Description: Do not edit
 */

// proj4 includes
#include <proj.h>
#include <stdio.h>
#include <string>
#include <iostream>

namespace Location
{
    class proj
    {
    public:
        proj();
        ~proj();

        // for setting data

        // for debug on ROS

        // output
        /**
         * @description: 
         * @param {*}
         * @return {*}
         */
        bool LLtoGaus(const char *sour_EPSG, const char *des_EPSG,
                      const double Long, const double Lat, double &Easting, double &Northing);
        bool GaustoLL(const char* sour_EPSG, const char* des_EPSG,
                      const double Easting, const double Northing, double &Long, double &Lat);


    private:
        // variables
        /* proj4 variables
        */
        PJ_CONTEXT *C;
        PJ *P;
        char* sour_EPSG_init ;
        char* des_EPSG_init ;
        // initializer
        void initForProj4();
    };
} // Location

#endif // PROJ4_7_2_1_H
