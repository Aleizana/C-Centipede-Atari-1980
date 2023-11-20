#ifndef _BlasterAIMoveUpDiagRight
#define _BlasterAIMoveUpDiagRight

#include "BlasterAIMoveStateBase.h"

class BlasterAIMoveUpDiagRight : public BlasterAIMoveState
{
public:
	BlasterAIMoveUpDiagRight();
	BlasterAIMoveUpDiagRight(const BlasterAIMoveUpDiagRight& copyMe) = delete;
	BlasterAIMoveUpDiagRight& operator=(const BlasterAIMoveUpDiagRight&) = delete;
	~BlasterAIMoveUpDiagRight() = default;

	virtual const BlasterAIMoveState* GetNextState() const override;
	virtual void Show() const override;

private:

};

#endif