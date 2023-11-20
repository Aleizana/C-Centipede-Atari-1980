#include "BlasterAIMoveUpDiagRight.h"
#include <iostream>
#include "BlasterAIMoveCollection.h"
#include <assert.h>
#include "MoveFSM.h"

BlasterAIMoveUpDiagRight::BlasterAIMoveUpDiagRight()
{
	std::cout << "Initializing BlasterAIMoveUpDiagRight state\n";

	MyMoveOffsets = BlasterAIMoveCollection::OffsetsUpDiagonalRight;
}
void BlasterAIMoveUpDiagRight::Show() const
{
	std::cout << "BlasterAIMoveUpDiagRight";
}

const BlasterAIMoveState* BlasterAIMoveUpDiagRight::GetNextState() const
{
	return (BlasterAIMoveState*)&MoveFSM::StateBlasterAIMoveDownDiagLeft;
}