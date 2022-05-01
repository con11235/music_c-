#pragma once
#include<atlimage.h>
#include"SongType.h"
#include"AlbumType.h"
#include"SingerType.h"

class TabSinger;
class CMainDlg;

// MasterInfo3 대화 상자

class MasterInfo3 : public CDialogEx
{
	DECLARE_DYNAMIC(MasterInfo3)

public:
	MasterInfo3(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MasterInfo3();

	TabSinger *parent;
	CMainDlg *mparent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFO_MASTER3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CImage m_Img;
	SingerType mSinger;
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnPaint();
	CListCtrl mAlbumList;
	CListCtrl mSongList;
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
};
