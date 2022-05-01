#include "stdafx.h"
#include "SongType.h"

SongType::SongType() :
	s_Name(""), s_Id(""), s_Singer(""), s_Album(""), s_NumLikes(0) {}
SongType::~SongType() {}

CString SongType::getName() { return s_Name; }
CString SongType::getId() { return s_Id; }
CString SongType::getSinger() { return s_Singer; }
CString SongType::getAlbum() { return s_Album; }
int SongType::getNumLikes() { return s_NumLikes; }

void SongType::setName(CString inName) { s_Name = inName; }
void SongType::setId(CString inId) { s_Id = inId; }
void SongType::setSinger(CString inSinger) { s_Singer = inSinger; }
void SongType::setAlbum(CString inAlbum) { s_Album = inAlbum; }
void SongType::setNumLikes(int inNumLikes) { s_NumLikes = inNumLikes; }



void SongType::operator = (const SongType &item) {
	this->s_Name = item.s_Name;
	this->s_Id = item.s_Id;
	this->s_Singer = item.s_Singer;
	this->s_Album = item.s_Album;
	this->s_NumLikes = item.s_NumLikes;
}
bool SongType::operator == (const SongType &item) {
	if (this->s_Id == item.s_Id)
		return true;
	return false;
}
bool SongType::operator < (const SongType &item) {
	if (this->s_Id < item.s_Id)
		return true;
	return false;
}
bool SongType::operator > (const SongType &item) {
	if (item.s_Id < this->s_Id)
		return true;
	return false;
}