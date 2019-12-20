/*
Student Name: Furkan Atasoy
Student Number: 2017400216
Project Number: 1
Compile Status: [SUCCESS]
Running Status: [SUCCESS]
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/


#include "Restaurant.h"

using namespace std;

void Restaurant::execute(const vector<string>& operations) {
    for (const string& op : operations){
        cout << "Operation: " << op << "\t";

        if(op == "N") {
            bool flag = false;
            for(int i = 0; !flag; i++) {
                if(!this->tables[i].isOccupied()) {
                    this->tables[i].occupy();
                    flag = true;
                }
            }
        } else if (op == "S") {
            bool flag = false;
            for(int i = this->tables.size() - 1; !flag; i--) {
                if(!this->tables[i].isOccupied()) {
                    this->tables[i].occupy();
                    flag = true;
                }
            }
        } else {
            this->tables[stoi(op) - 1].empty();
        }

        cout << "State: " << *this << endl;
    }

}


Restaurant::Restaurant(unsigned int N)
	: tables{N}
{
    cout << "-Starting- \tState: " << *this << endl;
}

ostream &operator<<(ostream &out, Restaurant &restaurant) {
    for (Table table : restaurant.tables) {
        out << table.isOccupied();
    }
	return out;
}

