#include <iostream>
#include <memory>
#include <iomanip>
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "Array.h"

using namespace std;

// выводим инфу про фигуру на экран
template <Scalar T>
void printFigureInfo(const shared_ptr<Figure<T>> &fig)
{
    if (fig)
    {
        cout << *fig << endl;
        cout << "  Центр: " << fig->getCenter() << endl;
        cout << "  Площадь: " << fixed << setprecision(2) << fig->getArea() << endl;
        // можно еще через оператор приведения получить площадь
        cout << "  Площадь (через operator double): " << static_cast<double>(*fig) << endl;
    }
}

// считаем общую площадь всех фигур в массиве
template <Scalar T>
double calculateTotalArea(const Array<shared_ptr<Figure<T>>> &arr)
{
    double sum = 0.0;
    for (size_t idx = 0; idx < arr.getSize(); ++idx)
    {
        sum += arr[idx]->getArea();
    }
    return sum;
}

// первый пример - работаем с полиморфным массивом фигур
void demonstratePolymorphicArray()
{
    cout << "\n=== Пример 1: Работа с Array<shared_ptr<Figure<int>>> (полиморфный массив) ===" << endl;

    Array<shared_ptr<Figure<int>>> figures;

    // создаем прямоугольник, координаты подобрал чтобы был валидный
    auto rect = make_shared<Rectangle<int>>(Point<int>(0, 0), Point<int>(4, 0),
                                            Point<int>(4, 3), Point<int>(0, 3));
    figures.add(rect);

    // тут трапеция которая должна вписаться в окружность
    // потратил немало времени подбирая координаты :)
    auto trap = make_shared<Trapezoid<int>>(Point<int>(0, 0), Point<int>(4, 0),
                                            Point<int>(3, 2), Point<int>(1, 2));
    figures.add(trap);

    // добавляем ромб
    auto rhomb = make_shared<Rhombus<int>>(Point<int>(2, 0), Point<int>(4, 1),
                                           Point<int>(2, 2), Point<int>(0, 1));
    figures.add(rhomb);
    cout << "\nВсего фигур в массиве: " << figures.getSize() << endl;

    // теперь выводим информацию про каждую фигуру
    cout << "\nИнформация о фигурах:" << endl;
    for (size_t i = 0; i < figures.getSize(); ++i)
    {
        cout << "\nФигура " << (i + 1) << " (" << figures[i]->getTypeName() << "):" << endl;
        printFigureInfo(figures[i]);
    }

    // считаем сколько места все фигуры занимают
    double total = calculateTotalArea(figures);
    cout << "\nОбщая площадь всех фигур: " << fixed << setprecision(2) << total << endl;

    // попробуем удалить одну фигуру (например вторую)
    cout << "\nУдаление фигуры с индексом 1..." << endl;
    figures.remove(1); // shared_ptr автоматически освободит память

    cout << "Фигур после удаления: " << figures.getSize() << endl;

    // память очистится автоматически благодаря shared_ptr
}

// второй пример - массив конкретных прямоугольников с дробными координатами
void demonstrateRectangleArray()
{
    cout << "\n=== Пример 2: Работа с Array<Rectangle<double>> (массив прямоугольников) ===" << endl;

    Array<Rectangle<double>> rects;

    // создаем несколько прямоугольников, тут уже можно double использовать
    Rectangle<double> r1(Point<double>(0.0, 0.0), Point<double>(4.5, 0.0),
                         Point<double>(4.5, 3.2), Point<double>(0.0, 3.2));
    rects.add(r1);

    Rectangle<double> r2(Point<double>(1.0, 1.0), Point<double>(5.0, 1.0),
                         Point<double>(5.0, 4.0), Point<double>(1.0, 4.0));
    rects.add(r2);

    Rectangle<double> r3(Point<double>(0.0, 0.0), Point<double>(6.0, 0.0),
                         Point<double>(6.0, 2.0), Point<double>(0.0, 2.0));
    rects.add(r3);

    cout << "\nКоличество прямоугольников: " << rects.getSize() << endl;

    // выводим что получилось
    cout << "\nИнформация о прямоугольниках:" << endl;
    for (size_t j = 0; j < rects.getSize(); ++j)
    {
        cout << "\nПрямоугольник " << (j + 1) << ":" << endl;
        cout << "  " << rects[j] << endl;
        cout << "  Центр: " << rects[j].getCenter() << endl;
        cout << "  Площадь: " << fixed << setprecision(2) << rects[j].getArea() << endl;
    }

    // проверим как работают операторы
    cout << "\n--- Тестирование операторов ---" << endl;
    Rectangle<double> r4 = rects[0]; // вызовется копирующий конструктор
    cout << "Копия первого прямоугольника создана" << endl;
    cout << "r4 == rects[0]: " << (r4 == rects[0] ? "true" : "false") << endl;

    // посчитаем общую площадь через оператор приведения типа
    double s = 0.0;
    for (size_t k = 0; k < rects.getSize(); ++k)
    {
        s += static_cast<double>(rects[k]);
    }
    cout << "\nОбщая площадь всех прямоугольников: " << fixed << setprecision(2) << s << endl;
}

