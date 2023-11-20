#ifndef _BlasterAIMoveCollection
#define _BlasterAIMoveCollection

#include "TEAL\CommonElements.h"

struct BlasterAIOffsetArray
{
private:
	float rowoffset;
	float coloffset;

public:
	BlasterAIOffsetArray(float c, float r);
	BlasterAIOffsetArray() = default;
	BlasterAIOffsetArray(const BlasterAIOffsetArray& copyCollect) = default;
	BlasterAIOffsetArray& operator=(const BlasterAIOffsetArray&) = delete;
	~BlasterAIOffsetArray() = default;

	const float GetColOffset() const;
	const float GetRowOffset() const;
};

class BlasterAIMoveCollection
{
public:
	BlasterAIMoveCollection() = delete;
	BlasterAIMoveCollection(const BlasterAIMoveCollection& copyCollect) = delete;
	BlasterAIMoveCollection& operator=(const BlasterAIMoveCollection&) = delete;
	~BlasterAIMoveCollection() = default;

	//The maximum amount of values that are present in each array
	static const int arrMax = 32;

	static const BlasterAIOffsetArray OffsetsUpDiagonalLeft[];
	static const BlasterAIOffsetArray OffsetsUpDiagonalRight[];
	static const BlasterAIOffsetArray OffsetsDownDiagonalLeft[];
	static const BlasterAIOffsetArray OffsetsDownDiagonalRight[];

};

#endif
