#include "BlasterAIMoveUpDiagLeft.h"
#include "BlasterAIMoveCollection.h"
#include "MoveFSM.h"

BlasterAIMoveUpDiagLeft::BlasterAIMoveUpDiagLeft()
{
	std::cout << "Initializing BlasterAIMoveUpDiagLeft state\n";

	MyMoveOffsets = BlasterAIMoveCollection::OffsetsUpDiagonalLeft;
}
void BlasterAIMoveUpDiagLeft::Show() const
{
	std::cout << "BlasterAIMoveUpDiagLeft";
}

const BlasterAIMoveState* BlasterAIMoveUpDiagLeft::GetNextState() const
{
	return (BlasterAIMoveState*)&MoveFSM::StateBlasterAIMoveDownDiagRight;
}