// третий пример - тут покажем как работает move семантика на ромбах
void demonstrateRhombusArray()
{
    cout << "\n=== Пример 3: Работа с Array<Rhombus<int>> (массив ромбов) ===" << endl;

    Array<Rhombus<int>> rhombs;

    // делаем пару ромбов
    Rhombus<int> rh1(Point<int>(3, 0), Point<int>(6, 2), Point<int>(3, 4), Point<int>(0, 2));
    rhombs.add(rh1);

    Rhombus<int> rh2(Point<int>(5, 1), Point<int>(7, 3), Point<int>(5, 5), Point<int>(3, 3));
    rhombs.add(rh2);

    cout << "\nКоличество ромбов: " << rhombs.getSize() << endl;

    // смотрим что получилось
    cout << "\nИнформация о ромбах:" << endl;
    for (size_t i = 0; i < rhombs.getSize(); ++i)
    {
        cout << "\nРомб " << (i + 1) << ":" << endl;
        cout << "  " << rhombs[i] << endl;
        cout << "  Центр: " << rhombs[i].getCenter() << endl;
        cout << "  Площадь: " << fixed << setprecision(2) << rhombs[i].getArea() << endl;
    }

    // тестируем перемещение массива (move constructor)
    cout << "\n--- Тестирование move-семантики ---" << endl;
    Array<Rhombus<int>> newRhombs = std::move(rhombs);
    cout << "Массив перемещен" << endl;
    cout << "Размер исходного массива: " << rhombs.getSize() << endl;
    cout << "Размер нового массива: " << newRhombs.getSize() << endl;
}

// пример 4 - ввод фигур из консоли (std::cin)
void demonstrateInputFromConsole()
{
    cout << "\n=== Пример 4: Ввод фигур из консоли (std::cin) ===" << endl;

    Array<shared_ptr<Figure<double>>> figures;

    cout << "\nВведите количество фигур для создания: ";
    int count;
    cin >> count;

    if (count <= 0)
    {
        cout << "Количество должно быть положительным" << endl;
        return;
    }

    for (int i = 0; i < count; ++i)
    {
        cout << "\n--- Фигура " << (i + 1) << " ---" << endl;
        cout << "Выберите тип фигуры:" << endl;
        cout << "1 - Прямоугольник" << endl;
        cout << "2 - Трапеция" << endl;
        cout << "3 - Ромб" << endl;
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        shared_ptr<Figure<double>> fig = nullptr;

        try
        {
            if (choice == 1)
            {
                cout << "Введите 4 точки прямоугольника (x y для каждой):" << endl;
                auto rect = make_shared<Rectangle<double>>();
                cin >> *rect;
                fig = rect;
            }
            else if (choice == 2)
            {
                cout << "Введите 4 точки трапеции (x y для каждой):" << endl;
                auto trap = make_shared<Trapezoid<double>>();
                cin >> *trap;
                fig = trap;
            }
            else if (choice == 3)
            {
                cout << "Введите 4 точки ромба (x y для каждой):" << endl;
                auto rhomb = make_shared<Rhombus<double>>();
                cin >> *rhomb;
                fig = rhomb;
            }
            else
            {
                cout << "Неверный выбор, пропускаем фигуру" << endl;
                continue;
            }

            figures.add(fig);
            cout << "Фигура добавлена!" << endl;
        }
        catch (const exception &e)
        {
            cout << "Ошибка при создании фигуры: " << e.what() << endl;
            // shared_ptr автоматически освободит память при выходе из области видимости
        }
    }

    // выводим что получилось
    cout << "\n\n=== Созданные фигуры ===" << endl;
    cout << "Всего фигур: " << figures.getSize() << endl;

    for (size_t i = 0; i < figures.getSize(); ++i)
    {
        cout << "\nФигура " << (i + 1) << " (" << figures[i]->getTypeName() << "):" << endl;
        printFigureInfo(figures[i]);
    }

    // общая площадь
    if (figures.getSize() > 0)
    {
        double total = calculateTotalArea(figures);
        cout << "\nОбщая площадь всех фигур: " << fixed << setprecision(2) << total << endl;
    }

    // память очистится автоматически благодаря shared_ptr
}

