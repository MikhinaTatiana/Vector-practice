#include "Vector.h"

Vector::Vector(const ValueType* arr, const size_t size, float coef)
{
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;

    if (_size > 0)
    {
        _data = new ValueType[_size];
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = arr[i];
        }
    }
    else
    {
        _data = nullptr;
    }
}

Vector::Vector(const Vector& other)
{
    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;

    if (_size > 0)
    {
        _data = new ValueType[_size];
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = other._data[i];
        }
    }
    else
    {
        _data = nullptr;
    }
}

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
        return *this;

    delete[] _data;

    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;

    if (_size > 0)
    {
        _data = new ValueType[_size];
    }
    else
    {
        _data = nullptr;
    }

    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }

    return *this;
}

Vector::Vector(Vector&& other) noexcept
{
    _data = other._data;
    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this == &other)
        return *this;

    delete[] _data;

    _data = other._data;
    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;

    return *this;
}

Vector::~Vector()
{
    delete[] _data;
}

void Vector::pushBack(const ValueType& value)
{
    if (_size == _capacity)
    {
        size_t newcap;
        if (_capacity == 0)
        {
            newcap = 1;
        }
        else
        {
            newcap = _capacity * _multiplicativeCoef;
        }

        reserve(newcap);
    }

    _data[_size] = value;
    _size++;
}

void Vector::pushFront(const ValueType& value)
{
    insert(value, 0);
}

void Vector::insert(const ValueType& value, size_t pos)
{
    if (pos > _size)
        pos = _size;

    if (_size == _capacity)
    {
        size_t newcap;
        if (_capacity == 0)
        {
            newcap = 1;
        }
        else
        {
            newcap = _capacity * _multiplicativeCoef;
        }

        reserve(newcap);
    }

    for (size_t i = _size; i > pos; i--)
    {
        _data[i] = _data[i - 1];
    }

    _data[pos] = value;
    _size++;
}

void Vector::insert(const ValueType* arr, size_t size, size_t pos)
{
    if (pos > _size)
        pos = _size;

    if (_size + size > _capacity)
    {
        reserve(_size + size);
    }

    for (size_t i = _size; i > pos; i--)
    {
        _data[i + size - 1] = _data[i - 1];
    }

    for (size_t i = 0; i < size; i++)
    {
        _data[pos + i] = arr[i];
    }

    _size += size;
}

void Vector::insert(const Vector& vector, size_t pos)
{
    insert(vector._data, vector._size, pos);
}

void Vector::popBack()
{
    if (_size > 0)
    {
        _size--;
    }
}

void Vector::popFront()
{
    erase(0);
}

void Vector::erase(size_t pos, size_t count)
{
    if (pos >= _size)
        return;

    if (pos + count > _size)
    {
        count = _size - pos;
    }

    for (size_t i = pos; i + count < _size; i++)
    {
        _data[i] = _data[i + count];
    }

    _size -= count;
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    erase(beginPos, endPos - beginPos);
}

size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

double Vector::loadFactor() const
{
    if (_capacity == 0)
    {
        return 0;
    }

    return (double)_size / _capacity;
}

ValueType& Vector::operator[](size_t idx)
{
    return _data[idx];
}

const ValueType& Vector::operator[](size_t idx) const
{
    return _data[idx];
}

long long Vector::find(const ValueType& value) const
{
    for (size_t i = 0; i < _size; i++)
    {
        if (_data[i] == value)
        {
            return i;
        }
    }

    return -1;
}

void Vector::reserve(size_t capacity)
{
    if (capacity <= _capacity)
    {
        return;
    }

    ValueType* tmp = new ValueType[capacity];

    for (size_t i = 0; i < _size; i++)
    {
        tmp[i] = _data[i];
    }

    delete[] _data;
    _data = tmp;
    _capacity = capacity;
}

void Vector::shrinkToFit()
{
    if (_size == _capacity)
    {
        return;
    }

    ValueType* tmp = new ValueType[_size];

    for (size_t i = 0; i < _size; i++)
    {
        tmp[i] = _data[i];
    }

    delete[] _data;
    _data = tmp;
    _capacity = _size;
}

Vector::Iterator::Iterator(ValueType* ptr)
{
    _ptr = ptr;
}

ValueType& Vector::Iterator::operator*()
{
    return *_ptr;
}

const ValueType& Vector::Iterator::operator*() const
{
    return *_ptr;
}

ValueType* Vector::Iterator::operator->()
{
    return _ptr;
}

const ValueType* Vector::Iterator::operator->() const
{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++()
{
    _ptr++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int)
{
    Iterator tmp = *this;
    _ptr++;
    return tmp;
}

bool Vector::Iterator::operator==(const Iterator& other) const
{
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const
{
    return _ptr != other._ptr;
}

Vector::Iterator Vector::begin()
{
    return Iterator(_data);
}

Vector::Iterator Vector::end()
{
    return Iterator(_data + _size);
}
