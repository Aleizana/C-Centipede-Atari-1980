#include "MovementCollection.h"
#include "CentipedeHeadFactory.h"
#include "Grid.h"
#include <assert.h>

OffsetArray::OffsetArray(float c, float r) : rowoffset(r), coloffset(c)
{
}
const float OffsetArray::GetColOffset() const
{
	return coloffset;
}
const float OffsetArray::GetRowOffset() const
{
	return rowoffset;
}
;

const OffsetArray MovementCollection::OffsetsStraightRight[] = {
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0),
	OffsetArray(1.0f, 0)
};

const OffsetArray MovementCollection::OffsetsTurnUpEndRight[] = {
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(0.5f , -1.0f),
	OffsetArray(0.5f , -1.0f),
	OffsetArray(0.5f , -1.0f),
	OffsetArray(0.5f , -1.0f),
	OffsetArray(0.5f , -1.0f),
	OffsetArray(0.5f , -1.0f),
	OffsetArray(0.5f , -1.0f),
	OffsetArray(0.5f , -1.0f)
};

const OffsetArray MovementCollection::OffsetsTurnDownEndRight[] = {
	OffsetArray(-0.5f,   1.0f),
	OffsetArray(-0.5f,   1.0f),
	OffsetArray(-0.5f,   1.0f),
	OffsetArray(-0.5f,   1.0f),
	OffsetArray(-0.5f,   1.0f),
	OffsetArray(-0.5f,   1.0f),
	OffsetArray(-0.5f,   1.0f),
	OffsetArray(-0.5f,   1.0f), //switch X movement
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f)
};

const OffsetArray MovementCollection::OffsetsStraightLeft[] = {
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0),
	OffsetArray(-1.0f, 0)
};

const OffsetArray MovementCollection::OffsetsTurnUpEndLeft[] = {
	OffsetArray(0.5f,   -1.0f),
	OffsetArray(0.5f,   -1.0f),
	OffsetArray(0.5f,   -1.0f),
	OffsetArray(0.5f,   -1.0f),
	OffsetArray(0.5f,   -1.0f),
	OffsetArray(0.5f,   -1.0f),
	OffsetArray(0.5f,   -1.0f),
	OffsetArray(0.5f,   -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f),
	OffsetArray(-0.5f, -1.0f)
};

const OffsetArray MovementCollection::OffsetsTurnDownEndLeft[] = {
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f),
	OffsetArray(0.5f, 1.0f), //Switch X here
	OffsetArray(-0.5f, 1.0f),
	OffsetArray(-0.5f, 1.0f),
	OffsetArray(-0.5f, 1.0f),
	OffsetArray(-0.5f, 1.0f),
	OffsetArray(-0.5f, 1.0f),
	OffsetArray(-0.5f, 1.0f),
	OffsetArray(-0.5f, 1.0f),
	OffsetArray(-0.5f, 1.0f)
};

// Note: In this demoe, I move one cell per frame, so I only need one movement offset per direction.
// If your centipede takes 8 frame to move fro mone cell to another, then these offset collection would 
// need to be an array of 8 offsets, one for each frame. The sprite position at frame i would be
// previous cell center + ith offset value

int MovementCollection::GetArrMax()
{
	return arrMax;
}
