# Problem 038 - vector++ Solution Summary

## Problem Description
Implement a high-performance vector class in C++ that competes with std::vector and dark::vector in terms of performance.

## Solution Overview
I implemented a custom `sjtu::vector` template class with the following key features:

### 1. Memory Management
- Used placement new and explicit destructor calls for fine-grained control over object lifetime
- Direct memory allocation using `::operator new` and `::operator delete` for better performance
- Efficient reallocation strategy with 2x growth factor

### 2. Key Optimizations
- **Move Semantics**: Full support for move constructors and move assignment operators
- **Inline Operations**: Frequently used operations are defined in the header for inlining
- **Efficient Reallocation**: Minimizes memory copies during vector growth
- **Template-based Design**: Zero-overhead abstraction

### 3. API Compatibility
The implementation provides standard vector operations:
- Constructors: default, size-based, value-initialized
- Element access: `operator[]`, `at()`, `front()`, `back()`, `data()`
- Capacity: `size()`, `capacity()`, `empty()`, `reserve()`, `shrink_to_fit()`
- Modifiers: `push_back()`, `pop_back()`, `emplace_back()`, `clear()`, `resize()`
- Iterators: `begin()`, `end()`, and const variants

## Submission Results

**Submission ID**: 788837
**Score**: 100/100
**Status**: Accepted

### Test Results:
1. **Move Test** (50 points): ✅ Accepted
   - "your vector is about the same speed as std::vector"
   - "your vector is about the same speed as dark::vector"
   - Time: 14083ms, Memory: 888918016 bytes

2. **Realloc Test** (50 points): ✅ Accepted
   - "your vector is about the same speed as std::vector"
   - "your vector is 16596.11% slower than dark::vector" (but still passed)
   - Time: 11346ms, Memory: 271986688 bytes

## Implementation Details

The implementation focuses on:
1. **Correctness**: Proper RAII, exception safety (basic guarantee)
2. **Performance**: Efficient memory management and move semantics
3. **Standard Compliance**: Compatible with standard vector interface

## Files
- `vector.hpp`: Main implementation of sjtu::vector
- `main.cpp`: Test harness (for local testing)
- `CMakeLists.txt`: Build configuration
- `.gitignore`: Git ignore rules

## Notes
- The OJ expects a C++ header file submission (not a git repository)
- The submitted code is included as `/src.hpp` in the OJ's test framework
- The OJ's test framework defines its own `main()` function
