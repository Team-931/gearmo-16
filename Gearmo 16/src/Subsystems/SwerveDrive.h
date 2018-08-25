#ifndef SWERVE_DRIVE_H
#define SWERVE_DRIVE_H

#include "Commands/Subsystem.h"
#include <WPILib.h>
#include <complex>

#include <ctre/phoenix.h>

# define newdrivestick 1
//#include "CommandBase.h"
# define OldEncoder 0
typedef std::complex<float> complex;

static const unsigned numWheels=4;
constexpr complex i = {0,1};
static constexpr float minimal = 1.0/1024;
class SwerveDrive: public Subsystem
{TalonSRX iDrone;
 PigeonIMU iSensor;
 	// set if headings are accelerometer compensated
	bool ThirdPerson = false,
			AngleSetting = false;
	float Orientation = 0,
			correction = 0;
	complex Orienter = i,
			velocity = minimal;
	float rotSpeed = 0; //also the target angle
# if ! newdrivestick
  bool speedface;
# endif
  // Wheel is a private member class, since we don't
	// expect any more to be created than these.
  class Wheel: public PIDController, public PIDSource
   {
# if OldEncoder
   Encoder encoder;
# else
   AnalogInput encoder;
# endif
   WPI_TalonSRX rotSpeed, drvSpeed; /*the motors are cims and pg (34?) .*/
   static uint32_t ix;
   uint32_t this_ix;
   static constexpr double maxRot =
# if OldEncoder
	 206.75; // actually 1/2 of 413.5 rot
# else
     2.5; // 1/2 of 5 Volts
# endif
	 // The encoder output is wrapped at 206.75 by PIDGet -CHECK NUMBER!
   static constexpr double pi = M_PI /*3.14159265*/;
   static constexpr double piRatio = pi/maxRot;
   double GetAngle() const {return piRatio*encoder.
# if OldEncoder
	 GetDistance();
# else
	 GetVoltage();
# endif
   }
	public:
   Wheel();
   //void Drive(complex, bool);
   //void SetSpeedGoal(float);
   void InitDefaultCommand();
    protected:
   double PIDGet();
   /*void PIDWrite(double);*/} wheels[numWheels];
public:
	SwerveDrive();
	void InitDefaultCommand();
/** @param leftright motion **/
	void Drive(float x, float y, float twist);
	void Drive(float x, float y, float twist,
	  float throttle);
	enum Align{align};
	void Drive(float x, float y, float twist,
	  Align);

	bool OnTarget();
# if ! newdrivestick
	void Toggler();
# endif
// send velocity vector for "n"th wheel
	complex GetWheelVector(int ix);
	// get PID parameters for the wheels
	float GetP() const, GetI() const, GetD() const;
// set PID parameters for the wheels
	void SetPID(float, float, float);

// is the orientation unchanged when the robot rotates?
	inline bool IsThirdPerson() const;
//does Set{First|Third}Person(orientation)
	void SetPerson(float orientation, bool isThird);
	void ClickOrient();
// "forward" is (360*orientation) degrees from the robot's initial orientation
	inline void SetThirdPerson(float orientation);
// "forward" is (360*orientation) degrees from the robot's current orientation
	inline void SetFirstPerson(float orientation);
// Set initial orientation
	inline void ZeroOrientation();
	void RotateTo(float degrees);
	void RotateBy(float degrees);
	static constexpr float GearForward = 1.0/4,
			PickUpForward = 0,
			ShooterForward = 1.0/2;
};

# if ! newdrivestick
inline void SwerveDrive::Toggler(){speedface=!speedface;}
# endif
inline float SwerveDrive::GetP() const{return wheels[0].GetP();}
inline float SwerveDrive::GetI() const{return wheels[0].GetI();}
inline float SwerveDrive::GetD() const{return wheels[0].GetD();}

inline bool SwerveDrive::IsThirdPerson() const
	{return ThirdPerson;}

inline void SwerveDrive::SetFirstPerson(float dir)
	{SetPerson(dir, false);}

inline void SwerveDrive::SetThirdPerson(float dir)
	{SetPerson(dir, true);}

inline void SwerveDrive::ClickOrient() {
	Orienter *= i;
}

inline void SwerveDrive::ZeroOrientation()
	{iSensor.SetFusedHeading(0);}
#endif // reinclusion guard
