template<typename T>
SharedPtr<T>::SharedPtr(T* t):_p(t),_use_count(t?new std::atomic<int>(1):nullptr){}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& ptr):_p(ptr._p),_use_count(ptr._use_count){
    if(_p){
        _use_count->fetch_add(1, std::memory_order_relaxed);
    }
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& ptr):_p(ptr._p),_use_count(ptr._use_count){
    ptr._p = nullptr;
    ptr._use_count = nullptr;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& ptr){
    if(this != &ptr){      //防止出现自赋值的情况   //如果比较*this和ptr,此时比较的是const和非const类型,不能比较
        if(!_p && --*_use_count == 0){
            delete _p;     //当一个被赋值成了另一个,注意要将原本的引用计数-1
            delete _use_count;
        }
        _p = ptr._p;
        _use_count = ptr._use_count;
        if(_p){
        _use_count->fetch_add(1, std::memory_order_relaxed);
        }
    }
    return *this;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr&& ptr){
    if(this != &ptr){
        if(!_p && --*_use_count == 0){
            delete _p;     //当一个被赋值成了另一个,注意要将原本的引用计数-1
            delete _use_count;
        }
        _p = ptr._p;
        _use_count = ptr._use_count;
        ptr._p = nullptr;
        ptr._use_count=nullptr;
    }
    return *this;
}

template<typename T>
T* SharedPtr<T>::get(){
    return _p;
}

template<typename T>
T& SharedPtr<T>::operator*(){
    if(!_p){
        throw std::runtime_error("Attempt to dereference a null pointer");
    }else{
        return *_p;
    }
}

template<typename T>
T* SharedPtr<T>::operator->(){
    return _p;
}

template<typename T>
void SharedPtr<T>::reset(){
    if(!_p && --*_use_count == 0){
        delete _p;
        delete _use_count;
        _p = nullptr; 
        _use_count =nullptr;
    }
    _p = nullptr;
    _use_count->store(0,std::memory_order_relaxed);
}

template<typename T>
void SharedPtr<T>::reset(T* t){
    if(!_p && --*_use_count == 0){
        delete _p;
        delete _use_count;
        _p = nullptr; 
        _use_count =nullptr;
    }
    _p = t;
    _use_count=new std::atomic<int>(1);
}

template<typename T>
int SharedPtr<T>::use_count() const{
    if (_use_count == nullptr){
        return 0;
    }else{
        return _use_count->load();
    }
}

template<typename T>
inline SharedPtr<T>::~SharedPtr(){
    if (_p && --*_use_count == 0) {    //和前面的重新赋值的一样,调用时仅减小use_cout的值,直到为0时再删除
        delete _p;
        delete _use_count;
        _p = nullptr; 
        _use_count =nullptr;
    }
}

template <typename T>
SharedPtr<T> make_shared(T &&t){
    return SharedPtr(new T(t));
}