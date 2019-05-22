#ifndef TREE_H

#define TREE_H

#include <iostream>
#include "container.h"

// Описание функций в хэдере, потому что это шаблоны
// Можно было делать с tree.cpp, но его пришлось бы инклюдить
// Просто так работают шаболны

// Шаблон для структуры: Бинарное дерево

template <typename data_t>
class tree : public container<data_t>
        {
private:
            // Вложенный класс: узел дерева
	class node
	        {
	public:
		node* left;
		node* right;
		unsigned height;
		data_t val;

		node(data_t val);
		~node();

		node* insert(data_t val);
		node* remove(data_t val);
		bool exists(data_t val);
		void printNode();

		node* balance();
		int bfactor();

		node* rotateLeft();
		node* rotateRight();
		void fixHeight();

		node* findMin();
		node* removeMin();
	};

	node* root;

public:
	tree();
	~tree();

	//Вставка элемента в дерево (с последующими: пересчетом глубины и балансировкой)
	void insert(data_t z);

	//Наличие элемента дереве
	bool exists(data_t z);

	//Удаление элемента из дерева (с последующими: пересчетом глубины и балансировкой)
	void remove(data_t z);

	//Вывод дерева на экран
	void dump();
};

// Шаблон инициации пустого дерева
template <typename data_t>
tree<data_t>::tree()
{
    root = nullptr;
}

// Шаблон деструктора дерева
template <typename data_t>
tree<data_t>::~tree()
{
    delete root;

    root = nullptr;
}

// Шаблон вставки элемента в дерево
template <typename data_t>
void tree<data_t>::insert(data_t z)
{
    if (root == nullptr)
    {
        root = new node(z);
    } else {
        root = root->insert(z);
    }
}

// Шаблон проверки существования элемента в дереве
template <typename data_t>
bool tree<data_t>::exists(data_t z)
{
    if (root == nullptr)
    {
        std::cout << "Empty tree" << std::endl;
        return false;
    }
    return root->exists(z);
}

// Шаблон удаления элемента из дерева
template <typename data_t>
void tree<data_t>::remove(data_t z)
{
    root = root->remove(z);
}

// Шаблон вывода деерва на экран
template <typename data_t>
void tree<data_t>::dump()
{
    if (root == nullptr)
        std::cout << "Empty tree" << std::endl;

    root->printNode();
}

// Шаблон создания листа дерева
template <typename data_t>
tree<data_t>::node::node(data_t val) : val(val)
{
    left = nullptr;
    right = nullptr;
    height = 1;
}

// Шаблон деструктора узла дерева
template <typename data_t>
tree<data_t>::node::~node()
{
    delete left;
    delete right;
}

// Шаблон вставки элемента в дерево
template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::insert(data_t val)
{
    // Элементы меньше - налево, остальные направо
    // Рекурсивная вставка элементов
    if (val < this->val)
    {
        if (left == nullptr)
        {
            left = new node(val);
        }
        else
            {
            left = left->insert(val);
            }
    }
    else
        {
        if (right == nullptr)
        {
            right = new node(val);
        } else
            {
            right = right->insert(val);
            }
        }
    // Возвращаем сбалансированное дерево
    return balance();
}

// Шаблон для удаления элемента из дерева
// По сути: находим удаляемый элемент  - его удаляем - на его место ставим минимальный элемент в правом поддереве
template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::remove(data_t val)
{
    // Поиск, есть ли удалаемый элемент в дереве

    // Смотрим слева
    if (val < this->val)
    {
        if (left != nullptr)
        {
            left = left->remove(val);
        }
    }

    //Смотрим справа
    else if (val > this->val)
    {
        if (right != nullptr)
        {
            right = right->remove(val);
        }
    }
    // Если нашли элемент, то выполняем
    else
        {
        // Записываем дочерние ветки узла, который удаляем
        node* q = left;
        node* r = right;
        // Очищаем все что было внизу после элемента
        left = nullptr;
        right = nullptr;
        // Удаляем сам элемент
        delete this;
        // Если справа было пусто, двигаем нижний слева наверх
        if (r == nullptr)
            return q;
        // Иначе: ищем наименьший элемент в правой дочерней ветке
        node* min = r->findMin();
        // Удаляем наименьший узел снизу
        min->right = r->removeMin();
        // Поднимаем самый маленький узел наверх
        min->left = q;
        // Возвращаем корень поддерева
        return min->balance();
        }
    return balance();
}

// Балансировка дерева
template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::balance()
{
    //Обновляем все высоты
    fixHeight();

    // Если дерево перевесило справа, исправляем
    if (bfactor() == 2)
    {
        // Проверка, надо ли делать большой поворот дерева
        if (right->bfactor() < 0)
            right = right->rotateRight();

        return rotateLeft();
    }
    // Если дерево перевесило слева, исправляем
    if (bfactor() == -2)
    {
        // Проверка, надо ли делать большой поворот дерева
        if (left->bfactor() > 0)
            left = left->rotateLeft();

        return rotateRight();
    }
    // Возвращаем корень сбалансированного поддерева
    return this;
}

// Шаблон функции нахождения разности между высотами дочерних веток
// Если больше справа, то >0
template <typename data_t>
int tree<data_t>::node::bfactor()
{
    if (right != nullptr && left != nullptr)
    {
        return right->height - left->height;
    }

    if (right != nullptr)
        return right->height;

    if (left != nullptr)
        return left->height;

    return 0;
}

// Шаблон правого простого поворота дерева
template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::rotateRight()
{
    node* q = left;
    left = q->right;
    q->right = this;

    fixHeight();
    q->fixHeight();

    return q;
}

//Шаблон левого простого поворота дерева
template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::rotateLeft()
{
    node* q = right;
    right = q->left;
    q->left = this;

    fixHeight();
    q->fixHeight();

    return q;
}

// Большие повороты - это комбинации маленьких поворотов


// Шаблон функции корректировкивысот узлов
template <typename data_t>
void tree<data_t>::node::fixHeight()
{
    // Елси у узла есть деревья, то его высота это высота наибольшей ветки + 1
    if (left != nullptr && right != nullptr)
    {
        height = (left->height > right->height) ? (left->height) : (right->height) + 1;
        return;
    }

    if (left != nullptr)
    {
        height = left->height + 1;
        return;
    }

    if (right != nullptr)
    {
        height = right->height + 1;
        return;
    }

    height = 1;
}

// Шаблон функции нахождения минимального значения
template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::findMin()
{
    if (left == nullptr)
    {
        return this;
    }
    return left->findMin();
}

// Шаблон функции удаления минмального узла
template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::removeMin()
{
    if (left == nullptr)
    {
        return right;
    }
    left = left->removeMin();
    return balance();
}

// Шаблон функци нахождения узла
template <typename data_t>
bool tree<data_t>::node::exists(data_t val)
{
    if (val < this->val && left != nullptr)
    {
        return left->exists(val);
    }
    else if (val > this->val && right != nullptr)
    {
        return right->exists(val);
    }
    else if (val == this->val)
    {
        return true;
    }

    return false;
}

// Шаблон функции вывода поддерева
template <typename data_t>
void tree<data_t>::node::printNode()
{
    if (this == nullptr)
    {
        return;
    }

    std::cout << val << " height = " << height << std::endl;


    if (left != nullptr)
    {
        left->printNode();
    }
    if (right != nullptr)
    {
        right->printNode();
    }
}
#endif
