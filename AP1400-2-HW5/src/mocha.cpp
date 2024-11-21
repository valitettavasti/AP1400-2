#include "mocha.h"
#include "sub_ingredients.h"

Mocha::Mocha()
{
    ingredients = std::vector<Ingredient*>{};
    side_items = std::vector<Ingredient*>{};
    name = "Mocha";
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha& moc)
{
    if(this != &moc){
        for(const auto& i : ingredients)
           delete i;
        ingredients.clear();
        for(const auto& i :  side_items)
            delete i;
        side_items.clear();
        for(const auto& i : moc.ingredients)
            this->ingredients.push_back(i->copy());
        for(const auto& i : moc.side_items)
            this->side_items.push_back(i->copy());
        name = moc.name;
    }
}

Mocha::~Mocha(){
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
    for(const auto& i :  side_items)
        delete i;
    side_items.clear();
}

void Mocha::operator=(const Mocha& moc){
    if(this != &moc){
        for(const auto& i : ingredients)
           delete i;
        ingredients.clear();
        for(const auto& i :  side_items)
            delete i;
        side_items.clear();
        for(const auto& i : moc.ingredients)
            this->ingredients.push_back(i->copy());
        for(const auto& i : moc.side_items)
            this->side_items.push_back(i->copy());
        name = moc.name;
    }
}

std::string Mocha::get_name()
{
    return name;
}

double Mocha::price()
{
    double p = 0;
    for(const auto& item : ingredients){
        p += item->price();
    }
    for(const auto& item :side_items){
        p += item->price();
    }
    return p;
}

void Mocha::add_side_item(Ingredient *side)
{
    side_items.push_back(side);
}

std::vector<Ingredient *> &Mocha::get_side_items()
{
    return side_items;
}