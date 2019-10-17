#pragma once
#include <utility>
#include <dlfcn.h>
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


/** Type synonym for shared library handler
 *  Requires: #include <dlfcn.h> and -ldl linker flag */
//using LibHandle = std::unique_ptr<void, std::function<void (void*)>>;

//auto loadDLL(const std::string& libPath) -> LibHandle {
//     // Return unique_ptr for RAAI -> Resource Acquisition is Initialization
//     // releasing closing handle when the unique_ptr goes out of scope.
//     return LibHandle(
//             dlopen(libPath.c_str(), RTLD_LAZY),
//             [](void* h){
//                std::cout << " [INFO] Shared library handle released OK." << "\n";
//                dlclose(h);
//             });
//}

///** Load symbol from shared library
//  *  Requires: #include <dlfcn.h> and -ldl linker flag */
//template<typename Function>
//auto loadSymbol(const LibHandle& handle, const std::string& symbol) -> Function* {
//     void* voidptr = dlsym(handle.get(), symbol.c_str());
//     if(voidptr == nullptr)
//       return nullptr;
//     return reinterpret_cast<Function*>(voidptr);
//}


}
