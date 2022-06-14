#pragma once
#include "Item.h"
#include "Grid.h"
#include "GridRow.h"
#include "IntegerItem.h"
#include "FloatItem.h"
#include "StringItem.h"
#include "ItemFactory.h"
#include<iostream>
#include<string>
using namespace std;
class Engine {
private:
    Grid* grid;
    bool isGridSet;
    string opernFileName;
    ItemFactory itemFactory;

    void printCommands();
    static Engine* inst_;
    Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    Grid* inputGridFromConsole();
    void saveAs(const string& fileName);
protected:
    int value_;
public:
    static Engine* getInstance();
    void run();
};
