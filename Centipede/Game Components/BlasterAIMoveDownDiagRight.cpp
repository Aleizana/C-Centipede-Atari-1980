#include "BlasterAIMoveDownDiagRight.h"
#include "BlasterAIMoveCollection.h"
#include "MoveFSM.h"

BlasterAIMoveDownDiagRight::BlasterAIMoveDownDiagRight()
{
	std::cout << "Initializing BlasterAIMoveDownDiagRight state\n";

	MyMoveOffsets = BlasterAIMoveCollection::OffsetsDownDiagonalRight;
}
void BlasterAIMoveDownDiagRight::Show() const
{
	std::cout << "BlasterAIMoveDownDiagRight";
}

const BlasterAIMoveState* BlasterAIMoveDownDiagRight::GetNextState() const
{
	return (BlasterAIMoveState*)&MoveFSM::StateBlasterAIMoveUpDiagRight;
}