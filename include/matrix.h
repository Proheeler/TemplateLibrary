#pragma once
#include <cstdint>
#include <vector>
#include <cassert>

#include <math.h>
namespace va_temps {

template <typename T>
class Vector;





template <typename T>
class Matrix
{
public:
    Matrix():rows_(0),cols_(0),data_(std::vector<T>()){}
    Matrix(std::size_t rows,std::size_t cols):rows_(rows),cols_(cols),data_(std::vector<T>()){}
    Matrix(T* pointer,std::size_t rows,std::size_t cols):rows_(rows),cols_(cols),data_(std::vector<T>(pointer,pointer+rows*cols)){}
    Matrix(std::initializer_list<T> data,std::size_t rows,std::size_t cols):rows_(rows),cols_(cols),data_(std::vector<T>(data)) {}
    void Print() const
    {
        for(size_t row=0;row<rows_;++row)
        {
            for(size_t col=0;col<cols_;++col)
            {
                std::cout<<data_.at(col+cols_*row)<<" ";
            }
            std::cout<<endl;
        }
    }
    auto Add(Matrix const & m) const
    {
        Matrix tmp(*this);
        for(size_t i=0;i<rows_*cols_;++i)
        {
            tmp.data_.at(i)+=m.data_.at(i);
        }
        return tmp;
    }

    auto Substract(Matrix const & m) const
    {
        Matrix tmp(*this);
        for(size_t i=0;i<rows_*cols_;++i)
        {
            tmp.data_.at(i)-=m.data_.at(i);
        }
        return tmp;
    }
    auto Multiply(Matrix const & m) const
    {
        assert(this->cols_ == m.getRows());
        Matrix tmp(*this);
        tmp.data_.clear();
        tmp.data_.resize(cols_*m.getRows(),0);
        for(size_t row=0;row<rows_;++row)
        {
            for(size_t col=0;col<m.getCols();++col)
            {
                T sum(0);
                for(size_t row_=0;row_<m.getRows();++row_)
                    sum+=data_.at(row*cols_+row_)*m.getData().at(row_*m.getCols()+col);
                tmp.data_.at(row*m.getCols()+col) = sum;
            }
        }
        tmp.cols_=m.getRows();
        return tmp;
    }
    auto Multiply(T const & value) const
    {
        Matrix tmp(*this);
        for(size_t row=0;row<rows_;++row)
        {
            for(size_t col=0;col<cols_;++col)
            {
                tmp.data_.at(col+cols_*row) =value*data_.at(col+cols_*row);
            }
        }
        return tmp;
    }
    auto Multiply(Vector<T> const & vect) const
    {
        assert(rows_==vect.getVect().size());
        Vector<T> tmp{};
        std::vector<T> tmp_vector(vect.getVect().size());

        for(size_t row=0;row<rows_;++row)
        {
            for(size_t col=0;col<cols_;++col)
            {
                tmp_vector.at(row)+=data_.at(col+cols_*row)*vect.getVect().at(col);
            }
        }
        tmp.setVect(tmp_vector);
        return tmp;
    }
    auto Divide(T const & value) const
    {
        Matrix<T> tmp(rows_,cols_);
        tmp.data_.resize(rows_*cols_);
        for(size_t row=0;row<rows_;++row)
        {
            for(size_t col=0;col<cols_;++col)
            {
                tmp.data_.at(col+cols_*row) =data_.at(col+cols_*row)/value;
            }
        }
        return tmp;
    }

    auto Transpose() const
    {
        Matrix tmp(*this);
        for(size_t row=0;row<rows_;++row)
        {
            for(size_t col=0;col<cols_;++col)
            {
                tmp.data_.at(col+row*cols_) = data_.at(col*rows_+row);
            }
        }
        return tmp;
    }
    auto getSubMatrix(size_t const & row_start,size_t const & row_end,
                      size_t const & col_start,size_t const& col_end) const
    {
        assert(row_end<rows_ && col_end<cols_ && row_start>=0 && col_start>=0);
        size_t tmp_rows=row_end-row_start+1,tmp_cols =col_end-col_start+1;
        Matrix tmp(tmp_rows,tmp_cols);
        tmp.data_.resize(tmp_rows*tmp_cols);
        int index=0;
        for(size_t row=row_start;row<=row_end;++row)
        {
            for(size_t col=col_start;col<=col_end;++col)
            {
                tmp.data_.at(index)=data_.at(col+row*cols_);
                ++index;
            }
        }
        return tmp;
    }
    std::size_t getRows() const
    {
        return rows_;
    }

    std::size_t getCols() const
    {
        return cols_;
    }

    std::vector<T> getData() const
    {
        return data_;
    }

    void setData(const std::vector<T> &data)
    {
        data_ = data;
    }
    std::vector<T> data_;
private:
    std::size_t rows_;
    std::size_t cols_;

};





}
