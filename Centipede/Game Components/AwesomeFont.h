// AwesomeFont
// Andre Berthiaume, May 2013

#ifndef _AwesomeFont
#define _AwesomeFont

#include "FontSheet.h"

class AwesomeFont : public FontSheet
{
public:
	AwesomeFont();
	AwesomeFont(const AwesomeFont&) = delete;
	AwesomeFont& operator=(const AwesomeFont&) = delete;
	virtual ~AwesomeFont() = default;

private:
	virtual int CharToIndex(char& c);
};


#endif _AwesomeFont