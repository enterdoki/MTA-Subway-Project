/*
File name: TEST
Name: Yu Tong Chen
Date: 5/6/2019
Assignment:  
Description:
*/

#include <iostream>
#include <fstream>
#include "subway_portal.h"
#include "subway_system.h"
#include "subway_station.h"

using namespace std;

int main() {
    string line;
    string file = "subwaydata_newstationnames.csv";

    ifstream input_stream(file);
    if(!input_stream) cerr << "Error opening file!";

    SubwaySystem sub_line;
    SubwayPortal portal;
    while(getline(input_stream, line)) {
        SubwayPortal bob(line);

        sub_line.add_portal(bob);

    }
    cout << sub_line.form_stations() << endl;
    cout << "************************" << endl;
    sub_line.list_all_stations(cout);
    cout << "************************" << endl;
    sub_line.list_all_portals(cout, "Broadway-7th Ave-Times Square");
    cout << "************************" << endl;
    sub_line.list_stations_of_route(cout, "FS");
    cout << "************************" << endl;
    cout << "--------------------" << endl;
    cout << sub_line.get_portal("4th Ave,25th St,SE,2",portal) << endl;
    cout << "************************" << endl;
    cout << sub_line.nearest_portal(40.91,-73.86) << endl;
    cout << "************************" << endl;
    cout << sub_line.nearest_routes(40.91,-73.86) << endl;
    cout << endl;


    return 0;
}