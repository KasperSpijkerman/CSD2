//main, class, functies, public
#include <iostream>
#include <random>
#include <ctime>
#include <list>

class Pizza 
{
public:
    int size = 0;
    std:: string sauce;
    std::array<std::string, 4> ingredients { "Mushroom", "Salami", "Mozarella", "Pesto" };

    void chooseSize()
    {
        std::cout << "Choose pizza size, Small = 15, Italian = 25, Big is 30: " << std::endl;
        std::cin >> size;
        if (size == 15)
        {
            std::cout << "Small pizza" << size << std::endl;
        }
}

};


int main() 
{

return 0;
}