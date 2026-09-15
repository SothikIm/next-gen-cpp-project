#ifdef _WIN32
    #include <windows.h>
#endif
#include<iostream>
#include "link_list.hpp"
#include<limits>
#include <conio.h>
#include<fstream>
using namespace std;
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RED_BOLD     "\033[1;31m"
#define GREEN_BOLD   "\033[1;32m"
#define YELLOW_BOLD  "\033[1;33m"
#define BLUE_BOLD    "\033[1;34m"
#define RESET   "\033[0m"

template <typename T>  
T inputVariable(const string messages);
void pressSpaceToContinue();

enum TASKSTATUS {
    PENDING = 1, COMPLETED
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
        os << "{" << tdl.task << ", " << ((tdl.taskStatus == PENDING) ? "Pending" : "Completed") << "}";
        return os;
    }
    
    bool operator>(const ToDoList& other) const{
        return taskStatus > other.taskStatus;
    }
    
    friend istream& operator>>(istream& is, ToDoList& tdl){
        cout << BLUE << "Enter your task: ";
        getline(is >> ws, tdl.task);
        
        int chooseStatus;
        while (true)
        {
            /* code */
            cout << YELLOW << "Enter your status (1 = Pending, 2 = Complete): " << RESET;
            if(!(is >> chooseStatus)){
                is.clear();
                is.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED_BOLD << "Invalid input, please input a number" << RESET << endl;
                continue;
            }
            if(chooseStatus != static_cast<int>(TASKSTATUS::PENDING) && chooseStatus != static_cast<int>(TASKSTATUS::COMPLETED)){
                is.clear();
                is.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED_BOLD << "Invalid input, please enter 1 or 2" << RESET << endl;
                continue;
            }
            is.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        tdl.taskStatus = static_cast<TASKSTATUS>(chooseStatus);
        return is;
    }
};
LinkList<ToDoList> loadCsvFile();

// Sambath
void markTaskComplete(LinkList<ToDoList>& tasks, string taskName){
    if(tasks.isEmpty()){
        cout << YELLOW << "No tasks available." << endl << RESET;
        return;
    }
    for (auto itr = tasks.begin(); itr != tasks.end(); ++itr){
        if(itr->task == taskName && itr->taskStatus == COMPLETED){
            cout << YELLOW << "Task \"" << taskName << "\" already completed." << endl << RESET;
            return;
        }
        else if (itr->task == taskName){
            itr->taskStatus = COMPLETED;
            cout << GREEN << "Task \"" << taskName << "\" marked as complete." << endl << RESET;
            return;
        }
    }
    cout << RED_BOLD << "Task \"" << taskName << "\" not found." << endl << RESET;
}

void viewPendingTasks(LinkList<ToDoList>& tasks){
    cout << "Pending Tasks: " << endl;
    for(auto itr = tasks.begin(); itr != tasks.end(); ++itr){
        if(itr->taskStatus == PENDING){
            cout << "\t\t" << itr->task << endl;
        }   
    }
    cout << endl;
}

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
    cout << "\t\t│  9. Save Task                                        │\n";
    cout << "\t\t│  10. Exit Application                                 │\n";
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

int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    LinkList<ToDoList> tasks = loadCsvFile();
    tasks.display();
    ToDoList tdl;
    ToDoList oldTdl;
    string task;

    int choice;
    do
    {
        displayMenu();
        choice = inputVariable<int>("Enter your choice: ");
        switch (choice)
        {
        case 1:
            /* code */
            cin >> tdl;
            tasks.pushBack(tdl);
            break;
        case 2:
            clearScreen();
            cout << BLUE;
            tasks.display();
            pressSpaceToContinue();
            cout << RESET;
            break;
        case 3: // Update task (Nyta)
            cout << GREEN << "Input your old task" << RESET << endl;
            cin >> oldTdl;
            
            cout << GREEN << "Input your old task" << RESET << endl;
            cin >> tdl;
            tasks.update(oldTdl, tdl);
            break;
        case 4: // Delete task (Nyta)
            cin >> tdl;
            tasks.pop(tdl);
            break;
        case 5: // Mark task as complete (Sambath)
            task = inputVariable<string>("Enter your task name: ");
            markTaskComplete(tasks, task);
            break;
        case 6: // View all pending task (Sambath)
            clearScreen();
            if(!tasks.isEmpty())
                viewPendingTasks(tasks);
            else
                cout << RED << "The task is empty" << endl << RESET;
            pressSpaceToContinue();
            break;
        case 7:
            break;
        case 8:
            break;
        case 10:
            cout << GREEN_BOLD << "System Exit" << endl << RESET;
            break;
        default:
            cout << RED << "Invalid Input" << RESET << endl;
            break;
        }
    } while (choice != 10);

    
    return 0;
}

template <typename T>  
T inputVariable(const string messages){
    T var;
    while(true)
    {
        try{
            cout << BLUE << messages;
            // constexpr means “this can be evaluated at compile time.”
            if constexpr (is_same_v<T, string>){ 
                // ws mean remove whitespace in input buffer
                getline(cin >> ws, var); 
                while (!var.empty() && var.back() == ' ')
                {
                    var.pop_back();
                }
            }
            else{
                if(!(cin >> var)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw runtime_error("Invalid Input");
                }
                cout << RESET;
            }
            break;
        }
        catch (runtime_error& e){
            cerr << RED_BOLD << e.what() << RESET << endl;
        }
    }
    return var;
}

void pressSpaceToContinue(){
    cout << GREEN_BOLD << "Press space to continue: ";
    while (true)
    {
        char key = _getch();
        if(key == ' ')
            break;
    }
    cout << endl;
}

LinkList<ToDoList> loadCsvFile(){
    ifstream ifs("tasks.csv");
    LinkList<ToDoList> tasks;
    try{
        if(!ifs.is_open()){
            cout << "Hello" << endl;
            throw runtime_error("File Not Found.");
        }
        ToDoList tdl;
        TASKSTATUS status;
        string task;
        string taskStatus;
        while(getline(ifs, task, ',')){
            getline(ifs, taskStatus);
            status = (taskStatus == "Completed") ? COMPLETED : PENDING;
            tdl = {task, status};
            tasks.pushBack(tdl);
        }
    }
    catch (runtime_error& e){
        cerr << RED_BOLD << e.what() << RESET << endl;
    }
    return tasks;
}