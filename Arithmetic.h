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

    template <typename T>
    void log(T val)
    {
       std::cout<<val<<" ";
    }
    template <typename T,typename... U>
    void log(T val, U ... args)
    {
       std::cout<<val<< " ";
       log(args...);
       std::cout<<std::endl;
    }
    template <typename... T>
    void logFold(T ... val)
    {
       (std::cout<< ... <<(val))<<'\n';
    }
    template<typename T, typename... Args>
    void push_back_vec(std::vector<T>& v, Args&&... args)
    {
        (v.push_back(args), ...);
    }

}
