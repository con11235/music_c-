#pragma once
#include<time.h>
#include"SongType.h"

class PlayItemType
{
private:
	CString m_Id;
	CString m_Song;
	CString m_Singer;
	CString m_Album;
	int m_UsersNum;
	int m_InTime;
	int m_NumLikes;
	CString m_priority;

public:
	PlayItemType();
	~PlayItemType();

	CString getId();
	CString getSong();
	CString getSinger();
	CString getAlbum();
	int getUsersNum();
	int getInTime();
	int getNumLikes();
	CString getPriority();

	void setId(CString inId);
	void setSong(CString inSong);
	void setSinger(CString inSinger);
	void setAlbum(CString inAlbum);
	void setUsersNum(int inNum);
	void setInTime();
	void setNumLikes(int inNum);
	void setPriority(int num);
	

	void operator = (PlayItemType &item);
	bool operator == (const PlayItemType &item);
	bool operator < (const PlayItemType &item);
	bool operator > (const PlayItemType &item);
	void operator = (SongType &item);
};
