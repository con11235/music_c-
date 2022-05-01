#pragma once
#include<atlimage.h>
#include"SongType.h"
#include"AlbumType.h"
#include"SingerType.h"

class TabSong;
// MasterInfo 대화 상자

class MasterInfo : public CDialogEx
{
	DECLARE_DYNAMIC(MasterInfo)

public:
	MasterInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MasterInfo();

	TabSong *parent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFO_MASTER };
#endif
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CStatic mAlbumImage;
	CImage m_Img;
	SongType mSong;
	AlbumType mAlbum;
	SingerType mSinger;
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnPaint();
};
