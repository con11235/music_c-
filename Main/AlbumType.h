#pragma once
using namespace std;

class AlbumType
{
private:
	CString s_Name;
	CString s_Comeout;
	CString s_Type;
	CString s_Genre;
	CString s_Singer;
	int s_NumLikes;

public:
	AlbumType();
	~AlbumType();

	CString getName();
	CString getComeout();
	CString getType();
	CString getGenre();
	CString getSinger();
	int getNumLikes();

	void setName(CString inName);
	void setComeout(CString inComeout);
	void setType(CString inType);
	void setGenre(CString inGenre);
	void setSinger(CString inSinger);
	void setNumLikes(int inNumLikes);

	void operator = (AlbumType &item);
	bool operator == (const AlbumType &item);
	bool operator < (const AlbumType &item);
	bool operator > (const AlbumType &item);
};