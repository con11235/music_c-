#pragma once
using namespace std;

class SingerType
{
private:
	CString s_Name;
	CString s_DebutYear;
	CString s_Type;
	CString s_Genre;
	int s_NumLikes;
public:
	SingerType();
	~SingerType();

	CString getName();
	CString getDebutYear();
	CString getType();
	CString getGenre();
	int getNumLikes();
	
	void setName(CString inName);
	void setDebutYear(CString inDebutYear);
	void setType(CString inType);
	void setGenre(CString inGenre);
	void setNumLikes(int inNumLikes);

	void operator = (SingerType &item);
	bool operator == (const SingerType &item);
	bool operator < (const SingerType &item);
	bool operator > (const SingerType &item);
};