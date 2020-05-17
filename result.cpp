#include<stdlib.h>
#include<iostream>
#include "./headers/result.hpp"
using namespace std;
//using namespace result;

void panic(string msg, const std::experimental::source_location& location){
    cout << msg << " file: " << location.file_name() << " line: " << location.line() << endl;
    exit(-1);
}
void panic(const std::experimental::source_location& location){
    cout << "panic at: file: " << location.file_name() << " line: " << location.line() << endl;
    exit(-1);
}
template<typename T> Result<T>::Result(ResState st, T val){
    state = st;
    data = val;
}
template<typename T> Result<T>::Result(ResState st){
    state = st;
}
template<typename T> T Result<T>::unwrap(const std::experimental::source_location& location){
    if (this->state == Okay){
        return this->data;
    }else{
        panic("called Result::unwrap() on an error value at", location);
    }
}
template<typename T> T Result<T>::expect(string msg, const std::experimental::source_location& location){
    if(this->state == Error){
        panic(msg, location);
    }
    return this->data;
}
template<typename T> Result<T> Result<T>::Err(T val){
    return Result<T>(ResState::Error, val);
}
template<typename T> Result<T> Result<T>::Ok(T val){
    return Result<T>(ResState::Okay, val);
}
template<typename T> T Option<T>::unwrap(const std::experimental::source_location& location){
    if (this->state == Void){
        panic("called Option::unwrap() on a None value at", location);
    }
    return this->data;
}
template<typename T> T Option<T>::expect(string msg, const std::experimental::source_location& location){
    if (this->state == Some){
        return this->data;
    }else{
        panic(msg, location);
    }
}
template<typename T> Option<T>::Option(OpState st, T val){
    state = st;
    data = val;
}
template<typename T> Option<T>::Option(OpState st){
    state = st;
}
template<typename T> Option<T> Option<T>::Some(T val){
    return Option<T>(OpState::Some, val);
}
