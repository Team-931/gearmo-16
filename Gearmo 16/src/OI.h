#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI
{
private:
  Joystick driveStick, operatorStick;
  JoystickButton straightenup,
# if ! usingnewstick
  speeder
# endif
;
public:
	OI();
	Joystick & DriveStick(), &OperatorStick();
	JoystickButton & Straightenup();
# if ! usingnewstick
	JoystickButton & Speeder();
# endif
};

inline Joystick & OI::DriveStick()
 {return driveStick;}

inline Joystick & OI::OperatorStick()
 {return operatorStick;}

inline JoystickButton & OI::Straightenup()
 {return straightenup;}

# if ! usingnewstick
inline JoystickButton & OI::Speeder()
 {return speeder;}
# endif
#endif
