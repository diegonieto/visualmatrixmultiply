#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix
{
protected:
    const int _nrows;
    const int _ncols;
    T *_matrix;
public:
    Matrix(const int nrows, const int ncols) :
    _nrows(nrows), _ncols(ncols)
    {
        _matrix = new T[_nrows*_ncols];
    }

    virtual ~Matrix()
    {
        delete[] _matrix;
    }

    virtual T get(const int i, const int j) const;
    virtual bool set(const int i, const int j, const T value);
};

template <typename T>
T Matrix<T>::get(const int i, const int j) const
{
    return _matrix[i*_ncols+j];
}

template <typename T>
bool Matrix<T>::set(const int i, const int j, const T value)
{
    _matrix[i*_ncols+j] = value;
    return true;
}

#endif // MATRIX_H
