#ifndef _BlasterAIMoveUpDiagLeft
#define _BlasterAIMoveUpDiagLeft

#include "BlasterAIMoveStateBase.h"

class BlasterAIMoveUpDiagLeft : public BlasterAIMoveState
{
public:
	BlasterAIMoveUpDiagLeft();
	BlasterAIMoveUpDiagLeft(const BlasterAIMoveUpDiagLeft& copyMe) = delete;
	BlasterAIMoveUpDiagLeft& operator=(const BlasterAIMoveUpDiagLeft&) = delete;
	~BlasterAIMoveUpDiagLeft() = default;

	virtual const BlasterAIMoveState* GetNextState() const override;
	virtual void Show() const override;

private:

};

#endif