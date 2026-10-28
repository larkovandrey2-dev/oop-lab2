#pragma once
#include <cstddef>
#include <iosfwd>

class String{
    private:
        char* data_;
        std::size_t capacity_;
        std::size_t size_;
    public:
        static constexpr std::size_t npos = static_cast<std::size_t>(-1);
        String();
        String(const String& other);
        String(const char* text);
        String(String&& other) noexcept;
        ~String();
        String& operator=(String other);
        void swap(String& other) noexcept;
        std::size_t size() const;
        const char* c_str() const;
        void print(std::ostream& output) const;
        void push_back(char c);
        void append(const String& other);
        std::size_t find(const String& substr) const;
        String wrap(std::size_t width) const;
        
};

