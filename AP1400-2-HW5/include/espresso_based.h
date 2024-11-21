#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include <vector>
#include "ingredient.h"
#include <string>

class EspressoBased
{
public:
    virtual std::string get_name() = 0;  //使用=0声明,强制派生类来实现
    virtual double price() = 0;

    void brew();
    std::vector<Ingredient*>& get_ingredients();

    virtual ~EspressoBased(){        //析构函数需要定义为虚函数,否则在几个测试中会调用父类中的析构函数
        for(const auto& i : ingredients)   //子类会先调用父类的虚函数再调用子类的
            delete i;
        ingredients.clear();
    }

protected:
    EspressoBased();
    EspressoBased(const EspressoBased& esp);
    void operator=(const EspressoBased& esp);

    std::vector<Ingredient*> ingredients;
    std::string name;
};

#endif // ESPRESSO_BASED_H