#ifndef _ScoreByValue
#define _ScoreByValue

#include "CmdScore.h"

class CmdScoreValue : public CmdScore
{
protected:
	int points;	// points to add
	
public:
	CmdScoreValue() = delete;
	CmdScoreValue(const CmdScoreValue&) = delete;
	CmdScoreValue& operator=(const CmdScoreValue&) = delete;
	virtual ~CmdScoreValue() = default;

	CmdScoreValue(int val);

    virtual void Execute() override;
};

#endif