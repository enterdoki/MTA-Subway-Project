/******************************************************************************
  Title          : subway_station.cpp
  Author         : Yu Tong Chen
  Created on     : 4/27/2019
  Description    : The implementation of SubwayStation class derived from _SubwayStation class provided by Professor Weiss.
  Purpose        :
  Usage          :
  Build with     :
  Modifications  :

******************************************************************************/

#include "subway_station.h"

SubwayStation::SubwayStation():m_parent_id(-1) {

}

SubwayStation::SubwayStation(SubwayPortal portal):m_parent_id(-1) {
    this->portal = portal;
    portal_unique_name = portal.name();
    m_station_names.insert(portal.name());
    portal_ids.push_back(portal.id);
    s_name = portal.get_station_name();
}


void SubwayStation::set_parent(int newparent) {
    m_parent_id = newparent;
}

void SubwayStation::add_child(int child) {
    children.push_back(child);
}

bool connected(SubwayStation s1, SubwayStation s2){
    bool a = (s1.portal.routes() ^ s2.portal.routes()) == 0;    //checks if bitmasks equal using XOR
    double distance = distance_between(s1.portal, s2.portal);
    double distance_limit = 0.28;
    bool b = (distance <= distance_limit);
    bool c = s1.parent_id() == s2.parent_id();

    return a and b and c;

}

int SubwayStation::add_station_name(string newname) {
    bool is_in = m_station_names.find(newname) != m_station_names.end();
    if(!is_in) {
        m_station_names.insert(newname);
        return 1;
    }
    return 0;
}

list<string> SubwayStation::names() const {
    list<string> stations_names;
    for(auto &i:m_station_names)
        stations_names.push_back(i);

    return stations_names;
}

string SubwayStation::primary_name() const {
    string primary_name;
    primary_name = *m_station_names.begin();
    return primary_name;
}

int SubwayStation::parent_id() const {
    return m_parent_id;
}

list<int> SubwayStation::portal_list() const {
    return portal_ids;
}

string SubwayStation::portal_name() const {
    return portal_unique_name;
}

void SubwayStation::get_portal(SubwayPortal &x) const {
    x = portal;
}

string SubwayStation::station_name() const {
    return s_name;
}

list<int> SubwayStation::children_list() const {
    return children;
}

