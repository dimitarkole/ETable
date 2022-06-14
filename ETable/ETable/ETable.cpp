#include <iostream>
#include "Grid.h"
#include "GridRow.h"
#include <iostream>
#include "Engine.h"

int main()
{
	Engine* e = Engine::getInstance();
	e->run();
	return 0;
}

//
//#include "IntegerItem.h"
//#include "FloatItem.h"
//#include "StringItem.h"
//using namespace std;
//int main()
//{
//
//	try
//	{
//		size_t size = 5;
//		Grid myGrid(size);
//		IntegerItem i(5);
//		StringItem s("dsadsa");
//		FloatItem f(2.5);
//		myGrid.setItem(0, 0, i);
//		myGrid.setItem(3, 3, s);
//		myGrid.setItem(4, 0, f);
//		myGrid.Print(cout);
//	}
//	catch (const char* ex)
//	{
//		cout << ex;
//	}
//
//}
