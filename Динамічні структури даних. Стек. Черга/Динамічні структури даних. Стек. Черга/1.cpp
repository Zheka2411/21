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
    size_t front_index = 0;
public:
    void push(const T& value) { arr.push_back(value); }
    void pop() { if (front_index < arr.size()) ++front_index; }
    T& top() { return arr[front_index]; }
    bool empty() const { return front_index >= arr.size(); }
    void clear() { arr.clear(); front_index = 0; }
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
                std::cout << "Error in position " << i << ": extra closing bracket " << ch << "\n";
                return false;
            }
            char open = stack.top();
            stack.pop();
            if ((ch == ')' && open != '(') ||
                (ch == '}' && open != '{') ||
                (ch == ']' && open != '[')) {
                std::cout << "Error in position " << i << ": discrepancy " << open << " и " << ch << "\n";
                return false;
            }
        }
    }
    if (!stack.empty()) {
        std::cout << "Error: not all opening brackets are closed." << std::endl;
        return false;
    }
    std::cout << "Brackets are placed correctly." << std::endl;
    return true;
}

int main() {
    std::string input;
    std::cout << "Enter a string with brackets (ended by the character ';'): ";
    std::getline(std::cin, input);
    isBalanced(input);
    return 0;
}
