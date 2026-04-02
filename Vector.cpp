#include "Vector.h"

// конструктор с массивом
Vector::Vector(const ValueType* rawArray, const size_t size, float coef)
{
    _size = size;
    _capacity = size;
    _multiplicativeCoef = coef;

    if (_size > 0)
    {
        _data = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++)
            _data[i] = rawArray[i];
    }
}

// копирующий конструктор
Vector::Vector(const Vector& other)
{
    _size = other._size;
    _capacity = other._size;
    _multiplicativeCoef = other._multiplicativeCoef;

    if (_size > 0)
    {
        _data = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }
}

// оператор копирования
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
        _data = new ValueType[_capacity];
        for (size_t i = 0; i < _size; i++)
            _data[i] = other._data[i];
    }
    else
        _data = nullptr;

    return *this;
}

// конструктор перемещения
Vector::Vector(Vector&& other) noexcept
{
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

// оператор перемещения
Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this == &other)
        return *this;

    delete[] _data;

    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    _multiplicativeCoef = other._multiplicativeCoef;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;

    return *this;
}

// деструктор
Vector::~Vector()
{
    delete[] _data;
}

// pushBack
void Vector::pushBack(const ValueType& value)
{
    if (_size == _capacity)
    {
        size_t newCap = (_capacity == 0) ? 1 : _capacity * _multiplicativeCoef;
        reserve(newCap);
    }

    _data[_size] = value;
    _size++;
}

// pushFront
void Vector::pushFront(const ValueType& value)
{
    insert(value, 0);
}

// вставка одного элемента
void Vector::insert(const ValueType& value, size_t pos)
{
    if (pos > _size)
        pos = _size;

    if (_size == _capacity)
    {
        size_t newCap = (_capacity == 0) ? 1 : _capacity * _multiplicativeCoef;
        reserve(newCap);
    }

    for (size_t i = _size; i > pos; i--)
        _data[i] = _data[i - 1];

    _data[pos] = value;
    _size++;
}

// вставка массива
void Vector::insert(const ValueType* values, size_t size, size_t pos)
{
    if (pos > _size)
        pos = _size;

    if (_size + size > _capacity)
        reserve(_size + size);

    for (size_t i = _size; i > pos; i--)
        _data[i + size - 1] = _data[i - 1];

    for (size_t i = 0; i < size; i++)
        _data[pos + i] = values[i];

    _size += size;
}

// вставка вектора
void Vector::insert(const Vector& vector, size_t pos)
{
    insert(vector._data, vector._size, pos);
}

// popBack
void Vector::popBack()
{
    if (_size > 0)
        _size--;
}

// popFront
void Vector::popFront()
{
    erase(0);
}

// erase
void Vector::erase(size_t pos, size_t count)
{
    if (pos >= _size)
        return;

    if (pos + count > _size)
        count = _size - pos;

    for (size_t i = pos; i + count < _size; i++)
        _data[i] = _data[i + count];

    _size -= count;
}

// eraseBetween
void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (endPos > _size)
        endPos = _size;

    erase(beginPos, endPos - beginPos);
}

// size
size_t Vector::size() const
{
    return _size;
}

// capacity
size_t Vector::capacity() const
{
    return _capacity;
}

// loadFactor
double Vector::loadFactor() const
{
    if (_capacity == 0)
        return 0;
    return (double)_size / _capacity;
}

// operator[]
ValueType& Vector::operator[](size_t idx)
{
    return _data[idx];
}

const ValueType& Vector::operator[](size_t idx) const
{
    return _data[idx];
}

// find
long long Vector::find(const ValueType& value) const
{
    for (size_t i = 0; i < _size; i++)
        if (_data[i] == value)
            return i;

    return -1;
}

// reserve
void Vector::reserve(size_t capacity)
{
    if (capacity <= _capacity)
        return;

    ValueType* newData = new ValueType[capacity];

    for (size_t i = 0; i < _size; i++)
        newData[i] = _data[i];

    delete[] _data;

    _data = newData;
    _capacity = capacity;
}

// shrinkToFit
void Vector::shrinkToFit()
{
    if (_capacity == _size)
        return;

    ValueType* newData = new ValueType[_size];

    for (size_t i = 0; i < _size; i++)
        newData[i] = _data[i];

    delete[] _data;

    _data = newData;
    _capacity = _size;
}

// ===== Iterator =====

Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}

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
    Iterator temp = *this;
    _ptr++;
    return temp;
}

bool Vector::Iterator::operator==(const Iterator& other) const
{
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const
{
    return _ptr != other._ptr;
}

// begin
Vector::Iterator Vector::begin()
{
    return Iterator(_data);
}

// end
Vector::Iterator Vector::end()
{
    return Iterator(_data + _size);
}