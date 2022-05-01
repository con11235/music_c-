#pragma once

class MasterDlg;
class CMainDlg;
class MasterInfo3;
// TabSinger 대화 상자

class TabSinger : public CDialogEx
{
	DECLARE_DYNAMIC(TabSinger)

public:
	TabSinger(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TabSinger();

	MasterDlg *parent;
	CMainDlg *mparent;
	MasterInfo3 *pInfoDlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SINGERLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	CListCtrl mListCtrl;
	CComboBox mComboType;
	CComboBox mComboGenre;
	afx_msg void OnBnClickedAdd();
	CDateTimeCtrl mDate;
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedReplace();
	afx_msg void OnBnClickedSavefile();
	afx_msg void OnBnClickedGetfile();
	afx_msg void OnBnClickedInfo();
};
