#pragma once

class MasterDlg;
class CMainDlg;
class MasterInfo2;
// TabAlbum 대화 상자

class TabAlbum : public CDialogEx
{
	DECLARE_DYNAMIC(TabAlbum)

public:
	TabAlbum(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TabAlbum();

	MasterDlg *parent;
	CMainDlg *mparent;
	MasterInfo2 *pInfoDlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALBUMLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	CListCtrl mListCtrl;
	CDateTimeCtrl mDate;
	CComboBox mComboGenre;
	CComboBox mComboSinger;
	CComboBox mComboType;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedReplace();
	afx_msg void OnBnClickedInfo();
	afx_msg void OnBnClickedSavefile();
	afx_msg void OnBnClickedGetfile();
};
