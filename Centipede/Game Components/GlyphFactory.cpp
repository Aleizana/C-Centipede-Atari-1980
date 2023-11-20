// GlyphFactory
// Andre Berthiaume, April 2013

#include "GlyphFactory.h"
#include "TEAL\CommonElements.h"
#include "GlyphObjectPool.h"
#include "Glyph.h"
#include "FontSheet.h"

GlyphFactory* GlyphFactory::ptrInstance = nullptr;

GlyphFactory::GlyphFactory()
{
	myGlyphPool = new GlyphObjectPool;
}

Glyph* GlyphFactory::privCreateGlyph(FontSheet* sheet, int cellInd, sf::Vector2f pos)
{
	//Create a new Glyph from the pool
	Glyph* GlyphRef = myGlyphPool->GetGlyph();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	GlyphRef->SetExternalManagement(RecycleGlyph);
	GlyphRef->InitGlyph(sheet, cellInd, pos);
	return GlyphRef;
}

void GlyphFactory::privRecycleGlyph(GameObject* _GlyphRef)
{
	myGlyphPool->ReturnGlyph(static_cast<Glyph*>(_GlyphRef));
}

void GlyphFactory::Terminate()
{
	delete Instance().myGlyphPool;
	delete ptrInstance;
	ptrInstance = nullptr;	// important habit for Singleton. Why?
}
