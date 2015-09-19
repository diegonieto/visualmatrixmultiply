#ifndef POINT_H
#define POINT_H

template <class T>
class Point
{
    const int _row;
    const int _column;
    const T _value;

public:
    Point(int row, int col, T value)
        : _row(row), _column(col), _value(value) {};
    int getRow() const;
    int getCol() const;
    T getValue() const;
};

template <typename T>
int Point<T>::getRow() const
{
    return _row;
}

template <typename T>
int Point<T>::getCol() const
{
    return _column;
}

template <typename T>
T Point<T>::getValue() const
{
    return _value;
}

#endif // POINT_H
