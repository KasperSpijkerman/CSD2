//main, class, functies, public
#include <iostream>
#include <array>
#include <string>


class Pizza 
{
public:
    int size;
    std:: string sauce;
    //list with ingedrients
    std::string ingredients[4] = { "Mushroom", "Salami", "Mozarella", "Pesto" };
    
    void chooseSize()
    {
        std::cout << "Choose pizza size, Small = 15, Italian = 25, Big is 30: " << std::endl;
        std::cin >> size;
        if (size == 15)
        {
            std::cout << "Small pizza size = " << size << " cm" << std::endl;
        }
        if (size == 25)
        {
            std::cout << "Italian pizza size = " << size << " cm" << std::endl;
        }
        if (size == 30)
        {
            std::cout << "Big pizza size = " << size << " cm" << std::endl;
        }
        else 
        {
        std::cout << "Choose pizza size, Small = 15, Italian = 25, Big is 30: " << std::endl;
        std::cin >> size; 
        }

    }
    void printIngredients() 
    {
        std::cout << "The List of the ingedrients are: " << std::endl;
        for (int i = 0; i < 4; i++)
        std::cout << ingredients[i] << "\n";
    }

};


int main() 
{
Pizza myPizza;
myPizza.chooseSize();
myPizza.printIngredients();
return 0;
}