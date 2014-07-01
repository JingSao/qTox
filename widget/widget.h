#ifndef WIDGET_H
#define WIDGET_H

#include <QThread>
#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QMenu>
#include "core.h"
#include "widget/form/addfriendform.h"
#include "widget/form/settingsform.h"
#include "camera.h"

#define PIXELS_TO_ACT 5

namespace Ui {
class Widget;
}

class GroupWidget;
class AddFriendForm;
class SettingsForm;
struct FriendWidget;
class Group;
struct Friend;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    enum TitleMode { CleanTitle = 0, OnlyCloseButton, MenuOff, MaxMinOff, FullScreenMode, MaximizeModeOff, MinimizeModeOff, FullTitle };
    void setTitlebarMode(const TitleMode &flag);
    void setTitlebarMenu(QMenu *menu, const QString &icon = "");
    void setCentralWidget(QWidget *widget, const QString &widgetName);
    QString getUsername();
    Core* getCore();
    Camera* getCamera();
    static Widget* getInstance();
    void showTestCamview();
    void newMessageAlert();
    bool isFriendWidgetCurActiveWidget(Friend* f);
    void updateFriendStatusLights(int friendId);
    int useNativeTheme;
    ~Widget();

signals:
    void friendRequestAccepted(const QString& userId);
    void friendRequested(const QString& friendAddress, const QString& message);
    void statusSet(Status status);
    void statusSelected(Status status);
    void usernameChanged(const QString& username);
    void statusMessageChanged(const QString& statusMessage);

private slots:
    void maximizeBtnClicked();
    void minimizeBtnClicked();
    void onConnected();
    void onDisconnected();
    void onStatusSet(Status status);
    void onAddClicked();
    void onGroupClicked();
    void onTransferClicked();
    void onSettingsClicked();
    void onFailedToStartCore();
    void onUsernameChanged(const QString& newUsername, const QString& oldUsername);
    void onStatusMessageChanged(const QString& newStatusMessage, const QString& oldStatusMessage);
    void onUsernameChanged(const QString& newUsername);
    void onStatusMessageChanged(const QString& newStatusMessage);
    void setUsername(const QString& username);
    void setStatusMessage(const QString &statusMessage);
    void addFriend(int friendId, const QString& userId);
    void addFriendFailed(const QString& userId);
    void onFriendStatusChanged(int friendId, Status status);
    void onFriendStatusMessageChanged(int friendId, const QString& message);
    void onFriendUsernameChanged(int friendId, const QString& username);
    void onFriendStatusMessageLoaded(int friendId, const QString& message);
    void onFriendUsernameLoaded(int friendId, const QString& username);
    void onFriendWidgetClicked(FriendWidget* widget);
    void onFriendMessageReceived(int friendId, const QString& message);
    void onFriendRequestReceived(const QString& userId, const QString& message);
    void onEmptyGroupCreated(int groupId);
    void onGroupInviteReceived(int32_t friendId, uint8_t *publicKey);
    void onGroupMessageReceived(int groupnumber, int friendgroupnumber, const QString& message);
    void onGroupNamelistChanged(int groupnumber, int peernumber, uint8_t change);
    void onGroupWidgetClicked(GroupWidget* widget);
    void removeFriend(int friendId);
    void copyFriendIdToClipboard(int friendId);
    void removeGroup(int groupId);

protected slots:
    void moveWindow(QMouseEvent *e);

private:
    void hideMainForms();
    Group* createGroup(int groupId);

private:
    Ui::Widget *ui;
    QHBoxLayout *centralLayout;
    QPoint dragPosition;
    TitleMode m_titleMode;
    bool moveWidget;
    bool inResizeZone;
    bool allowToResize;
    bool resizeVerSup;
    bool resizeHorEsq;
    bool resizeDiagSupEsq;
    bool resizeDiagSupDer;
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void paintEvent (QPaintEvent *);
    void resizeWindow(QMouseEvent *e);
    bool event(QEvent *event);
    int isWindowMinimized;
    Core* core;
    QThread* coreThread;
    AddFriendForm friendForm;
    SettingsForm settingsForm;
    static Widget* instance;
    FriendWidget* activeFriendWidget;
    GroupWidget* activeGroupWidget;
    int isFriendWidgetActive, isGroupWidgetActive;
    SelfCamView* camview;
    Camera* camera;
};

#endif // WIDGET_H
