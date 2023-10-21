#include <iostream>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <iterator> // std::begin and std::end
#include "AVLTree.h"

int main()
{

    int asc[50], dsc[50], shf[50];
    AVLTree<int> ascTree, dscTree, shfTree;

    for (int i = 0; i < 50; i++)
    {
        asc[i] = 1 + i * 2;
        dsc[i] = 99 - i * 2;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::copy(std::begin(asc), std::end(asc), std::begin(shf));
    shuffle(std::begin(shf), std::end(shf), std::default_random_engine(seed));

    for (int i = 0; i < 50; i++)
    {
        ascTree.insert( asc[i] );
        dscTree.insert( dsc[i] );
        shfTree.insert( shf[i] );
    }

    std::cout << "Height of ascending tree: " << ascTree.height() << "\nValidity of ascending tree: " << ascTree.validate() << std::endl;
    std::cout << "Height of descending tree: " << dscTree.height() << "\nValidity of descending tree: " << dscTree.validate() << std::endl;
    std::cout << "Height of shuffled tree: " << shfTree.height() << "\nValidity of shuffled tree: " << shfTree.validate() << std::endl;

    for (int i = 1; i <= 100; i++)
    {
        if (i % 2 == 1 && !ascTree.contains(i))
        {
            std::cout << "My AVL implementation is wrong for ascending tree";
        }

        else if (i % 2 == 0 && ascTree.contains(i))
        {
            std::cout << "My AVL implementation is wrong for ascending tree";
        }

        if (i % 2 == 1 && !dscTree.contains(i))
        {
            std::cout << "My AVL implementation is wrong for descending tree";
        }

        else if (i % 2 == 0 && dscTree.contains(i))
        {
            std::cout << "My AVL implementation is wrong for descending tree";
        }

        if (i % 2 == 1 && !ascTree.contains(i))
        {
            std::cout << "My AVL implementation is wrong for shuffled tree";
        }

        else if (i % 2 == 0 && ascTree.contains(i))
        {
            std::cout << "My AVL implementation is wrong for shuffled tree";
        }
    }

    return 0;
}