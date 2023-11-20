#ifndef _BlasterAIMoveDownDiagRight
#define _BlasterAIMoveDownDiagRight

#include "BlasterAIMoveStateBase.h"

class BlasterAIMoveDownDiagRight : public BlasterAIMoveState
{
public:
	BlasterAIMoveDownDiagRight();
	BlasterAIMoveDownDiagRight(const BlasterAIMoveDownDiagRight& copyMe) = delete;
	BlasterAIMoveDownDiagRight& operator=(const BlasterAIMoveDownDiagRight&) = delete;
	~BlasterAIMoveDownDiagRight() = default;

	virtual const BlasterAIMoveState* GetNextState() const override;
	virtual void Show() const override;

private:

};

#endif