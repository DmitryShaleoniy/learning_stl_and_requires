#include "Container.h"
#include "Algorithm.h"
#include <iostream>

struct Goods
{
    uint32_t    m_id;                // Код товара
    std::string m_name;              // Название
    std::string m_manufacturer;      // Производитель
    std::string m_warehouse_address; // Адрес склада
    double      m_weight;            // Вес
    bool operator<(const Goods& other) {
        return m_name.size() < (other.m_name).size();
    }
};

struct Functor_weight {
    bool operator()(const Goods& el) {
        return (el.m_weight >= 40 && el.m_weight <= 90);
    }
};

struct Functor {
    bool operator()(const Goods& el) {
        return el.m_manufacturer == "Voronin Konstantin";
    }
};

int main() {
    std::initializer_list<Goods> i_list{
        {2248, "T-Shirts", "Voronin Konstantin", "Moscow", 80},
        {229, "Strawberry", "John", "Liverpool", 0.5},
        {230, "Drive", "Ryan Gosling", "Detroit",2000},
        {228, "Vaz 2108", "Rinat", "Yekaterinburg", 1000}
    };
    Deque <Goods> cont_1(i_list);
    std::cout << "cont_1:" << std::endl;
    auto print = [](Goods& el) {
        std::cout << "code = " << el.m_id << ", \tname: " << el.m_name << ", \tmanufacturer: " << el.m_manufacturer << ", \tadress: " << el.m_warehouse_address << ", \tweight: " << el.m_weight << std::endl;
        };
    forEach(cont_1.begin(), cont_1.end(), print);
    Deque <Goods> cont_2;
    Goods el1({ 1488, "Boots", "Kulakov Makar", "Belozerskiy", 45 });
    Goods el2({ 2005, "Dog candy", "Maxim Kudruavtsev", "Dubna", 55 });
    Goods el3({ 8841, "Chocolate", "Willy Wonka", "Saransk", 0.2 });
    Goods el4({ 1, "Sport magazine", "Voronin Konstantin", "Moscow", 80 });

    cont_2.pushBack(el1);
    cont_2.pushFront(el2);
    cont_2.pushFront(el4);
    DequeIterator <Goods> iter_cont2 = cont_2.begin() + 1;
    cont_2.insert(iter_cont2, el3);
    std::cout << std::endl << "cont_2:" << std::endl;
    forEach(cont_2.begin(), cont_2.end(), print);
    DequeIterator <Goods> iter_cont1 = cont_1.begin() + 2;
    cont_1.insert(iter_cont1, cont_2.begin(), cont_2.end());
    std::cout << std::endl << "inserted cont_1:" << std::endl;
    forEach(cont_1.begin(), cont_1.end(), print);
    Sort(cont_1.begin(), cont_1.end());
    std::cout << std::endl << "sorted cont_1:" << std::endl;
    forEach(cont_1.begin(), cont_1.end(), print);
    auto weig = [](Goods& el)->bool {
        int min = 40;
        int max = 60;
        if (el.m_weight >= min && el.m_weight <= max) {
            return 1;
        }
        return 0;
        };
    std::cout << std::endl << "first from cont_1 with weight 40 - 60:" << std::endl;
    iter_cont1 = findIf(cont_1.begin(), cont_1.end(), weig);
    print((*iter_cont1));
    iter_cont1->m_warehouse_address = "Moscow";
    std::cout << std::endl << "changed cont_1:" << std::endl;
    forEach(cont_1.begin(), cont_1.end(), print);
    int m_count = 0;
    auto count = [&m_count](Goods& el) {
        if (el.m_manufacturer == "Voronin Konstantin")
            m_count++;
        };
    forEach(cont_1.begin(), cont_1.end(), count);
    std::cout << std::endl << "number of goods of Voronin Konstantin = " << m_count << std::endl;
    Deque <Goods> cont_3(m_count);
    Functor f;
    copyIf(cont_1.begin(), cont_1.end(), cont_3.begin(), f);
    std::cout << std::endl << "new container of Voronin Konstantin goods:" << std::endl;
    forEach(cont_3.begin(), cont_3.end(), print);

    Functor_weight f_w;
    Deque <Goods> cont_front;
    front_insert_iterator_deq <Goods> frontIter (cont_front);
    copyIf(cont_1.begin(), cont_1.end(), frontIter, f_w);
    std::cout << std::endl << "new container cont_front goods with weight 40 - 90:" << std::endl;
    forEach(cont_front.begin(), cont_front.end(), print);
}