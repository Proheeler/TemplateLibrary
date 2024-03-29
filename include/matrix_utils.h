#pragma once
#include <algorithm>
#include <type_traits>
#include "matrix.h"
namespace var_temps {

template <typename T>
Matrix<T> CoFractor(Matrix<T> const & mat,size_t i, size_t j) {
    assert(mat.getCols()==mat.getRows());
    auto data = mat.getData();
    Matrix<T> t(mat.getRows()-1,mat.getRows()-1);
    t.data_.resize((mat.getRows()-1)*(mat.getRows()-1));
    for(size_t ki=0;ki<mat.getRows();++ki){
        for(size_t kj=0;kj<mat.getRows();++kj)
        {
            if(kj==j) data.at(kj+ki*mat.getRows())=-99999;
        }
    }
    for(size_t ki=0;ki<mat.getRows();++ki){
        data.at(ki+i*mat.getRows())=-99999;
    }

    data.erase(std::remove_if(data.begin(),data.end(),[](auto i){return i==-99999;}),data.end());
    t.setData(data);
    return t;
}




template <typename T>
auto Det(Matrix<T> const & mat,int rank)
{
    int rows_ = mat.getRows();
    int cols_ = mat.getCols();
    assert(rows_==cols_);
    T d(0);
    if(rows_<=0)
        throw std::exception();
    if(rows_==1)
        return mat.getData().at(0);
    if (rows_ == 2) return ((mat.getData()[0] * mat.getData()[3])- (mat.getData()[1] * mat.getData()[2]));
    else
    {
        int k=1;
        for (int i = 0; i<rows_; i++) {
            auto p = CoFractor(mat,0,i);
            d = d + k * mat.getData().at(i)* Det(p, rank-1);
            k = -k;
        }
        return d;
    }
}
template <typename T>
Matrix<T> AdjugateMatrix(Matrix<T> const & mat)
{
    Matrix<T> retMat(mat);
    int k=1;
    for(size_t ki=0;ki<mat.getRows();++ki){
        for(size_t kj=0;kj<mat.getCols();++kj)
        {
            auto cofactor = CoFractor(mat,ki,kj);
            retMat.data_.at(ki+kj*mat.getRows())=k*Det(cofactor,cofactor.getRows());
            k=-k;
        }
    }
    return retMat;

}

template <typename T>
auto InverseMatrix(Matrix<T> const & mat)
{
    return AdjugateMatrix(mat).Divide(Det(mat,mat.getRows()));
}

template <typename T>
void ApplyKernel(Matrix<T*> const & mat ,Matrix<T> const & kernel)
{
    size_t sizeKernel = kernel.getRows()*kernel.getCols();
    size_t sizeMat = mat.getRows()*mat.getCols();
    auto data=mat.getData();
    auto kern = kernel.getData();
    assert(mat.getRows()>= kernel.getRows() && mat.getCols()>=kernel.getCols());
    assert(kernel.getRows() %2!=0 && kernel.getCols() %2!=0);
    if(sizeKernel==1)
    {
        for(size_t i=0;i<sizeMat;++i)
        {
            *data[i]+=(*data[i]*kern[0]);
        }
    }
    else if(sizeKernel>1)
    {
        for(size_t ki=1;ki<mat.getRows()-1;++ki){
            for(size_t kj=1;kj<mat.getCols()-1;++kj)
            {
                auto sub = mat.getSubMatrix(ki-1,ki+kernel.getRows()-2,kj-1,kj+kernel.getCols()-2);
                auto dataSub = sub.getData();
                *data[ki+kj*mat.getRows()]=0;
                for(size_t i=0;i<sub.getRows();++i){
                    for(size_t j=0;j<sub.getCols();++j)
                    {
                        *data[ki+kj*mat.getRows()]+=(*dataSub[i+j*sub.getRows()]) *kern.at(i+j*sub.getRows());
                    }
                }
            }
        }

    }
}



}
