/***************************************************************************
 *  This file is part of Saaghar, a Persian poetry software                *
 *                                                                         *
 *  Copyright (C) 2010-2013 by S. Razi Alavizadeh                          *
 *  E-Mail: <s.r.alavizadeh@gmail.com>, WWW: <http://pozh.org>             *
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 3 of the License,         *
 *  (at your option) any later version                                     *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details                            *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program; if not, see http://www.gnu.org/licenses/      *
 *                                                                         *
 ***************************************************************************/

#ifndef SAAGHARWINDOW_H
#define SAAGHARWINDOW_H

#include "saagharwidget.h"

#include <QMainWindow>
#include <QSettings>
#include <QSpinBox>
#include <QToolButton>
#include <QUndoGroup>
#include <QComboBox>

class QExtendedSplashScreen;
class QMultiSelectWidget;
class OutLineTree;
class Settings;

namespace Ui
{
class SaagharWindow;
}

class SaagharWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SaagharWindow(QWidget* parent = 0, QExtendedSplashScreen* splashScreen = 0);
    ~SaagharWindow();

    enum TabType {
        SaagharViewerTab,
        WidgetTab
    };

    SaagharWidget* saagharWidget;
//      void emitReSizeEvent();
    static bool autoCheckForUpdatesState;
    static QSettings* getSettingsObject();
    void checkRegistration(bool forceShow = false);
    QMenu* cornerMenu();

//  public slots:
//      void emitReSizeEvent();

    static QString resourcesPath;//not-writable
    static QString userHomePath;//writable

private:
    QSplitter* splitter;
    OutLineTree* outlineTree;
    bool skipContextMenu;
    void setupBookmarkManagerUi();
    QBoxLayout* searchToolBarBoxLayout;
    bool skipSearchToolBarResize;
    void setupSearchToolBarUi();
    bool eventFilter(QObject* receiver, QEvent* event);
    void toolBarViewActions(QToolBar* toolBar, QMenu* menu, bool subMenu);
    QStringList selectedRandomRange;
    QStringList selectedSearchRange;
    bool randomOpenInNewTab;
    int previousTabIndex;
//      void importDataBase(const QString fileName);
    QStringList mainToolBarItems;
    QAction* actionInstance(const QString &actionObjectName = "", QString iconPath = "", QString displayName = "");
    void deleteActionInstance(const QString &actionObjectName);
    void multiSelectObjectInitialize(QMultiSelectWidget* multiSelectWidget, const QStringList &selectedData = QStringList(), int insertIndex = 0);
    QString convertToTeX(SaagharWidget* saagharObject);
    QPrinter* defaultPrinter;
    void printPreview(QPrinter* printer);
    QString tableToString(QTableWidget* table, QString columnSeparator, QString rowSeparator, int startRow, int startColumn, int endRow, int endColumn);
    void writeToFile(QString fileName, QString textToWrite);
    QString convertToHtml(SaagharWidget* saagharObject);
    //QStringList openedTabs;
    void scrollToFirstFoundedItem(QString phrase, int PoemID, int vorder);
    QTabWidget* mainTabWidget;
    void loadTabWidgetSettings();

    void loadGlobalSettings();
    void saveSettings();
    bool processTextChanged;
    QToolBar* parentCatsToolBar;
    SaagharWidget* getSaagharWidget(int tabIndex);
    Qt::MouseButtons pressedMouseButton;
    QWidget* insertNewTab(TabType tabType = SaagharWindow::SaagharViewerTab, const QString &title = QString(),
                          int id = -1, const QString &type = "CatID", bool noError = true,
                          bool pushToStack = true);
    Ui::SaagharWindow* ui;
    void createConnections();
    void setupUi();
    QMultiSelectWidget* selectSearchRange;
    QComboBox* comboBoxSearchRegion;
    QSpinBox* spinBoxMaxSearchResult;
    QPushButton* pushButtonSearch;
    QMenu* menuNavigation;
    QMenu* menuTools;
    QMenu* menuFile;
    QMenu* menuHelp;
    QMenu* menuView;
    QMenu* menuBookmarks;
    QMenu* m_cornerMenu;

    //submenus
    QMenu* menuOpenedTabs, *menuClosedTabs;
    //void updateTabsSubMenus();//move to slot section

    QMap<QString, QAction*> allActionMap;
    QAction* labelMaxResultSeparator;
    //QAction *labelMaxResultAction;
    QAction* spinBoxMaxSearchResultAction;
    QMenu* searchOptionMenu;
    QString mainToolBarSizeAction;
    QString mainToolBarStyleAction;
    //bool dataFromIdentifier(const QString &identifier, QString *type = 0, int *id = 0);

    //Undo FrameWork
    QUndoGroup* undoGroup;
    QAction* globalRedoAction;
    QAction* globalUndoAction;
    Settings* m_settingsDialog;
    QExtendedSplashScreen* m_splash;

    static bool isPortable;

