#ifndef PickUp_H
#define PickUp_H

#include "../CommandBase.h"

class PickUp : public CommandBase {
bool onOff = false;
public:
	PickUp(bool onOff);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // PickUp_H
