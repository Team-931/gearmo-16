#ifndef ToggleThirdPerson_H
#define ToggleThirdPerson_H

#include "../CommandBase.h"

class ToggleThirdPerson : public CommandBase {
public:
	ToggleThirdPerson();
	void Initialize();
	bool IsFinished();
};

#endif  // ToggleThirdPerson_H
