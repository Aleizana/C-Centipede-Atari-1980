// AttractorMode

#ifndef _AttractorMode
#define _AttractorMode

#include "TEAL\CommonElements.h"


class AttractorMode : public Scene
{
public:
	AttractorMode() = default;
	AttractorMode(const AttractorMode&) = delete;
	AttractorMode& operator=(const AttractorMode&) = delete;
	~AttractorMode() = default;

	virtual void Initialize();
	virtual void Terminate();



private:
};

#endif _AttractorMode