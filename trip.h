#ifndef trip_h
#define trip_h
#include "date.h"
#include "storable.cpp"
#include "user.h"
#include "vehicle.h"
#include <string>
using namespace std;
class Trip : public Storable{
    private:
        const Vehicle * vehicle;
        const User * user;
        Date startDate;
        Date endDate;
        long startReading;
        long endReading;
        double fare;
        bool completed;
    public:
        Trip(const Vehicle * vehicle, const User * user, Date startDate, Date endDate, long recordId = 0, long startReading = 0, long endReading = 0, double fare = 0.0, bool isCOmpleted = false);
        const User & getUser() const;
        const Vehicle & getVehicle() const;
        Date getStartDate() const;
        Date getEndDate() const;
        long getStartReading() const;
        long getEndReading() const;
        long getFare() const;
        bool isCompleted() const;
        void startTrip(long startReading);
        double completeTrip(long endReading);
        void display() const;
        string toString() const;
        void setDataFrom (Storable * s);
};
#endif