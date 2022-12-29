#include "timer.h"
time_t start_timer()
{
    return time(0);
}

void split_time(time_t total_seconds, hms_time *hms)
{
    hms->hours = (total_seconds / 3600) % HOUR_FORMAT;

    int seconds_remainder_from_hours = total_seconds % SECONDS_IN_HOUR;
    hms->minutes = seconds_remainder_from_hours / MINUTES_IN_HOUR;

    int seconds_remainder_from_minutes = seconds_remainder_from_hours % SECONDS_IN_MINUTE;
    hms->seconds = seconds_remainder_from_minutes;
}

time_t resume_timer(hms_time elapsed_time)
{
    time_t elapsed_seconds = elapsed_time.hours * 3600 + elapsed_time.minutes * 60 + elapsed_time.seconds;
    return time(0) - elapsed_seconds;
}

void get_elapsed_time(time_t timer_start, hms_time *elapsed_time)
{
    time_t timer_now = time(0);
    split_time(timer_now - timer_start, elapsed_time);
}