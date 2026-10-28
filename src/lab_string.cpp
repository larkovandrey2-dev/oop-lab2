#include "lab_string.hpp"
#include <ostream>
#include <stdexcept>
#include <utility>

String::String(): 
    data_(new char[2]{}),
    capacity_(1),
    size_(0) {
}

String::~String(){delete[] data_;}

String::String(const String& other):
    data_(nullptr),
    capacity_(other.capacity_ == 0 ? 1 : other.capacity_),
    size_(other.size_) {
    data_ = new char[capacity_ + 1];
    for (std::size_t i = 0; i < size_; ++i){
        data_[i] = other.data_[i];
    }
    data_[size_] = '\0';
}

String::String(const char* text){
    std::size_t length = 0;
    while (text[length] != '\0'){
        length++;
    }
    size_ = length;
    capacity_ = (length == 0) ? 1 : length;
    data_ = new char[capacity_ + 1];
    for (std::size_t i = 0; i <= size_; ++i){
        data_[i] = text[i];
    }
}

void String::swap(String& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
}

String& String::operator=(String other){
    swap(other);
    return *this;
}

String::String(String&& other) noexcept:
    data_(other.data_),
    capacity_(other.capacity_),
    size_(other.size_){
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

std::size_t String::size() const{
    return size_;
}

const char* String::c_str() const{
    return data_ != nullptr ? data_ : "";
}

void String::print(std::ostream& output) const {
    output << c_str();
}

void String::push_back(char c){
    if (size_ == capacity_){
        std::size_t new_capacity = (capacity_ != 0) ? capacity_ * 2 : 1;
        char* new_data = new char[new_capacity + 1];
        for (std::size_t i = 0; i < size_; ++i){
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
    data_[size_] = c;
    data_[++size_] = '\0';
}

void String::append(const String& other){
    std::size_t saved_size = other.size_;
    for (std::size_t i = 0; i < saved_size; ++i){
        push_back(other.data_[i]);
    }
}

std::size_t String::find(const String& substr) const{
    if (substr.size_ == 0) return 0;
    if (substr.size_ > size_) return npos;
    for (std::size_t i = 0; i <= (size_ - substr.size_); ++i){
        bool ok = true;
        for (std::size_t j = 0; j < substr.size_; ++j){
            if (data_[i+j] != substr.data_[j]){
                ok = false;
                break;
            }
        }
        if (ok) return i;
    }
    return npos;
}


String String::wrap(std::size_t width) const{
    if (width == 0) {
        throw std::invalid_argument("wrap width must be positive");
    }

    String result;
    std::size_t i = 0;
    std::size_t line_l = 0;

    while (i < size_) {
        // Пропускаем пробелы перед очередным словом.
        while (i < size_ && data_[i] == ' ') {
            ++i;
        }
        if (i == size_) {
            break;
        }

        // Слово занимает диапазон [start, i).
        std::size_t start = i;
        while (i < size_ && data_[i] != ' ') {
            ++i;
        }
        std::size_t word_len = i - start;

        // В непустой строке перед словом нужен пробел или перенос.
        if (line_l != 0) {
            if (line_l + 1 + word_len <= width) {
                result.push_back(' ');
                ++line_l;
            } else {
                result.push_back('\n');
                line_l = 0;
            }
        }

        for (std::size_t j = start; j < i; ++j) {
            result.push_back(data_[j]);
        }
        line_l += word_len;
    }
    return result;
}
