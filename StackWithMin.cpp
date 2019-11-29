#include <deque>

template <typename T>
class StackWithMin
{
public:
    StackWithMin() {}
    virtual ~StackWithMin() {}

    T& top();
    const T& top() const;
    const T& min() const;
    void push(const T& value);
    void pop();

private:
    std::deque<T> _data;
    std::deque<int> _min_index;
}

template<typename T>
T& StackWithMin<T>::top()
{
    return _data.back();
}

template<typename T>
const T& StackWithMin<T>::top() const
{
    return _data.back();
}

template<typename T>
const T& StackWithMin<T>::min()
{
    return _data.at(_min_index.back());
}

template<typename T>
void StackWithMin<T>::push(const T& value)
{
    _data.push_back(value);
    if (_min_index.empty())
        _min_index.push_back(0);
    else
    {
        if (value < _data.at(_min_index.back()))
            _min_index.push_back(_data.size()-1);
        else
            _min_index.push_back(_min_index.back());
    }
}

template<typename T>
void StackWithMin<T>::pop()
{
    _data.pop_back();
    _min_index.pop_back();
}
