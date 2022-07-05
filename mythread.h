#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QWidget>
#include <QThread>
#include <QTimer>
#include <Windows.h>
#include <mmsystem.h>
class MidiItem : public QWidget //记录音乐各个参数
{
public:
    HMIDIOUT *handle;
    int value,channel;
	int dur,sleep;//持续时间，等待时间
    QTimer *sleeper,*duration;
    MidiItem(int sleepp,int val,int durr,int chann)
    {
        sleep=sleepp;
        dur=durr;
        value=val;
        channel=chann;
	}
};
class myThread : public QThread
{
    Q_OBJECT
public:
    myThread();
    MidiItem *m[1000];
    int endm=0,headm=0;
    void makeSound(int a);
protected:
    void run();

};

#endif // MYTHREAD_H
