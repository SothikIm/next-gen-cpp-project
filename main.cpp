#include<iostream>
#include "link_list.hpp"
using namespace std;

enum TASKSTATUS {
    PENGIND, COMPLETE
};

struct ToDoList
{
    string task;
    TASKSTATUS taskStatus;

    ToDoList(string task, TASKSTATUS status): task(task), taskStatus(status){}

    bool operator==(const ToDoList& other) const {
        return task == other.task && taskStatus == other.taskStatus;
    }

    friend ostream& operator<<(ostream& os, ToDoList& tdl){
        os << "{" << tdl.task << ", " << ((tdl.taskStatus == PENGIND) ? "Pending" : "Completed") << "}";
        return os;
    }

};


int main(){

    ToDoList arr[] = {
        {"Dek c", PENGIND}, {"Juk tnam", COMPLETE}, {"pherk", COMPLETE}
    };
    LinkList<ToDoList> tasks(arr, size(arr));
    tasks.pushBack({"Mlbb", PENGIND});
    tasks.display();
    
    tasks.pop_at(tasks.getSize() - 1);
    tasks.display();

    tasks.pop({"Dek c", PENGIND});
    tasks.display();
    cout << tasks.isEmpty() << endl;
    cout << tasks.getSize() << endl;

    tasks.insert({"c bay", PENGIND}, 2);
    tasks.display();

    LinkList<ToDoList>::Iterator itr;
    for(itr = tasks.begin(); itr != tasks.end(); ++itr){
        cout << itr->task << " ";
    }
    cout << endl;
    itr = tasks.begin();
    for(ToDoList& task : tasks){
        if(task.task == "Juk tnam")
            cout << task.task;
    }


    return 0;
}