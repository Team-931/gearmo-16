#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Subsystems/SwerveDrive.h"
#include "Subsystems/Shooter.h"
#include <string>
#include "Commands/Command.h"
#include "OI.h"
#include "WPILib.h"
#include "Subsystems/BPM.h"
#include "Subsystems/Winch.h"
/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command
{
public:
	CommandBase(char const *name);
	CommandBase();
	CommandBase(double timeout);
	static void init(RobotBase *);
	// Create a single static instance of all of your subsystems
	static RobotBase *robot;
	static BPM *bpm;
	static SwerveDrive *swerveDrive;
	static Shooter * shooter;
	static OI *oi;
	static Winch *winch;
};

#endif
