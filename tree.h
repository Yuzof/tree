#ifndef TREE_H

#define TREE_H

#include <iostream>

template <typename data_t>
class tree {
private:
	class node {
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

template <typename data_t>
tree<data_t>::tree() {
    root = nullptr;
}

template <typename data_t>
tree<data_t>::~tree() {
    delete root;

    root = nullptr;
}

template <typename data_t>
void tree<data_t>::insert(data_t z) {
    if (root == nullptr) {
        root = new node(z);
    } else {
        root = root->insert(z);
    }
}

template <typename data_t>
bool tree<data_t>::exists(data_t z) {
    return root->exists(z);
}

template <typename data_t>
void tree<data_t>::remove(data_t z) {
    root->remove(z);
}

template <typename data_t>
void tree<data_t>::dump() {
    if (root == nullptr)
        std::cout << "Empty tree" << std::endl;

    root->printNode();
}

template <typename data_t>
tree<data_t>::node::node(data_t val) : val(val) {
    left = nullptr;
    right = nullptr;
    height = 1;
}

template <typename data_t>
tree<data_t>::node::~node(){
    delete left;
    delete right;
}

template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::insert(data_t val) {
    if (val < this->val) {
        if (left == nullptr) {
            left = new node(val);
        } else {
            left->insert(val);
        }
    } else {
        if (right == nullptr) {
            right = new node(val);
        } else {
            right->insert(val);
        }
    }

    return balance();
}

template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::remove(data_t val) {

    if (val < this->val) {
        if (left != nullptr) {
            left = left->remove(val);
        }
    } else if (val > this->val) {
        if (right != nullptr) {
            right = right->remove(val);
        }
    } else { // found val
        node* q = left;
        node* r = right;
        left = nullptr;
        right = nullptr;
        delete this;
        if (r == nullptr)
            return q;
        node* min = r->findMin();
        min->right = r->removeMin();
        min->left = q;
        return min->balance();
    }
    return balance();
}

template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::balance() {
    fixHeight();

    if (bfactor() == 2) {
        if (right->bfactor() < 0)
            right = right->rotateRight();
        return rotateLeft();
    }
    if (bfactor() == -2) {
        if (left->bfactor() > 0)
            left = left->rotateLeft();
        return rotateRight();
    }
    return this;
}

template <typename data_t>
int tree<data_t>::node::bfactor() {
    if (right != nullptr && left != nullptr) {
        return right->height - left->height;
    }

    if (right != nullptr)
        return right->height;

    if (left != nullptr)
        return left->height;

    return 0;
}

template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::rotateRight() {
    node* q = left;
    left = q->right;
    q->right = this;

    fixHeight();
    q->fixHeight();

    return q;
}

template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::rotateLeft() {
    node* q = right;
    right = q->left;
    q->left = this;

    fixHeight();
    q->fixHeight();

    return q;
}

template <typename data_t>
void tree<data_t>::node::fixHeight() {
    if (left != nullptr && right != nullptr) {
        height = (left->height > right->height) ? (left->height) : (right->height) + 1;
        return;
    }

    if (left != nullptr) {
        height = left->height + 1;
        return;
    }

    if (right != nullptr) {
        height = right->height + 1;
        return;
    }

    height = 0;
}

template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::findMin() {
    if (left == nullptr) {
        return this;
    }
    return left->findMin();
}

template <typename data_t>
typename tree<data_t>::node* tree<data_t>::node::removeMin() {
    if (left == nullptr) {
        return right;
    }
    left = left->removeMin();
    return balance();
}

template <typename data_t>
bool tree<data_t>::node::exists(data_t val) {
    if (val < this->val && left != nullptr) {
        return left->exists(val);
    } else if (val > this->val && right != nullptr) {
        return right->exists(val);
    } else if (val == this->val) {
        return true;
    }

    return false;
}

template <typename data_t>
void tree<data_t>::node::printNode() {
    std::cout << val << " height = " << height << std::endl;
    if (left != nullptr) {
        left->printNode();
    }
    if (right != nullptr) {
        right->printNode();
    }
    std::cout << std::endl;
}
#endif
