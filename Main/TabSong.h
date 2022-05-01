#pragma once

class MasterDlg;
class CMainDlg;
class MasterInfo;
// TabSong 대화 상자

class TabSong : public CDialogEx
{
	DECLARE_DYNAMIC(TabSong)

public:
	TabSong(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TabSong();

	MasterDlg *parent;
	CMainDlg *mparent;
	MasterInfo *pInfoDlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SONGLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	CListCtrl mListCtrl;
	CComboBox mComboSinger;
	CComboBox mComboAlbum;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedReplace();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedInfo();
	afx_msg void OnBnClickedSavefile();
	afx_msg void OnBnClickedGetfile();
	afx_msg void OnCbnSelchangeComboSinger();
};
