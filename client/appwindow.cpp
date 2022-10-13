#include "appwindow.h"

//#define DEBUG_DESIGN

using ec = ReciverSingle<MainPocket>::f_error;
using mf = MainPocket::function;

AppWindow::AppWindow(QWidget *parent)
    : QMainWindow{parent},client("188.168.25.28",21112), is_exit(false)
{

    // try connect area

#ifndef DEBUG_DESIGN
    if(!client.connect())
    {
        QMessageBox::warning(this,"error","error connection");
        exit(0);
    }
#endif
    client_settings();

    ///////////////////


    setting();

    createChannels(CHANNELS_SIZE);

}

void AppWindow::setting()
{
    auto * main_area = new QWidget;

    main_area->setStyleSheet("background: #111111;");

    auto * main_layout = new QVBoxLayout;

    main_area->setLayout(main_layout);

    setCentralWidget(main_area);

    this->main_layout = main_layout;

    //safety for threads
    connect(this,&AppWindow::set_channel_status_thread_safety, this,
                  &AppWindow::setChannelStatus,Qt::ConnectionType::QueuedConnection);

    connect(this,&AppWindow::set_request_status_thread_safety, this,
                  &AppWindow::setRequestStatus,Qt::ConnectionType::QueuedConnection);

    connect(this,&AppWindow::set_result_thread_safety, this,
                  &AppWindow::setResult,Qt::ConnectionType::QueuedConnection);

    this->statusBar()->showMessage("ok, start");

}

void AppWindow::client_settings()
{
    recv_th = std::thread([&]{
        this->_recv_procces();
    });
}

void AppWindow::createChannels(int n)
{
    //names of channels
    QQuickWidget * names =  new QQuickWidget(QUrl("qrc:/Annotation.qml"));
    names->setResizeMode(QQuickWidget::SizeRootObjectToView);
    names->setFixedHeight(50);

    main_layout->addWidget(names);


    for(int i=0;i<n;i++)
    {
        QQuickWidget * pv =  new QQuickWidget(QUrl("qrc:/Channel.qml"));
        pv->setResizeMode(QQuickWidget::SizeRootObjectToView);
        pv->setFixedHeight(50);

        main_layout->addWidget(pv);

        channels.push_back(pv);

        setChannelStatus(i,MainPocket::codeState::idle_state);

        auto * root = pv->rootObject();

        // connect all signals system
        if(root)
        {
          root->setProperty("channel",i);

          auto * button1 = root->findChild<QObject*>("start");
          if(!button1)
              continue;
          connect(button1,SIGNAL(click(int)),this,SLOT(req_start(int)));

          auto * button2 = root->findChild<QObject*>("stop");
          if(!button2)
              continue;
          connect(button2,SIGNAL(click(int)),this,SLOT(req_stop(int)));

          auto * button3 = root->findChild<QObject*>("set_range");
          if(!button3)
              continue;
          connect(button3,SIGNAL(click(int,int)),this,SLOT(req_set_range(int,int)));

          auto * button4 = root->findChild<QObject*>("get_result");
          if(!button4)
              continue;
          connect(button4,SIGNAL(click(int)),this,SLOT(req_get_result(int)));

          auto * channel_numb = root->findChild<QObject*>("channel");
          if(!channel_numb)
              continue;
          channel_numb->setProperty("text",QString("    ")+QString::number(i));
        }

    }

    main_layout->addStretch(1);

    //refresh status in 1 sec
    for(int i=0;i<CHANNELS_SIZE;i++)
        connect(&timer,&QTimer::timeout,this,[this,i]{ req_get_status(i); },Qt::QueuedConnection);

    timer.start(1000);

}

