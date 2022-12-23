#include "timer.h"
time_t start_timer(){
    return time(0);
}

hms_time split_time(time_t total_seconds){
    hms_time time;
    time.hours = (total_seconds/3600) % HOUR_FORMAT; 
    
    int seconds_remainder_from_hours = total_seconds % SECONDS_IN_HOUR;
    time.minutes = seconds_remainder_from_hours/MINUTES_IN_HOUR;
    
    int seconds_remainder_from_minutes = seconds_remainder_from_hours % SECONDS_IN_MINUTE;
    time.seconds = seconds_remainder_from_minutes;

    return time;
}

hms_time get_elapsed_time(time_t timer_start){
    time_t timer_now = time(0);
    return split_time(timer_now-timer_start);
}