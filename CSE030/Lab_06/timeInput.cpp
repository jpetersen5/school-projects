#include <iostream>
#include <iomanip>
using namespace std;


struct Time {
        int hr = 0;
        int min = 0;
        int sec = 0;
};


bool getTimeFromUser(Time &usrTime) {
        string fullTime;

        // get input
        getline(cin,fullTime);

        // check for HH:MM:SS structure validity
        if (fullTime.find(":",0) == -1 || fullTime.find(":",fullTime.find(":",0) + 1) == -1) {
                return false;
        }

        // if structure is followed, assign variables for hr min sec
        usrTime.hr = atoi(fullTime.c_str());
        usrTime.min = atoi(fullTime.c_str() + fullTime.find(":",0) + 1);
        usrTime.sec = atoi(fullTime.c_str() + fullTime.find(":",fullTime.find(":",0) + 1) + 1);

        // check for values within valid ranges
        if (((usrTime.hr < 0 || usrTime.hr > 23) || (usrTime.min < 0 || usrTime.min > 59)) || (usrTime.sec < 0 || usrTime.sec > 59)) {
                return false;
        }

        return true;
}


void print24Hour(Time usrTime) {
        cout << setfill('0') << setw(2) << usrTime.hr;
        cout << ":";
        cout << setfill('0') << setw(2) << usrTime.min;
        cout << ":";
        cout << setfill('0') << setw(2) << usrTime.sec;
        return;
}


int main() {
        // get start time
        cout << "Enter the start time for the lecture (format is HH:MM:SS): ";
        Time startTime;
        if (!getTimeFromUser(startTime)) {
                cout << "The start time entered is invalid!" << endl;
                return 0;
        }

        // get end time
        cout << "Enter the end time for the lecture (format is HH:MM:SS): ";
        Time endTime;
        if (!getTimeFromUser(endTime)) {
                cout << "The end time entered is invalid!" << endl;
                return 0;
        }

        // output
        cout << "The lecture starts at ";
        print24Hour(startTime);
        cout << " and ends at ";
        print24Hour(endTime);
        cout << endl;

        return 0;
}