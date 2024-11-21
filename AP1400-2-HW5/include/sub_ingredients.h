#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

// 需要提供一个深拷贝功能,但是其他地方没有合适的实现位置,只能在宏里面实现
// 如果没有该功能,仅是浅拷贝的话会出现double free这种问题
#define SUB_INGREDIENT_CLASS(NAME,UNIT_PRICE) \
class NAME : public Ingredient \
{ \
public: \
    NAME(size_t units) : Ingredient(UNIT_PRICE, units) \
    { \
        this->name = #NAME; \
    } \
    virtual std::string get_name() {return this->name;} \
    virtual Ingredient* copy() {return new NAME(units);} \
};


SUB_INGREDIENT_CLASS(Cinnamon, 5);
SUB_INGREDIENT_CLASS(Chocolate, 5);
SUB_INGREDIENT_CLASS(Sugar, 1);
SUB_INGREDIENT_CLASS(Cookie, 10);
SUB_INGREDIENT_CLASS(Espresso, 15);
SUB_INGREDIENT_CLASS(Milk, 10);
SUB_INGREDIENT_CLASS(MilkFoam, 5);
SUB_INGREDIENT_CLASS(Water, 1);


/*
class Cinnamon:public Ingredient
{
public:
    Cinnamon(size_t units):Ingredient(5, units)
    {
        this->name = "Cinnamon";
    }
    virtual std::string get_name() {return this->name;}
};

class Chocolate:public Ingredient
{
public:
    Chocolate(size_t units):Ingredient(5, units)
    {
        this->name = "Chocolate";
    }
    virtual std::string get_name() {return this->name;}
};

class Sugar:public Ingredient
{
public:
    Sugar(size_t units):Ingredient(1, units)
    {
        this->name = "Sugar";
    }
    virtual std::string get_name() {return this->name;}
};

class Cookie:public Ingredient
{
public:
    Cookie(size_t units):Ingredient(10, units)
    {
        this->name = "Cookie";
    }
    virtual std::string get_name() {return this->name;}
};


class Espresso:public Ingredient
{
public:
    Espresso(size_t units):Ingredient(15, units)
    {
        this->name = "Espresso";
    }
    virtual std::string get_name() {return this->name;}
};

class Milk:public Ingredient
{
public:
    Milk(size_t units):Ingredient(10, units)
    {
        this->name = "Milk";
    }
    virtual std::string get_name() {return this->name;}
};

class MilkFoam:public Ingredient
{
public:
    MilkFoam(size_t units):Ingredient(5, units)
    {
        this->name = "MilkFoam";
    }
    virtual std::string get_name() {return this->name;}
};

class Water:public Ingredient
{
public:
    Water(size_t units):Ingredient(1, units)
    {
        this->name = "Water";
    }
    virtual std::string get_name() {return this->name;}
};
*/


#endif // SUB_INGREDIENTS_H