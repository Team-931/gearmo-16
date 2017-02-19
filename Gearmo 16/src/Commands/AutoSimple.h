#ifndef AutoSimple_H
#define AutoSimple_H

#include "../CommandBase.h"

class AutoSimple : public CommandBase {
public:
	AutoSimple();
	void Initialize();
	bool IsFinished();
};

#endif  // AutoSimple_H
