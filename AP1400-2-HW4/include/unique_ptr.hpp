template <typename T>
UniquePtr<T>::UniquePtr(T* t):_p(t){}

template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& ptr) :_p(ptr._p)
{
    ptr._p = nullptr;
}

template <typename T>
inline UniquePtr<T>::~UniquePtr()
{
    delete _p;
}


template <typename T>
UniquePtr<T> &UniquePtr<T>::operator=(const UniquePtr<T> &&ptr)
{
    if(this != &ptr){
        delete _p;
        _p=ptr._p;
        ptr._p = nullptr;
    }
    return *this;
}

template <typename T>
UniquePtr<T> make_unique(T &&t)
{
   return UniquePtr<T>(new T(t));
}

template <typename T>
T* UniquePtr<T>::get(){
    return _p;
}

template <typename T>
T& UniquePtr<T>::operator*()
{
    if (!_p) {
        throw std::runtime_error("Attempt to dereference a null pointer");
    }
    return *_p;
}

template <typename T>
T* UniquePtr<T>::operator->()
{
    return _p;
}

template <typename T>
void UniquePtr<T>::reset()
{
    delete _p;
    _p = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T* t)
{
    delete _p;
    _p = t;
}

template <typename T>
T *UniquePtr<T>::release()
{
    T* ptr = _p;       //将所有权转移,并且返回原指针,并且该智能指针不在存储
    _p = nullptr;
    return ptr;
}
