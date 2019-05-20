#include "tree.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

int main()
{
	container<int> *t = new tree<int>();

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
            printf("enter - insert a new element to the tree\n");
            printf("remove - remove an element\n");
            printf("dump - print the whole tree\n");
            printf("fmin - find the min element\n");
            printf("BalInf - balance theory\n");
            printf("removemin - remove the least element");
            printf("wq");
            printf("\n");

            d = 1;
        }

        if (strcmp("enter", com) == 0)
        {
            printf("Type element value\n");

            scanf("%d", &a);

           t->insert(a);

            d = 1;
        }

        if (strcmp("dump", com) == 0)
        {
            t->dump();

            d = 1;
        }

        if (strcmp("remove", com) == 0)
        {
            std::cout << "Type element value" << std::endl;

            std::cin >> a;

            t->remove(a);

            d = 1;
        }

        if (strcmp("exists", com)==0)
        {
            std::cout << "Type an element you want to check" << std::endl;

            std::cin >> a;

            std::cout << t->exists(a) << std::endl;

            d = 1;
        }


        if (strcmp("BalInf", com) == 0)
        {
            printf("Reference balance commands\n");
            printf("RR - simple right rotation\n");
            printf("RL - simple left rotation\n");
            printf("HR - complicated right rotation\n");
            printf("HL - complicated left rotation\n");
            printf("Type a theory command\n");

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