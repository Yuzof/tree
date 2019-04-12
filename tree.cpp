#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tree_value
{
    int inf;
    int height;
    int depeche_mode;
    int balance_factor;
    struct tree_value* left;
    struct tree_value* right;
    struct tree_value* maternal;
}TREE;

int depth(TREE* p)
{
    return p->height;
}

int bfactor(TREE* p)
{
	if (p == NULL)
	{
		printf("bfactor mistake: NULL node\n");
		return 0;
	}
	if ((p->left == NULL) && (p->right != NULL))
	{
		return p->right->height;
	}
	if ((p->right == NULL) && (p->left != NULL))
	{
		return p->left->height;
	}
	if ((p->left == NULL) && (p->right == NULL))
	{
		printf("bfactor mistake: NULL pointers\n");
		return 0;
	}
    return (p->right->height) - (p-> left->height);
}

void fixheight (TREE* p)
{
	if (p == NULL)
		return;
	if ((p->left == NULL) || (p->right == NULL)) 
	{
		return;
	}
    if (p->left->height > p->right->height)
        p->height = p->left->height + 1;
    else
        p->height = p->right->height + 1;
}

TREE* rotateright(TREE* p) //правый поворот
{
    TREE* q = p->left; // отцепил от дерева его левое поддерево
    p->left = q->right; // отцепил от отцепленного дерева его правую ветку и прицеил ее слева к первому дереву
    q->right = p;  // к первой отцепленной прицепил справа то, что раньше было головой
    fixheight(p); // выжен пор€док исправлени€ глубины: сначало то, что получилось дочерним
    fixheight(q);
    return q; //вернул указатель на голову сбалансированного дерева
}

TREE* rotateleft(TREE* p) // левый поворот; абсолютно аналогично правому
{
    TREE* q = p-> right;
    p->right = q->left;
    q->left = p;
    fixheight(p);
    fixheight(q);
    return q;
}
/*
Ѕалансировка сложной ротацией - это композици€ двух простых поворотов.
–ассмотрим правый поворот



*/

TREE* balance(TREE* p)
{
    fixheight(p); // обновл€ем значение глубины дерева
    if (bfactor(p) >= 2) // провер€ем, есть ли расбалансировка дерева. ѕровер€ем, если справа расбалансировалось
    {
        if (bfactor(p->right) < 0) // проверка, какой поворот делать (в любом случае делаем хоть один, ведь есть расбалансировка)
            p->right = rotateright(p->right); // делаем сложный поворот
        return rotateleft(p); // делаем простой поворот или завершаем сложный
    }
    if (bfactor(p) <= -2) // провер€ем, есть ли расбалансировка дерева. ѕровер€ем,если слева расбалансировалось
    {
        if (bfactor(p->left) > 0) //провер€ем,какой поворот делать
            p->left = rotateleft(p->left); // делаем сложный
        return rotateright(p); // делаем простой или завершаем сложынй
    }
    return p; // корень сбалансированного дерева (|bfactor| < 1) если балансировка не нужна
}

void goup(TREE* root)
{

    if (root->maternal == NULL)
    {
        return;
    }
    else if ((((root->left == NULL) && ( root->right == NULL)) && ((root->maternal->left != NULL) && (root->maternal->left != root) ) || ((root->maternal->right != NULL) && (root->maternal->right != root))) && (root->height == 0))
    {
        return;
    }
    else
    {
		if (root->maternal->height < (root->height + 1))
		{
			root->maternal->height = root->height + 1;
		}
		root=root->maternal;
        goup(root);
    }
	if (root->maternal != NULL)
	{
		if (root->maternal->maternal == NULL) root->maternal->height = root->height + 1;
	}
	return;

}

TREE* insert(TREE* root, int x, int i, TREE* mum)
{
    if (root == NULL)
    {
        root = (TREE*) calloc(1,sizeof(TREE));

        root->inf = x;
        root->depeche_mode = i;
        root->balance_factor = 0;
        root->maternal = mum;
        root->left = root->right = NULL;

        goup(root);
		balance(root->maternal);
    }
    else
    {
        if (x < root->inf)
        {
            root->left = insert(root->left, x, i+1, root);
        }
        else
        {
            root->right = insert(root->right, x, i+1, root);
        }
    }
	
    return root;
}


void priTre(TREE *root)
{
	if (root == NULL)
	{
		printf("Empty tree\n");
		return;
	}
	printf("%10d   ", root->inf);
	printf("depth %2d   ", root->depeche_mode);
	printf("height %2d\n", root->height);

    if (root->left != NULL)
        priTre(root->left);

    if (root->right != NULL)
        priTre(root->right);
}

int main()
{
    TREE* mytree = NULL;
    int a, d;
    char com[20];

    printf("Start\n");
    printf("\n");
    printf("\n");

    while (strcmp("wq", com) != 0)
    {
        d = 0;

        printf("Type command\n");

        scanf("%s", com);

        if (strcmp("help", com) == 0)
        {
            printf("The list of commands\n");
            printf("enter - insert a new element to a tree\n");
            printf("           delete - remove an element from tree\n");
            printf("priTre - print the whole tree\n");
            printf("           fixheight - fix current depth of already fixed roots\n");
            printf("           depth - shows the depth of a current node\n");
            printf("bfactor - shows the difference between depths\n");
            printf("bal - balance the tree and show after\n");
            printf("BalInf - balance theory\n");
            printf("\n");

            d = 1;
        }

        if (strcmp("enter", com) == 0)
        {
            printf("Type element value\n");

            scanf("%d", &a);

            mytree = insert(mytree, a, 1, NULL);

            d = 1;
        }

		if (strcmp("bfactor", com) == 0)
		{
			d = bfactor(mytree);

			printf("The difference between subsidiary branches is %d\n", d);

			d = 1;
		}
        if (strcmp("priTre", com) == 0)
        {
            priTre(mytree);

            d = 1;
        }

        if (strcmp("bal", com) == 0)
        {
            mytree = balance(mytree);

            priTre(mytree);

            d = 1;
        }

        if (strcmp("BalInf", com) == 0)
        {
            printf("Reference balance commands\n");
            printf("RR - simple right rotation\n");
            printf("RL - simple left rotation\n");
            printf("HR - complicated right rotation\n");
            printf("HL - complicated left rotation\n");
            printf("Type command\n");
            scanf("%s", com);
            if (strcmp("RR", com) == 0)
            {

            }
            if (strcmp("RL", com) == 0)
            {

            }
            if (strcmp("HR", com) == 0)
            {

            }
            if (strcmp("HL", com) == 0)
            {

            }
            d = 1;
        }

        if ((d == 0) && (strcmp("wq", com) != 0))

        {
            printf("Incorrect syntax\n");
            printf("Type 'help' to see hints\n");
        }
    }

    return 0;
}




