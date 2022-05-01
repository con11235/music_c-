#include "stdafx.h"
#include "UserType.h"


UserType::UserType():
	u_Id(_T("con")), u_Pw(_T("1234")) {}


UserType::~UserType()
{}

CString UserType::getId() { return u_Id; }
CString UserType::getPw() { return u_Pw; }

void UserType::setId(CString inId) { u_Id = inId; }
void UserType::setPw(CString inPw) { u_Pw = inPw; }

void UserType::AddToPL(PlayItemType item) { 
	item.setInTime();
	item.setUsersNum(PlayList.GetLength());
	PlayList.Add(item); 

}
int UserType::getPLLength() { return PlayList.GetLength(); }
int UserType::DeletePL(PlayItemType inSong) { return PlayList.Delete(inSong); }
int UserType::ReplacePL(PlayItemType inSong) { return PlayList.Replace(inSong); }
void UserType::ResetPLPointer() { PlayList.ResetPointer(); }
int UserType::GetNextPL(PlayItemType &inSong) { return PlayList.GetNextItem(inSong); }
int UserType::GetPLItem(PlayItemType inSong) { return PlayList.Get(inSong); }
PlayItemType UserType::GetPLItem(int idx) { return PlayList.at(idx); }
void UserType::UpdatePL(int num) {
	SortedList<PlayItemType> tmpList = PlayList;
	PlayList.MakeEmpty();
	PlayItemType item;
	tmpList.ResetPointer();
	while (tmpList.GetNextItem(item) != -1) {
		item.setPriority(num);
		PlayList.Add(item);
	}
}

bool UserType::SongInLlist(CString inSong) {
	if (LSongList.Get(inSong) != -1)
		return true;
	return false;
}
bool UserType::AlbumInLlist(CString inAlbum) {
	if (LAlbumList.Get(inAlbum) != -1)
		return true;
	return false;
}
bool UserType::SingerInLlist(CString inSinger) {
	if (LSingerList.Get(inSinger) != -1)
		return true;
	return false;
}
void UserType::AddSongtoL(CString inSong) { LSongList.Add(inSong); }
void UserType::AddAlbumtoL(CString inAlbum) { LAlbumList.Add(inAlbum); }
void UserType::AddSingertoL(CString inSinger) { LSingerList.Add(inSinger); }
void UserType::DelSongInL(CString inSong) { LSongList.Delete(inSong); }
void UserType::DelAlbumInL(CString inAlbum) { LAlbumList.Delete(inAlbum); }
void UserType::DelSingerInL(CString inSinger) { LSingerList.Delete(inSinger); }

bool UserType::operator == (const UserType &item) {
	if (this->u_Id == item.u_Id)
		return true;
	return false;
}
