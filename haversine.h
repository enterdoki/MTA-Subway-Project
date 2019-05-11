//
// Created by Tommy Chen on 2019-05-07.
//

#ifndef HAVERSINE_H
#define HAVERSINE_H

#include <cmath>

#define R 6372.8
#define TO_RAD (3.1415926536 / 180)

double haversine(double lat1, double lon1, double lat2, double lon2);


#endif //HAVERSINE_H
