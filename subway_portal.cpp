/******************************************************************************
  Title          : subway_portal.cpp
  Author         : Yu Tong Chen
  Created on     : 4/27/2019
  Description    : The implementation of SubwayPortal class derived from _SubwayPortal class provided by Professor Weiss.
  Purpose        :
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

#include "subway_portal.h"

SubwayPortal::SubwayPortal() {}


SubwayPortal::SubwayPortal(string data_row) {
    stringstream csv_stream(data_row);
    vector<string> fields;
    string str;

    while(getline(csv_stream, str, ','))
    {
        fields.push_back(str);
    }

    division = fields[0];
    line = fields[1];
    station_name = fields[2];
    station_latitude = stod(fields[3]);
    station_longitude = stod(fields[4]);
    route1 = fields[5];
    route2 = fields[6];
    route3 = fields[7];
    route4 = fields[8];
    route5 = fields[9];
    route6 = fields[10];
    route7 = fields[11];
    route8 = fields[12];
    route9 = fields[13];
    route10 = fields[14];
    route11 = fields[15];
    entrance_type = fields[16];
    entry = fields[17];
    exit_only = fields[18];
    vending = fields[19];
    staffing = fields[20];
    staff_hours = fields[21];
    ada = fields[22];
    ada_notes = fields[23];
    free_crossover = fields[24];
    north_south_street = fields[25];
    east_west_street = fields[26];
    corner = fields[27];
    id = stoi(fields[28]);
    entrance_latitude = stod(fields[29]);
    entrance_longitude = stod(fields[30]);
    station_location.setGPS(station_latitude,station_longitude);
    entrance_location.setGPS(entrance_latitude,entrance_longitude);

    arr_lines.push_back(fields[5]);
    arr_lines.push_back(fields[6]);
    arr_lines.push_back(fields[7]);
    arr_lines.push_back(fields[8]);
    arr_lines.push_back(fields[9]);
    arr_lines.push_back(fields[10]);
    arr_lines.push_back(fields[11]);
    arr_lines.push_back(fields[12]);
    arr_lines.push_back(fields[13]);
    arr_lines.push_back(fields[14]);
    arr_lines.push_back(fields[15]);

    portal = routes();



}

double SubwayPortal::distance_from(double latitude, double longitude) {
    return haversine(entrance_latitude, entrance_longitude, latitude, longitude);

}

double distance_between( SubwayPortal portal1, SubwayPortal portal2){
    return haversine(portal1.get_portal_lat(), portal1.get_portal_lon(), portal2.get_portal_lat(), portal2.get_portal_lon());

}
bool same_routes( SubwayPortal portal1, SubwayPortal portal2) {
    return portal1.route1 == portal2.route1 && portal1.route2 == portal2.route2 && portal1.route3 == portal2.route3 &&
           portal1.route4 == portal2.route4 && portal1.route5 == portal2.route5 && portal1.route6 == portal2.route6 &&
           portal1.route7 == portal2.route7 && portal1.route8 == portal2.route8 && portal1.route9 == portal2.route9 &&
           portal1.route10 == portal2.route10 && portal1.route11 == portal2.route11;
}

bool same_station( SubwayPortal portal1, SubwayPortal portal2) {
    return portal1.station_name == portal2.station_name;
}
ostream & operator<< ( ostream & out, SubwayPortal e){
    return out << e.division + ',' + e.line + ',' + e.station_name + ',' + to_string(e.station_latitude) + ',' + to_string(e.station_longitude) +
                  e.route1 + ',' + e.route2 + ',' + e.route3 + ',' + e.route4 + ',' + e.route5 + ',' + e.route6 + ',' + e.route7 + ',' + e.route8 +
                  ',' + e.route9 + ',' + e.route10 + ',' + e.route11 + ',' + e.entrance_type + ',' + e.entry + ',' + e.exit_only + ',' + e.vending +
                  ',' + e.staffing + ',' + e.staff_hours + ',' + e.ada + ',' + e.ada_notes + ',' + e.free_crossover + ',' + e.north_south_street +
                  ',' + e.east_west_street + ',' + e.corner + ',' + to_string(e.id) + ',' + to_string(e.entrance_latitude) + ',' + to_string(e.entrance_longitude) +
                  ',' + '(' + to_string(e.station_latitude) + ", " + to_string(e.station_longitude) + ')' + ',' +  '(' + to_string(e.entrance_latitude) + ", " +
                  to_string(e.entrance_longitude) + ')';
}


string SubwayPortal::name() const {
    string portal_name;
    portal_name += north_south_street + ',' + east_west_street + ',' + corner + ',' + to_string(id);
    return portal_name;
}



bool SubwayPortal::can_access(route_set route) const {
    return portal == route;
}

GPS SubwayPortal::p_location() const {
    return entrance_location;
}

GPS SubwayPortal::s_location() const {
    return station_location;
}

string SubwayPortal::get_station_name() const{
    return station_name;
}

double SubwayPortal::get_station_lat() const{
    return station_latitude;
}

double SubwayPortal::get_station_lon() const{
    return station_longitude;
}
double SubwayPortal::get_portal_lat() const{
    return entrance_latitude;
}
double SubwayPortal::get_portal_lon() const{
    return entrance_longitude;
}

string SubwayPortal::get_routes() const {
    string routes;
    for(auto &i:arr_lines)
        routes += i + ' ';
    return routes;
}

route_set SubwayPortal::routes() const {
    route_set bit_mask = 0;

    for(unsigned int i = 0; i < arr_lines.size();i++){
        int k = line_hash(arr_lines[i]);
        unsigned long mask_k = 1UL << k;
        bit_mask = bit_mask | mask_k;
    }

    return bit_mask;
}

int SubwayPortal::line_hash(string x) const{
    int hash_val = 0;

    for(unsigned int i = 0;i < x.length();i++){
        hash_val = x[i] + 33*hash_val;
    }
    return hash_val%51;
}

