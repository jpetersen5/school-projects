#ifndef TIME_H
#define TIME_H

class Time {
        // private variables (unchangeable outside class)
        private:
                int t_hr;
                int t_min;
                int t_sec;

        // public functions (useable whereever)
        public:
                Time();
                Time(int hr, int min, int sec);
                ~Time();

                int getHr();
                int getMin();
                int getSec();

                void setHr(int hr);
                void setMin(int min);
                void setSec(int sec);
};

#endif