#include "stdafx.h"
#include "SingerType.h"

SingerType::SingerType() :
	s_Name(""), s_DebutYear("00000000"), s_Type(""), s_Genre(""), s_NumLikes(0) {}
SingerType::~SingerType() {}

CString SingerType::getName() { return s_Name; }
CString SingerType::getDebutYear() { return s_DebutYear; }
CString SingerType::getType() { return s_Type; }
CString SingerType::getGenre() { return s_Genre; }
int SingerType::getNumLikes() { return s_NumLikes; }

void SingerType::setName(CString inName) { s_Name = inName; }
void SingerType::setDebutYear(CString inDebutYear) { s_DebutYear = inDebutYear; }
void SingerType::setType(CString inType) { s_Type = inType; }
void SingerType::setGenre(CString inGenre) { s_Genre = inGenre; }
void SingerType::setNumLikes(int inNumLikes) { s_NumLikes = inNumLikes; }


void SingerType::operator = (SingerType &item) {
	if(&item.s_Name != NULL)
		this->s_Name = item.s_Name;
	if (&item.s_DebutYear != NULL)
		this->s_DebutYear = item.s_DebutYear;
	if (&item.s_Type != NULL)
		this->s_Type = item.s_Type;
	if (&item.s_Genre != NULL)
		this->s_Genre = item.s_Genre;
	if (&item.s_NumLikes != NULL)
		this->s_NumLikes = item.s_NumLikes;
}
bool SingerType::operator == (const SingerType &item) {
	if (this->s_Name == item.s_Name)
		return true;
	return false;
}
bool SingerType::operator < (const SingerType &item) {
	if (this->s_Name < item.s_Name)
		return true;
	return false;
}
bool SingerType::operator > (const SingerType &item) {
	if (item.s_Name < this->s_Name)
		return true;
	return false;
}