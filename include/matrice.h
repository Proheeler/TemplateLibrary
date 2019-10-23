#include <cstdint>
#include <vector>
#include <cassert>
namespace va_temps {
template <typename T,std::size_t rows,std::size_t cols>
class Matrix
{
public:
    Matrix(std::initializer_list<T> data):rows_(rows),cols_(cols),data_(std::vector<T>(data)) {}
    void Print()
    {
        for(size_t row=0;row<rows_;++row)
        {
            for(size_t col=0;col<cols_;++col)
            {
                std::cout<<data_.at(col+cols*row)<<" ";
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
    template <typename U,size_t t_rows,size_t t_cols>
    auto Multiply(Matrix<U,t_rows,t_cols> const & m)
    {
      assert(this->cols_ == m.getRows());
      Matrix tmp(*this);
      tmp.data_.clear();
      tmp.data_.resize(cols*m.getRows(),0);
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
