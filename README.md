# CS335-Project2-Part2
by Yu Tong Chen


## How to run

Download all the files, make in terminal, edit main.cpp function parameters 
to see different outputs. Command parsing not set up yet. 

Can edit most of these (those with string parameters):


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


Type "make" in the command line. It should output to a compiled "project2" file.
then
./project subwaydata_newstationnames.csv <some command file>

### Aril 25, 2019
Started the subway project, mainly just getting the header files finished and cleaned up.

### April 29, 2019
Continued the project by implementing subway_portal.cpp. Was able to successfully parse the file and grab all the fields as well as bitmask the routes.
Almost done with all the functions, one left.

### May 1, 2019
Finishing up Subway_portal and Subway_route. Not quite sure how to do bit string encoding but I just decided to temporary hash the string of all routes at the portal and do a bit mask from there. A bit fustrated that I could not
figure out a way to represent all the routes at a portal with 1 representing it services that route and 0 representing it doesn't using a 64 bit string.

### May 2, 2019
Working on Subway_station. Decent progress.

### May 5, 2019 - May 8, 2019
Continuing to work on Subway_station and Subway_system. Slow progress due to trouble understanding the interaction between subway station and subway system class. Ended up using a vector of pairs (SubwayStation, parent tree)
to represent both the set of stations and parent tree. Unionized and compressed (find function) all the stations. Had a total of 1374 disjoint sets created, not sure if that's right but the number looks somewhat believable
due to the large data provided. List all stations is working but that function is simple simply because we're just listing every single subway station. Started to make hash tables for SubwayStation.

### May 9, 2019 - May 10,2019
Omitted fully using a hash table as I into output discrepancies. I know, I know, it's very inefficient but that was the only way to
have my program execute all the functions(list all, get near functions). 465 unique stations found and 1374 disjoint sets created. Everything's completed. DONE!
