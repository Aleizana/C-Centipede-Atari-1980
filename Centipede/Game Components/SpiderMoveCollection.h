#ifndef _SpiderMoveCollection
#define _SpiderMoveCollection

#include "TEAL\CommonElements.h"

struct SpiderOffsetArray
{
private:
	float rowoffset;
	float coloffset;

public:
	SpiderOffsetArray(float c, float r);
	SpiderOffsetArray() = default;
	SpiderOffsetArray(const SpiderOffsetArray& copyCollect) = default;
	SpiderOffsetArray& operator=(const SpiderOffsetArray&) = delete;
	~SpiderOffsetArray() = default;

	const float GetRowOffset() const;
	const float GetColOffset() const;
};

class SpiderMoveCollection
{
public:
	SpiderMoveCollection() = delete;
	SpiderMoveCollection(const SpiderMoveCollection& copyCollect) = delete;
	SpiderMoveCollection& operator=(const SpiderMoveCollection&) = delete;
	~SpiderMoveCollection() = default;

	//The maximum amount of values that are present in each array
	static const int arrMax = 8;

	static const SpiderOffsetArray OffsetsUpDiagonalLeft[];
	static const SpiderOffsetArray OffsetsUpDiagonalRight[];
	static const SpiderOffsetArray OffsetsDownDiagonalLeft[];
	static const SpiderOffsetArray OffsetsDownDiagonalRight[];
	static const SpiderOffsetArray OffsetsUp[];
	static const SpiderOffsetArray OffsetsDown[];

};

#endif
