#include <iostream>
#include <vector>
using namespace std;

namespace var_temps {

    template<typename T, typename... Args>
    void push_back_vec(std::vector<T>& v, Args&&... args)
    {
        (v.push_back(args), ...);
    }

}
