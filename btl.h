/*

file: btl.h
by: Brian Dunlay

MIT License

Copyright (c) 2016 Brian Dunlay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */

namespace btl
{

#define nullptr 0

template <typename T>
class Vector {
 public:
    Vector() :
     _size(0),
     _capacity(100) {
        _elements = new T[_capacity];
        _front = _elements;
        _back = _elements;
    };

    Vector(int capacity) :
     _size(0),
     _capacity(capacity) {
        _elements = new T[capacity];
        _front = _elements;
        _back = _elements;
    }

    int size() {
        return _size;
    }

    int capacity() {
        return _capacity;
    }

    const T& front() {
        return *_front;
    }

    const T& back() {
        return *_back;
    }

    void push_back(const T &element) {
        resize(_size);
        _back++;
        _size++;
        *_back = element;
    }

    void push_front(const T &element) {
        resize(0);
        _back++;
        _size++;
        *_front = element;
    }

    void insert(int index, const T &element) {
        if (index < 0 || index > _size) {
            return;
        }

        resize(index);
        _back++;
        _size++;
        *(_front + index) = element;
    }

    void clear() {
        for (int i = 0; i < _size; i++) {
            _elements[i] = 0;
        }
    }

    void erase(int index) {
        if (index < 0 || index >= _size) {
            return;
        }
        _elements[index] = 0;
        for (int i = index+1; index < _size; index++) {
            _elements[i-1] = _elements[i];
        }
    }

 private:
    T *_elements;
    T *_front;
    T *_back;
    int _size;
    int _capacity;

    inline void resize(int holeIndex) {
        int nextCapacity = 2*_capacity;
        if (_size == _capacity) {
            T *newElements = new T[nextCapacity];
            for (int i = 0; i < _size; i++) {
                int j = (i < holeIndex) ? i : i+1;
                newElements[i] = _elements[j];
            }
            delete _elements;
            _elements = newElements;
            _capacity = nextCapacity;
        }
    }
};

template <typename T>
class Stack {
 public:
    Stack() {
    }

    bool empty() {
        return (_stack.size() == 0);
    }

    int size() {
        return (_stack.size());
    }

    const T& top() {
        return _stack.back();
    }

    void push(const T &element) {
        _stack.push_back(element);
    }

    void pop() {
        int size = _stack.size();
        if (size > 0) {
            _stack.erase(size-1);
        }
    }

 private:
    Vector<T> _stack;
};

template <typename T>
class List {
    struct Node {
        T val;
        Node *next;
        Node *prev;
    };
 public:
    List() :
     _head(nullptr),
     _tail(nullptr),
     _size(0) {
    }

    void push_front(const T& element) {
        Node* node = new Node();
        if (_head == nullptr) {
            _head = node;
            _tail = node;
            node->next = nullptr;
        } else {
            _head->prev = node;
            node->next = _head;
            _head = node;
        }
        node->prev = nullptr;
        _size++;
    }

    void push_back(const T& element) {
        Node *node = new Node();
        node->val = element;
        if (_tail == nullptr) {
            _head = node;
            _tail = node;
            node->prev = nullptr;
        } else {
            _tail->next = node;
            node->prev = _tail;
            _tail = node;
        }
        node->next = nullptr;
        _size++;
    }

    const T& back() {
        return _tail;
    }

    const T& front() {
        return _head;
    }

    void pop_back() {
        if (_size > 1) {
            Node *todelete = _tail;
            _tail = todelete->prev;
            _tail->next = nullptr;
            delete todelete;
            _size--;
        } else if (_size == 1) {
            delete _tail;
            _head = nullptr;
            _tail = nullptr;
            _size--;
        }
    }

    void pop_front() {
        if (_size > 1) {
            Node *todelete = _head;
            _head = todelete->next;
            _head->prev = nullptr;
            delete todelete;
            _size--;
        } else if (_size == 1) {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
            _size--;
        }
    }

    void clear() {
        Node *curr = _head;
        while (curr != nullptr) {
            Node *next = _head->next;
            delete curr;
            curr = next;
            _size--;
        }
        _head = nullptr;
        _tail = nullptr;
    }

    void reverse() {
        Node *curr = _head;
        _tail = _head;
        while (curr != nullptr) {
            Node *next = _head->next;
            curr->next = curr->prev;
            curr->prev = next;
            curr = next;
        }
        _head = curr;
    }

    int size() {
        return _size;
    }

 private:
    Node *_head;
    Node *_tail;
    int _size;
};

}
