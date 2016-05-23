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

    T& operator[](int i)
    {
        return _elements[i];
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
        if (_size++ > 0) {
            _back++;
        }
        *_back = element;
    }

    void push_front(const T &element) {
        resize(0);
        if (_size++ > 0) {
            _back++;
        }
        *_front = element;
    }

    void pop_back() {
        erase(_size - 1);
    }

    void pop_front() {
        erase(0);
    }

    void insert(int index, const T &element) {
        if (index < 0 || index > _size) {
            return;
        }

        resize(index);
        if (_size++ > 0) {
            _back++;
        }
        *(_front + index) = element;
    }

    void clear() {
        for (int i = 0; i < _size; i++) {
            _elements[i] = 0;
        }
    }

    void erase(int index) {
        if (index >= 0 && index < _size) {
            _elements[index] = 0;
            for (int i = index+1; i < _size; i++) {
                _elements[i-1] = _elements[i];
            }
            if (_size > 0) {
                _back--;
            }
            _size--;
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

template <typename T>
class Queue {
 public:
    Queue() {
    }

    bool empty() {
        return (_list.size() == 0);
    }

    const T& front() {
        return _list.front();
    }

    const T& back() {
        return _list.back();
    }

    void push(const T& element) {
        _list.push_back(element);
    }

    void pop() {
        _list.pop_front();
    }

 private:
    List<T> _list;
};

template <typename T, bool compare(int a, int b)>
class Priority_Queue {

 public:
    Priority_Queue() {
    }

    bool empty() {
        return (_vector.size() == 0);
    }

    int size() {
        return _vector.size();
    }

    const T& top() {
        return _vector.front();
    }

    void push(const T& element) {
        _vector.push_back(element);
        int index = _vector.size() - 1;
        int swapIndex;
        while (index > 0) {
            if (index % 2 == 1) {
                swapIndex = (index - 1)/2;
            } else {
                swapIndex = (index - 2)/2;
            }
            if (compare(_vector[index], _vector[swapIndex])) {
                T temp = _vector[swapIndex];
                _vector[swapIndex] = _vector[index];
                _vector[index] = temp;
                index = swapIndex;
            } else {
                break;
            }
        }
    }

    void pop() {
        _vector[0] = _vector.back();
        _vector.pop_back();
        int index = 0;
        while (++index < _vector.size()) {
            if (compare(_vector[index], _vector[index-1])) {
                T temp = _vector[index-1];
                _vector[index-1] = _vector[index];
                _vector[index] = temp;
            } else {
                break;
            }
        }
    }

 private:
    Vector<T> _vector;
};

template <typename T, bool compare(const T& a, const T& b)>
class Binary_Search_Tree
{
    struct Node {
        T val;
        Node* left;
        Node* right;
        Node* parent;
    };

 public:
    Binary_Search_Tree() :
     _root(nullptr),
     _min(nullptr),
     _max(nullptr),
     _size(0) {
    }

    bool exists(const T& element) {
        return exists(element, _root);
    }

    void insert(const T& element) {
        insert(element, _root);
        _size++;
        if (_size == 1) {
            _min = _root;
            _max = _root;
        } else {
            if (compare(element, _min->val)) {
                // should be on the left!
                _min = _min->left;
            } else if (compare(_max->val, element)) {
                // should be on the right!
                _max = _max->right;
            }
        }
    }

    const T& min() {
        return _min->val;
    }

    const T& max() {
        return _max->val;
    }

    bool empty() {
        return (_size == 0);
    }

    int size() {
        return _size;
    }

    void clear() {
        clear(_root);
    }

    void pop_min() {
        Node *temp = _min;
        if (temp != nullptr) {
            _min = _min->parent;
            delete temp;
            _size--;
        }
    }

    void pop_max() {
        Node *temp = _max;
        if (temp != nullptr) {
            _max = _max->parent;
            delete temp;
            _size--;
        }
    }

    // void erase(const T& element) {
    //     // what if there are duplicates?
    //     // need to know which node
    // }

    // T* preOrder() {

    // }

    // T* inOrder() {

    // }

    // T* postOrder() {

    // }

 private:
    Node *_root;
    Node *_min;
    Node *_max;
    int _size;

    bool exists(const T& element, Node *node) {
        if (node == nullptr) {
            return false;
        }

        if (element == node->val) {
            return true;
        }

        if (compare(element, node->val)) {
            return exists(element, node->left);
        } else {
            return exists(element, node->right);
        }
    }

    void clear(Node *node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    void insert(const T& element, Node *node) {
        if (node == nullptr) {
            node = new Node();
            node->left = nullptr;
            node->left = nullptr;
            node->parent = nullptr;
            node->val = element;
        }

        if (compare(element, node->val)) {
            if (node->left == nullptr) {
                node->left = new Node();
                node->left->parent = node;
                node->left->left = nullptr;
                node->left->right = nullptr;
                node->left->val = element;
            } else {
                insert(element, node->left);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new Node();
                node->right->parent = node;
                node->right->left = nullptr;
                node->right->right = nullptr;
                node->right->val = element;
            } else {
                insert(element, node->right);
            }
        }
    }
};

}
