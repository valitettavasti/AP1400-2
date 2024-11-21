#include "cappuccino.h"
#include "sub_ingredients.h"
#include <iostream>

Cappuccino::Cappuccino()
{
    ingredients = std::vector<Ingredient*>{};
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    side_items = std::vector<Ingredient*>{};
    name = "Cappuccino";
}

Cappuccino::Cappuccino(const Cappuccino &cap)
{
    if(this != &cap){
        for(const auto& i : ingredients)
           delete i;
        ingredients.clear();
        for(const auto& i :  side_items)
            delete i;
        side_items.clear();
        for(const auto& i : cap.ingredients)
            this->ingredients.push_back(i->copy());
        for(const auto& i :  cap.side_items)
            this->side_items.push_back(i->copy());
        name = cap.name;    
    }
}

Cappuccino::~Cappuccino()
{
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
    for(const auto& i : side_items)
    {
        delete i;
    }
    side_items.clear();
}

void Cappuccino::operator=(const Cappuccino &cap)
{
    if(this != &cap){
        for(const auto& i : ingredients)
           delete i;
        ingredients.clear();
        for(const auto& i :  side_items)
            delete i;
        side_items.clear();
        for(const auto& i : cap.ingredients)
            this->ingredients.push_back(i->copy());
        for(const auto& i :  cap.side_items)
            this->side_items.push_back(i->copy());
        name = cap.name;    
    }
}

std::string Cappuccino::get_name()
{
    return name;
}

double Cappuccino::price()
{
    double p = 0;
    for(const auto& item : ingredients){
        p += item->price();
    }
    for(const auto& item : side_items){
        p += item->price();
    }
    return p;
}

void Cappuccino::add_side_item(Ingredient *side)
{
    side_items.push_back(side);
}

std::vector<Ingredient *>& Cappuccino::get_side_items()
{
    return side_items;
}