// пример 5 - работа с массивом сырых указателей на базовый класс Figure*
// ВНИМАНИЕ: это единственное место где используются сырые указатели для демонстрации полиморфизма
void demonstrateRawPointerArray()
{
    cout << "\n=== Пример 5: Работа с Array<Figure<int>*> (массив сырых указателей) ===" << endl;
    cout << "ВНИМАНИЕ: Сырые указатели используются только для демонстрации требования лабораторной работы" << endl;

    Array<Figure<int> *> figures;

    try
    {
        // создаем фигуры через new и добавляем указатели в массив
        Figure<int> *rect = new Rectangle<int>(Point<int>(0, 0), Point<int>(5, 0),
                                               Point<int>(5, 4), Point<int>(0, 4));
        figures.add(rect);

        Figure<int> *trap = new Trapezoid<int>(Point<int>(0, 0), Point<int>(6, 0),
                                               Point<int>(4, 3), Point<int>(2, 3));
        figures.add(trap);

        Figure<int> *rhomb = new Rhombus<int>(Point<int>(3, 0), Point<int>(5, 2),
                                              Point<int>(3, 4), Point<int>(1, 2));
        figures.add(rhomb);

        cout << "\nКоличество фигур в массиве: " << figures.getSize() << endl;

        // демонстрируем полиморфизм - вызываем виртуальные методы через указатели базового класса
        cout << "\nИнформация о фигурах (через указатели на базовый класс):" << endl;
        for (size_t i = 0; i < figures.getSize(); ++i)
        {
            cout << "\nФигура " << (i + 1) << " (тип: " << figures[i]->getTypeName() << "):" << endl;
            cout << "  " << *figures[i] << endl;
            cout << "  Центр: " << figures[i]->getCenter() << endl;
            cout << "  Площадь: " << fixed << setprecision(2) << figures[i]->getArea() << endl;
        }

        // вычисляем общую площадь
        double totalArea = 0.0;
        for (size_t i = 0; i < figures.getSize(); ++i)
        {
            totalArea += figures[i]->getArea();
        }
        cout << "\nОбщая площадь всех фигур: " << fixed << setprecision(2) << totalArea << endl;

        // ВАЖНО: вручную освобождаем память (недостаток сырых указателей)
        cout << "\nОсвобождение памяти..." << endl;
        for (size_t i = 0; i < figures.getSize(); ++i)
        {
            delete figures[i];
        }
        cout << "Память освобождена вручную (delete для каждого указателя)" << endl;
    }
    catch (const exception &e)
    {
        // в случае ошибки нужно очистить память
        cerr << "Ошибка: " << e.what() << endl;
        for (size_t i = 0; i < figures.getSize(); ++i)
        {
            delete figures[i];
        }
        throw;
    }

    cout << "\nВЫВОД: Сырые указатели требуют ручного управления памятью." << endl;
    cout << "Рекомендуется использовать умные указатели (std::shared_ptr, std::unique_ptr)" << endl;
}

int main()
{

    try
    {
        // запускаем все примеры по очереди
        demonstratePolymorphicArray();
        demonstrateRectangleArray();
        demonstrateRhombusArray();
        demonstrateRawPointerArray();

        // ВАЖНО: пример с вводом из std::cin
        cout << "\n\n";
        cout << "Хотите ввести фигуры вручную из консоли? (y/n): ";
        char answer;
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            demonstrateInputFromConsole();
        }
    }
    catch (const exception &e)
    {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    cout << "\n\nПрограмма завершена успешно!" << endl;
    return 0;
}
