#ifndef _CentiMoveCollection
#define _CentiMoveCollection

#include "TEAL\CommonElements.h"

struct OffsetArray
{
private:
	float rowoffset;
	float coloffset;

public:
	OffsetArray(float c, float r);
	OffsetArray() = default;
	OffsetArray(const OffsetArray& copyHead) = default;
	OffsetArray& operator=(const OffsetArray&) = delete;
	~OffsetArray() = default;

	const float GetColOffset() const;
	const float GetRowOffset() const;
};

class MovementCollection
{
public:
	MovementCollection() = delete;
	MovementCollection(const MovementCollection& copyHead) = delete;
	MovementCollection& operator=(const MovementCollection&) = delete;
	~MovementCollection() = default;

	static int GetArrMax();

	static const OffsetArray OffsetsStraightRight[];
	static const OffsetArray OffsetsTurnUpEndRight[];
	static const OffsetArray OffsetsTurnDownEndRight[];
	static const OffsetArray OffsetsStraightLeft[];
	static const OffsetArray OffsetsTurnUpEndLeft[];
	static const OffsetArray OffsetsTurnDownEndLeft[];

private:
	//The maximum amount of values that are present in each array
	static const int arrMax = 16;

};

#endif
