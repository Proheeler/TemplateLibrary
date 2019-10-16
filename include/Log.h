#include <iostream>
#include <vector>
using namespace std;

namespace var_temps {

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

}
