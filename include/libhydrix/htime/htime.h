#pragma once
void time_init();
int getSeconds();
int getMinutes();
int getHours();
int getDay();
int getMonth();
int getYear();
int getCentury();
int getDayOfWeek();


long long getTimeFromBoot();
long long currentTime();

typedef struct {
    int seconds;
    int minutes;
    int hours;
    bool pm;
} Time_t;

typedef enum {
    //cmos default is UTC
    UTC = 0,
    PacificTime = -7,
    MountainTime = -6,
    CentralTime = -5,
    EasternTime = -4,
    London = 1,
    CenteralEurope = 2,
    Berlin = 2,
    Moscow = 3,
    Dubai = 4,
    Mumbai = 5,
    Singapore = 8,
    Beijing = 8,
    ChinaTime = 8,
    Tokyo = 9,
    Sydney = 10,
    NewZealand = 12

} TIMEZONE_OFFSET;
#define DAYOFWEEK(x) (x == 0 ? "Sunday" : x == 1 ? "Monday" : x == 2 ? "Tuesday" : x == 3 ? "Wednesday" : x == 4 ? "Thursday" : x == 5 ? "Friday" : x == 6 ? "Saturday" : "Unknown")
TIMEZONE_OFFSET GetCurrentTimezone();
void SetCurrentTimezone(TIMEZONE_OFFSET offset);
Time_t getTime(TIMEZONE_OFFSET timezone);
Time_t getTime();
Time_t getTime12Hour(TIMEZONE_OFFSET SpecifiedTimezone);
Time_t getTime12Hour();