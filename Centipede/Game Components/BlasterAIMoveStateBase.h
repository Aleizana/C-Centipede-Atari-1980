#ifndef _BlasterAIMoveStateBase
#define _BlasterAIMoveStateBase

struct BlasterAIOffsetArray;
class BlasterAIMover;

class BlasterAIMoveState
{
public:
	BlasterAIMoveState() = default;
	BlasterAIMoveState(const BlasterAIMoveState& copyMe) = delete;
	BlasterAIMoveState& operator=(const BlasterAIMoveState&) = delete;
	~BlasterAIMoveState() = default;
	const BlasterAIOffsetArray* GetMoveOffsets() const { return MyMoveOffsets; }
	virtual const BlasterAIMoveState* GetNextState() const = 0;
	virtual void Show() const = 0;

protected:
	const BlasterAIOffsetArray* MyMoveOffsets = nullptr;

};

#endif 