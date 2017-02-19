/*
 * TestPersoShift.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Developer
 */

#include "Commands/TestPersoShift.h"
#include "Commands/AutoSimple.h"
#include "Commands/ToggleThirdPerson.h"

TestPersoShift::TestPersoShift() :
	CommandGroup("Test Third->First Shift while moving")
{
	AddSequential(new ToggleThirdPerson);
	AddSequential(new AutoSimple);
	AddSequential(new WaitCommand(1));
	AddSequential(new ToggleThirdPerson);
	AddSequential(new WaitCommand(1));
}

