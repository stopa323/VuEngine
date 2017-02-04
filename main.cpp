/*
 * main.cpp
 */

#include "Engine/FEngine.h"
#include <iostream>
#include <memory>


int main() {

	std::unique_ptr<FEngine> Engine( new FEngine );

	/** Initialization **/
	try {
		Engine->Initialize();
	}
	catch ( std::runtime_error& err ) {
		std::exit( -1 );
	}

	Engine->GetEngineLoop()->Run();

	return 0;
}


