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

bool canWork(const AvailabilityMatrix& avail, const size_t maxShifts, int day, Worker_T worker);
void dayAdd(vector<int>& shiftCounts, Worker_T worker);
void dayRemove(vector<int>& shiftCounts, Worker_T worker);
bool generateWeeks(DailySchedule& schedule, const size_t& dailyNeed, vector<Worker_T>& day_roster, const AvailabilityMatrix& avail, const size_t maxShifts, vector<int>& shiftCounts, int day);



// Add your implementation of schedule() and other helper functions here

bool canWork(const AvailabilityMatrix& avail, vector<int>&shiftCounts, const size_t maxShifts, int day, Worker_T worker){
    return (shiftCounts[worker] < maxShifts && avail[day][worker]);
}

void dayAdd(vector<int>& shiftCounts, Worker_T worker){
    shiftCounts[worker]++;
}

void dayRemove(vector<int>& shiftCounts, Worker_T worker){
    shiftCounts[worker]--;
}

bool generateWeeks(DailySchedule& schedule, const size_t& dailyNeed, vector<Worker_T>& day_roster, const AvailabilityMatrix& avail, const size_t maxShifts, vector<int>& shiftCounts, int day){

      if(day_roster.size() == dailyNeed){
          vector<Worker_T>added = day_roster;
          schedule.push_back(added);
          return true;
      }

      for(unsigned int j = 0; j < shiftCounts.size(); j++){
            if(canWork(avail, shiftCounts, maxShifts, day, j)){
                dayAdd(shiftCounts, j);
                day_roster.push_back(j);
                if(generateWeeks(schedule, dailyNeed, day_roster, avail, maxShifts, shiftCounts, day)){
                  day_roster.clear();
                  return true;
                }
                dayRemove(shiftCounts, j);
                day_roster.pop_back();
          }
      }
      return false;
}

bool schedule(
        const AvailabilityMatrix& avail,
        const size_t dailyNeed,
        const size_t maxShifts,
        DailySchedule& sched
)
{
    if(avail.size() == 0U || dailyNeed == 0){
        return false;
    }
    sched.clear();

    vector<Worker_T> day_roster;
    vector<int>shiftCount(avail[0].size(), 0);

    for(unsigned int i = 0; i < avail.size(); i ++){
    generateWeeks(sched, dailyNeed, day_roster, avail, maxShifts, shiftCount, i);
    }

    if(sched.size() == avail.size()){
        return 1;
    }

    return 0;
}

