#pragma once
#include "Item.h"
#include "Grid.h"
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
    string openFileName;
    ItemFactory itemFactory;

    void printCommands();
    static Engine* inst_;

    Engine();
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    void inputGridFromConsole();
    void changeItem(const string& data);
    void saveAs(const string& fileName) const;
    void readFrom(const string& fileName);
    bool willRefillGrid();
protected:
    int value_;
public:
    static Engine* getInstance();
    void run();
};
