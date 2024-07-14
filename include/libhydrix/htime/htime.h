#pragma once
void InitializeTime();
int TimeGetSeconds();
int TimeGetMinutes();
int TimeGetHours();
int TimeGetDay();
int TimeGetMonth();
int TimeGetYear();
int TimeGetCentury();
int TimeGetDayOfTheWeek();


long long TimeSinceBootMS();
long long TimeCurrentTime();

typedef struct {
    int seconds;
    int Minimumutes;
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

} TimezoneOffset_t;
#define DAYOFWEEKTRANSLATOR(x) (x == 0 ? "Sunday" : x == 1 ? "Monday" : x == 2 ? "Tuesday" : x == 3 ? "Wednesday" : x == 4 ? "Thursday" : x == 5 ? "Friday" : x == 6 ? "Saturday" : "Unknown")
TimezoneOffset_t GetCurrentTimezone();
void SetCurrentTimezone(TimezoneOffset_t offset);
Time_t TimeGetTime(TimezoneOffset_t timezone);
Time_t TimeGetTime();
Time_t TimeGetTime12(TimezoneOffset_t SpecifiedTimezone);
Time_t TimeGetTime12();