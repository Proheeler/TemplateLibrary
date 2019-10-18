#pragma once
#include <vector>
#include <stdexcept>
namespace va_temps
{
template <typename T,int size=2>
class Vector{
public:
    explicit Vector(std::initializer_list<T> data)
    {
        vect=(data.size()==size)?std::vector(data):std::vector(size,0);
    }
    void Add(Vector const &v)
    {
        if(v.vect.size()==vect.size())
        {
            for(size_t i=0;i<vect.size();++i)
            {
                vect.at(i)+=v.vect.at(i);
            }
        }
        else
        {
            throw std::invalid_argument("Dims are not the same");
        }
    }
    void Substract(Vector const &v)
    {
        if(v.vect.size()==vect.size())
        {
            for(size_t i=0;i<vect.size();++i)
            {
                vect.at(i)-=v.vect.at(i);
            }
        }
        else
        {
            throw std::invalid_argument("Dims are not the same");
        }
    }
    auto ScalarMultiply(Vector const &v)
    {
        if(v.vect.size()==vect.size())
        {
        double product = 0;
        for (size_t i = 0; i < v.vect.size(); i++)
                product += (v.vect[i])*(vect[i]);
        return product;
        }
        throw std::invalid_argument("Dims are not the same");
    }
    auto VectorMultiply(Vector const &v)
    {
        Vector tmp=*this;
        for (size_t i = 0; i < vect.size(); i++)
            tmp.vect.at(i)= vect[i+1]*v.vect[i+2]-vect[i+2]*v.vect[i+1];
        return tmp;

    }
    std::vector<T> getVect() const
    {
        return vect;
    }

private:
    std::vector<T> vect;
};



}
