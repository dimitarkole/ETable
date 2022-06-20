#include<stdlib.h>
#include "Engine.h"
Engine* Engine::inst_ = NULL;
size_t MAX_INPUT_LEN = 1024;

Engine::Engine() : value_(0) {
}

Engine* Engine::getInstance() {
    if (inst_ == NULL) {
        inst_ = new Engine();
    }

    return(inst_);
}

void Engine::run() {
    try
    {
        string command;
        system("CLS");
        printCommands();
        this->isGridSet = false;
        do {
            cout << "Input command" << endl;
            getline(cin, command);
            if (command == "Clear")
            {
                system("CLS");
            }
            else if (command == "Create grid")
            {
                inputGridFromConsole();
            }
            else if (command == "Print")
            {
                if (!isGridSet) {
                    cout << "No any data in grid" << endl;
                }
                else grid->printWithSpaces(cout);
            }
            else if (command.find("SaveAs") == 0)
            {
                string fileName = command.substr(command.find(' ') + 1);
                saveAs(fileName);
            }
            else if (command == "Save")
            {
                saveAs(this->openFileName);
            }
            else if (command.find("Read") == 0)
            {
                string fileName = command.substr(command.find(' ') + 1);
                readFrom(fileName);
            }
            else if (command.find("Edit") == 0)
            {
                changeItem(command.substr(command.find(' ') + 1));
            }
            else if (command == "Help")
            {
                system("CLS");
                printCommands();
            }
            else {
                cout << "Wrong command" << endl;
            }
        } while (command != "End");
        delete this->grid;
    }
    catch (const std::exception& ex)
    {
        cout << "ERR: " << ex.what();
        delete this->grid;
    }
}

void Engine::printCommands()
{
    cout << "Commands:" << endl;
    cout << "Create grid" << endl;
    cout << "Print" << endl;
    cout << "Save" << endl;
    cout << "SaveAs fileName.dat" << endl;
    cout << "Read fileName.dat" << endl;
    cout << "Edit row col data" << endl;
    cout << "Help" << endl;
    cout << "Clear" << endl;
    cout << "End" << endl;
}

void Engine::inputGridFromConsole() {
    if (!willRefillGrid()) return;
    cout << "Input grid size: ";
    size_t size;
    cin >> size;
    Grid* grid = new Grid(size);
    cout << "Set data in grid: (row col data/End)" << endl;
    string data = "";
    char newLine = '\n';
    size_t indexOfEndOfRow, indexOfEndOfCol, col, row;
    cin.get(newLine);
    getline(cin, data, '\n');
    while (data != "End") {
        changeItem(data);
        getline(cin, data);
    }

    delete this->grid;
    this->grid = grid;
    isGridSet = true;
}

void Engine::saveAs(const string& fileName) const {
    if (!isGridSet) { 
        cout << "No any data in grid" << endl;
        return; 
    }

    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "File is not opened!" << endl;
        return;
    }

    try
    {
        grid->print(file);
    }
    catch (const std::exception&)
    {
    }
}

void Engine::readFrom(const string& fileName) {
    if (!willRefillGrid()) return;

    this->openFileName = fileName;
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "File is not opened!" << endl;
        return;
    }

    try
    {
        size_t size;
        file >> size;
        Grid* grid = new Grid(size);
        grid->read(file);
        delete this->grid;
        this->grid = grid;
        isGridSet = true;
    }
    catch (const std::exception&)
    {
    }
}

void Engine::changeItem(const string& data) {
    if (!isGridSet) {
        cout << "No any data in grid" << endl;
        return;
    }
    size_t indexOfEndOfRow, indexOfEndOfCol, col, row;
    indexOfEndOfRow = data.find(' ');
    indexOfEndOfCol = data.find(' ', indexOfEndOfRow + 1);
    row = convertToNumber(data.substr(0, indexOfEndOfRow));
    col = convertToNumber(data.substr(indexOfEndOfRow + 1, indexOfEndOfCol - 2));
    string itemData = data.substr(indexOfEndOfCol + 1);
    Item* item = itemFactory.createItem(itemData);
    grid->setItem(row, col, item);
    delete item;
    return;
}

bool Engine::willRefillGrid()
{
    if (isGridSet)
    {
        cout << "Grid is full. Do you want to change it? Yes/No" << endl;
        string response;
        getline(cin, response, '\n');
        if (response != "Yes") return false;
        else delete grid;
    }

    return true;
}