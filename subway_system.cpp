/******************************************************************************
  Title          : subway_system.cpp
  Author         : Yu Tong Chen
  Created on     : 4/27/2019
  Description    : The implementation of SubwaySystem class derived from _SubwaySystem class provided by Professor Weiss.
  Purpose        :
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

#include "subway_system.h"
#include "subway_station.h"

SubwaySystem::SubwaySystem():portal_(){

}

SubwaySystem::~SubwaySystem() {
}


int SubwaySystem::add_portal(SubwayPortal portal) {
    pair<SubwayStation, int> station_set(portal, -1);
    portal_.push_back(station_set);

    return 1;
}

void SubwaySystem::list_all_stations(ostream &out)  {
    int station_count = 0;
    for(auto &i: unique_stations) {
        out << i.portal_name() << endl;
        station_count++;
    }
    cout << "Total number of stations: " << station_count << endl;
}
void SubwaySystem::list_all_portals(ostream &out, string station_name)  {
    list<string> portals;

    for(unsigned int i = 0; i < portal_.size(); i++) {
        if(portal_[i].second < 0 && portal_[i].first.station_name() == station_name) {
            portals = portal_[i].first.names();
        }
    }
    for(auto &i:portals)
        cout << i << endl;
}
void SubwaySystem::list_stations_of_route(ostream &out, route_id route)  {
    SubwayPortal temp;
    for(unsigned int i = 0; i < unique_stations.size(); i++) {
        unique_stations[i].get_portal(temp);
        if(temp.get_routes().find(route) !=string::npos) {
            out << unique_stations[i].station_name() << endl;
        }
    }
}

int SubwaySystem::form_stations() {
    int sets_created = 0;
    for(unsigned int i = 0; i < portal_.size()-1; i++) {
        SubwayStation s1;
        SubwayStation s2;
        s1 = portal_[i].first;
        s2 = portal_[i+1].first;
        if(connected(s1,s2)) {
            unionize(i, i+1);
            sets_created++;
        }

    }

    // compress the parent tree, make all children point directly to parent
    for(unsigned int i = 0; i < portal_.size(); i++) {
        find(i);
    }

    for(unsigned int i = 0; i < portal_.size(); i++) {
        if(portal_[i].second <0) {      // root of parent tree, has children
            vector<int> indices;
            indices.push_back(i);
            SubwayPortal temp;
            portal_[i].first.get_portal(temp);

            if(portal_[i].second < -1) {
                int children = portal_[i].second+1;
                for(unsigned int j = i+1; j < portal_.size(); j++) {
                    portal_[i].first.add_child(j);      // add child
                    if(portal_[j].second == (signed) i) {
                        portal_[i].first.add_station_name(portal_[j].first.portal_name());  // add to parent subway station the children it encompasses
                        portal_[j].first.set_parent(i);     // sets child's parent id to root
                        ++children;
                    }
                    else if(children == 0)
                        break;
                }
            }

            unique_stations.push_back(portal_[i].first);

        }

    }

    cout << "Number of disjoint sets created: ";

    return sets_created;
}


bool SubwaySystem::get_portal(string name_to_find, SubwayPortal &portal)  {
    bool found = false;
    SubwayPortal temp;
    for(unsigned int i = 0; i < portal_.size(); i++) {
        portal_[i].first.get_portal(temp);
        if(temp.name() == name_to_find) {
            portal = temp;
            found = true;
        }
    }
    return found;

}
string SubwaySystem::nearest_portal(double latitude, double longitude)  {
    string portal_name;
    SubwayPortal temp;
    double lat;
    double lon;
    portal_[0].first.get_portal(temp);      // get first portal to set up initial distance
    lat = temp.get_portal_lat();
    lon = temp.get_portal_lon();
    double distance;
    double smallest_distance = haversine(lat, lon, latitude, longitude);
    portal_name = temp.name();

    for(unsigned int i = 0; i < portal_.size(); i++) {
        portal_[i].first.get_portal(temp);
        lat = temp.get_portal_lat();
        lon = temp.get_portal_lon();
        distance = haversine(lat, lon, latitude, longitude);
        if(distance < smallest_distance) {      // squeeze the distance until it is the smallest it can find
            smallest_distance = distance;
            portal_name = portal_[i].first.portal_name();
        }
        else if( distance == smallest_distance)
            portal_name = portal_[i].first.portal_name();
    }

    return portal_name;
}
string SubwaySystem::nearest_routes(double latitude, double longitude)  {
    string routes;
    SubwayPortal temp;
    double lat;
    double lon;
    portal_[0].first.get_portal(temp);      // get first portal to set up initial distance
    lat = temp.get_portal_lat();
    lon = temp.get_portal_lon();
    double distance;
    double smallest_distance = haversine(lat, lon, latitude, longitude);
    routes = temp.get_routes();

    for(unsigned int i = 0; i < portal_.size(); i++) {
        portal_[i].first.get_portal(temp);
        lat = temp.get_portal_lat();
        lon = temp.get_portal_lon();
        distance = haversine(lat, lon, latitude, longitude);
        if(distance < smallest_distance) {      // squeeze the distance until it is the smallest it can find
            SubwayPortal temp2;
            smallest_distance = distance;
            portal_[i].first.get_portal(temp2);
            routes = temp2.get_routes();
        }
        else if( distance == smallest_distance) {
            SubwayPortal temp3;
            portal_[i].first.get_portal(temp3);
            routes = temp3.get_routes();
        }
    }

    return routes;
}



/*******************************************************************************
Private helper functions
*******************************************************************************/
void SubwaySystem::unionize(int root1, int root2) {
    if ((unsigned)root1 >= portal_.size() || (unsigned)root2 >= portal_.size()) {
        return;
    }
    if (root1 != root2) {
        if(portal_[root2].second < portal_[root1].second) {
            // root2 is deeper
            if (portal_[root1].second > 0) {
                portal_[root2].second = root1;
            } else {
                portal_[root2].second += portal_[root1].second;
                portal_[root1].second = root2;
            }
        }
        else {
            // root1 is deeper
            if (portal_[root2].second > 0) {
                portal_[root1].second = root2;
            } else {
                portal_[root1].second += portal_[root2].second;
                portal_[root2].second = root1;
            }
        }
    }
}

int SubwaySystem::find(int value) {
    if ( portal_[value].second < 0 )
        return value;
    else
        return portal_[value].second = find (portal_[value].second);
}



