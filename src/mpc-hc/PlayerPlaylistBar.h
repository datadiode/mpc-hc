/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2017 see Authors.txt
 *
 * This file is part of MPC-HC.
 *
 * MPC-HC is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-HC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include <afxcoll.h>
#include "CMPCThemePlayerBar.h"
#include "PlayerListCtrl.h"
#include "Playlist.h"
#include "DropTarget.h"
#include "../Subtitles/TextFile.h"
#include "CMPCThemeInlineEdit.h"
#include "YoutubeDL.h"
#include "AppSettings.h"
#include "WebView2EnvironmentOptions.h"
#include "WebView2.h"


class OpenMediaData;

class CMainFrame;

struct CueTrackMeta {
    CString title;
    CString performer;
    int fileID = 0;
    int trackID = 0;
    REFERENCE_TIME time = 0;
};

class CPlayerPlaylistBar : public CMPCThemePlayerBar, public CDropClient
{
    DECLARE_DYNAMIC(CPlayerPlaylistBar)

private:
    enum { COL_NAME, COL_TIME };

    CMainFrame* m_pMainFrame;

    Microsoft::WRL::ComPtr<ICoreWebView2Environment> m_webViewEnvironment;
    Microsoft::WRL::ComPtr<ICoreWebView2Controller> m_controller;
    Microsoft::WRL::ComPtr<ICoreWebView2> m_webView;
    EventRegistrationToken m_tokenNavigationCompleted;
    CString m_url;

    void InitializeWebView();
    HRESULT OnCreateEnvironmentCompleted(HRESULT result, ICoreWebView2Environment* environment);
    HRESULT OnCreateCoreWebView2ControllerCompleted(HRESULT result, ICoreWebView2Controller* controller);

    CMPCThemeInlineEdit m_edit;
    int inlineEditXpos;

    CFont m_font;
    void ScaleFont();

    CImageList m_fakeImageList;
    CPlayerListCtrl m_list;

    int m_itemHeight = 0;
    int m_initialWindowDPI = 0;
    bool createdWindow;
    CPlaylistIDs m_ExternalPlayListFNCopy;
    void ExternalPlayListLoaded(CStringW fn);

    EventClient m_eventc;
    void EventCallback(MpcEvent ev);

    int m_nTimeColWidth;
    void ResizeListColumn();

    CPlaylistItem* GetCur();

    void AddItem(CString fn, bool insertAtCurrent = false);
    void AddItem(CString fn, CAtlList<CString>* subs);
    void AddItem(CAtlList<CString>& fns, CAtlList<CString>* subs = nullptr, CString label = _T(""), CString ydl_src = _T(""), CString ydl_ua = _T(""), CString cue = _T(""), CAtlList<CYoutubeDLInstance::YDLSubInfo>* ydl_subs = nullptr);
    bool AddItemNoDuplicate(CString fn, bool insertAtCurrent = false);
    bool AddFromFilemask(CString mask, bool recurse_dirs, bool insertAtCurrent = false);
    bool AddItemsInFolder(CString folder, bool insertAtCurrent = false);
    void ParsePlayList(CString fn, CAtlList<CString>* subs, int redir_count = 0);
    void ParsePlayList(CAtlList<CString>& fns, CAtlList<CString>* subs, int redir_count = 0, CString label = _T(""), CString ydl_src = _T(""), CString ydl_ua = _T(""), CString cue = _T(""), CAtlList<CYoutubeDLInstance::YDLSubInfo>* ydl_subs = nullptr);
    void ResolveLinkFiles(CAtlList<CString>& fns);

    bool ParseBDMVPlayList(CString fn);

    bool PlaylistCanStripPath(CString path);
    bool ParseMPCPlayList(CString fn);
    bool SaveMPCPlayList(CString fn, CTextFile::enc e);
    bool ParseM3UPlayList(CString fn, bool* lav_fallback);
    bool ParseCUESheet(CString fn);
    
    void SetupList();
    void UpdateList();
    void EnsureVisible(POSITION pos);
    int FindItem(const POSITION pos) const;
    POSITION FindPos(int i);
    POSITION m_insertingPos;

    CImageList* m_pDragImage;
    BOOL m_bDragging;
    int m_nDragIndex, m_nDropIndex;
    CPoint m_ptDropPoint;

