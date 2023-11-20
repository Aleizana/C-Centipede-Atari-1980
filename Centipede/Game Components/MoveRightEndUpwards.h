#ifndef _MoveRightEndUp
#define _MoveRightEndUp

#include "MoveState.h"

class MoveRightEndUpwards : public MoveState
{
public:
	MoveRightEndUpwards();
	MoveRightEndUpwards(const MoveRightEndUpwards& copyMe) = delete;
	MoveRightEndUpwards& operator=(const MoveRightEndUpwards&) = delete;
	~MoveRightEndUpwards() = default;

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
	const int RowIncrement = 0;

	const int ColIncrement = 1;

	//Variables related to the initialization and animation of the sprite from a sprite sheet
	const int SpriteFirstFrame = 0;		//For setting the animation of the sprite given the different sprites in the sheet
	const int SpriteLastFrame = 7;		//For setting the animation of the sprite given the different sprites in the sheet
	const float SpriteScalar_X = -2.0f;	//For setting the size of the sprite, negative so as to flip the sprite on the x-axis to face it right
	const float SpriteScalar_Y = 2.0f;	//For setting the size of the sprite

	//Function to determine if the centipede will be hitting the player area
	const bool CheckForPlrArea(CentipedeHead* headToMove) const;
	const bool CheckForPlrArea(sf::Vector2f pos) const;
};

#endif