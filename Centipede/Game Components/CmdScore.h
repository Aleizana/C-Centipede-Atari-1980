#ifndef _CmdScore
#define _CmdScore

#include "TEAL\CommonElements.h"

class CmdScore
{
public:
	CmdScore() = default;
	CmdScore(const CmdScore&) = delete;
	CmdScore& operator=(const CmdScore&) = delete;
	virtual ~CmdScore() = default;

	// Note: the Excecute method must NOT have _any_ paramters
	virtual void Execute() = 0;
};

#endif