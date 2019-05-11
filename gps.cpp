/******************************************************************************
  Title          : gps.cpp
  Author         : Yu Tong Chen
  Created on     : 4/7/2019
  Description    : The implementation of GPS class that encapsulates GPS points. Interface provided by Professor Weiss.
  Purpose        :
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

#include "gps.h"

GPS::GPS(double lon, double lat) throw(BadPoint):longitude(lon), latitude(lat) {}

GPS::GPS(const GPS &location) {
    latitude = location.latitude;
    longitude = location.longitude;
}

GPS::~GPS() {}

void GPS::setGPS(double latitude, double longitude){
    this->latitude = latitude;
    this->longitude = longitude;
}
double GPS::getLatitude(){
    return latitude;
}
double GPS::getLongitude(){
    return longitude;
}

double distance_between( GPS point1, GPS point2) {
    const double R = 6372.8; //radius of earth in km
    const double TO_RAD = M_PI / 180.0;    //conversion of degrees to rads

    point1.latitude= TO_RAD * point1.latitude;
    point2.latitude = TO_RAD * point2.latitude;
    point1.longitude = TO_RAD * point1.longitude;
    point2.longitude = TO_RAD * point2.longitude;

    double dLat = (point2.latitude - point1.latitude)/2;
    double dLon = (point2.longitude - point1.longitude)/2;
    double a = sin(dLat);
    double b = sin(dLon);

    return 2 * R * asin(sqrt(a*a + cos(point1.latitude) * cos(point2.latitude) * b*b));
}
ostream & operator<< ( ostream & out, GPS point ) {
    out << "(" <<point.latitude << ", " << point.longitude << ")" << endl;
    return out;
}

GPS GPS::operator=(GPS const &) {
    return 0;
}