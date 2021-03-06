#ifndef DAEMONQT_H
#define DAEMONQT_H

#include <QObject>
#include <QThread>
#include <QMutex>

namespace i2p
{
namespace qt
{
    class DaemonQTImpl
    {
    public:

		DaemonQTImpl ();
		~DaemonQTImpl ();	

        typedef void (*runningChangedCallback)();

        /**
         * @brief init
         * @param argc
         * @param argv
         * @return success
         */
        bool init(int argc, char* argv[]);
        void start();
        void stop();
        void restart();
        void setRunningCallback(runningChangedCallback cb);
        bool isRunning();
    private:
        void setRunning(bool running);
	private:
		QMutex* mutex;
        bool m_IsRunning;
		runningChangedCallback m_RunningChangedCallback;
    };

	class Worker : public QObject
    {
        Q_OBJECT
	public:

		Worker (DaemonQTImpl& daemon);		

	private:

		DaemonQTImpl& m_Daemon;		

    public slots:
        void startDaemon();
        void restartDaemon();
        void stopDaemon();

    signals:
        void resultReady();
    };	

    class Controller : public QObject
    {
        Q_OBJECT
        QThread workerThread;
    public:
        Controller(DaemonQTImpl& daemon);
        ~Controller();
	private:
		DaemonQTImpl& m_Daemon;	

    public slots:
        void handleResults(){}
    signals:
        void startDaemon();
        void stopDaemon();
        void restartDaemon();
    };
}
}

#endif // DAEMONQT_H
