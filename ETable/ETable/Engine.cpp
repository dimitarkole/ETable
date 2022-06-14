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
        do {
            cout << "Input command" << endl;
            getline(cin, command);
            if (command == "Create grid")
            {
                grid = inputGridFromConsole();
            }
            else if (command == "Print grid")
            {
                grid->Print(cout);
            }
            else if (command.find("SaveAs") == 0)
            {
                string fileName = command.substr(command.find(' ') + 1);
                saveAs(fileName);
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
    }
    catch (const std::exception& ex)
    {
        cout << "ERR: " << ex.what();
    }
}

void Engine::printCommands()
{
    cout << "Commands:" << endl;
    cout << "Create grid" << endl;
    cout << "Print grid" << endl;
    cout << "SaveAs fileName.dat" << endl;
    cout << "Help" << endl;
    cout << "End" << endl;
}

Grid* Engine::inputGridFromConsole() {
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
        indexOfEndOfRow = data.find(' ');
        indexOfEndOfCol = data.find(' ', indexOfEndOfRow + 1);
        row = convertToNumber(data.substr(0, indexOfEndOfRow));
        col = convertToNumber(data.substr(indexOfEndOfRow + 1, indexOfEndOfCol - 2));
        string itemData = data.substr(indexOfEndOfCol + 1);
        Item* item = itemFactory.createItem(itemData);
        grid->setItem(row, col, item);
        getline(cin, data);
    }

    return grid;
}

void Engine::saveAs(const string& fileName) {
    ofstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cout << "File is not opened!" << endl;
        return;
    }

    try
    {
        grid->Print(file);
    }
    catch (const std::exception&)
    {
    }
}