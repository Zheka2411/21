#include <iostream>
#include <string>

template<typename T>
class Array {
private:
    T* data;
    size_t capacity;
    size_t size;
public:
    Array(size_t cap = 10) : capacity(cap), size(0) {
        data = new T[capacity];
    }
    ~Array() { delete[] data; }
    void push_back(const T& value) {
        if (size == capacity) {
            capacity *= 2;
            T* newData = new T[capacity];
            for (size_t i = 0; i < size; ++i)
                newData[i] = data[i];
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }
    void pop_back() { if (size > 0) --size; }
    T& back() { return data[size - 1]; }
    T& front() { return data[0]; }
    void erase_front() {
        if (size > 0) {
            for (size_t i = 0; i < size - 1; ++i)
                data[i] = data[i + 1];
            --size;
        }
    }
    bool empty() const { return size == 0; }
    void clear() { size = 0; }
};

template<typename T>
class Stack {
private:
    Array<T> arr;
public:
    void push(const T& value) { arr.push_back(value); }
    void pop() { arr.pop_back(); }
    T& top() { return arr.back(); }
    bool empty() const { return arr.empty(); }
    void clear() { arr.clear(); }
};

template<typename T>
class Queue {
private:
    Array<T> arr;
public:
    void push(const T& value) { arr.push_back(value); }
    void pop() { arr.erase_front(); }
    T& top() { return arr.front(); }
    bool empty() const { return arr.empty(); }
    void clear() { arr.clear(); }
};

bool isBalanced(const std::string& str) {
    Stack<char> stack;
    for (size_t i = 0; i < str.length(); ++i) {
        char ch = str[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (stack.empty()) {
                std::cout << "Position error " << i << ": extra closing parenthesis " << ch << "\n";
                return false;
            }
            char open = stack.top();
            stack.pop();
            if ((ch == ')' && open != '(') ||
                (ch == '}' && open != '{') ||
                (ch == ']' && open != '[')) {
                std::cout << "Position error " << i << ": incompatibility " << open << " і " << ch << "\n";
                return false;
            }
        }
    }
    if (!stack.empty()) {
        std::cout << "Error: Not all opening parentheses are closed." << std::endl;
        return false;
    }
    std::cout << "The brackets are positioned correctly." << std::endl;
    return true;
}

int main() {
    std::string input;
    std::cout << "Enter a string with brackets (ending with a ';'): ";
    std::getline(std::cin, input);
    isBalanced(input);
    return 0;
}
