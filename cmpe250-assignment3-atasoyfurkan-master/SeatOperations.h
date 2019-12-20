#ifndef CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#define CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Person{
    int type=0;
    int line=0, seatNumber=0;
    int type3LastOperation=0;
    string realTicketInfo = "";
};

class SeatOperations{

private:
    vector<Person> lines[2];
    int getSeatNumber(const Person& person);

public:
    SeatOperations(int N, int M);
    void addNewPerson(int personType, const string& ticketInfo);
    void printAllSeats(ofstream& outFile);

};

#endif //CMPE250_ASSIGNMENT3_SEATOPERATIONS_H
