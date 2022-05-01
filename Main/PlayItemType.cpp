#include "stdafx.h"
#include "PlayItemType.h"


PlayItemType::PlayItemType()
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	m_InTime = tm.tm_sec;
	m_InTime += (tm.tm_min)*100;
	m_InTime += (tm.tm_hour)*10000;
	m_InTime += (tm.tm_mday)*1000000;
	m_InTime += (tm.tm_mon + 1) * 100000000;

	m_Id = _T("");
	m_Song = _T("");
	m_Singer = _T("");
	m_Album = _T("");
	m_UsersNum = m_InTime;
	m_priority = _T("");
}


PlayItemType::~PlayItemType()
{
}

CString PlayItemType::getId() { return m_Id; }
CString PlayItemType::getSong() { return m_Song; }
CString PlayItemType::getSinger() { return m_Singer; }
CString PlayItemType::getAlbum() { return m_Album; }
int PlayItemType::getUsersNum() { return m_UsersNum; }
int PlayItemType::getInTime() { return m_InTime; }
int PlayItemType::getNumLikes() { return m_NumLikes; }
CString PlayItemType::getPriority() { return m_priority; }

void PlayItemType::setId(CString inId) { m_Id = inId; }
void PlayItemType::setSong(CString inSong) { m_Song = inSong; }
void PlayItemType::setSinger(CString inSinger) { m_Singer = inSinger; }
void PlayItemType::setAlbum(CString inAlbum) { m_Album = inAlbum; }
void PlayItemType::setUsersNum(int inNum) { m_UsersNum = inNum; }
void PlayItemType::setInTime() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	m_InTime = tm.tm_sec;
	m_InTime += (tm.tm_min) * 100;
	m_InTime += (tm.tm_hour) * 10000;
	m_InTime += (tm.tm_mday) * 1000000;
	m_InTime += (tm.tm_mon + 1) * 100000000;
}
void PlayItemType::setNumLikes(int inNum) { m_NumLikes = inNum; }
void PlayItemType::setPriority(int num) {
	switch (num)
	{
	case 0:
		m_priority = m_Id;
		break;
	case 1:
		m_priority = m_Song;
		break;
	case 2:
		m_priority = m_Singer;
		m_priority += m_Song;
		break;
	case 3:
		m_priority.Format(_T("%d"), m_UsersNum);
		break;
	case 4:
		m_priority.Format(_T("%d"), m_InTime);
		break;
	case 5:
		m_priority.Format(_T("%d"),900000 - m_NumLikes);
		break;
	default:
		break;
	}
}


void PlayItemType::operator = (PlayItemType &item) {
	this->m_Id = item.m_Id;
	this->m_Song = item.m_Song;
	this->m_Singer = item.m_Singer;
	this->m_Album = item.m_Album;
	this->m_UsersNum = item.m_UsersNum;
	this->m_InTime = item.m_InTime;
	this->m_NumLikes = item.m_NumLikes;
	this->m_priority = item.m_priority;
}
void PlayItemType::operator = (SongType &item) {
	this->m_Id = item.getId();
	this->m_Song = item.getName();
	this->m_Album = item.getAlbum();
	this->m_Singer = item.getSinger();
	this->m_NumLikes = item.getNumLikes();
}
bool PlayItemType::operator == (const PlayItemType &item) {
	if (this->m_priority == item.m_priority)
		return true;
	return false;
}
bool PlayItemType::operator < (const PlayItemType &item) {
	if (this->m_priority < item.m_priority)
		return true;
	return false;
}
bool PlayItemType::operator > (const PlayItemType &item){
	if (item.m_priority < this->m_priority)
		return true;
	return false;
}

