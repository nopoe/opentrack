#include "ftnoir_tracker_udp.h"
#include "opentrack/plugin-api.hpp"

FTNoIR_Tracker::FTNoIR_Tracker() : last_recv_pose { 0,0,0, 0,0,0 }, should_quit(false) {}

FTNoIR_Tracker::~FTNoIR_Tracker()
{
    should_quit = true;
    wait();
}

void FTNoIR_Tracker::run() {
    QByteArray datagram;
    datagram.resize(sizeof(last_recv_pose));
    (void) sock.bind(QHostAddress::Any, (int) s.port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    for (;;) {
        if (should_quit)
            break;
        {
            QMutexLocker foo(&mutex);
            while (sock.hasPendingDatagrams()) {
                sock.readDatagram((char * ) last_recv_pose, sizeof(double[6]));
            }
        }
        msleep(1);
    }
}

void FTNoIR_Tracker::start_tracker(QFrame*)
{
	start();
}

void FTNoIR_Tracker::data(double *data)
{
    QMutexLocker foo(&mutex);
    for (int i = 0; i < 6; i++)
        data[i] = last_recv_pose[i];
    
    int values[] = {
        0,
        90,
        -90,
        180,
        -180,
    };
    int indices[] = {
        s.add_yaw,
        s.add_pitch,
        s.add_roll,
    };
    
    for (int i = 0; i < 3; i++)
        data[Yaw + i] += values[indices[i]];
}

extern "C" OPENTRACK_EXPORT ITracker* GetConstructor()
{
    return new FTNoIR_Tracker;
}
