#ifndef _TurnDownSwitchLeft
#define _TurnDownSwitchLeft

#include "MoveState.h"

class TurnDownSwitchToLeft : public MoveState
{
public:
	TurnDownSwitchToLeft();
	TurnDownSwitchToLeft(const TurnDownSwitchToLeft& copyMe) = delete;
	TurnDownSwitchToLeft& operator=(const TurnDownSwitchToLeft&) = delete;
	~TurnDownSwitchToLeft() = default;

	virtual const MoveState* GetNextState(CentipedeHead* chead) const override;
	virtual const MoveState* GetNextState(int row, int col, sf::Vector2f pos) const override;
	virtual void Show() const override;

	virtual int IncrementRow() const override;
	virtual int IncrementCol() const override;

	//Function that returns the animated sprite values to the centipede head and body depending on the state they are in, and which part of that state they are in
	virtual std::stack<int> GetSpriteProperties(const int offsetArrIndex) const override;


private:
	//Val to determine how many cells away the centipede will check in the grid
	const int GridCheckDistance = 1;

	//Value to increase the row of the centipede after the state is completed
	const int RowIncrement = 1;

	const int ColIncrement = 0;

	//Variables related to the initialization and animation of the sprite from a sprite sheet
	//Values for the first state of the sprite as it's facing diagonal-down-right
	const int SpriteFirstFrame_FirstState = 8;		//For setting the animation of the sprite given the different sprites in the sheet
	const int SpriteLastFrame_FirstState = 11;		//For setting the animation of the sprite given the different sprites in the sheet
	const float SpriteScalar_X_FirstState = -2.0f;	//For setting the size of the sprite, negative so as to flip the sprite on the x-axis to face it right

	//Values for the second state of the sprite as it's facing down
	const int SpriteFirstFrame_SecState = 12;		//For setting the animation of the sprite given the different sprites in the sheet
	const int SpriteLastFrame_SecState = 15;		//For setting the animation of the sprite given the different sprites in the sheet
	const float SpriteScalar_X_SecState = 2.0f;	//For setting the size of the sprite, negative so as to flip the sprite on the x-axis to face it right

	//Values that are the same in both sprites
	const float SpriteScalar_Y = 2.0f;	//For setting the size of the sprite

	//Splits the maximum size of the offset arrays in half to know when the sprite needs to change
	const int ArrMaxHalf = 2;
};

#endif