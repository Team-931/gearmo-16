#ifndef ThirdPerson_H
#define ThirdPerson_H

#include "../CommandBase.h"

class ThirdPerson : public CommandBase {
	bool onOff;
public:
	ThirdPerson(bool onOff);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ThirdPerson_H
