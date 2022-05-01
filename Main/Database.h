#pragma once
#include"SortedList.h"
#include"DoublyLinkedList.h"
#include"SingerType.h"
#include"SongType.h"
#include"AlbumType.h"
#include"UserType.h"
#include"PlayItemType.h"

class Database
{
private:
	SortedList<SingerType> mSingerList;
	SortedList<SongType> mSongList;
	SortedList<AlbumType> mAlbumList;
	UserType mUser;
	SortedList<PlayItemType> mChartList;
	
public:
	Database();
	~Database();
	
	PlayItemType mPlaying;

	int GetSingerLength();
	int AddSinger(SingerType inSinger);
	SingerType GetSinger(int idx);
	int GetSinger(SingerType &inSinger);
	int DeleteSinger(SingerType inSinger);
	int DeleteSinger(int idx);
	int ReplaceSinger(SingerType inSinger);
	void ResetSingerPointer();
	int GetNextSinger(SingerType &inSinger);
	int GetAlbumLength(SingerType inSinger);
	int GetSongLength(SingerType inSinger);

	int GetAlbumLength();
	int AddAlbum(AlbumType inAlbum);
	AlbumType GetAlbum(int idx);
	int GetAlbum(AlbumType &inAlbum);
	int DeleteAlbum(AlbumType inAlbum);
	int DeleteAlbum(int idx);
	int ReplaceAlbum(AlbumType inAlbum);
	void ResetAlbumPointer();
	int GetNextAlbum(AlbumType &inAlbum);
	int GetSongLength(AlbumType inAlbum);

	int GetSongLength();
	int AddSong(SongType inSong);
	SongType GetSong(int idx);
	int GetSong(SongType &inSong);
	int DeleteSong(SongType inSong);
	int DeleteSong(int idx);
	int ReplaceSong(SongType inSong);
	void ResetSongPointer();
	int GetNextSong(SongType &inSong);

	void SetUser(UserType inUser);
	UserType GetUser();
	void SetUserId(CString inId);
	void SetUserPw(CString inPw);
	CString GetUserId();
	CString GetUserPw();
	void AddToPL(PlayItemType item);

	void UpdateChart(int num = 5);
	int GetChartLength();
	int AddChart(PlayItemType inSong);
	int DeleteChart(PlayItemType inSong);
	int ReplaceChart(PlayItemType inSong);
	void ResetChartPointer();
	int GetNextChart(PlayItemType &inSong);
	PlayItemType GetChartItem(int idx);


	bool SongInLlist(CString inSong);
	bool AlbumInLlist(CString inAlbum);
	bool SingerInLlist(CString inSinger);
	void AddSongtoL(CString inSong);
	void AddAlbumtoL(CString inAlbum);
	void AddSingertoL(CString inSinger);
	void DelSongInL(CString inSong);
	void DelAlbumInL(CString inAlbum);
	void DelSingerInL(CString inSinger);


	void UpdatePL(int num = 3);
	int GetPLLength();
	int DeletePL(PlayItemType inSong);
	int ReplacePL(PlayItemType inSong);
	void ResetPLPointer();
	int GetNextPL(PlayItemType &inSong);
	PlayItemType GetPLItem(int idx);
	void GetBeforePLItem();
	void GetNextPLItem();
};

