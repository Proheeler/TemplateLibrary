#include <iostream>
#include <vector>
using namespace std;

namespace var_temps {

    template<typename T>
    T sum(T first)
    {
        return first;
    }

    template<typename T, typename... Args>
    T sum(T first, Args... args)
    {
        return first + sum(args...);
    }
    template<typename ...Args> auto sumFold(Args ...args)
    {
        return (args + ...);
    }


    template<typename T, typename... Args>
    T minus(T first, Args... args)
    {
        return first - (args + ...);
    }

    template<typename T, typename... Args>
    T plus(T first, Args... args)
    {
        return first + (args + ...);
    }


    template<typename ... Args>
    auto multiply(Args ... args)
    {
        return (args * ...);
    }

//    template<typename T, typename... Args>
//    auto divide(T first,Args ... args)
//    {
//        return ((first/(args...)));
//    }



}
