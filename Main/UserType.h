#pragma once
#include "UnSortedList.h"
#include "SortedList.h"
#include "PlayItemType.h"

class UserType
{
private:
	CString u_Id;
	CString u_Pw;
	SortedList<PlayItemType> PlayList;
	UnSortedList<CString> LSongList;
	UnSortedList<CString> LAlbumList;
	UnSortedList<CString> LSingerList;
public:
	UserType();
	~UserType();

	CString getId();
	CString getPw();
	
	void setId(CString inId);
	void setPw(CString inPw);

	void AddToPL(PlayItemType item);
	int getPLLength();
	int DeletePL(PlayItemType inSong);
	int ReplacePL(PlayItemType inSong);
	void ResetPLPointer();
	int GetNextPL(PlayItemType &inSong);
	int GetPLItem(PlayItemType inSong);
	PlayItemType GetPLItem(int idx);
	void UserType::UpdatePL(int num);

	bool SongInLlist(CString inSong);
	bool AlbumInLlist(CString inAlbum);
	bool SingerInLlist(CString inSinger);
	void AddSongtoL(CString inSong);
	void AddAlbumtoL(CString inAlbum);
	void AddSingertoL(CString inSinger);
	void DelSongInL(CString inSong);
	void DelAlbumInL(CString inAlbum);
	void DelSingerInL(CString inSinger);

	bool operator == (const UserType &item);
};

