#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;


struct Time {
        int hr = 0;
        int min = 0;
        int sec = 0;
};


struct Course {
        string name;
        int credits;
        bool majorRequirement;
        double avgGrade;
        string days;
        Time startTime;
        Time endTime;
};


// modified from timeInput.cpp
void getTime(Time &usrTime, string fullTime) {
        // assign time values
        usrTime.hr = atoi(fullTime.c_str());
        usrTime.min = atoi(fullTime.c_str() + fullTime.find(":",0) + 1);
        usrTime.sec = atoi(fullTime.c_str() + fullTime.find(":",fullTime.find(":",0) + 1) + 1);

        return;
}


// modified from timeInput.cpp
void print12Hour(Time usrTime) {
        // convert 24hr time to 12hr time
        int clockHour;
        bool pm;
        if (usrTime.hr == 0) { // 12am
                clockHour = 12;
                pm = 0;
        } else if (usrTime.hr == 12) { // 12pm
                clockHour = 12;
                pm = 1;
        } else { // all other times
                clockHour = usrTime.hr % 12;
                pm = clockHour < usrTime.hr;
        }

        // print in 12hr format
        cout << clockHour;
        cout << ":";
        cout << setfill('0') << setw(2) << usrTime.min;
        cout << ":";
        cout << setfill('0') << setw(2) << usrTime.sec;
        if (pm) {
                cout << "pm";
        } else {
                cout << "am";
        }

        return;
}


int main() {
        // open file
        ifstream coursefile("in.txt");

        // start course output
        cout << "-------------------" << endl;
        cout << "SCHEDULE OF STUDENT" << endl;
        cout << "-------------------" << endl;

        // get first line for number of courses
        string coursesstr;
        getline(coursefile,coursesstr);
        int courses = atoi(coursesstr.c_str());

        // initialize courses
        Course *courseList = new Course[courses];

        // loop to create courses
        for (int i = 0; i < courses; i++) {
                // get course name
                getline(coursefile,courseList[i].name);
                // get course credits
                string credits;
                getline(coursefile,credits);
                courseList[i].credits = atoi(credits.c_str());
                // get major requirement
                string majorRequirement;
                getline(coursefile,majorRequirement);
                courseList[i].majorRequirement = atoi(majorRequirement.c_str());
                // get average grade
                string avgGrade;
                getline(coursefile,avgGrade);
                courseList[i].avgGrade = atof(avgGrade.c_str());
                // get lecture days
                getline(coursefile,courseList[i].days);
                // get start time
                string startTimestr;
                getline(coursefile,startTimestr);
                getTime(courseList[i].startTime,startTimestr);
                // get end time
                string endTimestr;
                getline(coursefile,endTimestr);
                getTime(courseList[i].endTime,endTimestr);
        }

        // loop to print courses
        for (int i = 0; i < courses; i++) {
                // print course, major req, credits, days
                cout << "COURSE " << i + 1 << ": " << courseList[i].name << endl;
                if (courseList[i].majorRequirement) {
                        cout << "Note: this course is a major requirement!" << endl;
                } else {
                        cout << "Note: this course is not a major requirement..." << endl;
                }
                cout << "Number of Credits: " << courseList[i].credits << endl;
                cout << "Days of Lectures: " << courseList[i].days << endl;

                // print times
                cout << "Lecture Time: ";
                print12Hour(courseList[i].startTime);
                cout << " -";
                print12Hour(courseList[i].endTime);
                cout << endl;

                // print average
                cout << "Stat: on average students get " << courseList[i].avgGrade << "% in this course." << endl;

                // formatting
                cout << "-------------------" << endl;
        }

        // free memory
        delete[] courseList;

        return 0;
}