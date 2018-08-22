#pragma once
#include "Camera.h"
#include "cameraGuide.h"
#include "cameraSim.h"

// CTrackerDlg �Ի���
class CTrackerDlg : public CDialogEx
{
#define WM_UPDATEDATA WM_USER+1
// ����
public:
	CTrackerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRACKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnUpdateData(WPARAM wParam, LPARAM IParam);

	Camera **m_camera;
	static DWORD WINAPI _OperGuide(LPVOID lpParameter);
	static DWORD WINAPI _ShowGuide(LPVOID lpParameter);
	static DWORD WINAPI _OperImaging(LPVOID lpParameter);
	static DWORD WINAPI _ShowImaging(LPVOID lpParameter);
public:
	afx_msg void OnBnClickedBtnGuide();
	afx_msg void OnBnClickedBtnImaging();
};
