#include "application.h"
#include "database_templates.cpp"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <limits>
Application :: Application(){
    try{
        this->db = new Database();
    }catch(Error e){
        cout<<e.getMessage();
        exit(EXIT_FAILURE);
    };
}
void Application :: gotoXY(int x, int y) const {
    printf("%c[%d;%df", 0x1B, y, x);
}
void Application :: renderMenu() {
    unsigned char choice = 1;
    while(true){
        system("clear");
        gotoXY(25, 4);
        cout<<"Select Any option from below";
        gotoXY(25,5);
        cout<<"1. Add new vehicle";
        gotoXY(25,6);
        cout<<"2. View vehicle details";
        gotoXY(25,7);
        cout<<"3. Edit vehicle details";
        gotoXY(25,8);
        cout<<"4. Add new user";
        gotoXY(25,9);
        cout<<"5. Add new trip";
        gotoXY(25,10);
        cout<<"6. View Trip";
        gotoXY(25,11);
        cout<<"7. Start trip";
        gotoXY(25,12);
        cout<<"8. Complete trip";
        gotoXY(25,13);
        cout<<"9. Exit";

        gotoXY(30,15);
        printf("Enter your choice: ");

        gotoXY(50, 15);
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case '1':
                this->renderAddNewVehicleMenu();
                break;
            case '2':
                this->renderViewTripMenu();
                break;
            case '3':
                this->renderEditVehicleMenu();
                break;
            case '4':
                this->renderAddNewUserMenu();
                break;
            case '5':
                this->renderViewTripMenu();
                break;
            case '6':
                this->renderAddNewTripMenu();
                break;
            case '7':
                this->renderStartTripMenu();
                break;
            case '8':
                this->renderCompleteTripMenu();
                break;
            case '9':
                this->cleanMemory();
                system("clear");
                exit(EXIT_SUCCESS);
                break;
        }
    }
}
void Application :: renderAddNewVehicleMenu() const{
    string header = "Enter details of vehicle (All fields are required) ";
    string registrationNoLabel = "Enter vehicle registration number: ";
    string vehiclaTypeLabel = "Enter vehicle type: ";
    string vehicleOptionLabel = "(1. Bike, 2. Car, 3. Towera)";
    string seatLabel = "Enter no. of seats: ";
    string companyNameLabel = "Enter name of company: ";
    string priceLabel = "Enter price per km: ";
    string pucExpirationDateLabel = "Enter PUC expiration date(d/m/yyyy): ";

    string registrationNo;
    int vehicleType;
    int seat;
    string companyName;
    double price;
    string pucExpirationDate;
    system("clear");
    gotoXY(0,1);
    cout<<header;
    gotoXY(0,3);
    cout<<registrationNoLabel;
    gotoXY(0,4);
    cout<<vehiclaTypeLabel;
    gotoXY(0,5);
    cout<<vehicleOptionLabel;
    gotoXY(0,6);
    cout<<seatLabel;
    gotoXY(0,7);
    cout<<companyNameLabel;
    gotoXY(0,8);
    cout<<priceLabel;
    gotoXY(0,9);
    cout<<pucExpirationDateLabel;
    gotoXY(int(registrationNoLabel.length()), 3);
    getline(cin, registrationNo);
    gotoXY(int(vehiclaTypeLabel.length()), 4);
    cin>>vehicleType;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    gotoXY(int(pucExpirationDateLabel.length()),9);
    getline(cin,pucExpirationDate);
    Vehicle * vehicle;
    try{
        vehicle = new Vehicle(registrationNo,VehicleType(vehicleType),seat,companyName,price,Date(pucExpirationDate));
        this->db->addNewRecord(vehicle);
        stringstream ss;
        ss<<"Vehicle Id:" <<vehicle->getRecordId();
        showDialog("Vehicle added successfully",ss.str());
    }
    catch(Error e){
        showDialog(e.getMessage());
    }
    delete vehicle;
}
void Application::renderViewVehicleMenu()const{
    string header="Enter registration no. of vehicle:";
    string registrationNo;
    system("clear");
    gotoXY(0,1);
    cout<<header;
    gotoXY(int(header.length()),1);
    getline(cin,registrationNo);
    gotoXY(0,3);
    try{
        auto vehicle=this->db->getVehicle(registrationNo);
        vehicle->display();
        cout<<endl<<"Press any key to continue";
        cin.get();
    }
    catch(Error e){
        this->showDialog(e.getMessage());
    }
}
void Application::renderEditVehicleMenu()const{
    string header="Enter registration no of vehicle you want to edit:";
    string priceLabel="Enter new price per km:";
    string registrationNo;
    system("clear");
    gotoXY(0,1);
    cout<<header;
    gotoXY(int(header.length()),1);
    getline(cin, registrationNo);
    gotoXY(0,3);
    Vehicle * modifiedVehicle;
    try{
        auto vehicle=this->db->getVehicle(registrationNo);
        modifiedVehicle = new Vehicle(*vehicle);
        vehicle->display();
        string newPrice;
        gotoXY(0,12);
        cout<<priceLabel;
        gotoXY(int(priceLabel.length()),12);
        getline(cin,newPrice);
        if(newPrice!=""){
            modifiedVehicle->setPricePerKm(stod(newPrice));
            this->db->updateRecord(modifiedVehicle);
            this->showDialog("vehicle data updated successfully");
        }
    }
    catch(Error e){
        this->showDialog(e.getMessage());
    }
    delete modifiedVehicle;
}
void Application::renderAddNewUserMenu()const{
    string header = "Enter details of user";
    string userNameLabel = "Enter name of user:";
    string usercontactLabel="Enter contact no of user:";
    string userEmailLabel="Enter email of user(optional)";
    string name;
    string contact;
    string email;
    system("clear");
    gotoXY(0,1);
    cout<<header;
    gotoXY(0,3);
    cout<<userNameLabel;
    gotoXY(0,4);
    cout<<usercontactLabel;
    gotoXY(0,5);
    cout<<userEmailLabel;
    gotoXY(int(userNameLabel.length()),3);
    getline(cin,name);
    gotoXY(int(usercontactLabel.length()),4);
    getline(cin,contact);
    gotoXY(int(userEmailLabel.length()),5);
    getline(cin,email);
    User * user;
    try{
        user = new User(name,contact,email);
        this->db->addNewRecord(user);
        stringstream ss;
        ss<<"User Id :"<<user->getRecordId();
        showDialog("user added successfully",ss.str());
        }
        catch(Error e){
            showDialog(e.getMessage());
        }
        delete user;
}
void Application::renderAddNewTripMenu() const{
    string header = "Enter details of trip(All fields are required)";
    string startDateLabel = "Enter start date of trip{d/m/yyyy)";
    string endDateLabel = "Enter end date of trip (d/m/yyyy)";
    string vehicleTypeLabel = "Enter vehicle type:";
    string vehicleOptionLabel="(1.Bike, 2.Car, 3.Towera)";
    string registrationNoLabel = "Enter registration no of vehicle:";
    string contactNo;
    string startDate;
    string endDate;
    int vehicleType;
    string registrationNo;
    const User*user;
    const Vehicle * vehicle;
    system("clear");
    gotoXY(0,1);
    cout<<startDateLabel;
    gotoXY(int(startDateLabel.length()),1);
    getline(cin, contactNo);
    try{
        user = this->db->getUser(contactNo);
        gotoXY(0,3);
        cout<<"User found:"<<user->getName();
    }
    catch(Error e){
        this->showDialog(e.getMessage());
    }
    gotoXY(0,5);
    cout<<header;
    gotoXY(0,7);
    cout<<startDateLabel;
    gotoXY(0,8);
    cout<<endDateLabel;
    gotoXY(0,9);
    cout<<vehicleTypeLabel;
    gotoXY(0,10);
    cout<<vehicleOptionLabel;
    gotoXY(int(startDateLabel.length()),7);
    getline(cin,startDate);
    gotoXY(int(endDateLabel.length()),8);
    getline(cin,endDate);
    gotoXY(int(vehicleTypeLabel.length()),9);
    cin>>vehicleType;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    auto freeVehicles = this->db->getVehicle(Date(startDate),Date(endDate),VehicleType(vehicleType));
    if(freeVehicles.size()==0){
        this->showDialog("No vehicles are free in given date range");
        return;
    }
    gotoXY(0,12);
    cout<<"|Registration no|"<<"seats|"<<"Price per km|"<<endl;
    for(auto & vehicle:freeVehicles){
        string registrationNo=vehicle->getRegistrationNumber();
        string seats=to_string(vehicle->getSeats());
        stringstream ss;
        ss<<std::fixed;
        ss<<std::setprecision(2);
        ss<<vehicle->getPricePerKm();
        string price=ss.str()+"Rs/Km";
        cout<<"|"<<registrationNo<<string(7,' ')<<"|"<<seats<<string(7-seats.length(),' ')<<"|"<<price<<string(14-price.length(),' ')<<"|"<<endl;
    }
    int offset=int(freeVehicles.size())+2;
    gotoXY(0,12+offset);
    cout<<registrationNoLabel;
    gotoXY(int(registrationNoLabel.length()),12+offset);
    getline(cin,registrationNo);
    try{
        vehicle = this->db->getVehicle(registrationNo);
    }
    catch(Error e){
        this->showDialog(e.getMessage());
        return;
    }
    long userId=user->getRecordId();
    long vehicleId = vehicle->getRecordId();
    Trip*trip;
    try{
        trip = new Trip(this->db->getVehicleRef()->getRecordForId(vehicleId),this->db->getUserRef()->getRecordForId(userId),Date(startDate),Date(endDate));
        this->db->addNewRecord(trip);
        stringstream ss;
        ss<<"Trip id:"<<trip->getRecordId();
        showDialog("Trip added successfully",ss.str());
    }
    catch(Error e){
        showDialog(e.getMessage());
    }
    delete trip;
}
void Application :: renderViewTripMenu()const{
    string header="Enter trip id:";
    long tripId;
    system("clear");
    gotoXY(int(header.length()),1);
    cin>>tripId;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    gotoXY(0,3);
    try{
        auto trip=this->db->getTripRef()->getRecordForId(tripId);
        trip->display();
        cout<<endl<<"press any key to continue";
        cin.get();
    }
    catch(Error e){
        this->showDialog(e.getMessage());
    }
}
void Application :: renderStartTripMenu()const{
    string header="Enter trip id:";
    string readingLabel = "Enter odometer reading: ";
    long tripId;
    long startReading;
    system("clear");
    gotoXY(0,1);
    cout << header;
    gotoXY(0,2);
    cout << readingLabel;

    gotoXY(int(header.length()), 1);
    cin >> tripId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    gotoXY(int(readingLabel.length()), 2);
    cin >> startReading;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Trip * modifiedTrip;

    try{
        auto trip = this->db->getTripRef()->getRecordForId(tripId);
        modifiedTrip = new Trip(*trip);
        modifiedTrip->startTrip(startReading);
        this->db->updateRecord(modifiedTrip);
        showDialog("Trip started successfully!");
    }
    catch(Error e){
        this->showDialog(e.getMessage());
    }
    delete modifiedTrip;
}
void Application::renderCompleteTripMenu()const{
    string header ="Enter trip id:";
    string readingLabel = "Enter odometer reading:";
    long tripId;
    long endReading;
    system("clear");
    gotoXY(0,1);
    cout<<header;
    gotoXY(0,2);
    cout<<readingLabel;
    gotoXY(int(header.length()),1);
    cin>>tripId;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    gotoXY(int(readingLabel.length()), 2);
    cout << endReading;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    try{
        auto trip = this->db->getTripRef()->getRecordForId(tripId);
        Trip * modifiedTrip = new Trip(*trip);
        auto fare = modifiedTrip->completeTrip(endReading);
        this->db->updateRecord(modifiedTrip);
        stringstream ss;
        ss<<"Total fare:"<<fare;
        showDialog("Trip completed successfully");
    }
    catch(Error e){
        this->showDialog(e.getMessage());
    }
}
void Application::showDialog(string message, string id)const{
    auto messageLength=int(message.length());
    string pressAnyKey="Press any key to continue";
    int infoLength=int(pressAnyKey.length());
    int leftOffset=15;
    int length=50;
    int lineOffset=9;
    system("clear");
    gotoXY(leftOffset,lineOffset++);
    cout<<"****************************************";
    gotoXY(leftOffset,lineOffset);
    cout<<"*";
    gotoXY(leftOffset+length-1,lineOffset++);
    cout<<"*";
    gotoXY(leftOffset,lineOffset);
    cout<<"*";
    gotoXY((80-messageLength)/2,lineOffset);
    cout<<message;
    gotoXY(leftOffset+length-1,lineOffset++);
    cout<<"*";
    if(id!=""){
        gotoXY(leftOffset,lineOffset);
        cout<<"*";
        gotoXY((int)((80-int(id.length()))/2),lineOffset);
        cout<<id;
        gotoXY(leftOffset+length-1,lineOffset++);
        cout<<"*";
    }
    gotoXY(leftOffset,lineOffset);
    cout<<"*";
    gotoXY((int)((80-infoLength)/2),lineOffset);
    cout<<pressAnyKey;
    gotoXY(leftOffset+length-1,lineOffset++);
    cout<<"*";
    gotoXY(leftOffset,lineOffset++);
    cout<<"******************************************";
    cin.get();
    }
    void Application::welcome(){
        system("clear");
        gotoXY(25,5);
        cout<<"Welcome to vehicle renting system"<<endl;
        gotoXY(27,23);
        cout<<"Press any key to continue";
        cin.get();
        this->renderMenu();
    }
    void Application::start(){
        welcome();
    }
    void Application::cleanMemory(){
        delete db;
    }