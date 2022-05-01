#pragma once
using namespace std;

class SongType
{
private:
	CString s_Name;
	CString s_Id;
	CString s_Singer;
	CString s_Album;
	int s_NumLikes;
public:
	SongType();
	~SongType();

	CString getName();
	CString getId();
	CString getSinger();
	CString getAlbum();
	int getNumLikes();

	void setName(CString inName);
	void setId(CString inId);
	void setSinger(CString inSinger);
	void setAlbum(CString inAlbum);
	void setNumLikes(int inNumLikes);


	void operator = (const SongType &item);
	bool operator == (const SongType &item);
	bool operator < (const SongType &item);
	bool operator > (const SongType &item);
};
