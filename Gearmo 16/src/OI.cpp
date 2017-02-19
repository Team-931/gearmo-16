#include "OI.h"
#include "robotmap.h"
#include "Commands/Straightenup.h"
#include "Commands/GearForward.h"
#include "Commands/TestPersoShift.h"
#include "Commands/ToggleThirdPerson.h"
#include "Commands/RopeClimb.h"

/*struct POVShift : CommandBase
	{
	POVShift() {}
	void Initialize()
	{swerveDrive ->ClickOrient();}
	bool IsFinished() {return true;}
	};
*/

OI::OI() : driveStick(1), operatorStick(0),
  straightenup(&driveStick, 6),
# if ! usingnewstick
  // driveStick must be Gamepad, elevStick logitech
 speeder(&driveStick, 5)
# endif

{	// Process operator interface input here.
  straightenup.WhileHeld(new ::Straightenup);
# if ! newdrivestick
  speeder.WhenPressed(new ::SpeedToggle);
# endif
  Button * personToggle = new JoystickButton(&driveStick, 3);
  SmartDashboard::PutData(new TestPersoShift);
  personToggle->WhenPressed(new ToggleThirdPerson);
//  (new  JoystickButton(&driveStick, 4)) -> WhenPressed(new POVShift);
  //driveStick.GetPOV();

  SmartDashboard::PutData(new GearForward);
  SmartDashboard::PutData(new RopeClimb(true));



}
