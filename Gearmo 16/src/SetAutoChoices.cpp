#include "Commands/AutoDrive.h"
#include "Commands/ThirdPerson.h"
#include "Commands/RotateTo.h"
#include "Commands/AutoShooter.h"
#include "Commands/StopShooter.h"

void SetAutoChoices(SendableChooser<Command*> &autoChooser) {
		auto gp = new CommandGroup("fast forward gp");
		gp->AddSequential(new ThirdPerson(true));
		gp->AddSequential(new AutoDrive(0.25,1,0)); //drive straight forward, with a fudge factor for rightward drift
		gp->AddSequential(new RotateTo(0));         //face gear delivery forward
		gp->AddSequential(new WaitCommand(.8));     //for .8 seconds
		gp->AddSequential(new ThirdPerson(false));
		autoChooser.AddObject("fast forward", gp);

		gp = new CommandGroup("forward turn left gp");
		gp->AddSequential(new ThirdPerson(true));
		gp->AddSequential(new AutoDrive(.25,.75,0));//drive forward, with fudge factor
		gp->AddSequential(new WaitCommand(1.25));   //for 1.25 seconds
		gp->AddSequential(new AutoDrive(3.0*sqrt(3)/8,3.0/8,0));//drive leftish
		gp->AddSequential(new RotateTo(60));        //face leftish
		gp->AddSequential(new WaitCommand(.7));     //for .7 seconds
		gp->AddSequential(new ThirdPerson(false));
		autoChooser.AddObject("forward turn left", gp);

		gp = new CommandGroup("forward turn right gp");
		gp->AddSequential(new ThirdPerson(true));
		gp->AddSequential(new AutoDrive(.25,.75,0));//ditto above
		gp->AddSequential(new WaitCommand(1.25));
		gp->AddSequential(new AutoDrive(-3.0*sqrt(3)/8,3.0/8,0));//rightish
		gp->AddSequential(new RotateTo(-60));       //rightish
		gp->AddSequential(new WaitCommand(.7));
		gp->AddSequential(new ThirdPerson(false));
		autoChooser.AddObject("forward turn right", gp);

		gp = new CommandGroup("shoot balls gp");    //for being positioned in front of red3
		gp->AddSequential(new AutoShooter(52));     //run the shooter at 52 rps (not tested)
		gp->AddSequential(new WaitCommand(3));      //for 3 seconds
		gp->AddSequential(new StopShooter());       //TODO why doesn't it stop?
		gp->AddSequential(new ThirdPerson(true));
		gp->AddSequential(new AutoDrive(0.25,1,0)); //drive forward
		gp->AddSequential(new WaitCommand(1));
		gp->AddSequential(new ThirdPerson(false));
		autoChooser.AddObject("shoot balls", gp);

		gp = new CommandGroup("forward and shoot gp");//for red elsewhere, untested
		gp->AddSequential(new ThirdPerson(true));
		gp->AddSequential(new WaitCommand(2));
		gp->AddSequential(new AutoDrive(-.75,0,0));   //drive right
		gp->AddSequential(new WaitCommand(1.5));
		gp->AddSequential(new AutoDrive(0,0,0));
		gp->AddSequential(new AutoShooter(52));       //then shoot
		gp->AddSequential(new WaitCommand(3));
		gp->AddSequential(new StopShooter());
		gp->AddSequential(new ThirdPerson(false));
		autoChooser.AddObject("drive and shoot",gp);

		autoChooser.AddDefault("nothing",0);
		SmartDashboard::PutData("Which autonomous?", &autoChooser);
}
