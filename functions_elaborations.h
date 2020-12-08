    #ifndef FUNC_ELAB
    #define FUNC_ELAB
   
    #include <iostream>
    #include <sstream>
    #include <vector>
    #include "round_robin.h"
    using namespace std;

   

    //vector<int> ready_queue;
    double int_vector_averager(vector<int> input_vector);

    vector<int> check_for_identical_arrival_time(int clock_time, vector<int> pid, vector<int> arrival_vector, vector<int> burst_vector);

    vector<int> organize_ready_queue_by_time(vector<int> ready_queue, vector<int> burst_vector, vector<int> pid);
  
    vector<int> removing_process_from_ready_queue(vector<int> arrived_processes_vector,int index);
    
    bool task_list_checker(string process_string);
    

    void list_file_format_specifier();

    vector<int> vector_populater(vector<int> temp_vector, int identifier);

    void scheduler(vector<int> pid, vector<int> arrival_vector, vector<int> burst_vector, string policy, int quantum);
    #endif