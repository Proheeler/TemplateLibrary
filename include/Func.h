#pragma once
#include <utility>
namespace var_temps
{

template<class A, class F>
auto functionPipeline( A& t, F& f )
{
    f( t );
}
template<class A>
auto functionPipeline( A&& t )
{
    return t;
}
template<class A, class F, class ...Fns>
auto functionPipeline( A&& t, F& f, Fns... fns )
{
    return functionPipeline( f( t ), fns... );
}


template <typename T,typename... U>
void filterFold(T& val, U ... args)
{
    return (args(val), ...);
}



}
