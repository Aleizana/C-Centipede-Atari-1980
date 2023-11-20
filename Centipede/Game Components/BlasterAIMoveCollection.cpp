#include "BlasterAIMoveCollection.h"


BlasterAIOffsetArray::BlasterAIOffsetArray(float c, float r) : rowoffset(r), coloffset(c)
{
}
const float BlasterAIOffsetArray::GetColOffset() const
{
	return coloffset;
}
const float BlasterAIOffsetArray::GetRowOffset() const
{
	return rowoffset;
}
;

const BlasterAIOffsetArray BlasterAIMoveCollection::OffsetsUpDiagonalLeft[] = {
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f),
	BlasterAIOffsetArray(-1.0f, -1.0f)

};

const BlasterAIOffsetArray BlasterAIMoveCollection::OffsetsUpDiagonalRight[] = {
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f),
	BlasterAIOffsetArray(1.0f, -1.0f)

};

const BlasterAIOffsetArray BlasterAIMoveCollection::OffsetsDownDiagonalLeft[] = {
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f),
	BlasterAIOffsetArray(-1.0f, 1.0f)

};

const BlasterAIOffsetArray BlasterAIMoveCollection::OffsetsDownDiagonalRight[] = {
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f),
	BlasterAIOffsetArray(1.0f, 1.0f)

};