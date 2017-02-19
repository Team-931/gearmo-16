#ifndef POV_H
#define POV_H

#include "../CommandBase.h"
#include "WPILib.h"

class POV : public CommandBase {
public:
	POV();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // POV_H
