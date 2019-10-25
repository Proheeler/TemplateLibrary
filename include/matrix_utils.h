#pragma once
#include <algorithm>
#include "matrix.h"
namespace va_temps {
// Получение матрицы без i-й строки и j-го столбца
template <typename T>
Matrix<T> GetMatr(Matrix<T> const & mat,int i, int j) {
    auto data = mat.getData();
    Matrix<T> t(mat.getRows()-1,mat.getRows()-1);
    t.data_.resize((mat.getRows()-1)*(mat.getRows()-1));
    for(int ki=0;ki<mat.getRows();++ki){
//        if(ki==i) data.at(ki)=-99999;
        for(int kj=0;kj<mat.getRows();++kj)
        {
            if(kj==j) data.at(kj+ki*mat.getRows())=-99999;
//            if(ki==i)data.at(ki+kj*mat.getRows())=-99999;
        }
    }
        for(int ki=0;ki<mat.getRows();++ki){
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
    if (rows_ == 2) return ((mat.getData()[0] * mat.getData()[3]) - (mat.getData()[1] * mat.getData()[2]));
    else
    {
        int k=1;
        for (int i = 0; i<rows_; i++) {
            auto p = GetMatr(mat,0,i);
            d = d + k * mat.getData().at(i)* Det(p, rank-1);
            k = -k;
        }
        return d;
    }
}
}
