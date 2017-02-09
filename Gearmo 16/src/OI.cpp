#include "OI.h"
#include "robotmap.h"
#include "Commands/Straightenup.h"
#include "Commands/MoveElevator.h"

static const float elevLevels[] ={0, levelSize, 2*levelSize};
static const size_t numLevels = sizeof(elevLevels)/sizeof(float);
static size_t level = 0,
  incLevel(), decLevel();

OI::OI() : driveStick(1), elevStick(2),
  straightenup(&driveStick, 6),
# if ! usingnewstick
  // driveStick must be Gamepad, elevStick logitech
 speeder(&driveStick, 5),
# endif
 elevUp(&elevStick, 4), elevDown(&elevStick, 2),
 elevStop(&elevStick, 10)
{
	// Process operator interface input here.
  straightenup.WhileHeld(new ::Straightenup);
# if ! newdrivestick
  speeder.WhenPressed(new ::SpeedToggle);
# endif
//  elevUp.WhenPressed(new ::MoveElevatorTo(elevLevels[incLevel()]));
//  elevDown.WhenPressed(new ::MoveElevatorTo(elevLevels[decLevel()]));
//  elevStop.WhenPressed(new ::StopElev);
}

size_t incLevel()
 {if (level != numLevels - 1) ++ level;
  return level;}

size_t decLevel()
 {if (level != 0) -- level;
  return level;}
