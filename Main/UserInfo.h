#pragma once
#include<atlimage.h>
#include"SongType.h"
#include"AlbumType.h"
#include"SingerType.h"

class UserDlg;
class CMainDlg;
// UserInfo 대화 상자

class UserInfo : public CDialogEx
{
	DECLARE_DYNAMIC(UserInfo)

public:
	UserInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UserInfo();

	UserDlg *parent;
	CMainDlg *mparent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFO_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	CImage m_Img;
	SongType mSong;
	AlbumType mAlbum;
	SingerType mSinger;
	afx_msg void OnPaint();
	CButton mLikesAlbum;
	CButton mLikesSinger;
	CButton mLikesSong;
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBnClickedLikesSong();
	afx_msg void OnBnClickedLikesAlbum();
	afx_msg void OnBnClickedLikesSinger();
};
