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
        Table<Trip> * tripTable;
        void fetchAllVehicles() throw (IOError, MemoryError);
        void fetchAllUsers() throw (IOError, MemoryError);
        void fetchAllTrips() throw (IOError, MemoryError);
        void cleanUp();
    public:
        Database () throw (MemoryError, IOError);
        ~Database();
        const Table<Vehicle> * const getVehicleRef() const;
        const Table<User> * const getUserRef() const;
        const Table<Trip> * const getTripRef() const;
        const Vehicle * const getVehicle(string registrationNo) const throw (NoSuchRecordError) ;
        const User * const getUser (string contactNo) const throw (NoSuchRecordError);
        const vector<const Vehicle *> getVehicle(Date startDate, Date endDate, VehicleType type) const;
        template <class T> void addNewRecord (T * record) throw (IOError, MemoryError);
        template <class T> void updateRecord (T * record) throw (IOError, NoSuchRecordError);
};
#endif