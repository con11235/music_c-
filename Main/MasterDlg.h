#pragma once
#include"Database.h"
class CMainDlg;
class TabSong;
class TabSinger;
class TabAlbum;

// MasterDlg 대화 상자

class MasterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MasterDlg)

public:
	MasterDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MasterDlg();

	CMainDlg* parent;
	TabSong* pSongDlg;
	TabAlbum* pAlbumDlg;
	TabSinger* pSingerDlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MASTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	CTabCtrl mTab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
