/**
 * here is the algorithm for the code below:
 * just by default, lets use index 0 as the "shortest one before user_mode even starts."
 * while(user_mode){
 *      push all processes that arrive at clock time onto the ready queue
 *      
 *      scan all processes on the ready queue so far to see which one is the shortest 
 *      if(there is a shorter one now in the ready queue)
 *          push the currently executing process onto the ready queue 
 *          move the shortest processes index into the run_slot
 *      if(fsv.at(run_slot) == -1){
 *          fsv.at(run_slot) == clock_time
 *      }
 *      burst_vector.at(run_slot)--;
 *      clock_time++;
 *      if(burst_vector.at(run_slot) == 0){
 *          fpv.at(run_slot) = clock_time;
 *          //dont add it back to the ready queue
 *          run_slot = index of next shortest process in ready queue
 *          fsv.at(run_slot) = clock_time;
 *      }
 *      if(nothing is in the ready queue and we have reached the end of the pid vector){
 *          user_mode = false;
 *      }
 *      
 * 
 * }
 * 
 */
 #include <bits/stdc++.h>
#include <string>
#include <iostream>
#include <vector>
#include "srtf.h"
using namespace std;
void srtf_implementation(vector<int> pid, vector<int> arrival_vector, vector<int> burst_vector_in_srtf);


int clock_time_in_srtf = 0, burst_time_in_srtf, run_slot_in_srtf = 0, arrival_index_in_srtf = 0, temp;

void srtf_implementation(vector<int> pid, vector<int> arrival_vector, vector<int> burst_vector_blah){
    bool srtf_user_mode = true;
    vector<int> first_started_vector_in_srtf, finished_process_vector_in_srtf, ready_queue_in_srtf;
    vector<int> burst_time_in_srtf = burst_vector_blah, temp_vector;
    //below is part of the implementation to save times in this program
    for (int i = 0; i < pid.size(); i++){
            first_started_vector_in_srtf.push_back(-1);
            finished_process_vector_in_srtf.push_back(-1);
        
            
    }


    while(srtf_user_mode){
        //below is the code for adding any processes that arrived at the clock time to the ready queue
        if(arrival_index_in_srtf < pid.size()){
                while(arrival_vector.at(arrival_index_in_srtf) == clock_time_in_srtf){//arrival index is used for seeing how many processes arrived at the clock_time in the vector
                    cout << "process is being added to the ready queue at time: " << clock_time_in_srtf << "\n";
                    ready_queue_in_srtf.push_back(pid.at(arrival_index_in_srtf));//push back pid relating to the arrival time.
                    arrival_index_in_srtf++;
                    if(arrival_index_in_srtf == pid.size())
                        break;     
                }
        }

        //below is the selection code for the process in the run slot.
        //cout << "size of the ready queue is: " << ready_queue_in_srtf.size() << "\n";
        temp = run_slot_in_srtf;
        for(int i = 0; i < ready_queue_in_srtf.size(); i++)
        {
            if(burst_time_in_srtf.at(i) < burst_time_in_srtf.at(run_slot_in_srtf) && burst_time_in_srtf.at(i) != 0){
                run_slot_in_srtf = i;//reassigning the the pid with the smallest amount of process left.
                cout << "found a shorter process.\n";
            }
        }
        //if there is a new shorter process found, then we remove it from the ready queue and push the old process to the back.
        if(temp != run_slot_in_srtf){
            ready_queue_in_srtf.erase(ready_queue_in_srtf.begin() + run_slot_in_srtf);//this should erase the index of the shortest process
        
            ready_queue_in_srtf.push_back(temp + 1);//this pushes the index back onto the ready queue if there is now a new shorter process.
        }


        //below is recording when the process started.
        if(first_started_vector_in_srtf.at(run_slot_in_srtf) == -1){
            first_started_vector_in_srtf.at(run_slot_in_srtf) = clock_time_in_srtf;
        }

        //below is the actual work section
        cout << "<process " << run_slot_in_srtf + 1 << "> is executing.\n";
        burst_time_in_srtf.at(run_slot_in_srtf) = burst_time_in_srtf.at(run_slot_in_srtf) - 1;
        cout << "value left in burst vector is: " << burst_time_in_srtf.at(run_slot_in_srtf) << "\n";;
        //cout << "value in run slot is: " << run_slot_in_srtf << "\n";
        clock_time_in_srtf++;

        //checking to see if burst time for the given process is done.
        if(burst_time_in_srtf.at(run_slot_in_srtf) == 0){
            cout << "   burst vector for the current index is now empty.\n";
            finished_process_vector_in_srtf.at(run_slot_in_srtf) = clock_time_in_srtf;
            cout << "burst time copy now contains: \n";
            for (int i = 0; i < burst_time_in_srtf.size(); i++)
            {
                cout << burst_time_in_srtf.at(i) << "\n";
            }
            cout << "\nready queue contains:" << ready_queue_in_srtf.size();
            
            for (int j = 0; j < ready_queue_in_srtf.size(); j++)
            {
                cout << ready_queue_in_srtf.at(j) << "\n";
            }
            
          
            run_slot_in_srtf = 0;//dont do this before 
            cout<< "start of for loop\n";
            for(int i = 0; i < ready_queue_in_srtf.size(); i++){  
                //cout << burst_time_in_srtf.at(ready_queue_in_srtf.at(i) - 1) << "\n";
               
                //cout << burst_time_in_srtf.at(ready_queue_in_srtf.at(run_slot_in_srtf) - 1) << "\n";
               
                //cout << burst_time_in_srtf.at((ready_queue_in_srtf.at(i) - 1)) << "\n";
                
                if(burst_time_in_srtf.at(ready_queue_in_srtf.at(i) - 1) < burst_time_in_srtf.at(ready_queue_in_srtf.at(run_slot_in_srtf) - 1)){  
                   
                  
                        cout << "shorter process is found at: " << ready_queue_in_srtf.at(i) - 1 << "\n";
                        run_slot_in_srtf = ready_queue_in_srtf.at(i) - 1;//reassigning the the pid with the smallest amount of process left.
                                          //now we need to rmove i from the ready queue because it was just moved to the run slot
                        
                }
            }
           
            first_started_vector_in_srtf.at(run_slot_in_srtf) = clock_time_in_srtf;
           
            ready_queue_in_srtf.erase(ready_queue_in_srtf.begin() + run_slot_in_srtf);//removing the new found minimum process from the ready queue

        }
        cout << "run slot is now: " << run_slot_in_srtf << "\n";
        if(clock_time_in_srtf == 20){
            srtf_user_mode = false;
        }
    }

}
    