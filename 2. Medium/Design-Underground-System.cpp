/*
  https://leetcode.com/problems/design-underground-system/

  An underground railway system is keeping track of customer travel times
  between different stations. They are using this data to calculate
  the average time it takes to travel from one station to another.
/**/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <cassert>

using namespace std;

class UndergroundSystem {
public:
    using Id = int;

public:
    UndergroundSystem()
    {
    }

    void checkIn(Id id, string stationName, int t)
    {
        open_tickets_[id] = open_ticket(move(stationName), t);
    }

    void checkOut(Id id, string stationName, int t)
    {
        auto& ticket = open_tickets_[id];
        assert(ticket.is_valid);

        auto travel_time = t - ticket.time_of_departure;
        time_info_[Route{ticket.start_station, stationName}].add_time(travel_time);
        ticket.close();
    }

    double getAverageTime(string startStation, string endStation)
    {
        return time_info_[Route {startStation, endStation}].average_time();
    }

private:
    struct Ticket {
        Ticket(string start = "", int time = 0, bool valid = false)
            : start_station(move(start))
            , time_of_departure(time)
            , is_valid(valid)
        {
        }

        Ticket& operator=(Ticket&& other)
        {
            start_station = move(other.start_station);
            time_of_departure = other.time_of_departure;
            is_valid = other.is_valid;
            return *this;
        }

        void close()
        {
            time_of_departure = 0;
            start_station = "";
            is_valid = false;
        }

        string start_station = "";
        int time_of_departure = 0;
        bool is_valid = false;
    };

    Ticket open_ticket(string station, int time)
    {
        return Ticket {move(station), time, true};
    }

    struct Route {
        string start;
        string destination;

        bool operator==(const Route& other) const
        {
            return start == other.start && destination == other.destination;
        }
    };

    struct RouteHasher {
        size_t operator()(const Route& route) const
        {
            return hash<string>{}(route.start + route.destination);
        }
    };

    struct RouteInfo {
        int total_time = 0;
        int travel_count = 0;

        void add_time(int time) { 
            total_time += time; 
            ++travel_count; 
        }
        double average_time() const {
            assert(travel_count > 0);
            return static_cast<double>(total_time) / travel_count;
        }
    };

    unordered_map<Id, Ticket> open_tickets_;
    unordered_map<Route, RouteInfo, RouteHasher> time_info_;
};

//==============================================================================================//

int main()
{
    UndergroundSystem system;
    while (true) {
        // TODO ASK AND ANSWER
    }
    return 0;
}
