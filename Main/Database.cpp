#include "stdafx.h"
#include "Database.h"


Database::Database()
{
}


Database::~Database()
{
}

int Database::GetSingerLength() { return mSingerList.GetLength(); }
int Database::AddSinger(SingerType inSinger) { return mSingerList.Add(inSinger); }
SingerType Database::GetSinger(int idx) { return mSingerList.at(idx); }
int Database::GetSinger(SingerType &inSinger) { return mSingerList.Get(inSinger); }
int Database::DeleteSinger(SingerType inSinger) { return mSingerList.Delete(inSinger); }
int Database::DeleteSinger(int idx) { return mSingerList.DeleteIndex(idx); }
int Database::ReplaceSinger(SingerType inSinger) { return mSingerList.Replace(inSinger); }
void Database::ResetSingerPointer() { mSingerList.ResetPointer(); }
int Database::GetNextSinger(SingerType &inSinger) { return mSingerList.GetNextItem(inSinger); }
int Database::GetAlbumLength(SingerType inSinger) {
	AlbumType album;
	int num = 0;
	mAlbumList.ResetPointer();
	while (mAlbumList.GetNextItem(album) != -1) {
		if (album.getSinger() == inSinger.getName())
			num++;
	}
	return num;
}
int Database::GetSongLength(SingerType inSinger) {
	SongType song;
	int num = 0;
	mSongList.ResetPointer();
	while (mSongList.GetNextItem(song) != -1) {
		if (song.getSinger() == inSinger.getName())
			num++;
	}
	return num;
}


int Database::GetAlbumLength() { return mAlbumList.GetLength(); }
int Database::AddAlbum(AlbumType inAlbum) { return mAlbumList.Add(inAlbum); }
AlbumType Database::GetAlbum(int idx) { return mAlbumList.at(idx); }
int Database::GetAlbum(AlbumType &inAlbum) { return mAlbumList.Get(inAlbum); }
int Database::DeleteAlbum(AlbumType inAlbum) { return mAlbumList.Delete(inAlbum); }
int Database::DeleteAlbum(int idx) { return mAlbumList.DeleteIndex(idx); }
int Database::ReplaceAlbum(AlbumType inAlbum) { return mAlbumList.Replace(inAlbum); }
void Database::ResetAlbumPointer() { mAlbumList.ResetPointer(); }
int Database::GetNextAlbum(AlbumType &inAlbum) { return mAlbumList.GetNextItem(inAlbum); }
int Database::GetSongLength(AlbumType inAlbum) {
	SongType song;
	int num = 0;
	mSongList.ResetPointer();
	while (mSongList.GetNextItem(song) != -1) {
		if (song.getAlbum() == inAlbum.getName())
			num++;
	}
	return num;
}

int Database::GetSongLength() { return mSongList.GetLength(); }
int Database::AddSong(SongType inSong) { return mSongList.Add(inSong); }
SongType Database::GetSong(int idx) { return mSongList.at(idx); }
int Database::GetSong(SongType &inSong) { return mSongList.Get(inSong); }
int Database::DeleteSong(SongType inSong) { return mSongList.Delete(inSong); }
int Database::DeleteSong(int idx) { return mSongList.DeleteIndex(idx); }
int Database::ReplaceSong(SongType inSong) { return mSongList.Replace(inSong); }
void Database::ResetSongPointer() { mSongList.ResetPointer(); }
int Database::GetNextSong(SongType &inSong) { return mSongList.GetNextItem(inSong); }

void Database::SetUser(UserType inUser) { mUser = inUser; }
UserType Database::GetUser() { return mUser; }

void Database::SetUserId(CString inId) { mUser.setId(inId); }
void Database::SetUserPw(CString inPw) { mUser.setPw(inPw); }
CString Database::GetUserId() { return mUser.getId(); }
CString Database::GetUserPw() { return mUser.getPw(); }
void Database::AddToPL(PlayItemType item) { mUser.AddToPL(item); }

void Database::UpdateChart(int num) {
	mChartList.MakeEmpty();
	mSongList.ResetPointer();
	SongType song;
	PlayItemType item;
	while (mSongList.GetNextItem(song) != -1) {
		item = song;
		item.setPriority(num);
		mChartList.Add(item);
	}
	
}
int Database::GetChartLength() { return mChartList.GetLength(); }
int Database::AddChart(PlayItemType inSong) { return mChartList.Add(inSong); }
int Database::DeleteChart(PlayItemType inSong) { return mChartList.Delete(inSong); }
int Database::ReplaceChart(PlayItemType inSong) { return mChartList.Replace(inSong); }
void Database::ResetChartPointer() { mChartList.ResetPointer(); }
int Database::GetNextChart(PlayItemType &inSong) { return mChartList.GetNextItem(inSong); }
PlayItemType Database::GetChartItem(int idx) { return mChartList.at(idx); }


bool Database::SongInLlist(CString inSong) { return mUser.SongInLlist(inSong); }
bool Database::AlbumInLlist(CString inAlbum) { return mUser.AlbumInLlist(inAlbum); }
bool Database::SingerInLlist(CString inSinger) { return mUser.SingerInLlist(inSinger); }
void Database::AddSongtoL(CString inSong) { mUser.AddSongtoL(inSong); }
void Database::AddAlbumtoL(CString inAlbum) { mUser.AddAlbumtoL(inAlbum); }
void Database::AddSingertoL(CString inSinger) { mUser.AddSingertoL(inSinger); }
void Database::DelSongInL(CString inSong) { mUser.DelSongInL(inSong); }
void Database::DelAlbumInL(CString inAlbum) { mUser.DelAlbumInL(inAlbum); }
void Database::DelSingerInL(CString inSinger) { mUser.DelSingerInL(inSinger); }


void Database::UpdatePL(int num) { mUser.UpdatePL(num); }
int Database::GetPLLength() { return mUser.getPLLength(); }
int Database::DeletePL(PlayItemType inSong) { return mUser.DeletePL(inSong); }
int Database::ReplacePL(PlayItemType inSong) { return mUser.ReplacePL(inSong); }
void Database::ResetPLPointer() { mUser.ResetPLPointer(); }
int Database::GetNextPL(PlayItemType &inSong) { return mUser.GetNextPL(inSong); }
PlayItemType Database::GetPLItem(int idx) { return mUser.GetPLItem(idx); }
void Database::GetBeforePLItem() {
	int idx = mUser.GetPLItem(mPlaying);
	mPlaying = mUser.GetPLItem((idx - 1 + mUser.getPLLength()) % mUser.getPLLength());
}
void Database::GetNextPLItem() {
	int idx = mUser.GetPLItem(mPlaying);
	mPlaying = mUser.GetPLItem((idx + 1)%mUser.getPLLength());
}
