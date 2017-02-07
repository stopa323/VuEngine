/*
 * main.cpp
 */

#include "Engine/FEngine.h"
#include "Engine/DummyPlayerController.h"
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

	DummyPlayerController dpc = DummyPlayerController();
	std::function<void(DummyPlayerController&)> f = &DummyPlayerController::Leszke;
	std::function<void(DummyPlayerController&)> g = &DummyPlayerController::Doniesiesz;
	Engine->GetInputManager()->BindAction(EMouseEvent::LMB_PRESS, &dpc, f);
	Engine->GetInputManager()->BindAction(EMouseEvent::RMB_PRESS, &dpc, g);

	Engine->GetEngineLoop()->Run();

	return 0;
}