public slots:
    void updateTabsSubMenus();
    void importDataBase(const QString &fileName, bool* ok = 0);

private slots:
    void openParentPage(int parentID, bool newPage = false);
    void openChildPage(int childID, bool newPage = false);
    void openPage(int id, SaagharWidget::PageType type, bool newPage = false);
    void createCustomContextMenu(const QPoint &pos);

#ifndef NO_PHONON_LIB
    void mediaInfoChanged(const QString &fileName, const QString &title = "", int id = -1);
#endif

    void ensureVisibleBookmarkedItem(const QString &type, const QString &itemText, const QString &data, bool ensureVisible = true, bool unbookmark = true);
    void setHomeAsDirty();
    void setAllAsDirty();
    void setAsDirty(int catId = -1, int poemId = -1);//-1 for skip it
    void actionClosedTabsClicked();
    void namedActionTriggered(bool checked = false);
    void toolbarViewChanges(QAction* action);
    void customizeRandomDialog();
    void toolBarContextMenu(const QPoint &pos);
    void checkForUpdates();
    void actFullScreenClicked(bool checked);
    void actionRemovePoet();
    //void newSearchNonAlphabetChanged(bool checked);
    //void newSearchFlagChanged(bool checked);
    void actionImportNewSet();
    void closeCurrentTab();
    void helpContents();
    void actionPrintPreviewClicked();
    void print(QPrinter* printer);
    void actionExportAsPDFClicked();
    void actionExportClicked();
    void actionPrintClicked();
    void openRandomPoem(int parentID, bool newPage = false);
    void aboutSaaghar();
    void tableSelectChanged();
    void tableItemPress(QTableWidgetItem* item);
    void tableItemClick(QTableWidgetItem* item);
    void tableItemMouseOver(QTableWidgetItem* item);
    void tableCurrentItemChanged(QTableWidgetItem* current, QTableWidgetItem* previous);
    void actionNewTabClicked();
    void actionNewWindowClicked();
    void currentTabChanged(int tabIndex);
    void tabCloser(int tabIndex);
    void showSettingsDialog();
    void applySettings();
    void newTabForItem(int id, const QString &type = "CatID", bool noError = true, bool pushToStack = true);
    void updateCaption();
    void searchStart();
    //Navigation
    void copySelectedItems();
    void actionHomeClicked();
    void actionPreviousPoemClicked();
    void actionNextPoemClicked();
    //Tools
    void actionGanjoorSiteClicked();

    //search options
    void showSearchOptionsDialog();
    void showSearchOptionMenu();
    void showSearchTips();
    void showStatusText(const QString &message, int newLevelsCount = 0);

protected:
//      void resizeEvent( QResizeEvent * event );
    void closeEvent(QCloseEvent* event);

signals:
    void maxItemPerPageChanged();
    void loadingStatusText(const QString &);
};
#endif // SAAGHARWINDOW_H
