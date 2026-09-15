#include<iostream>
#include<fstream>
#include<cctype>
using namespace std;




void loadCsvFile(){
    ifstream ifs("tasks.csv");
    if(!ifs.is_open()){
        cout << "Hello" << endl;
        return;
    }
    string task;
    string taskStatus;
    while(getline(ifs, task, ',')){
        getline(ifs, taskStatus);
        cout << task << " is " << taskStatus << endl;
    }
}

int main(){

    loadCsvFile();

    return 0;
}