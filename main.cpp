/*
 * main.cpp
 */

#include "Engine/FEngine.h"
#include "Engine/Game/Controller/FPlayerController.h"
#include "Engine/Game/Entity/FPawn.h"
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

	FPawn* Pawn = new FPawn();
	FPlayerController* PlayerController = new FPlayerController();

	PlayerController->Possess( Pawn );

	Engine->GetInputManager()->BindAction(EMouseEvent::LMB_PRESS,
			PlayerController, &FPlayerController::Event_InputAxisHorizontal);

	Engine->GetEngineLoop()->Run();

	delete PlayerController;
	delete Pawn;

	return 0;
}


