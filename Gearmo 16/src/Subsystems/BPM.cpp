#include "BPM.h"
#include "../RobotMap.h"
#include "Commands/PickUp.h"

BPM::BPM() : Subsystem("BallPickupMechanism"), bpMotor(11) {
}

void BPM::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new PickUp(false));
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void BPM::Run(bool runMotor) {
	if(runMotor) bpMotor.Set(1); //check polarity
	else bpMotor.Set(0);
}
