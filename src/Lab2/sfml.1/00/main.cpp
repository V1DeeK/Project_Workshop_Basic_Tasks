// Подключаем библиотеку для работы с вводом/выводом (iostream - input/output stream)
#include <iostream>

// Главная функция программы - точка входа
int main()
{
	
	int a = 0;
	int b = 0;
	std::cout << "enter two numbers:" << std::endl;
	std::cin >> a >> b;
	std::cout << "sum: " << (a + b) << std::endl;
}
