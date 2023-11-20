#ifndef _BlasterAIMoveDownDiagLeft
#define _BlasterAIMoveDownDiagLeft

#include "BlasterAIMoveStateBase.h"

class BlasterAIMoveDownDiagLeft : public BlasterAIMoveState
{
public:
	BlasterAIMoveDownDiagLeft();
	BlasterAIMoveDownDiagLeft(const BlasterAIMoveDownDiagLeft& copyMe) = delete;
	BlasterAIMoveDownDiagLeft& operator=(const BlasterAIMoveDownDiagLeft&) = delete;
	~BlasterAIMoveDownDiagLeft() = default;

	virtual const BlasterAIMoveState* GetNextState() const override;
	virtual void Show() const override;

private:

};

#endif