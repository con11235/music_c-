#pragma once

class CMainDlg;
class UserInfo;
class Mypage;
// UserDlg 대화 상자

class UserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserDlg)

public:
	UserDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UserDlg();

	CMainDlg *parent;
	UserInfo *pInfoDlg;
	Mypage* pMypageDlg;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnClose();
	CListCtrl mChart;
	CComboBox mSortChart;
	afx_msg void OnCbnSelchangeChartSort();
	afx_msg void OnBnClickedAddPl();
	afx_msg void OnBnClickedMypage();
	afx_msg void OnBnClickedInfo();
};
