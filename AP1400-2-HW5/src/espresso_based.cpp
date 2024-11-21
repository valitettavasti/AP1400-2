#include "espresso_based.h"
//#include <vector>
//#include "ingredient.h"

std::vector<Ingredient*>& EspressoBased::get_ingredients(){
    return ingredients;
}

void EspressoBased::brew(){

}

EspressoBased::EspressoBased(){
    ingredients=std::vector<Ingredient*>{};
    name = std::string {};
}

EspressoBased::EspressoBased(const EspressoBased &esp)
{
    if(this != &esp){
        for(const auto& i : esp.ingredients)
            this->ingredients.push_back(i->copy());
        name = esp.name;
    }
}

void EspressoBased::operator=(const EspressoBased &esp)
{
    if(this != &esp){
        for(const auto& i : esp.ingredients)
            this->ingredients.push_back(i->copy());
        name = esp.name;
    }
}
/*
EspressoBased::~EspressoBased()
{
    for(const auto& i : ingredients)
        delete i;
    ingredients.clear();
}*/