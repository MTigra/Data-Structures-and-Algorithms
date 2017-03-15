//////////////////////////////////////////////////////////////
/////// @author Nikita Marinosyan
/////// @date 14.03.2017
/////// Higher School of Economics, Faculty of Computer Science
//////////////////////////////////////////////////////////////

#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include "RailSystem.h"

void RailSystem::reset(void)
{
    // Reset the data objects of the
    // City objects' contained in cities
    for (map<string, City*>::iterator it = cities.begin(); it != cities.end() ; ++it)
    {
        it->second->total_distance = INT_MAX;
        it->second->total_fee = INT_MAX;
        it->second->visited = false;
        it->second->from_city = "";
    }
}

RailSystem::RailSystem(string const& filename)
{
    load_services(filename);
}

void RailSystem::load_services(string const& filename)
{
    ifstream inf(filename.c_str());
    string from, to;
    int fee, distance;

    while (inf.good())
    {
        // Read in the from city, to city, the fee, and distance.
        inf >> from >> to >> fee >> distance;

        if (inf.good())
        {
            // Add entries in the cities container and
            // and services in the rail system for the new
            // cities we read in
            cities[from] = new City(from);
            outgoing_services[from].push_back(new Service(to, fee, distance));
        }
    }

    inf.close();
}

RailSystem::~RailSystem(void)
{
    // Release all City* from cities
    for (map<string, City*>::iterator it = cities.begin(); it != cities.end(); ++it)
        delete it->second;

    // Release all Service* from outgoing_services
    for (map<string, list<Service*>>::iterator it = outgoing_services.begin(); it != outgoing_services.end() ; ++it)
        for (list<Service*>::iterator service = it->second.begin(); service != it->second.end(); ++service)
            delete *service;
}

void RailSystem::output_cheapest_route(const string& from, const string& to, ostream& out)
{
    reset();
    pair<int, int> totals = calc_route(from, to);

    if (totals.first == INT_MAX)
        out << "There is no route from " << from << " to " << to << "\n";
    else
    {
        out << "The cheapest route from " << from << " to " << to << "\n";
        out << "costs " << totals.first << " euros and spans " << totals.second
            << " kilometers\n";
        cout << recover_route(to) << "\n\n";
    }
}

bool RailSystem::is_valid_city(const string& name)
{
    return cities.count(name) == 1;
}

pair<int, int> RailSystem::calc_route(string from, string to)
{
    // You can use another container
    priority_queue<City*, vector<City*>, Cheapest> candidates;

    // Dijkstra's shortest path algorithm to
    // find the cheapest route between the cities

    // Set fee and distance to the
    // city we start out trip from
    cities[from]->total_fee = 0;
    cities[from]->total_distance = 0;
    candidates.push(cities[from]);

    while (!candidates.empty())
    {
        // Extract minimum cost vertex
        // from the priority queue
        City* current_city = candidates.top();
        candidates.pop();

        // Loop through all adjacent of current city
        for (list<Service*>::iterator adjacent = outgoing_services[current_city->name].begin();
             adjacent != outgoing_services[current_city->name].end() ; ++adjacent)
        {
            // If there is a cheaper path to adjacent
            // city through the current city
            if (((*adjacent)->fee + current_city->total_fee) < cities[(*adjacent)->destination]->total_fee)
            {
                // Update cost and distance to adjacent city
                cities[(*adjacent)->destination]->total_fee = (*adjacent)->fee + current_city->total_fee;
                cities[(*adjacent)->destination]->total_distance = (*adjacent)->distance + current_city->total_distance;

                // Update the city we got to the current city from
                cities[(*adjacent)->destination]->from_city = current_city->name;

                // Place the city into the candidates priority queue
                candidates.push(cities[(*adjacent)->destination]);
            }
        }

        // Mark city as visited
        current_city->visited = true;
    }

    // Return the total fee and total distance.
    // Return (INT_MAX, INT_MAX) if not path is found.
    if (cities[to]->visited)
        return pair<int, int>(cities[to]->total_fee, cities[to]->total_distance);
    else
        return pair<int, int>(INT_MAX, INT_MAX);

}

string RailSystem::recover_route(const string& city)
{
    if (cities[city]->from_city == "")
        return city;

    // Create iteration city pointer
    City* current_city = cities[cities[city]->from_city];

    // Add destination city
    string route = " to " + city;

    // Walk backwards through the cities
    // container to recover the route we found
    while (current_city->from_city != "")
    {
        route.insert(0, " to " + current_city->name);
        current_city = cities[current_city->from_city];
    }

    // Add the starting city
    route.insert(0, current_city->name);

    return route;
}

Route RailSystem::getCheapestRoute(const string& from, const string& to)
{
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p = calc_route(from, to);
    return Route(from, to, p.first, p.second);
}