#include "GlyphObjectPool.h"
#include "TEAL\CommonElements.h"
#include "Glyph.h"

GlyphObjectPool::GlyphObjectPool()
{
	// Alterninatively: pre-load the recycledItems queue is a few Glyphs already
}

GlyphObjectPool::~GlyphObjectPool()
{
	// forcefully delele all recycled gameobjects

	ConsoleMsg::WriteLine("Deleting " + Tools::ToString(recycledItems.size()) + " Glyphs");
	while (!recycledItems.empty())
	{
		//recycledItems.top()->DeregisterCollision<Glyph>(*recycledItems.top());

		delete recycledItems.top();
		recycledItems.pop();
	}
}

Glyph* GlyphObjectPool::GetGlyph()
{
	Glyph* b;

	if (recycledItems.empty())
	{
		ConsoleMsg::WriteLine("New Glyph"); // For illustration purposes

		b = new Glyph();
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Glyph"); // For illustration purposes

		b = recycledItems.top();
		recycledItems.pop();	// Remember: top doesn't pop and pop returns void...

		// Tell the object to register itself to the scene
		b->RegisterToCurrentScene();
	}

	return b;
}

void GlyphObjectPool::ReturnGlyph(Glyph* b)
{
	recycledItems.push(b);

	// For illustration purposes
	ConsoleMsg::WriteLine("Glyph Recycled Stack Size: " + Tools::ToString(recycledItems.size()));

}