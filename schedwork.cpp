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

// Helper function prototypes
bool validSchedule(const AvailabilityMatrix& avail, int dayIndex, Worker_T worker, map<Worker_T, int>& workerShifts, size_t maxShifts);
bool scheduleDay(size_t dayIndex, const AvailabilityMatrix& avail, DailySchedule& sched, size_t dailyNeed, size_t maxShifts, map<Worker_T, int> workerShifts);

// Main scheduling function
bool schedule(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched) {
    if (avail.empty() || avail[0].empty()) return false;

    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();
    //resize schedule to the number of workers 
    sched.resize(numDays, vector<Worker_T>(dailyNeed));

    // vector<int> shifts(numWorkers, 0);
    sched.clear();
    sched.resize(numDays);

    // int shifts = 0;
    // // shifts = 
    map<Worker_T, int> workerShift;

    // Start backtracking from the first day
    return scheduleDay(0, avail, sched, dailyNeed, maxShifts, workerShift);

    // // Start scheduling from day 0
    // return scheduleDay(0, avail, sched, shifts, dailyNeed, maxShifts);
}

// Recursive helper function to schedule workers day by day

bool scheduleDay(size_t dayIndex, const AvailabilityMatrix& avail, DailySchedule& sched, size_t dailyNeed, size_t maxShifts, map<Worker_T, int> workerShifts) {
    if (dayIndex == avail.size()) {
        return true;  // All days are successfully scheduled
    }

    size_t numWorkers = avail[dayIndex].size();
    // vector<Worker_T> todayWorkers;
    
    // Try to find a valid combination of workers for today
    
    for (Worker_T i = 0; i < numWorkers; ++i) {
         
        if (validSchedule(avail, dayIndex, i, workerShifts, maxShifts)) {
            // todayWorkers.push_back(i);
            sched[dayIndex].push_back(i);

            // # workers is enough -> go to next day
            if(sched[dayIndex].size() == dailyNeed) {
                // check next day
                if(scheduleDay(dayIndex+1, avail, sched, dailyNeed, maxShifts, workerShifts)) {
                    return true;
                }
                // backtrack
                sched[dayIndex].pop_back();
                workerShifts[i] -= 1;
            }
            else {
                    
                if(scheduleDay(dayIndex, avail, sched, dailyNeed, maxShifts, workerShifts)) {
                    return true;
                }
                // backtrack
                sched[dayIndex].pop_back();
                workerShifts[i] -= 1;
            }

        }
        
    }

    return false;

}

bool validSchedule(const AvailabilityMatrix& avail, int dayIndex, Worker_T worker, map<Worker_T, int>& workerShifts, size_t maxShifts) {

    // if worker is not available, return false
    if(!avail[dayIndex][worker]) {
        return false;
    }
    // create map with shifts for all workers
    // map<Worker_T, int> workerShifts;
// initialize shifts to 0
    int shifts = workerShifts[worker];
    
    // if # shfits per worker is greater than maxshifts, than schedule is NOT VALID
    if(shifts >= maxShifts) {
        return false;
    }
    // IF IT IS VALID, set # shifts for that specific worker -> true
    else {
        workerShifts[worker] += 1;
        return true;
    }

}

