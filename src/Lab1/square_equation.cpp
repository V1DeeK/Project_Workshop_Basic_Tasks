#include <iostream>
#include <cmath>  // для sqrt
using namespace std;

int main() {
    double a, b, c;
    cout << "Введите коэффициенты a, b, c: ";
    cin >> a >> b >> c;
    if (a == 0.0) {// Проверка квадратное ли уравнение
        cout << "Это не квадратное уравнение (a = 0)." << endl;
        if (b == 0.0) {
            if (c == 0.0) {
                cout << "Решение: любое действительное число." << endl;
            } else {
                cout << "Решений нет." << endl;
            }
        } else {// Линейное уравнение bx + c = 0
            
            cout << "Линейное уравнение. Корень: x = " << -c / b << endl;
        }
        return 0;
    }
    double D = b * b - 4 * a * c;
    if (D > 0) {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        cout << "Два корня:" << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    } else if (D == 0) {
        double x = -b / (2 * a);
        cout << "Один корень:" << endl;
        cout << "x = " << x << endl;
    } else {
        // D < 0 — комплексные корни
        double realPart = -b / (2 * a);
        double imagPart = sqrt(-D) / (2 * a);
        cout << "Два комплексных корня:" << endl;
        cout << "x1 = " << realPart << " + " << imagPart << "i" << endl;
        cout << "x2 = " << realPart << " - " << imagPart << "i" << endl;
    }
    return 0;
}


/*
Тесты
1 -5 6 корни: 2 и 3
1 0 -4 корни: 2 и -2
1 2 5 комплексные корни
0 2 -4 линейное уравнение, корень: 2
*/