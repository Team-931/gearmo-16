#include "OI.h"
#include "robotmap.h"
#include "Commands/Straightenup.h"
OI::OI() : driveStick(1), operatorStick(0),
  straightenup(&driveStick, 6),
# if ! usingnewstick
  // driveStick must be Gamepad, elevStick logitech
 speeder(&driveStick, 5)
# endif

{
	// Process operator interface input here.
  straightenup.WhileHeld(new ::Straightenup);
# if ! newdrivestick
  speeder.WhenPressed(new ::SpeedToggle);
# endif
}
