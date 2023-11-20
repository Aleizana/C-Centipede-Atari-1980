#include "BlasterAIMoveDownDiagLeft.h"
#include <iostream>
#include "BlasterAIMoveCollection.h"
#include "MoveFSM.h"

BlasterAIMoveDownDiagLeft::BlasterAIMoveDownDiagLeft()
{
	std::cout << "Initializing BlasterAIMoveDownDiagLeft state\n";

	MyMoveOffsets = BlasterAIMoveCollection::OffsetsDownDiagonalLeft;
}
void BlasterAIMoveDownDiagLeft::Show() const
{
	std::cout << "BlasterAIMoveDownDiagLeft";
}

const BlasterAIMoveState* BlasterAIMoveDownDiagLeft::GetNextState() const
{
	return (BlasterAIMoveState*)&MoveFSM::StateBlasterAIMoveUpDiagLeft;
}