void AppWindow::setChannelStatus(int channel,MainPocket::codeState state)
{

    //extra safe

    if(!checkSize(channel))
        return;

    auto * root = channels[channel]->rootObject();

    if(!root)
        return;

    auto * state_label = root->findChild<QObject*>("status");

    if(!state_label)
        return;

    using cs = MainPocket::codeState;
    switch(state)
    {
        case cs::busy_state:{
           state_label->setProperty("color",BUSY_STATE_COLOR);
           state_label->setProperty("text","Result     ");
        }break;
        case cs::error_state:{
            state_label->setProperty("color",ERROR_STATE_COLOR);
            state_label->setProperty("text","Error       ");
        }break;
        case cs::idle_state:{
            state_label->setProperty("color",IDLE_STATE_COLOR);
            state_label->setProperty("text","Free        ");
        }break;
        case cs::measure_state:{
            state_label->setProperty("color",MEASURE_STATE_COLOR);
            state_label->setProperty("text","Working");
        }break;
    }

}

void AppWindow::setRequestStatus(bool isOk, MainPocket::function func)
{

    //off status becouse this refreshng every second
    if(func == mf::getStatus)
        return;

    QString out_state="";
    if(isOk)
    {
        out_state+="ok | ";
        this->statusBar()->setStyleSheet(STATUSBAR_OK_COLOR);
    }
    else
    {
        out_state+="fail | ";
        this->statusBar()->setStyleSheet(STATUSBAR_FAIL_COLOR);
    }

    switch(func)
    {
          case mf ::getResult: out_state+= isOk ? "get_result" : "get_result: result not ready"; break;
          case mf ::getStatus: out_state+= isOk ? "get_status" : "get_status: unknwown error"; break;
          case mf ::setRange: out_state+= isOk ? "set_range" : "set_range: use value in range 0-3"; break;
          case mf ::startMeasure: out_state+= isOk ? "start_measure" : "start_measure: procces already run"; break;
          case mf ::stopMeasure: out_state+= isOk ? "stop_measure" : "stop_measure: procces not started"; break;
    }

    this->statusBar()->showMessage(out_state);
}

void AppWindow::setResult(int channel,float n)
{
    if(!checkSize(channel))
        return;

    auto * root = channels[channel]->rootObject();

    if(root)
    {
        auto * result_label = root->findChild<QObject*>("result");

        if(result_label)
            result_label->setProperty("text",QString::number(n));
    }

}

AppWindow::~AppWindow()
{

    is_exit.store(true);

    //extra exit unlock recv block
    req_get_result(0);

    if(recv_th.joinable())
          recv_th.join();
}

void AppWindow::req_start(int channel)
{

    MainPocket pocket;
    pocket.channel = channel;
    pocket.func = mf::startMeasure;

    client << pocket;
}

void AppWindow::req_stop(int channel)
{

    MainPocket pocket;
    pocket.channel = channel;
    pocket.func = mf::stopMeasure;

    client << pocket;
}

void AppWindow::req_set_range(int channel, int range)
{

    MainPocket pocket;
    pocket.channel = channel;
    pocket.func = mf::setRange;
    pocket.range = range;

    client << pocket;
}

void AppWindow::req_get_result(int channel)
{

    MainPocket pocket;
    pocket.channel = channel;
    pocket.func = mf::getResult;

    client << pocket;
}

void AppWindow::req_get_status(int channel)
{

    MainPocket pocket;
    pocket.channel = channel;
    pocket.func = mf::getStatus;

    client << pocket;
}

bool AppWindow::checkSize(int channel)
{
    return channel >=0 && channel < channels.size();
}

void AppWindow::_recv_procces()
{
    std::pair <MainPocket,ec> recv_pocket;

    while(!is_exit.load() && client.isConnected())
    {
        client >> recv_pocket;

        if(is_exit.load())
            break;

        auto & [pocket, er] = recv_pocket;

        switch(er)
        {
        case ec::ban: /*skip now*/ break;
        case ec::pause: /*skip now*/  break;
        case ec::none:
        {
            emit set_request_status_thread_safety(pocket.isOk,pocket.func);

            switch(pocket.func)
            {
            case mf ::getResult:{
                if(pocket.isOk)
                    emit set_result_thread_safety(pocket.channel,pocket.result);
            }break;

            case mf ::getStatus:{
                emit set_channel_status_thread_safety(pocket.channel,pocket.code);
            }break;

            case mf ::setRange:{
                // none
            }break;

            case mf ::startMeasure:{
                // none
            }break;

            case mf ::stopMeasure:{
                 // none
            }break;

            }
        }
        break;
        }
    }
}
