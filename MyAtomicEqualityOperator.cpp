/* 
   Конструктор принимает начальныое значение и передаёт std::atomic ДАЛЕЕ конструктор копирования вызывает функцию load() - 
   это всё мы делаем для получения атомарного значения из другого объекта ДАЛЕЕ оператор присваивания вызывает store() и load() для атомарной синхронизации
   и мы получаем класс который ведёт себя как атомарный инт, но присваивание и коприрование происхоят не целочисленные побитовые, а атомарно 
*/


#include <iostream>
#include <atomic>

class YourAtomic : public std::atomic<int> {
public:
    YourAtomic(int initial = 0) : std::atomic<int>(initial) {}

    YourAtomic(const YourAtomic& other) : std::atomic<int>(other.load()) {}

    YourAtomic& operator=(const YourAtomic& other) {
        this->store(other.load());
        return *this;
    }
};

int main() {

    YourAtomic a1(5);
    std::cout << "a1: " << a1.load() << std::endl;

    YourAtomic a2 = a1;
    std::cout << "a2: " << a2.load() << std::endl;

    YourAtomic a3;
    a3 = a1;
    std::cout << "a3: " << a3.load() << std::endl;

    return 0;
}
