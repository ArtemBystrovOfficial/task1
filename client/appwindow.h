#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QQuickWidget>
#include <QObject>
#include <QWidget>
#include <QQuickWidget>
#include <QLayout>
#include <QStatusBar>
#include <QMenuBar>
#include <QQuickItem>
#include <QObject>
#include <Colors.h>
#include <QMessageBox>
#include <QTimer>

#include <thread>
#include <atomic>
#include <vector>

#include "../../server/FManager/MainPocket.hpp"
#include "FClient.hpp"

class AppWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AppWindow(QWidget *parent = nullptr);

    //pre-work
    void setting();

    void client_settings();

    void createChannels(int n);

    ~AppWindow();

public slots:

    //operations with client
    void setChannelStatus(int channel, MainPocket::codeState state);

    void setRequestStatus(bool isOk, MainPocket::function func);

    void setResult(int channel, float n);

    //operation with server

    void req_start(int channel);

    void req_stop(int channel);

    void req_set_range(int channel,int range);

    void req_get_result(int channel);

    void req_get_status(int channel);

signals:

    void set_channel_status_thread_safety(int channel, MainPocket::codeState state);

    void set_request_status_thread_safety(bool isOk, MainPocket::function func);

    void set_result_thread_safety(int channel, float n);


private:

    // system functions and checks
    bool checkSize(int channel);

    void _recv_procces();

    // members

    std::vector< QQuickWidget * > channels;

    QVBoxLayout * main_layout;

    //server varibles
    FClient <MainPocket> client;

    std::thread recv_th;
    std::atomic<bool> is_exit;

    // timer for refresh connection

    QTimer timer;

};

#endif // APPWINDOW_H
