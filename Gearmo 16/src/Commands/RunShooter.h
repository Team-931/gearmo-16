#ifndef RunShooter_H
#define RunShooter_H

#include "../CommandBase.h"

class RunShooter : public CommandBase {
	int spdRange;
public:
	RunShooter();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // RunShooter_H
