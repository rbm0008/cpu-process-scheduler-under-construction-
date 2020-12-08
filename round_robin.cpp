#include "round_robin.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;


//algorithm for round robin
/*
    clock_time = 0, q_limit = incoming quantum, quantum_count = 0, first_started_vector = all -1's the the size of the pid vector
    finished_process_vector = all -1's the size of the pid vector
    user_mode = true;
    while(user_mode){
        push everything onto the ready queue that arrives at that particular clock time;
        if(nothing is in the run slot or quantum_count == quantum_limit)
qc = ql --> if(process still needs to finish and is in the run slot)
                push thecurrent process to the back of the ready queue
                empty run slot
            get next pid from rq and put in run slot
            if(first_started_vector(pid_now_in_run_slot - 1) == -1)
                record starting time in first_started_vector(pid_now_in_run_slot - 1)
    
        burst_time--;
        quantum_count++;
        clock_time++;
        if(current_process_burst_time == 0)
            record finish time for that process in finished_process_vector
            remove this process from the ready queue
    }
    do all the statistics


*/
/*
 clock_time = 0, q_limit = incoming quantum, quantum_count = 0, first_started_vector = all -1's the the size of the pid vector
    finished_process_vector = all -1's the size of the pid vector
    user_mode = true;
    while(user_mode){
        push everything onto the ready queue that arrives at that particular clock time;
        if(run_slot == -1 || q_lim == q_count){
            if(run_slot == -1){ //program has just starteds
                run_slot = 0
                record starting time for pid 1 in the fsv vector
            }
            if(q_limit == q_count){
                push current process to back of rq;
                retrieve new pid and assifn to run slot;
                reset q_count
            }
            if(fsv.at(run_slot) == -1){
                fsv.at(run_slot) = clock_time;
            }
        }
        burst_time--;
        q_count++;
        clock_time++;
        if(burst_vector.at(run_slot) == 0){
            record the clock time in fpv.at(run_slot);
            remove process from rq
            reset q_count
            get next process and assign to run_slot
            fsv.at(run_slot) = clock_time
        }
*/


void round_robin(vector<int> pid, vector<int> arrival_vector, vector<int> burst_vector, string policy, int quantum);


int clock_time_in_rr = 0, q_limit = 0, q_count = 0,arrival_index = 0, run_slot = -1;
bool user_mode = true;
vector<int> first_started_vector, finished_process_vector, ready_queue_in_rr;

void round_robin(vector<int> pid,vector<int> arrival_vector,vector<int> burst_vector,string policy, int quantum){//need to add error checking for command line arguments for rr
    q_limit = quantum;
    
    //below we are sizing the vectors to hold the start and finish times for each of the processes
    for (int i = 0; i < pid.size(); i++)
    {
        first_started_vector.push_back(-1);
        finished_process_vector.push_back(-1);
    }
    

    cout << "entering round robin\n";
   
    while(user_mode){
        
      
   
         //the while loop below is an implementation of line 14 of the algorithm above
        if(arrival_index < pid.size()){
            while(arrival_vector.at(arrival_index) == clock_time_in_rr){
                cout << "process is being added to the ready queue at time: " << clock_time_in_rr << "\n";
                ready_queue_in_rr.push_back(pid.at(arrival_index));//push back pid relating to the arrival time.
                arrival_index++;
                if(arrival_index == pid.size())
                    break;     
            }
        }

        cout << "at clock time " << clock_time_in_rr << " ";
        cout << "ready queue now contains: { ";
        for (int i = 0; i < ready_queue_in_rr.size(); i++)
        {
           cout << ready_queue_in_rr.at(i) << " ";
        }
        cout << "}\n";
        
        //the below section is for when the program is just starting or when the quantum has been reached
        if(run_slot == -1 || q_limit == q_count){//run_slot is symbolic for pictoral purposes. run_slot - 1 needs to be used when actual index values need to be addressed.
            if(run_slot == -1){
                run_slot = 1;//this assigns run slot with the first index in the ready queue.
                first_started_vector.at(run_slot - 1) = clock_time_in_rr;
                ready_queue_in_rr.erase(ready_queue_in_rr.begin() + 0);//remove it from the ready queue once it is assigned to the run slot.
              
            }// http://www.cplusplus.com/reference/vector/vector/erase/

            if(q_limit == q_count){//when the current process has reached it quantum limit
               // cout << "\nvalue left in burst time for process is: "<< burst_vector.at(run_slot - 1) << "\n\n";

                //cout << "run_slot value is: " << run_slot << "\n";
                ready_queue_in_rr.push_back(run_slot);//adding the process to the back of the ready_queue once the quantum has reached the limit.
                run_slot = ready_queue_in_rr.front();//getting the next process in line.
                ready_queue_in_rr.erase(ready_queue_in_rr.begin() + 0);//removing that process from the ready queue
                q_count = 0;
            }
            if(first_started_vector.at(run_slot) == -1){
                first_started_vector.at(run_slot - 1) = clock_time_in_rr;
            }


        }
        burst_vector.at(run_slot - 1) = burst_vector.at(run_slot - 1) - 1;
        //cout << "value left in " << run_slot << " is: " << burst_vector.at(run_slot - 1) << "\n";
        q_count++;
        clock_time_in_rr++;

        //since we are not pushing the run_slot number to the back of the queue, it will be erased all together.
        //the section below 
        if(burst_vector.at(run_slot - 1) == 0){
            cout << "burst value for process: " << run_slot << " has run out.\n";
            finished_process_vector.at(run_slot - 1) =clock_time_in_rr;
            q_count = 0;
            run_slot = ready_queue_in_rr.front();
            ready_queue_in_rr.erase(ready_queue_in_rr.begin() + 0);
            finished_process_vector.at(run_slot - 1) = clock_time_in_rr;
            cout << "process " << run_slot << " has been moved to the run_slot and " << burst_vector.at(run_slot - 1) << " is the remaining time\n"; 

        }


        //below is the exit from user_mode when all the processes are done.
        if(clock_time_in_rr == 30){//https://www.geeksforgeeks.org/how-to-find-the-sum-of-elements-of-a-vector-using-stl-in-c/
            //cout << "sum of all processes is: " << accumulate(burst_vector.begin(), burst_vector.end(), 0) << "\n";            
            user_mode = false;
            cout << "user_mode has been made false\n";
        }   
    }



    for (int i = 0; i < ready_queue_in_rr.size(); i++)
    {
        cout << "item in ready queue in round robin is: " << ready_queue_in_rr.at(i) << "\n";
    }
    
}
