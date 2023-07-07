#include <iostream>
using namespace std;

template<class t>
class test_unique_ptr {
    t* ptr;
public:
    test_unique_ptr() : ptr(nullptr) {}
    test_unique_ptr(const  test_unique_ptr& sp) = delete;
    test_unique_ptr(t* p) {
        ptr = p;
    }
    ~test_unique_ptr() {
        delete ptr;
    }

    t& operator* () {
        return *ptr;
    }

    t* get() {
        return ptr;
    }
    void reset() {
        delete ptr;
        ptr = nullptr;
    }
    void realese() {
        ptr = nullptr;
    }
    void swap(test_unique_ptr<t>& up) {
        std::swap(ptr, up.ptr);
    }
};

template<class t>
class  test_shared_ptr {
    t* ptr = nullptr;
    size_t* count = nullptr;
public:
    test_shared_ptr() : ptr(nullptr), count(nullptr) {}
    test_shared_ptr(const  test_shared_ptr& sp) {
        ptr = sp.ptr;
        count = sp.count;
        *count++;
    };
    test_shared_ptr(t* p) {
        ptr = p;
        count = new size_t(1);
    }

    ~test_shared_ptr() {
        if ((*count) > 1) {
            (*count)--;
            return;
        }
        delete ptr;
        delete count;
    }

    t& operator* () {
        return *ptr;
    }
    t* operator->() {
        return ptr;
    }
    void operator= (test_shared_ptr<t>& up) {
        up.ptr = ptr;
        (count)++;
    }

    t* get() {
        return ptr;
    }
    void reset() {
        delete ptr;
        ptr = nullptr;
    }
    void swap(test_shared_ptr<t>& up) {
        std::swap(ptr, up.ptr);
    }
    size_t use_count() {
        return *count;
    }
};


int main()
{

    shared_ptr<int> p(new int(5));
    shared_ptr<int> p2;
    cout << p.use_count() << endl;
    p2 = p;
    cout << p.use_count() << endl;

    shared_ptr<int> y;
    cout << p.use_count() << endl;
    y = p2;
    cout << p.use_count() << endl;

    cout << "---------------------------------------------------\n";
    test_shared_ptr<int> p3(new int(5));
    test_shared_ptr<int> p4;
    cout << p3.use_count() << endl;
    p4 = p3;
    cout << p3.use_count() << endl;

    test_shared_ptr<int> x;
    cout << p.use_count() << endl;
    x = p4;
    cout << p3.use_count() << endl;

    return 0;
}