#pragma once
#include <vector>
#include <stdexcept>
#include <cassert>
namespace va_temps
{
template <typename T>
class Vector
{
public:
    explicit Vector(std::initializer_list<T> data)
    {
        vect=std::vector(data);
    }
    auto Add(Vector const &v) const
    {
        assert(v.vect.size() == vect.size());
        Vector tmp=*this;
        for(size_t i=0;i<vect.size();++i)
        {
            tmp.vect.at(i)+=v.vect.at(i);
        }
        return tmp;
    }
    auto Substract(Vector const &v) const
    {
        assert(v.vect.size() == vect.size());
        Vector tmp=*this;
        for(size_t i=0;i<vect.size();++i)
        {
            tmp.vect.at(i)-=v.vect.at(i);
        }
        return tmp;
    }

    auto ScalarProduct(Vector const &v) const
    {
        assert(v.vect.size() == vect.size());
        double product = 0;
        for (size_t i = 0; i < v.vect.size(); i++)
            product += (v.vect[i])*(vect[i]);
        return product;
    }

    auto VectorProduct(Vector const &v) const
    {
        assert(v.vect.size() == vect.size());
        Vector tmp=*this;
        for (size_t i = 0; i < vect.size(); i++)
            tmp.vect.at(i)= vect[i+1]*v.vect[i+2]-vect[i+2]*v.vect[i+1];
        return tmp;
    }
    auto MixedVectorProduct(Vector const &v_,Vector const &v) const
    {

    }
    std::vector<T> getVect() const
    {
        return vect;
    }
    void Print()
    {
        for(auto &i:vect)
            cout<<i<<" ";
        cout<<endl;
    }

    void setVect(const std::vector<T> &value)
    {
        vect = value;
    }

private:
    std::vector<T> vect;
};




}
