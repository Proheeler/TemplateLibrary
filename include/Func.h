#pragma once
namespace var_temps
{
template <typename T,typename... U>
void filterFold(T& val, U ... args)
{
    return (args(val), ...);
}
}
