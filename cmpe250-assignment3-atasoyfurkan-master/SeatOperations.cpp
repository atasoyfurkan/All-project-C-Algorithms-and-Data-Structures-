/*
Student Name: Muhammed Furkan Atasoy
Student Number: 2017400216
Project Number: 3
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include "SeatOperations.h"

using namespace std;

SeatOperations::SeatOperations(int N, int M){
    lines[0].resize(N);
    lines[1].resize(M);
}

int SeatOperations::getSeatNumber(const Person& person) { // getting seat number according to real ticket info
    return (stoi(person.realTicketInfo.substr(1,person.realTicketInfo.size())) - 1) % lines[person.line].size();
}

void SeatOperations::addNewPerson(int personType, const string& ticketInfo){
    Person person;
    person.type = personType;
    person.realTicketInfo = ticketInfo;
    person.line = ticketInfo[0] == 'A'  ? 0 : 1; // convert from A and B to 0 and 1
    person.seatNumber = getSeatNumber(person);

    bool success = false;
    do {
        if(lines[person.line][person.seatNumber].type == 0) {
            lines[person.line][person.seatNumber] = std::move(person); // move person to empty seat
            success = true;
        }
        else {
            std::swap(person, lines[person.line][person.seatNumber]);
            if(person.type == 1) {
                person.line = (person.line + 1) % 2; // go to other line
                person.seatNumber = getSeatNumber(person);
            }
            if(person.type == 2) {
                if(person.seatNumber + 1 == lines[person.line].size()) { // if end of line
                    person.seatNumber = 0;
                    person.line = (person.line + 1) % 2;
                } else {
                    person.seatNumber++;
                }
            }
            if(person.type == 3) {
                person.seatNumber += 1 + person.type3LastOperation++ * 2; // find new seat of person
                while(person.seatNumber >= lines[person.line].size()) { // check for legal seat number
                    person.seatNumber -= lines[person.line].size(); // seat number for other line
                    person.line = (person.line + 1) % 2; // go to other line
                }
            }
        }
    } while(!success); // condition for sitting empty seat
}

void SeatOperations::printAllSeats(ofstream& outFile) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if(lines[i][j].type == 0)
                outFile << "0" << endl;
            else
                outFile << lines[i][j].type << " " << lines[i][j].realTicketInfo << endl;
        }
    }
}