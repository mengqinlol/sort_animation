#include "mythread.h"

myThread::myThread()
{

}

void myThread::makeSound(int a)//从主线程接收数据，发出value为a的声音
{
	qDebug()<<"making sound"<<a;
    m[endm++]=new MidiItem(0,a,300,0);
}

void myThread::run()//子线程函数
{
	//qDebug()<<"running thread";
	while(1)//保持子线程运行
    {
		//qDebug()<<"whileing";
		msleep(50);//睡眠50ms，子线程50ms执行一次
		if(headm==endm)	//检查有没有需要发出的声音
        {
            qDebug()<<"No sound";
            continue;
        }
		qDebug()<<"doing sounds";		//发出声音
        msleep(m[headm]->sleep);
        DWORD voice=(0x7F<<16)|(m[headm]->value<<8)|0x90|m[headm]->channel;
        m[headm]->handle=new HMIDIOUT;
        midiOutOpen(m[headm]->handle,0,0,0,0);
        midiOutShortMsg(*m[headm]->handle,voice);
        msleep(m[headm]->dur);
        midiOutClose(*m[headm++]->handle);
    }

}