    void DropItemOnList();

    bool m_bHiddenDueToFullscreen;

    CDropTarget m_dropTarget;
    void OnDropFiles(CAtlList<CString>& slFiles, DROPEFFECT) override;
    DROPEFFECT OnDropAccept(COleDataObject*, DWORD, CPoint) override;

    CString m_playListPath;

    ULONGLONG m_tcLastSave;
    bool m_SaveDelayed;

public:
    CPlayerPlaylistBar(CMainFrame* pMainFrame);
    virtual ~CPlayerPlaylistBar();

    BOOL Create(CWnd* pParentWnd, UINT defDockBarID);

    virtual void ReloadTranslatableResources();

    virtual void LoadState(CFrameWnd* pParent);
    virtual void SaveState();

    bool IsHiddenDueToFullscreen() const;
    void SetHiddenDueToFullscreen(bool bHidenDueToFullscreen, bool returningFromFullScreen = false );

    void Navigate();
    void Navigate(const GpsRecord<>& rec);

    void LoadDuration(POSITION pos);

    CPlaylist m_pl;

    INT_PTR GetCount() const;
    int GetValidCount() const;
    int GetSelIdx() const;
    void SetSelIdx(int i);
    bool IsAtEnd();
    bool GetCur(CPlaylistItem& pli, bool check_fns = false) const;
    CString GetCurFileName(bool use_ydl_source = false);
    CString GetCurFileNameTitle();
    bool SetNext();
    bool SetPrev();
    void SetFirstSelected();
    void SetFirst();
    void SetLast();
    void SetCurValid(bool fValid);
    void SetCurLabel(CString label);
    void SetCurTime(REFERENCE_TIME rt);
    void Randomize();
    void UpdateLabel(CString in);

    void Refresh();
    void PlayListChanged();
    bool Empty();

    void Open(CAtlList<CString>& fns, bool fMulti, CAtlList<CString>* subs = nullptr, CString label = _T(""), CString ydl_src = _T(""), CString ydl_ua = _T(""), CString cue = _T(""));
    void Append(CAtlList<CString>& fns, bool fMulti, CAtlList<CString>* subs = nullptr, CString label = _T(""), CString ydl_src = _T(""), CString ydl_ua = _T(""), CString cue = _T(""), CAtlList<CYoutubeDLInstance::YDLSubInfo>* ydl_subs = nullptr);
    void ReplaceCurrentItem(CAtlList<CString>& fns, CAtlList<CString>* subs = nullptr, CString label = _T(""), CString ydl_src = _T(""), CString ydl_ua = _T(""), CString cue = _T(""), CAtlList<CYoutubeDLInstance::YDLSubInfo>* ydl_subs = nullptr);
    void AddSubtitleToCurrent(CString fn);

    void OpenDVD(CString fn);
    void Open(CStringW vdn, CStringW adn, int vinput, int vchannel, int ainput);
    void Append(CStringW vdn, CStringW adn, int vinput, int vchannel, int ainput);

    OpenMediaData* GetCurOMD(REFERENCE_TIME rtStart = 0, ABRepeat abRepeat = ABRepeat());

    void LoadPlaylist(LPCTSTR filename);
    void SavePlaylist(bool can_delay = false);

    bool SelectFileInPlaylist(LPCTSTR filename);
    bool DeleteFileInPlaylist(POSITION pos, bool recycle = true);
    bool IsExternalPlayListActive(CStringW& playlistPath);
    void ClearExternalPlaylistIfInvalid();

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnDestroy();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLvnKeyDown(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLvnKeydownList(NMHDR* pNMHDR, LRESULT* pResult);
    //  afx_msg void OnCustomdrawList(NMHDR* pNMHDR, LRESULT* pResult);
    void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg BOOL OnPlayPlay(UINT nID);
    afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg BOOL OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
    afx_msg void OnLvnBeginlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnLvnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnXButtonDown(UINT nFlags, UINT nButton, CPoint point);
    afx_msg void OnXButtonUp(UINT nFlags, UINT nButton, CPoint point);
    afx_msg void OnXButtonDblClk(UINT nFlags, UINT nButton, CPoint point);
};
