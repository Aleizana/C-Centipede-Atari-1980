// GlyphFactory
// Andre Berthiaume, April 2013

#ifndef _GlyphFactory
#define _GlyphFactory

#include "GlyphObjectPool.h"
#include "SFML/Graphics.hpp"
#include "TEAL/CommonElements.h"

//To store a reference to the created Glyph to know when the blaster can fire
class Glyph;
class FontSheet;

class GlyphFactory
{
private:
	/******************************************************************
			  Currecctly set-up as a Singleton
	********************************************************************/
	static GlyphFactory* ptrInstance;			// Game set up as a singleton

	GlyphFactory();												// Private constructor
	GlyphFactory(const GlyphFactory&) = delete;				// Prevent copy-construction
	GlyphFactory& operator=(const GlyphFactory&) = delete;	// Prevent assignment
	~GlyphFactory() = default;											// Only this class can delete

	static GlyphFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (ptrInstance == nullptr)
			ptrInstance = new GlyphFactory();
			
		return *ptrInstance;
	};

	GlyphObjectPool* myGlyphPool;  // Back to be a non-static member instance

	//Store a reference to the live Glyph to know when the blaster can fire
	//Initialized to nullptr so that the check will pass upon first fire
	Glyph* GlyphRef = nullptr;

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time. Not done for this demo however

	// Private NON_STATIC methods to perform actual work on member var
	Glyph* privCreateGlyph(FontSheet* sheet, int cellInd, sf::Vector2f pos);
	void privRecycleGlyph(GameObject* _GlyphRef);

public:

	// Services/API as STATIC METHODS
	//    Usually just a pass-through arguments to private instance methods
	static Glyph* CreateGlyph(FontSheet* sheet, int cellInd, sf::Vector2f pos) { return Instance().privCreateGlyph(sheet, cellInd, pos); };
	static void RecycleGlyph(GameObject* b) { Instance().privRecycleGlyph(b); };

	static void Terminate();
};


#endif _GlyphFactory