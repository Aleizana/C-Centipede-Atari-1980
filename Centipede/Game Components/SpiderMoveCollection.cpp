#include "SpiderMoveCollection.h"
#include "SpiderFactory.h"
#include "Grid.h"
#include <assert.h>


SpiderOffsetArray::SpiderOffsetArray(float c, float r) : rowoffset(r), coloffset(c)
{
	//maxMove = moveOffset;
}
const float SpiderOffsetArray::GetRowOffset() const
{
	return rowoffset;
}
const float SpiderOffsetArray::GetColOffset() const
{
	return coloffset;
}
;

const SpiderOffsetArray SpiderMoveCollection::OffsetsUpDiagonalLeft[] = {
	SpiderOffsetArray(-1.0f, -1.0f),
	SpiderOffsetArray(-1.0f, -1.0f),
	SpiderOffsetArray(-1.0f, -1.0f),
	SpiderOffsetArray(-1.0f, -1.0f),
	SpiderOffsetArray(-1.0f, -1.0f),
	SpiderOffsetArray(-1.0f, -1.0f),
	SpiderOffsetArray(-1.0f, -1.0f),
	SpiderOffsetArray(-1.0f, -1.0f)

};

const SpiderOffsetArray SpiderMoveCollection::OffsetsUpDiagonalRight[] = {
	SpiderOffsetArray(1.0f, -1.0f),
	SpiderOffsetArray(1.0f, -1.0f),
	SpiderOffsetArray(1.0f, -1.0f),
	SpiderOffsetArray(1.0f, -1.0f),
	SpiderOffsetArray(1.0f, -1.0f),
	SpiderOffsetArray(1.0f, -1.0f),
	SpiderOffsetArray(1.0f, -1.0f),
	SpiderOffsetArray(1.0f, -1.0f)

};

const SpiderOffsetArray SpiderMoveCollection::OffsetsDownDiagonalLeft[] = {
	SpiderOffsetArray(-1.0f, 1.0f),
	SpiderOffsetArray(-1.0f, 1.0f),
	SpiderOffsetArray(-1.0f, 1.0f),
	SpiderOffsetArray(-1.0f, 1.0f),
	SpiderOffsetArray(-1.0f, 1.0f),
	SpiderOffsetArray(-1.0f, 1.0f),
	SpiderOffsetArray(-1.0f, 1.0f),
	SpiderOffsetArray(-1.0f, 1.0f)

};

const SpiderOffsetArray SpiderMoveCollection::OffsetsDownDiagonalRight[] = {
	SpiderOffsetArray(1.0f, 1.0f),
	SpiderOffsetArray(1.0f, 1.0f),
	SpiderOffsetArray(1.0f, 1.0f),
	SpiderOffsetArray(1.0f, 1.0f),
	SpiderOffsetArray(1.0f, 1.0f),
	SpiderOffsetArray(1.0f, 1.0f),
	SpiderOffsetArray(1.0f, 1.0f),
	SpiderOffsetArray(1.0f, 1.0f)

};

const SpiderOffsetArray SpiderMoveCollection::OffsetsUp[] = {
	SpiderOffsetArray(0, -1.0f),
	SpiderOffsetArray(0, -1.0f),
	SpiderOffsetArray(0, -1.0f),
	SpiderOffsetArray(0, -1.0f),
	SpiderOffsetArray(0, -1.0f),
	SpiderOffsetArray(0, -1.0f),
	SpiderOffsetArray(0, -1.0f),
	SpiderOffsetArray(0, -1.0f)

};

const SpiderOffsetArray SpiderMoveCollection::OffsetsDown[] = {
	SpiderOffsetArray(0, 1.0f),
	SpiderOffsetArray(0, 1.0f),
	SpiderOffsetArray(0, 1.0f),
	SpiderOffsetArray(0, 1.0f),
	SpiderOffsetArray(0, 1.0f),
	SpiderOffsetArray(0, 1.0f),
	SpiderOffsetArray(0, 1.0f),
	SpiderOffsetArray(0, 1.0f)

};

// Note: In this demoe, I move one cell per frame, so I only need one movement offset per direction.
// If your centipede takes 8 frame to move fro mone cell to another, then these offset collection would 
// need to be an array of 8 offsets, one for each frame. The sprite position at frame i would be
// previous cell center + ith offset value

