#include <iostream>
#include "functions_elaborations.h"
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "round_robin.h"
#include "srtf.h"
using namespace std;
int input_command_number;
int quantum = 0;
vector<string> processvector;
vector<int> pid_vector, arrival_time, burst_time, temp_vector;
void coordinator(int argc, char **argv);

void list_file_parser(vector<string> processvector);

void vector_populater(vector<int> temp_vector);

int main(int argc, char ** argv){//argc is the number of arguments, argv is the actual arguments
    int input_command_number = argc;
    char **input_command_strings = argv;
    string temp = argv[2];
    //int blahblah = stoi(argv[3]);
    ifstream fileopener;
    string full_line;
    stringstream input_string;
    fileopener.open(argv[1]);//here we are opening the file specified by the first command line vector.
    int i, j, k;
    if((bool)fileopener != 0){
        while(getline(fileopener, full_line)){
            processvector.push_back(full_line);
            
            input_string << full_line;
        
            cout << "input string is: " << full_line << "\n";
    
        }
   
    }

    for (int i = 0; i < processvector.size(); i++)
    {
        cout << "elements in the process vector are: " << processvector.at(i) << "\n";
        if(!task_list_checker(processvector.at(i))){
            list_file_format_specifier();
            goto exit;
        }
            //goto a function that will print out instructions for making a correctly formatted list file.
        //while(processvector.at(i) >> j){
        //    k++;
        // }
            
    }
    


    cout << "there are " << argc << " arguments: " << "\n";
    if(argc != 3 && argc != 4){
        cout << "\n\nplease enter the command line arguments in the following arrangement: \n";
        cout << "for srtf and fcfs policies, type the following: ./command <filename> <scheduling policy>\n";
        cout << "for the rr policy, please enter the following:  ./executable_name <filename> rr <quantum>\n\n";
        goto exit;
    

    }
    //cout << "input argument 4 is: " << argv[3] << "\n";
    cout << "number of command line arguments is: " << argc << "\n";
    cout << "scheduling policy is: " << temp << "\n";
    //if(argc == 4){}
       // cout << "the int conversion of the quantum is: " << blahblah << "\n";
    
    if((temp.compare("rr") == 0 && argc != 4)){
        cout << "please enter  non-zero integer quantum number for the rr policy you are wanting to implement.\n";
        goto exit;
    }
    // all the error checking is done. os now i should send the integer to the scheduler since it passed.....
    if(argc == 4){
        quantum = stoi(argv[3]);
    }
    cout << "quantum is: " << quantum << "\n";
    list_file_parser(processvector);
    for (int i = 0; i < temp_vector.size(); i++)
    {
        cout << "the value in the temp_vector at the " << i << " index is: " << temp_vector.at(i) << "\n";
    }

    vector_populater(temp_vector);
    
    scheduler(pid_vector, arrival_time, burst_time, argv[2], quantum);
    //below is a test to see what is in the temp_vector after calling the list_file_parser
   
    //below is the coordinator that will dictate which scheduling policy is enacted based on the user input.
    coordinator(input_command_number, input_command_strings);
    
    //cout << "the result of multiplying argc by 2 is: " << yah(argc) <<  "\n";
    for (int i = 0; i < argc; i++)
    {
        cout << "the argument is: " << argv[i] << "\n";
        /* code */
    }
    exit:
    return 0;
}//end of main

int sum_for_parser, number_for_parser;
string checker_for_parser;
void list_file_parser(vector<string> processvector){
    for (int i = 0; i < processvector.size(); i++){
    
        string process_string = processvector.at(i);
        sum_for_parser = 0;
            istringstream incoming_stream(process_string); //https://stackoverflow.com/questions/32627181/how-to-count-only-integers-in-a-string?answertab=active#tab-top
            while(incoming_stream >> checker_for_parser){
                istringstream potential_number(checker_for_parser);
                number_for_parser = 0;
                if(potential_number >> number_for_parser){
                    cout << "this is the number: " << number_for_parser << "\n";
                    temp_vector.push_back(number_for_parser);
                    cout << "number has been succesfully added to temp_vector\n";
                }
            }
    }
}


void coordinator(int input_command_number, char **input_command_strings){
        
        int something;
}

void vector_populater(vector<int> temp_vector){
    int i = 0, j = 0;
    cout << "temp_vector size is: " << temp_vector.size() << "\n";
    while(i < temp_vector.size())
    {
        pid_vector.push_back(temp_vector.at(i));
        arrival_time.push_back(temp_vector.at(i + 1));
        burst_time.push_back(temp_vector.at(i + 2));
        cout << "pid_vector: " << pid_vector.at(j) << " arrival_time: " << arrival_time.at(j) << " burst_time: " << burst_time.at(j) << " for index: " << j << " \n";
        i += 3;
        j++;
    }
    
}