#ifndef StopShooter_H
#define StopShooter_H

#include "../CommandBase.h"

class StopShooter : public CommandBase {
public:
	StopShooter();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // StopShooter_H
