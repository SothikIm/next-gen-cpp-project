#pragma once

#include<iostream>
#include<list>
using namespace std;

template <typename T>
class LinkList{
private:
    struct Node{
        T data;
        Node* next;
        Node(const T& d): data(d), next(nullptr){}
    };

    int size;
    Node* head;
    Node* tail;
public:
    LinkList(const T& d): size(0), head(new Node(d)), tail(head) {}

    LinkList(): head(nullptr), tail(nullptr), size(0){}
    

    LinkList(const T* arr, const int size): size(size){
        if(size == 0 || !arr){
            head = nullptr;
            tail = nullptr;
            return;
        }

        head = new Node(arr[0]);
        tail = head;
        for(int i = 1; i < size; i++){
            Node* t = new Node(arr[i]);
            tail->next = t;
            tail = t;
        }
    }

    int getSize(){
        return size;
    }

    void display(){
        cout << "[";
        for(Node* p = head; p != nullptr; p = p->next){
            if(p != head){
                cout << ", ";
            }
            cout << p->data;
        }
        cout << "]" << endl;
    }

    void pushBack(const T& val){
        Node* t = new Node(val);
        if(!head){
            head = t;
            tail = head;
        }
        else{
            tail->next = t;
            tail = t;
        }
        size++;
    }

    void pushFront(const T& val){
        Node* t = new Node(val);
        t->next = head;
        head = t;
        if (!tail)
            tail = t;
        size++;
    }

    void insert(const T& val, const int& index){
            try{
                if(index > size || index < 0)
                    throw invalid_argument("IndexError");
                else if(index == 0){
                    pushFront(val);
                    return;
                }
                else if(index == size){
                    pushBack(val);
                    return;
                }
                Node* p = head;
                for(int pos = 0; pos < index - 1; pos++){
                    p = p->next;
                }
                Node* t = new Node(val);
                t->next = p->next;
                p->next = t;
                size++;
                
            }
            catch (invalid_argument& e){
                cerr << e.what() << endl;
            }
        }

        Node* find(const T& key) {
            for (Node* i = head; i != nullptr; i = i->next) {
                if (i->data == key)
                    return i;
            }
        
            return nullptr;
        }

        bool isEmpty(){
            return !head;
        }

        // void sort(){
        //     // bubble sort
        //     if(!head || !head->next)
        //         return;
        //     bool swapped;

        //     do
        //     {
        //         swapped = false;
        //         Node* cur = head;
        //         Node* prev = nullptr;
        //         while (cur->next)
        //         {
        //             Node* next = cur->next;
        //             if(cur->data > next->data){
        //                 cur->next = next->next;
        //                 next->next = cur;
        //                 if(prev == nullptr)
        //                     head = next;
        //                 else
        //                     prev->next = next;
        //                 prev = next;
        //                 swapped = true;
        //             }
        //             else{
        //                 prev = cur;
        //                 cur = cur->next;
        //             }
        //         }
                
        //     } while (swapped);
            
        // }

        void pop(const T& key){
            if(!head)
                return;
            else if(key == head->data){
                Node* p = head->next;
                delete head;
                head = p;
                if(!head)
                    tail = nullptr;
                size--;
            }
            else{
                Node* cur = head->next;
                Node* prev = head;
                while(cur != nullptr){
                    if(key == cur->data){
                        if(cur == tail)
                            tail = prev;
                        prev->next = cur->next;
                        delete cur;
                        size--;
                        break;
                    }else{
                        prev = cur;
                        cur = cur->next;
                    }
                }
            }
        }

        void pop_at(const int& index){
            if(index >= size || index < 0)
                return;
            Node* cur = head;
            Node* prev = nullptr;
            for(int i = 0; i < index; i++){
                prev = cur;
                cur = cur->next;
            }

            if(prev){
                prev->next = cur->next;
            }
            else{
                head = cur->next;
            }

            if(cur == tail)
                tail = prev;
            delete cur;
            size--;
        }

        void clear(){
            Node* cur = head;
            while(cur){
                Node* next = cur->next;
                delete cur;
                cur = next;
            }
            head = nullptr;
            tail = head;
            size = 0;
        }

        ~LinkList(){
            clear();
        }
};