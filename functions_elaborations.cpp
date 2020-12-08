    #include <iostream>
    #include <sstream>
    #include <vector>
    #include "functions_elaborations.h"
    #include <bits/stdc++.h>
    #include <algorithm>
    #include "round_robin.h"
    #include "srtf.h"
    using namespace std;

    vector<int> ready_queue;
    vector<int> process_waiting_time;
    vector<int> process_response_time;
    vector<int> process_turnaround_time;
    string checker;
    
    vector<int> check_for_identical_arrival_time(int clock_time, vector<int> pid, vector<int> arrival_vector, vector<int> burst_vector);

    vector<int> organize_ready_queue_by_time(vector<int> ready_queue, vector<int> burst_vector, vector<int> pid);

    vector<int> removing_process_from_ready_queue(vector<int> arrived_processes_vector,int index);
    int number, sum = 0;
    bool task_list_checker(string process_string){
        sum = 0;
        istringstream incoming_stream(process_string); //https://stackoverflow.com/questions/32627181/how-to-count-only-integers-in-a-string?answertab=active#tab-top
        while(incoming_stream >> checker){
            istringstream potential_number(checker);
            number = 0;
            if(potential_number >> number)
                sum++;
        }
        if(sum > 3 || sum < 3){
           // cout << "list file is in incorrect format.\n";
            return false;
        }
        else
            return true;
    }
    

    void list_file_format_specifier(){
            cout << "list files for this program should be in the follwong format: \n";
            cout << "three columns: the first designating the process id, the second designating the arrival time, and the third designating the run time.\n";
    }

    vector<int> returning_vector;
    vector<int> vector_populater(vector<int> temp_vector, vector<int> output_vector, int identifier){
        for (int i = 0; i < temp_vector.size(); i++)
        {
             returning_vector.push_back(temp_vector.at(i));
             //, arrival_time, burst_time
        }
        return returning_vector;
        
    }

    int i = 0, clock_time = 0, currently_executing_process = 0, remaining_burst_time = 0, input = 0;
    bool executing_time = true;
    vector<int> sorted_vector, arrived_processes_vector;

    void scheduler(vector<int> pid, vector<int> arrival_vector, vector<int> burst_vector, string policy, int quantum){
        if(policy.compare("rr") == 0)
            round_robin(pid, arrival_vector, burst_vector, policy, quantum);

        cout << "the policy in scheduler is: " << policy << "\n";
        if(policy.compare("fcfs") == 0)
            cout << "fcfs policy check in scheduler works\n";
        else
            //cout << "fcfs policy check is not working\n";


        //waiting time - amount of time process has been waiting in a ready queue
        //turnaround time - amount of time to execute a particular process (waiting time plus execution time)
        //repsonse time - similiar to waiting time? 

        //fcfs policy enactment
        while(policy.compare("fcfs") == 0){//need to add average waiting time, average response time, average turnaround time, and overall cpu usage?
            // for (int i = 0; i < burst_vector.size(); i++)
            // {
            //     //cout << "the burst vector value at the " << i << " index is: " << burst_vector.at(i) << "\n";
            // }
            

            process_waiting_time.push_back(clock_time);//the index will correspond to the waiting time for that process.
            process_response_time.push_back(clock_time);
            cout << "waiting time for the process " << i << " is: " << process_waiting_time.at(i) << "\n";
            while(burst_vector.at(i) != 0 ){//will get the bursts that we need.
                
                //cout << "process " << i << " is executing.\n";
                burst_vector.at(i) = burst_vector.at(i) - 1;
                cout << "<time " << clock_time << "> process " << i << " is running.\n";
                clock_time++;
            }
            cout << "<time " << clock_time << "> process " << i << " is finished.\n";
            process_turnaround_time.push_back(clock_time);
            cout << "turnaround time for the process " << i << " is: " << process_turnaround_time.at(i) << "\n";

            if(i == pid.size() - 1){
                cout << "   Average waiting time:  " << int_vector_averager(process_waiting_time) << "\n";
                cout << "  Average response time:  " << int_vector_averager(process_response_time) << "\n";
                cout << "Average turnaround time:  " << int_vector_averager(process_turnaround_time) << "\n";
                
                break;//break from the inner while loop once all the processes are done.
            }

            i++;
           
    
    
        
                //below is a rough draft that is in an infinite loop. 

        

            //     while(arrival_vector.at(i) == clock_time){
            //         ready_queue.push_back(pid.at(i));//this is saving all the processes that arrive at the same time.
            //         i++;
            //         cout << "pid: " << i << " was pushed onto the ready queue\n";
            //         cout << "please enter a character to continue: \n";
            //         cin >> input;
            //     }

            //     if(remaining_burst_time == 0){//this is for accessing a new process from the ready queue in case a process hasnt started or one has just finished.
                    
            //         currently_executing_process = ready_queue.front();//getting the pid for the process at the from of the ready queue
                    
            //         for (int j = 0; j < ready_queue.size() - 1; j++){//this is for resizing the vector when a process has been removed.
            //             ready_queue.at(j) = ready_queue.at(j + 1);
            //         }

            //     }

            //     burst_vector.at(currently_executing_process) =  burst_vector.at(currently_executing_process) - 1;//mimicking a process 
            //     remaining_burst_time = burst_vector.at(currently_executing_process);
            //     cout << "process " << currently_executing_process << " is executing"  << burst_vector.at(i) << " is the remaining time for burst vector and clock_time is: " << clock_time << ".\n";
            //     clock_time++;

                
                
            //     if(burst_vector.at(burst_vector.size() - 1) == 0)
            //         break;

        }


        //srtf policy enactment
        while(policy.compare("srtf") == 0){

            //srtf_implementation(vector<int> pid, vector<int> arrival_vector, vector<int> burst_vector);
            srtf_implementation(pid, arrival_vector, burst_vector);


//             cout << "srtf section has begun\n";
//             int countup = 0;

//             for (int i = 0; i < sorted_vector.size(); i++)
//             {
//                 cout << "sorted vector at beginning of srtf is: " << sorted_vector.at(i) << "\n";
//             }
            
//             cout << "clock time is: " << clock_time << "\n";
//             //if there is a process or processes that arrive at this particular clock time, then sort and append them to the apv with the function below
          
//             if(count(arrival_vector.begin(), arrival_vector.end(), clock_time)){//the arrival index starts at zero. we are looking for the value instead of the index
//                 cout << "\n\n\n\n\n\narrival time matches clock time\n";
//                 sorted_vector =  check_for_identical_arrival_time(clock_time, pid, arrival_vector, burst_vector); //its redoing the sorted vector after every clock cycle
                
//                 //now we have an ordered list of processes that arrived at clock time i.
//                 //now lets check with a search funtion which process is the shortest and substract one from its burst time.
            
//                 //appending the sorted_vector for each clock cycle to the end of the ready_queue
//                 arrived_processes_vector.insert(arrived_processes_vector.end(), sorted_vector.begin(), sorted_vector.end());
//             }
//             for (int i = 0; i < sorted_vector.size(); i++)
//             {
//                 cout << "value in arrived_processes_vector is: " << arrived_processes_vector.at(i) << "\n";
//             }
//             for (int i = 0; i < burst_vector.size(); i++)
//             {
//                 cout << "value in burst_vector is: " << burst_vector.at(arrived_processes_vector.at(i)) << "\n";
//             }
//             int shortest_task_index = arrived_processes_vector.at(0);
//             for (int i = 0; i < arrived_processes_vector.size(); i++)
//             {
//                if(burst_vector.at(arrived_processes_vector.at(i) < burst_vector.at(shortest_task_index))){
//                    shortest_task_index = arrived_processes_vector.at(i);
//                }
//                 /* code */
//             }
            
//             cout << "shortest task index is: " << shortest_task_index << "\n";
//             cout << "shortest burst time is: " << burst_vector.at(sorted_vector.at(shortest_task_index)) <<"\n";
//             //now, we subtract one from this burst vector
//             burst_vector.at(sorted_vector.at(shortest_task_index)) = burst_vector.at(sorted_vector.at(shortest_task_index)) - 1;
//             //if the burst_vector contains 0, then we remove it from the ready_queue.

//             cout << "this burst time after one clock cycle is: " << burst_vector.at(sorted_vector.at(shortest_task_index)) <<"\n";

//             if(burst_vector.at(arrived_processes_vector.at(shortest_task_index)) == 0){
//                 arrived_processes_vector = removing_process_from_ready_queue(arrived_processes_vector, sorted_vector.at(shortest_task_index));
                
//                 break;
//             }
//             //now take what is in the ready queue and execute it.
//             //shift the sorted vector to account for the first process being removed. if a shorter process arrives, then we push that process back onto the front of the ready_queue
//             //what about a process that is shorter than one or more processes in the ready queue and longer than what is currently being run? will it be sorted into the
//             //ready queue? 
//             clock_time++;
//             cout << "please enter a number to continue \n";
//             cin >> countup;
            
            
//             // while(burst_vector.at(i) != 0 ){//will get the bursts that we need.
                
//             //     //cout << "process " << i << " is executing.\n";
//             //     burst_vector.at(i) = burst_vector.at(i) - 1;
//             //     cout << "<time " << clock_time << "> process " << i << " is running.\n";
//             //     clock_time++;//if arrival time equals clock time and burst time is less than remaining time in the current processes burst vector, replace the 
//             //                 //current process burst vector with the shorter one and push the replaced burst vector to the ready queue
//             // }
// //            i++;

        }
    }

    vector<int> check_for_identical_arrival_time(int clock_time, vector<int> pid, vector<int> arrival_vector, vector<int> burst_vector){
        cout << "i value inside of arrival time check is: " << i << "\n";

        ready_queue.clear();
        while(arrival_vector.at(i) == clock_time){ 
                cout << "entering while loop.\n";
                    ready_queue.push_back(pid.at(i));//this is saving all the processes that arrive at the same time. this is getting added onto double over.
                     i++;
                     cout << "pid: " << i << " was pushed onto the ready queue\n";
                     cout << "please enter a character to continue: \n";
                     cin >> input;
                     if(i == arrival_vector.size())
                        break;
             }
            cout << "size of ready queue is: " << ready_queue.size() << "\n";
            return organize_ready_queue_by_time(ready_queue, burst_vector,pid);
    }



    vector<int> temp_queue;
    int current_min = 0;
    vector<int> organize_ready_queue_by_time(vector<int> ready_queue, vector<int> burst_vector, vector<int> pid){
        //recieves a ready queue of one.......
        cout << "here is the ready queue in the organizer function\n";

        for (int i = 0; i < ready_queue.size(); i++){
            cout << "ready queue member is:" << ready_queue.at(i) << "\n";
            
        }
        
        int someting = ready_queue.size();
        cout << "heres whats in the ready queue: \n";
        for (int i = 0; i < ready_queue.size(); i++)//ready is holding the pids for the processes.
                                                    //just check the arrival times and sort the pids like that?
                                                    //look for the min in the vector, add the pid to a new temp vector, and save that 
                                                    //min value, then look for a min that is less than all the other processes and greater than 
                                                    //or equal to the value just sent to the temp vector. repeat this for the whole vector.
        {
            cout << "entering the for loop\n";
           if(i == ready_queue.size()){
                break;
                cout << "if statement has run\n";
           }
           cout <<  ready_queue.at(i) << "\n\n";
           
        }
        // if(ready_queue.size() >= 1)
        //     current_min = burst_vector.at(ready_queue.at(0));
        vector<int> temp_vector = burst_vector;
        sort(burst_vector.begin(), burst_vector.end());//say where you got this from!!!!!!!!
        

        // for (int i = 1; i < ready_queue.size(); i++){
        //     //need burst vector as input >> burst_vector(ready_queue.at(i)) will get the burst value for the pid that is stored in 
        //     //the ready_queue at that index
        //     if(current_min >= burst_vector.at(ready_queue.at(i))){
        //         current_min = burst_vector.at(ready_queue.at(i));
        //     }
        // }
       vector<int> sorted_ready_queue;
       sorted_ready_queue.clear();
       for (int i = 0; i < burst_vector.size(); i++){//burst_vector just got sorted
          // cout << "burst_vector index is: " << i << "\n";
           for (int j = 0; j < pid.size(); j++){
               //cout << "pid index is: " << j << "\n";
                if(j < pid.size() - 1){
                    cout << "i is: " << i << " and j is: " << j << "\n";
                    cout << "burst_vector at i is : " << burst_vector.at(i) << "\n";
                    cout << "pid at j is: " << pid.at(j) << "\n";
                    cout << "burst_vector at that pid value is: " << burst_vector.at(pid.at(j)) << "\n\n";

                    if(burst_vector.at(i) == temp_vector.at(pid.at(j)) && !count(sorted_ready_queue.begin(), sorted_ready_queue.end(), pid.at(j))){
                            cout << "\nif statement executed\n\n";
                            sorted_ready_queue.push_back(pid.at(j));
                    }
                }
               
           }
           if(i == burst_vector.size())
                break;
       }
           /* code */
       for (int i = 0; i < sorted_ready_queue.size(); i++){
           cout << "value in sorted ready queue is: " << sorted_ready_queue.at(i) << "\n";
       }
       
       for (int i = 0; i < pid.size(); i++)//looking for the index corresponding to the max value in the burst_vector.
       {    
           if(!count(sorted_ready_queue.begin(), sorted_ready_queue.end(), pid.at(i))){//every value in the sorted ready queue is -1 from the actual real value.
                //do a mod of the size.

                cout << "the index of the max burst time in the pid vector is: " << pid.at(i)%pid.size() << "\n";
                sorted_ready_queue.push_back(pid.at(i)%pid.size());
           }
       }
       
        for (int i = 0; i < sorted_ready_queue.size(); i++){
           cout << "value in sorted ready queue is: " << sorted_ready_queue.at(i) << "\n";
       }
       
       return sorted_ready_queue;

    }

    double int_vector_averager(vector<int> input_vector){
            double sum = 0, average = 0;
            for (int i = 0; i < input_vector.size(); i++)
            {
                sum += input_vector.at(i);
            }
            
            average = sum/input_vector.size();
        return average;
    }

    vector<int> removing_process_from_ready_queue(vector<int> arrived_processes_vector,int index){
        cout << "index is: " << index << "\n";
        cout << "entering process to remove process from ready queue\n";
        for (int i = 0; i < arrived_processes_vector.size(); i++)
        {
            cout << "arrived process vector in remove process is: " << arrived_processes_vector.at(i) << "\n";
            //the arrived processes vector is the pid ordered by their burst time.
            
            
        }

        for (int i = 0; i < arrived_processes_vector.size(); i++){
            if(arrived_processes_vector.at(i) == index){
                arrived_processes_vector.erase(arrived_processes_vector.begin() + i);
            }
        }
        for (int i = 0; i < arrived_processes_vector.size(); i++)
        {
            cout << "arrived process vector after remove process is: " << arrived_processes_vector.at(i) << "\n";
            //the arrived processes vector is the pid ordered by their burst time.
            
            
        }
        //cout << "burst time at the index in question is: " << 
             //whichever arrived_processes_vector holds the "index" value needs to be removed.
        
        cout << index << " is the index.\n";
        cout << "index with zero value is: " << sorted_vector.at(index) << "\n";
        return arrived_processes_vector;
    }



    