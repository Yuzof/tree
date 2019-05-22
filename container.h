#ifndef TREE_CONTAINER_H
#define TREE_CONTAINER_H

// шаблон класса контейнер
template <typename data_t>
class container
{
public:
    // Виртуальные методы, будут реализованы далее

    // Вставка элемента в контейнер
    virtual void insert(data_t value) = 0;

    // Проверка наличия элемента в контейнере
    virtual bool exists(data_t value) = 0;

    // Удаление элемента в контейнере
    virtual void remove(data_t value) = 0;

    // Вывод контейнера
    virtual void dump() = 0;

    // Виртуальный деструктор
    virtual ~container();
};

// Шаблон деструктора
template <typename data_t>
container<data_t>::~container() {}

#endif //TREE_CONTAINER_H
