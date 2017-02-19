#ifndef RopeClimb_H
#define RopeClimb_H

#include "../CommandBase.h"

class RopeClimb : public CommandBase {
	bool onOff;
public:
	RopeClimb(bool running);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RopeClimb_H
