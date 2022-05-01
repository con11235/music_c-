#pragma once
#include<atlimage.h>
#include"SongType.h"
#include"AlbumType.h"
#include"SingerType.h"

class TabAlbum;
class CMainDlg;
// MasterInfo2 대화 상자

class MasterInfo2 : public CDialogEx
{
	DECLARE_DYNAMIC(MasterInfo2)

public:
	MasterInfo2(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MasterInfo2();

	TabAlbum *parent;
	CMainDlg *mparent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFO_MASTER2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CImage m_Img;
	AlbumType mAlbum;
	SingerType mSinger;
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnPaint();
	CListCtrl mSongList;
};
