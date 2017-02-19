#include <Subsystems/SwerveDrive.h>
# include "Commands/TeleopDrive.h"
# include <cfenv> // for FE_DIVBYZERO

SwerveDrive::SwerveDrive() :
		Subsystem("SwerveDrive"), iDrone(14), iSensor(&iDrone)
# if ! newdrivestick
,		speedface(false)
# endif
{fedisableexcept (FE_DIVBYZERO);
ZeroOrientation();}

void SwerveDrive::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new TeleopDrive);
 }

// These should each be {y, -x}
// where (x, y) is the vector of
// this wheel from the center of rotation.
static const float length = 24.25; // TODO: check measure
static const float width  = 27.875; //   "       "
static const float rot_scale = 1/sqrt(length*length + width*width);
static const float rot_length = length * rot_scale;
static const float rot_width  = width  * rot_scale;
// In general, the wheel positions, scaled so the largest norm == 1
static const complex rot_vecs[numWheels] =
  { {-rot_width,  rot_length},{ rot_width,  rot_length},
	{ rot_width, -rot_length},{-rot_width, -rot_length}};

static const char* wheelnames[] = {"Wheel 0", "Wheel 1", "Wheel 2", "Wheel 3"};

static complex expi(double x) {return {cos(x), sin(x)};}

# if ! newdrivestick
static float sloper(float rotx){
  if(abs(rotx) *3 < 1) return 2*rotx;
  return (rotx +(rotx >0 ? 1: -1))/2;
}
# endif

void SwerveDrive::Drive(float x, float y, float rot, float throttle)
 {Drive(x*throttle, y*throttle, rot*throttle);}
void SwerveDrive::Drive(float x, float y, float rot, Align)
 {Drive(x, y, rot, minimal);}
void SwerveDrive::Drive(float x, float y, float rot)
 {/*SmartDashboard::PutNumber("SwerveDrive.Drive x:", x);
  SmartDashboard::PutNumber("SwerveDrive.Drive y:", y);
  SmartDashboard::PutNumber("SwerveDrive.Drive rot:", rot);
  SmartDashboard::PutNumber("SwerveDrive.Drive align:", align);
  SmartDashboard::PutBoolean("SwerveDrive.Toggle stat", speedface);*/
  complex straight(-x,y)/*, vecs[numWheels]*/;
   //straight *= norm(straight); // makes small motions smaller
# if ! newdrivestick
  if(speedface)
# endif
# if ! newdrivestick
   rot = sloper(rot); //same reason above
# endif
//   if(abs(rot) >=.85) oi->DriveStick();

 float max = abs(straight) + abs(rot);
 if(max > 1) straight /= max, rot /= max;//XXX
 velocity = straight * Orienter;
 rotSpeed = rot;
 AngleSetting = false;
/*
 for (unsigned n=0; n<numWheels; ++n)
   {vecs[n] = straight + i* rot * rot_vecs[n];
*/
    //if(n&2) vecs[n] *= .90; // ad hoc try to even up
    //SmartDashboard::PutNumber(wheelnames[n]/*"Talon x" + std::basic_string(n) + " setting"*/, real(vecs[n]));
    //SmartDashboard::PutNumber("Talon y" /*+ std::basic_string(n) + " setting"*/, imag(vecs[n]));
     //  }
//  for(unsigned i = 0; i < numWheels; ++i) wheels[i].Disable();
//  correction = -Orientation;
/*
  for (unsigned n=0; n<numWheels; ++n)
	wheels[n].Drive(float(n==3?1:-1) * Orienter * vecs[n] / max, align);
*/
//  for(unsigned i = 0; i < numWheels; ++i) wheels[i].Enable();
 }

void SwerveDrive::RotateTo(float degrees)
	{rotSpeed = degrees;
	AngleSetting = true;}

void SwerveDrive::RotateBy(float degrees)
{RotateTo(degrees + iSensor.GetFusedHeading());}

bool SwerveDrive::OnTarget()
 {for(unsigned n = 0; n < numWheels; ++n)
   if(!wheels[n].OnTarget()) return false;
  return true;
 }

void SwerveDrive::SetPID(float P, float I, float D)
 {for(unsigned n = 0; n < numWheels; ++n)
   wheels[n].SetPID(P, I, D);
 }

void SwerveDrive::SetPerson(float dir, bool Third)
	{for(unsigned i = 0; i < numWheels; ++i) wheels[i].Disable();
	 Orientation = dir;
	 Orienter = i * expi(dir);
	 if(Third != ThirdPerson)
		 {velocity *= expi((Third ? 1 : -1) * iSensor.GetFusedHeading() * M_PI/180);
		  ThirdPerson = Third;
		  SmartDashboard::PutBoolean("Third person is ", Third);}
	 for(unsigned i = 0; i < numWheels; ++i) wheels[i].Enable();}

/*
inline float SwerveDrive::YawCompens()
	{return (ThirdPerson ? iSensor.GetFusedHeading()/360 : 0) + correction;}
*/

uint32_t SwerveDrive::Wheel::ix = 0;

SwerveDrive::Wheel::Wheel(): PIDController(2/pi, 0, 0, this,&rotSpeed),
	  encoder(ix),
	  rotSpeed(ix + 1),drvSpeed(numWheels + ix + 1),
	  this_ix(ix++)
	//, speedGoal(0)
	 {//SetContinuous();
	  //SetInputRange(0, maxRot);
	  SetPercentTolerance((float)100/32);
	  SetSetpoint(0);
	  Enable();}

/*
void SwerveDrive::Wheel::Drive(complex vec, bool align)
 {speedGoal = align?0: vec;
  SetSetpoint((.5 + atan(imag(vec)/real(vec)) / pi) * maxRot);}
*/

static float P = 1, powerCap = 1;

complex SwerveDrive::GetWheelVector(int ix)
	{complex retval(velocity);
	 float heading = iSensor.GetFusedHeading();
	 if(ThirdPerson)
		 retval *= expi(-heading*M_PI/180);
	 float rot = rotSpeed;
	 if(AngleSetting)
	 	 {float diff = rotSpeed - heading, rotCap = powerCap - abs(velocity);
	 	 rot = std::max(std::min(diff * P, -rotCap), rotCap);}
	 return  retval - rot*rot_vecs[ix];}

// I'm using this to do other responses to
// encoder.PIDGet() before handing it to Calculate.
double SwerveDrive::Wheel::PIDGet()
 {SmartDashboard::PutNumber(wheelnames[this_ix], GetAngle());
 // This could be used more effectively
 // XXX: note the ad hoc correction for wheel mis-orientation
  complex rot_vec = float(this_ix==3?1:-1) * CommandBase::swerveDrive->GetWheelVector(this_ix) *
	expi(-GetAngle());
  // XXX: maybe have a ramp-up and/or conditional on this
  drvSpeed.Set(imag(rot_vec));
  return real(rot_vec)/imag(rot_vec);
 }
