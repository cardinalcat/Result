#include <experimental/source_location>
#include<iostream>
#include <string.h>
using namespace std;
enum ResState {Error, Okay};
enum OpState {Valid, Void};
void panic(const std::experimental::source_location& location);
void panic(string msg, const std::experimental::source_location& location);
template<typename T> class Result{
    public:
        Result(ResState st, T val);
        Result(ResState st);
        T unwrap(const std::experimental::source_location& location = std::experimental::source_location::current());
        T expect(string, const std::experimental::source_location& location = std::experimental::source_location::current());
        Result<T> Err(T val);
        Result<T> Ok(T val);
        bool operator == (const ResState &st){
            return this->state == st;
        }
    private:
        T data;
        ResState state;
};
template<class T> class Option{
    public:
        Option(OpState st, T val);
        Option(OpState st);
        T unwrap(const std::experimental::source_location& location = std::experimental::source_location::current());
        T expect(string, const std::experimental::source_location& location = std::experimental::source_location::current());
        static Option<T> Some(T val);
    private:
        T data;
        OpState state;
};
template<typename T> const Option<T> None = Option<T>(OpState::Void);