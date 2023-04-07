#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here
bool schedulechecker(const AvailabilityMatrix& avail,
const size_t dailyNeed,
const size_t maxShifts,
DailySchedule& sched,
int days,
int workers,
vector<int> workeddays
);

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int days = avail.size();
    int workers = avail[0].size();

    vector<int> workeddays;
    for(int i = 0; i < workers; i++){
        workeddays.push_back(0);
    }
    return schedulechecker(avail, dailyNeed, maxShifts, sched, days, workers, workeddays);
}

bool schedulechecker(const AvailabilityMatrix& avail,
const size_t dailyNeed,
const size_t maxShifts,
DailySchedule& sched,
int days,
int workers,
vector<int> workeddays
){
    if((int)sched.size() == days){
        if(sched[days - 1].size() == dailyNeed){
            return true;
        }
    }
    if(sched.size() == 0){
        vector<Worker_T> temp; 
        sched.push_back(temp);
    }

    int day = sched.size();

    if((int) sched[day - 1].size() == (int)dailyNeed){
        vector<Worker_T> temp;
        sched.push_back(temp);
    }
    day = sched.size();

    for(int i = 0; i < workers; i++){
        if(!(find(sched[day - 1].begin(), sched[day - 1].end(), i) != sched[day - 1].end())){
            if(avail[day - 1][i]){
                sched[day - 1].push_back(i);
                if(workeddays[i] < (int) maxShifts){
                    workeddays[i]++;
                
                if(schedulechecker(avail, dailyNeed, maxShifts, sched, days, workers,workeddays)){
                    return true;
                }
                workeddays[i]--;
            }
            sched[day - 1].pop_back();
        }
    }
}
if(sched[day - 1].size() == 0){
    sched.pop_back();
}
return false;
}