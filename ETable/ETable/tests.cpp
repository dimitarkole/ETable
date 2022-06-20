#pragma once
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ItemFactory.h"
#include "grid.h"

ItemFactory itemFactory;

TEST_SUITE("Item Tests")
{
    TEST_CASE("set integer item")
    {
        // Arrange
        const string data = "5";
        Item* item = itemFactory.createItem(data);

        // Check
        CHECK(item->getValue() == 5);
        delete item;
    }


    TEST_CASE("set float item")
    {
        // Arrange
        const string data = "5.25";
        Item* item = itemFactory.createItem(data);

        // Check
        CHECK(item->getValue() == 5.25);
        delete item;
    }

    TEST_CASE("set text")
    {
        // Arrange
        const string data = "Hi, I am a big boy!";
        Item* item = itemFactory.createItem(data);

        // Check
        CHECK(item->getData() == data);
        delete item;
    }
}

TEST_SUITE("Grid Tests")
{
    TEST_CASE("calculateFormula with numbers only")
    {
        // Arrange
        Grid grid(5, 5);
        const string formula = "= 10 + 10 * 2 - 5";

        // Act
        Item* result = grid.calculateFormula(formula);

        // Check
        CHECK(result->getValue() == 25);
        delete result;
    }

    TEST_CASE("set item with formula to grid and get it from grid")
    {
        // Arrange
        Grid grid(5, 5);
        const size_t row = 1, col = 1;
        const string data = "= 5";
        Item* item = itemFactory.createItem(data);

        // Act
        grid.setItem(row, col, item);

        // Check
        CHECK(grid.getItemValue(row, col) == 5);
        delete item;
    }

    TEST_CASE("set item with formula to grid using value from grid and get it from grid")
    {
        // Arrange
        Grid grid(5, 5);
        const size_t row = 1, col = 1;
        const string data = "= 5 + R1C2";
        grid.setItem(1, 2, "2");
        Item* item = itemFactory.createItem(data);

        // Act
        grid.setItem(row, col, item);

        // Check
        CHECK(grid.getItemValue(row, col) == 7);
        delete item;
    }

    TEST_CASE("set item with formula to grid using value from grid and get it from grid")
    {
        // Arrange
        Grid grid(2, 3);
        grid.setItem(1, 1, "10");
        grid.setItem(1, 2, "Hello world!");
        grid.setItem(1, 3, "123,56");
        grid.setItem(2, 1, "123");
        const string fromula1 = "= R1C1 + R1C3";
        const string fromula2 = "= R1C1 * R1C2";
        const string fromula3 = "= R1C1 * R2C1";
        const string fromula4 = "= R1C1 * R2C2";

        // Act
        Item* result1 = grid.calculateFormula(fromula1);
        Item* result2 = grid.calculateFormula(fromula2);
        Item* result3 = grid.calculateFormula(fromula3);
        Item* result4 = grid.calculateFormula(fromula4);

        // Check
        CHECK(result1->getValue() == 133.56f);
        CHECK(result2->getValue() == 0);
        CHECK(result3->getValue() == 1230);
        CHECK(result4->getValue() == 0);
        delete result1;
        delete result2;
        delete result3;
        delete result4;
    }

    TEST_CASE("set item with formula to grid using value from grid and get it from grid")
    {
        // Arrange
        Grid grid(5, 5);
        const size_t row = 1, col = 1;
        const string data = "= 5 + 2 * R1C2";
        grid.setItem(1, 2, "2");
        Item* item = itemFactory.createItem(data);

        // Act
        grid.setItem(row, col, item);

        // Check
        CHECK(grid.getItemValue(row, col) == 9);
        delete item;
    }

    TEST_CASE("set integer item to grid and get it from grid")
    {
        // Arrange
        Grid grid(5, 5);
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
        Grid grid(5, 5);
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
        Grid grid(5, 5);
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
