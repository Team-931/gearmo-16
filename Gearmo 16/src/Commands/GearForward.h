#ifndef GearForward_H
#define GearForward_H

#include "../CommandBase.h"

//todo delete this
class GearForward : public CommandBase {
public:
	GearForward();
	void Initialize();
	bool IsFinished();
};

#endif  // GearForward_H
