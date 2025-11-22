#include <iostream>

int main()
{
    
    for (int num = 1; num <= 100; num += 1)
    {
        
        if (num % 15 == 0) // Если число кратно 15, то оно кратно и 3, и 5 одновременно
        {
            std::cout << "FizzBuzz" << std::endl;
        }
        else if (num % 3 == 0)
        {
            std::cout << "Fizz" << std::endl;
        }
        else if (num % 5 == 0)
        {
            std::cout << "Buzz" << std::endl;
        }
        else
        {
            std::cout << num << std::endl;
        }
    }
    return 0;
}
