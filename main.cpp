#include "tree.h"

int main() {
	tree<int> t;

	t.insert(1);
	t.insert(2);
	t.insert(-1);

	t.dump();

	t.remove(2);

	t.dump();
}