#ifndef Winch_H
#define Winch_H

#include <Commands/Subsystem.h>
#include <CANTalon.h>

class Winch : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
CANTalon everest;
public:
	Winch();
	void InitDefaultCommand();
	void Climb(bool runMotor);
};

#endif  // Winch_H
