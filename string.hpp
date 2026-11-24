#pragma once

#include <iostream>
#include <algorithm>
#include <cstring>

class String
{
    private:

    size_t size_;
    size_t capacity_;
    char* data_;

    void ExpandArr(size_t new_capacity_)
    {
        char* new_data_ = new char[new_capacity_ + 1];

        std::copy(data_, data_ + size_ + 1, new_data_);
        new_data_[size_] = '\0';
            
        delete[] data_;

        data_ = new_data_;
        capacity_ = new_capacity_;
    }

    public:

    ~String()
    {
        delete[] data_;
    }

    String() : size_(0), capacity_(0), data_(new char[1])
    {
        data_[0] = '\0';
    }

    String(const char* c) : size_(std::strlen(c)), capacity_(std::strlen(c)), data_(new char[capacity_ + 1]) 
    {
        std::copy(c, c + size_, data_);
        data_[size_] = '\0';
    }

    String(size_t n, char c) : size_(n), capacity_(n), data_(new char[capacity_ + 1])
    {
        std::fill(data_, data_ + size_, c);
        data_[size_] = '\0';
    }

    String(const String& other) : size_(other.size_), capacity_(other.capacity_), data_(new char[capacity_ + 1])
    {
        std::copy(other.data_, other.data_ + size_, data_);
        data_[size_] = '\0';
    }

    String& operator=(const String& other)
    {
        if (this == & other)
        {
            return *this;
        }

        if (capacity_ < other.size_)
        {
            delete[] data_;
            capacity_ = other.size_;
            data_ = new char[capacity_ + 1];
        }

        size_ = other.size_;
        std::copy(other.data_, other.data_ + size_ + 1, data_);
        return *this;
    }

    char& operator[](size_t i)
    {
        return data_[i];
    }

    const char& operator[](size_t i) const
    {
        return data_[i];
    }


    size_t Length() const
    {
        return size_;
    }

    size_t Size() const
    {
        return size_;
    }

    size_t Capacity() const
    {
        return capacity_;
    }

    void PushBack(char c)
    {
        if (size_ == capacity_)
        {
            ExpandArr(capacity_ == 0 ? 2 : capacity_ * 2);
        }

        data_[size_] = c;
        size_ ++;
        data_[size_] = '\0';
    }

    void PopBack()
    {
        if (size_ > 0)
        {
            size_--;
            data_[size_] = '\0';
        }
    }

    char& Front()
    {
        return data_[0];
    }

    const char& Front() const
    {
        return data_[0];
    }

    char& Back()
    {
        return data_[size_ - 1];
    }

    const char& Back() const
    {
        return data_[size_ - 1];
    }

    String& operator+=(char c)
    {
        PushBack(c);
        return *this;
    }

    String& operator+=(const String& other)
    {
        size_t new_size_ = size_ + other.size_;
        if (new_size_ > capacity_)
        {
            ExpandArr(std::max(capacity_ * 2, new_size_));
        }

        std::copy(other.data_, other.data_ + other.size_, data_ + size_);
        size_ = new_size_;
        data_[size_] = '\0';
        return *this;
    }

    size_t Find(const String& substring) const
    {
        if (substring.size_ == 0)
        {
            return 0;
        }

        if (substring.size_ > size_)
        {
            return size_;
        }

        for (size_t i = 0; i <= size_ - substring.size_; i++)
        {
            if (std::strncmp(data_ + i, substring.data_, substring.size_) == 0)
            {
                return i;
            }
        }

        return size_;
    }

    size_t Rfind(const String& substring) const
    {
        if (substring.size_ == 0)
        {
            return size_;
        }

        if (substring.size_ > size_)
        {
            return size_;
        }

        for (size_t i = size_ - substring.size_ + 1; i > 0 ; i--)
        {
            if (std::strncmp(data_ + i - 1, substring.data_, substring.size_) == 0)
            {
                return i - 1;
            }
        }

        return size_;
    }

    String Substr(size_t start, size_t count) const
    {
        if (start >= size_)
        {
            return String();
        }

        size_t real_len = std::min(count, size_ - start);
        
        String result(real_len, '\0');
        std::copy(data_ + start, data_ + start + real_len, result.data_);
        return result;
    }

    bool Empty() const
    {
        return size_ == 0;
    }

    void Clear()
    {
        size_ = 0;
        data_[0] = '\0';
    }

    void ShrinkToFit()
    {
        if (capacity_ > size_)
        {
            char* new_data_ = new char[size_ + 1];

            std::copy(data_, data_ + size_ + 1, new_data_);
            new_data_[size_] = '\0';

            delete[] data_;
            data_ = new_data_;
            capacity_ = size_;
        }
    }

    char* Data()
    {
        return data_;
    }

    const char* Data() const
    {
        return data_;
    }
};


bool operator==(const String& lhs, const String& rhs)
{
    if (lhs.Size() != rhs.Size())
    {
        return false;
    }

    for (size_t i = 0; i < lhs.Size(); i++)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }

    return true;
}

bool operator<(const String& lhs, const String& rhs)
{
    size_t min_len = std::min(lhs.Size(), rhs.Size());

    for (size_t i = 0; i < min_len; i++)
    {
        if (lhs[i] < rhs[i])
        {
            return true;
        }

        if (lhs[i] > rhs[i])
        {
            return false;
        }
    }

    return lhs.Size() < rhs.Size();
}

bool operator>(const String& lhs, const String& rhs)
{
    return rhs < lhs;
}

bool operator<=(const String& lhs, const String& rhs)
{
    return !(rhs < lhs);
}

bool operator>=(const String& lhs, const String& rhs)
{
    return !(lhs < rhs);
}

String operator+(const String& lhs, const String& rhs)
{
    String result = lhs;
    result += rhs;
    return result;
}

String operator+(const String& lhs, char rhs)
{
    String result = lhs;
    result += rhs;
    return result;
}

String operator+(char lhs, const String& rhs)
{
    String result(1, lhs);
    result += rhs;
    return result;
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
    for (size_t i = 0; i < str.Size(); i++)
    {
        out << str[i];
    }
    return out;
}


std::istream& operator>>(std::istream& in, String& str)
{
    str.Clear(); 
    char c;
    while (in.get(c) && (c == ' ' || c == '\n' || c == '\t')){}

    if (in)
    {
        str.PushBack(c);
        while (in.get(c) && !(c == ' ' || c == '\n' || c == '\t'))
        {
            str.PushBack(c);
        }
    }
    return in;
}