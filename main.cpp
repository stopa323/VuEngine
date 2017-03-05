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

	Engine->GetInputManager()->BindAction(EKeyboardKey::KEY_UP, EInputModifier::NOOP,
			EInputType::PRESSED, PlayerController, &FPlayerController::Event_InputMoveForward);
	Engine->GetInputManager()->BindAction(EKeyboardKey::KEY_DOWN, EInputModifier::NOOP,
			EInputType::PRESSED, PlayerController, &FPlayerController::Event_InputMoveBackward);
	Engine->GetInputManager()->BindAction(EKeyboardKey::KEY_RIGHT, EInputModifier::NOOP,
			EInputType::PRESSED, PlayerController, &FPlayerController::Event_InputMoveRight);
	Engine->GetInputManager()->BindAction(EKeyboardKey::KEY_LEFT, EInputModifier::NOOP,
			EInputType::PRESSED, PlayerController, &FPlayerController::Event_InputMoveLeft);

	Engine->GetInputManager()->BindAction(EKeyboardKey::KEY_UP, EInputModifier::NOOP,
			EInputType::RELEASED, PlayerController, &FPlayerController::Event_RELEASE_InputMoveForward);
	Engine->GetInputManager()->BindAction(EKeyboardKey::KEY_DOWN, EInputModifier::NOOP,
			EInputType::RELEASED, PlayerController, &FPlayerController::Event_RELEASE_InputMoveBackward);
	Engine->GetInputManager()->BindAction(EKeyboardKey::KEY_RIGHT, EInputModifier::NOOP,
			EInputType::RELEASED, PlayerController, &FPlayerController::Event_RELEASE_InputMoveRight);
	Engine->GetInputManager()->BindAction(EKeyboardKey::KEY_LEFT, EInputModifier::NOOP,
			EInputType::RELEASED, PlayerController, &FPlayerController::Event_RELEASE_InputMoveLeft);


	Engine->GetPhysicsEngine()->RegisterTickableObjects( PlayerController );

	Engine->GetEngineLoop()->Run();

	delete PlayerController;
	delete Pawn;

	return 0;
}


