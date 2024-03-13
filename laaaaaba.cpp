#include <iostream>
using namespace std;
class Vector {
    double* p = nullptr; // Указатель на массив, задающий вектор
    int n = 0; // Размерность вектора (число элементов)
public:
    // Конструктор, создающий объект вектор на основе обычного одномерного массива размерности n
    Vector(double* p, int n) {
        this->n = n;
        this->p = new double[n]; // Выделение памяти под вектор
        for (int i = 0; i < n; i++) {
            this->p[i] = p[i]; // Копирование значений из переданного массива
        }
    }
    // Конструктор, создающий пустой объект вектор заданной размерности
    Vector(int n) : n(n) {
        p = new double[n]; // Выделение памяти под вектор
    }
    // Конструктор копирования
    Vector(const Vector& V) {
        n = V.n;
        p = new double[n];
        for (int i = 0; i < n; i++) {
            p[i] = V.p[i];
        }
    }
    // Конструктор перемещения
    Vector(Vector&& V) {
        swap(p, V.p); // Обмен указателями на массивы
        swap(n, V.n); // Обмен значениями размерностей
    }
    // Функция печати вектора
    void print() const {
        for (int i = 0; i < n; i++) {
            cout << p[i] << " ";
        }
        cout << endl;
    }
    // Перегрузка оператора доступа к элементу вектора по индексу
    double& operator[](int index) {
        return p[index];
    }
    // Перегрузка оператора присваивания с копированием
    Vector& operator =(const Vector& v2) {
        if (this != &v2) {
            n = v2.n;
            if (p != nullptr) {
                delete[] p; // Освобождаем память старого вектора
            }
            p = new double[n]; // Выделяем память для нового вектора
            for (int i = 0; i < n; i++) {
                p[i] = v2.p[i]; // Копируем значения из другого вектора
            }
        }
        return *this; // Возвращаем ссылку на текущий объект
    }
    // Перегрузка оператора присваивания с перемещением
    Vector& operator =(Vector&& v2) {
        if (this != &v2) {
            swap(p, v2.p); // Обмен указателями на массивы
            swap(n, v2.n); // Обмен значениями размерностей
        }
        return *this; // Возвращаем ссылку на текущий объект
    }
    // Перегрузка оператора сложения векторов
    Vector operator+(const Vector& v2) {
        int new_n = n + v2.n;
        Vector result(new_n); // Создаем новый объект вектора
        for (int i = 0; i < n; i++) {
            result.p[i] = p[i]; // Заполняем новый вектор первым вектором
        }
        for (int i = 0; i < v2.n; i++) {
            result.p[i + n] = v2.p[i]; // Заполняем новый вектор вторым вектором
        }
        return result; // Возвращаем новый вектор
    }
    // Деструктор
    ~Vector() {
        if (p != nullptr) {
            delete[] p; // Освобождаем память, если она была выделена
        }
    }
};
int main() {
    double m1[] = { 1, 2, 3, 4, 5 };
    double m2[] = { 6, 7, 8, 9, 10 };
    Vector V1(m1, 5);
    Vector V2(m2, 5);
    Vector V3 = V1 + V2;
    V3.print();
    return 0;
}