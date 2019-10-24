#include <cstdint>
#include <vector>
#include <cassert>
#include "math_vector.h"
namespace va_temps {
template <typename T>
class Matrix
{
public:
    Matrix():rows_(0),cols_(0),data_(std::vector<T>()){}
    Matrix(T* pointer,std::size_t rows,std::size_t cols):rows_(rows),cols_(cols),data_(std::vector<T>(pointer,pointer+rows*cols)){}
    Matrix(std::initializer_list<T> data,std::size_t rows,std::size_t cols):rows_(rows),cols_(cols),data_(std::vector<T>(data)) {}
    void Print()
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
    auto Add(Matrix const & m)
    {
        Matrix tmp(*this);
        for(size_t i=0;i<rows_*cols_;++i)
        {
            tmp.data_.at(i)+=m.data_.at(i);
        }
        return tmp;
    }

    auto Substract(Matrix const & m)
    {
        Matrix tmp(*this);
        for(size_t i=0;i<rows_*cols_;++i)
        {
            tmp.data_.at(i)-=m.data_.at(i);
        }
        return tmp;
    }
    auto Multiply(Matrix const & m)
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
    template <typename U>
    auto Multiply(U const & value)
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
    auto Multiply(Vector<T> const & vect)
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

    auto Transpose()
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

private:
    std::size_t rows_;
    std::size_t cols_;
    std::vector<T> data_;
};



}
