#include <iostream>
#include <string>
#include "Product.h"

void Product::setProductAttributes(string pluInput, string nameInput, int typeInput, double priceInput, int inventoryInput)
{
    PLU = pluInput;
    name = nameInput;
    type = typeInput;
    price = priceInput;
    inventory = inventoryInput;
}

void Product::setInventory(int input)
{
    inventory = input;
}

string Product::getPLU() const
{
    return PLU;
}

string Product::getName() const
{
    return name;
}

int Product::getType() const
{
    return type;
}

double Product::getPrice() const
{
    return price;
}

int Product::getInventory() const
{
    return inventory;
}
