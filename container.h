#ifndef TREE_CONTAINER_H
#define TREE_CONTAINER_H

template <typename data_t>
class container
{
public:
    // Виртуальные методы, будут реализованы далее
    virtual void insert(data_t value) = 0;
    virtual bool exists(data_t value) = 0;
    virtual void remove(data_t value) = 0;
    // Это потом заменим на перегруженный оператор <<
    virtual void dump() = 0;

    // Виртуальный деструктор
    virtual ~container();
};

template <typename data_t>
container<data_t>::~container() {}

#endif //TREE_CONTAINER_H
