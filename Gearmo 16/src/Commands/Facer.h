#ifndef Facer_H
#define Facer_H

#include "../CommandBase.h"

class Facer : public CommandBase {
public:
	float face;
	Facer(float facing);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Facer_H
