#include "Winch.h"
#include "../RobotMap.h"
#include "Commands/RopeClimb.h"

Winch::Winch() : Subsystem("Rope Climb"), everest(12) {

}

void Winch::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new RopeClimb(false));
}
//xxx delete me

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Winch::Climb(bool runMotor) {
	if(runMotor)
	everest.Set(1);
	else everest.Set(0);
}
