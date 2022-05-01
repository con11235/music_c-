#include "stdafx.h"
#include "AlbumType.h"

AlbumType::AlbumType() :
	s_Name(""), s_Comeout("00000000"), s_Type(""), s_Genre(""), s_NumLikes(0) {}
AlbumType::~AlbumType() {}

CString AlbumType::getName() { return s_Name; }
CString AlbumType::getComeout() { return s_Comeout; }
CString AlbumType::getType() { return s_Type; }
CString AlbumType::getGenre() { return s_Genre; }
CString AlbumType::getSinger() { return s_Singer; }
int AlbumType::getNumLikes() { return s_NumLikes; }

void AlbumType::setName(CString inName) { s_Name = inName; }
void AlbumType::setComeout(CString inComeout) { s_Comeout = inComeout; }
void AlbumType::setType(CString inType) { s_Type = inType; }
void AlbumType::setGenre(CString inGenre) { s_Genre = inGenre; }
void AlbumType::setSinger(CString inSinger) { s_Singer = inSinger; }
void AlbumType::setNumLikes(int inNumLikes) { s_NumLikes = inNumLikes; }


void AlbumType::operator = (AlbumType &item) {
	this->s_Name = item.s_Name;
	this->s_Comeout = item.s_Comeout;
	this->s_Type = item.s_Type;
	this->s_Genre = item.s_Genre;
	this->s_Singer = item.s_Singer;
	this->s_NumLikes = item.s_NumLikes;
}
bool AlbumType::operator == (const AlbumType &item) {
	if (this->s_Name == item.s_Name)
		return true;
	return false;
}
bool AlbumType::operator < (const AlbumType &item) {
	if (this->s_Name < item.s_Name)
		return true;
	return false;
}
bool AlbumType::operator > (const AlbumType &item) {
	if (item.s_Name < this->s_Name)
		return true;
	return false;
}