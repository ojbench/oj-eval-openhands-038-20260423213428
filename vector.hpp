#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <memory>

namespace sjtu {

template<typename T>
class vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_capacity) {
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        
        // Move or copy construct elements
        for (size_t i = 0; i < size_; ++i) {
            new (new_data + i) T(std::move(data_[i]));
            data_[i].~T();
        }
        
        ::operator delete(data_);
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    // Constructor
    vector() : data_(nullptr), size_(0), capacity_(0) {}
    
    explicit vector(size_t n) : data_(nullptr), size_(0), capacity_(0) {
        if (n > 0) {
            data_ = static_cast<T*>(::operator new(n * sizeof(T)));
            capacity_ = n;
            for (size_t i = 0; i < n; ++i) {
                new (data_ + i) T();
            }
            size_ = n;
        }
    }
    
    vector(size_t n, const T& value) : data_(nullptr), size_(0), capacity_(0) {
        if (n > 0) {
            data_ = static_cast<T*>(::operator new(n * sizeof(T)));
            capacity_ = n;
            for (size_t i = 0; i < n; ++i) {
                new (data_ + i) T(value);
            }
            size_ = n;
        }
    }
    
    // Copy constructor
    vector(const vector& other) : data_(nullptr), size_(0), capacity_(0) {
        if (other.size_ > 0) {
            data_ = static_cast<T*>(::operator new(other.size_ * sizeof(T)));
            capacity_ = other.size_;
            for (size_t i = 0; i < other.size_; ++i) {
                new (data_ + i) T(other.data_[i]);
            }
            size_ = other.size_;
        }
    }
    
    // Move constructor
    vector(vector&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    // Destructor
    ~vector() {
        clear();
        if (data_) {
            ::operator delete(data_);
        }
    }
    
    // Copy assignment
    vector& operator=(const vector& other) {
        if (this != &other) {
            clear();
            if (other.size_ > capacity_) {
                if (data_) {
                    ::operator delete(data_);
                }
                data_ = static_cast<T*>(::operator new(other.size_ * sizeof(T)));
                capacity_ = other.size_;
            }
            for (size_t i = 0; i < other.size_; ++i) {
                new (data_ + i) T(other.data_[i]);
            }
            size_ = other.size_;
        }
        return *this;
    }
    
    // Move assignment
    vector& operator=(vector&& other) noexcept {
        if (this != &other) {
            clear();
            if (data_) {
                ::operator delete(data_);
            }
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    // Element access
    T& operator[](size_t pos) { return data_[pos]; }
    const T& operator[](size_t pos) const { return data_[pos]; }
    
    T& at(size_t pos) {
        if (pos >= size_) throw std::out_of_range("vector::at");
        return data_[pos];
    }
    
    const T& at(size_t pos) const {
        if (pos >= size_) throw std::out_of_range("vector::at");
        return data_[pos];
    }
    
    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }
    
    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }
    
    T* data() { return data_; }
    const T* data() const { return data_; }
    
    // Capacity
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    
    void reserve(size_t new_cap) {
        if (new_cap > capacity_) {
            reallocate(new_cap);
        }
    }
    
    void shrink_to_fit() {
        if (size_ < capacity_) {
            if (size_ == 0) {
                if (data_) {
                    ::operator delete(data_);
                    data_ = nullptr;
                }
                capacity_ = 0;
            } else {
                reallocate(size_);
            }
        }
    }
    
    // Modifiers
    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;
    }
    
    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        new (data_ + size_) T(value);
        ++size_;
    }
    
    void push_back(T&& value) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        new (data_ + size_) T(std::move(value));
        ++size_;
    }
    
    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        new (data_ + size_) T(std::forward<Args>(args)...);
        ++size_;
    }
    
    void pop_back() {
        if (size_ > 0) {
            --size_;
            data_[size_].~T();
        }
    }
    
    void resize(size_t new_size) {
        if (new_size > size_) {
            if (new_size > capacity_) {
                reallocate(new_size);
            }
            for (size_t i = size_; i < new_size; ++i) {
                new (data_ + i) T();
            }
        } else if (new_size < size_) {
            for (size_t i = new_size; i < size_; ++i) {
                data_[i].~T();
            }
        }
        size_ = new_size;
    }
    
    void resize(size_t new_size, const T& value) {
        if (new_size > size_) {
            if (new_size > capacity_) {
                reallocate(new_size);
            }
            for (size_t i = size_; i < new_size; ++i) {
                new (data_ + i) T(value);
            }
        } else if (new_size < size_) {
            for (size_t i = new_size; i < size_; ++i) {
                data_[i].~T();
            }
        }
        size_ = new_size;
    }
    
    // Iterator support
    using iterator = T*;
    using const_iterator = const T*;
    
    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    const_iterator cbegin() const { return data_; }
    
    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }
    const_iterator cend() const { return data_ + size_; }
};

} // namespace sjtu

#endif // SJTU_VECTOR_HPP
