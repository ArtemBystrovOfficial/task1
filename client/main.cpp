#include "FClient.hpp"

#include "../server/FManager/MainPocket.hpp"

using fec = ReciverSingle<MainPocket>::f_error;

void printStat(bool is)
{
    if (is)
        std::cout << "ok: ";
    else
        std::cout << "fail: ";
}



using mf = MainPocket::function;
using mc = MainPocket::codeState;

int main()
{
    
    FClient <MainPocket> client("127.0.0.1", 2001);

    client.connect();

    std::thread th([&] {

        std::pair <MainPocket, fec> pocket_recv;

        auto& [pocket, er] = pocket_recv;


        while (client.isConnected())
        {

            client >> pocket_recv;

            switch (er)
            {

                //OK Pocket recived
            case fec::none:
            {

                printStat(pocket.isOk);

                switch (pocket.func)
                {
                case mf::getResult:
                {

                    std::cout << "get_result: \n";

                    if (pocket.isOk)
                        std::cout << pocket.result;
                }
                break;
                case mf::getStatus:
                {
                    std::cout << "get_status: \n";

                    if (pocket.isOk)
                        switch (pocket.code)
                        {
                        case mc::idle_state: std::cout << "Free\n";  break;
                        case mc::measure_state:  std::cout << "Working\n";  break;
                        case mc::busy_state:  std::cout << "Resultget\n";  break;
                        case mc::error_state:  std::cout << "Error\n";  break;
                        }
                }
                break;

                case mf::setRange:
                {
                    std::cout << "set_range: \n";
                }
                break;
                case mf::startMeasure:
                {
                    std::cout << "start_measure: \n";
                }
                break;
                case mf::stopMeasure:
                {
                    std::cout << "stop_measure: \n";
                }
                break;
                }
            }
            break;

            //OK Pocket recived
            case fec::pause: {/* server on pause */ } break;

                //OK Pocket recived
            case fec::ban: {/* server ban your IP */ } break;

                break;

            }
        }

        });

    //////////////////


    MainPocket out;

    std::string command;

    while (true)
    {
        std::cin >> command;

        if (command == "exit")
            break;

        if (command == "get_result")
        {
            out.func = mf::getResult;
        }
        if (command == "get_status")
        {
            out.func = mf::getStatus;

        }
        if (command == "set_range")
        {
            out.func = mf::setRange;

            std::cout << "range:\n";

            std::cin >> out.range;
        }
        if (command == "start_measure")
        {
            out.func = mf::startMeasure;

        }
        if (command == "stop_measure")
        {
            out.func = mf::stopMeasure;
        }

        std::cout << "channel: \n";
        std::cin >> out.channel;

        client << out;

    }

    client.disconect();

    th.join();

}