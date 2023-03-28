#ifndef database_h
#define databse_h
#include "vehicle.h"
#include "user.h"
#include "trip.h"
#include "table.cpp"
#include "error.cpp"
using namespace std;
class Database{
    private:
        Table<Vehicle> * vehicleTable;
        Table<User> * userTable;
        
};
#endif