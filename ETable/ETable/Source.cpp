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
