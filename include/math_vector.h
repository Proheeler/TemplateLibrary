#pragma once
#include <vector>
#include <stdexcept>
#include <cassert>
#include <algorithm>
#include "matrix.h"
namespace var_temps
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
    auto MixedVectorProduct(Vector  &v_dot,Vector  &v_cross) const
    {
        assert(vect.size() == v_dot.vect.size() && vect.size() == v_cross.vect.size());
        Matrix<T> mat(vect.size(),vect.size());
        std::vector<T> tmp(vect);
        tmp.resize(vect.size()+v_dot.vect.size()+v_cross.vect.size());
        for(size_t i=0;i<vect.size();++i)
        {
            tmp.at(i+vect.size()) = v_dot.vect.at(i);
            tmp.at(i+2*vect.size()) = v_cross.vect.at(i);
        }
        mat.setData(tmp);
        return Det(mat,mat.getRows());

    }
    auto Multiply(Matrix<T> const & mat) const
    {
        assert(vect.size()==mat.getCols());
        Vector<T> tmp{};
        std::vector<T> tmp_vector;
        tmp_vector.resize(vect.size());

        for(size_t row=0;row<mat.getRows();++row)
        {
            for(size_t col=0;col<mat.getCols();++col)
            {
                tmp_vector.at(row)+=mat.getData().at(col+mat.getCols()*row)*vect.at(col);
            }
        }
        tmp.setVect(tmp_vector);
        return tmp;
    }
    auto Multiply(T const & value) const
    {
        Vector tmp(*this);
        for(size_t index=0;index<vect.size();++index)
        {
            tmp.vect.at(index) =value*vect.at(index);
        }

        return tmp;
    }
    std::vector<T> getVect() const
    {
        return vect;
    }
    void Print() const
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
