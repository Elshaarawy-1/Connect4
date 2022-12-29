#ifndef TIMER_H
#define TIMER_H

#include <time.h>

#define HOUR_FORMAT 12
#define MINUTES_IN_HOUR 60
#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 3600 

typedef struct time_s{
    int hours;
    int minutes;
    int seconds;
} hms_time;


/// @brief starts a timer using time(0)
/// @return time_t that represents epoch time
time_t start_timer();

/// @brief splits time_t seconds to hours, minutes, seconds. Make sure that the hours of the given time aren't more that sizeof(int)
/// @param total_seconds time to be represented as hours,minutes and seconds
/// @param hms time as stuct with hours,minutes and seconds
void split_time(time_t total_seconds, hms_time* hms);

time_t resume_timer(hms_time elapsed_time);

/// @brief gets elapsed time between timer_start and now as hours, minutes and seconds
/// @param timer_start starting time to calcualate time from
/// @param elapsed_time elapsed time as hours, minutes and seconds
void get_elapsed_time(time_t timer_start, hms_time *elapsed_time);

#endif