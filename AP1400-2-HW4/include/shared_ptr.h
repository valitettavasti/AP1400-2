#ifndef SHARED_PTR
#define SHARED_PTR

#include <atomic>

template<typename T>
class SharedPtr
{
private:
    T* _p;
    std::atomic<int>* _use_count;  //AI给出的建议,原子操作是线程安全的,也有其他博主采用map的形式,从而可以保证共享同一个计数
public:
    SharedPtr(T* t = nullptr);
    SharedPtr(const SharedPtr<T>& ptr);
    SharedPtr(SharedPtr<T>&& ptr);
    SharedPtr& operator=(const SharedPtr& ptr);
    SharedPtr& operator=(const SharedPtr&& ptr);

    T* get();
    T& operator*();
    T* operator->();
    void reset();
    void reset(T* t);
    int use_count() const;
    ~SharedPtr();
    explicit operator bool() const {return _p!=nullptr;}
};

template <typename T>
SharedPtr<T> make_shared(T &&t);

#include <shared_ptr.hpp>

#endif //SHARED_PTR