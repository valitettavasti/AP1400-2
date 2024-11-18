#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr
{
private:
    T* _p;
public:
    UniquePtr(T* t = nullptr);  //默认构造参数
    UniquePtr(const UniquePtr<T>&) = delete;                //UniquePtr ptr2{ptr1}; 会报错
    UniquePtr(UniquePtr<T>&& ptr);
    UniquePtr& operator=(const UniquePtr<T>&) = delete;   //UniquePtr ptr2=ptr1; 会报错
    UniquePtr& operator=(const UniquePtr<T>&& ptr);

    T* get();
    T& operator*();  //这里要返回对原本值的引用,不能直接返回T(值)
    T* operator->(); 
    void reset();
    void reset(T* t);
    T* release();
    explicit operator bool() const {return _p!=nullptr;}   //explicit作用:防止可能出现的隐式转换,如bool b2 = ptr;
    ~UniquePtr();

};

template <typename T>      //两点,1主要是这不是类里面的函数,2是传入的是一个右值
UniquePtr<T> make_unique(T &&t);

#include<unique_ptr.hpp>

#endif //UNIQUE_PTR