#pragma once
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ItemFactory.h"
#include "grid.h"

ItemFactory itemFactory;

TEST_SUITE("Tests")
{
    TEST_CASE("set integer item to grid and get it from grid")
    {
        // Arrange
        Grid grid(5);
        const size_t row = 1, col = 1;
        const string data = "5";
        Item* item = itemFactory.createItem(data);

        // Act
        grid.setItem(row, col, item);

        // Check
        CHECK(grid.getItemValue(row, col) == 5);
        delete item;
    }


    TEST_CASE("set float item to grid and get it from grid")
    {
        // Arrange
        Grid grid(5);
        const size_t row = 1, col = 1;
        const string data = "5.25";
        cout << data;
        Item* item = itemFactory.createItem(data);

        // Act
        grid.setItem(row, col, item);

        // Check
        CHECK(grid.getItemValue(row, col) == 5.25);
        delete item;
    }

    TEST_CASE("set text to grid and get it from grid")
    {
        // Arrange
        Grid grid(5);
        const size_t row = 1, col = 1;
        const string data = "Hi, I am here!";
        cout << data;
        Item* item = itemFactory.createItem(data);

        // Act
        grid.setItem(row, col, item);

        // Check
        CHECK(grid.getItemValue(row, col) == 0);
        delete item;
    }
}