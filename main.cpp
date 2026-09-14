#ifdef _WIN32
    #include <windows.h>
#endif
#include<iostream>
#include "link_list.hpp"
#include<limits>
using namespace std;
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RED_BOLD     "\033[31m"
#define GREEN_BOLD   "\033[32m"
#define YELLOW_BOLD  "\033[33m"
#define BLUE_BOLD    "\033[34m"
#define RESET   "\033[0m"


enum TASKSTATUS {
    PENGIND = 1, COMPLETED
};
struct ToDoList
{
    string task;
    TASKSTATUS taskStatus;

    ToDoList(){}
    ToDoList(string task, TASKSTATUS status): task(task), taskStatus(status){}

    bool operator==(const ToDoList& other) const {
        return task == other.task && taskStatus == other.taskStatus;
    }

    friend ostream& operator<<(ostream& os, ToDoList& tdl){ 
        os << "{" << tdl.task << ", " << ((tdl.taskStatus == PENGIND) ? "Pending" : "Completed") << "}";
        return os;
    }

    bool operator>(const ToDoList& other) const{
        return taskStatus > other.taskStatus;
    }

};

void displayMenu(){
    cout << GREEN;
    cout << "\t\t┌──────────────────────────────────────────────────────┐\n";
    cout << "\t\t│  1. Add Task                                         │\n";
    cout << "\t\t│  2. View All Tasks                                   │\n";
    cout << "\t\t│  3. Update Task                                      │\n";
    cout << "\t\t│  4. Delete Task                                      │\n";
    cout << "\t\t│  5. Mark Task as Completed                           │\n";
    cout << "\t\t│  6. View Pending Tasks                               │\n";
    cout << "\t\t│  7. View Completed Tasks                             │\n";
    cout << "\t\t│  8. Search Tasks                                     │\n";
    cout << "\t\t│  9. Exit Application                                 │\n";
    cout << "\t\t└──────────────────────────────────────────────────────┘\n";
    cout << RESET;
}

void clearScreen(){
    #ifdef __WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

template <typename T>  
T inputVariable(const string messages){
    T var;
    while(true)
    {
        try{
            cout << BLUE << messages;
            if(!(cin >> var)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Invalid Input");
            }
            cout << RESET;
            break;
        }
        catch (runtime_error& e){
            cerr << RED_BOLD << e.what() << RESET << endl;
        }
    }
    return var;
}


int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    LinkList<ToDoList> tasks;
    ToDoList tdl;
    string task;
    TASKSTATUS taskStatus;
    int chooseStatus;
    int choice;
    do
    {
        displayMenu();
        choice = inputVariable<int>("Enter your choice: ");
        switch (choice)
        {
        case 1:
            /* code */
            task = inputVariable<string>("Enter your task: ");
            cout << YELLOW << "choose 1 for Pending and for Complete" << RESET << endl;
            chooseStatus = inputVariable<int>("Enter your status: ");
            taskStatus = static_cast<TASKSTATUS>(chooseStatus);
            tdl = {task, taskStatus};
            tasks.display();
            break;
        
        default:
            cout << RED << "Invalid Input" << RESET << endl;
            break;
        }
    } while (choice != 9);

    
    return 0;
}