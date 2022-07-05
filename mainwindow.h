#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include "mythread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


//void MidiIO(int value) {
//    HMIDIOUT handle;
//    midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);
//    int volume = 0x6f;
//    int voice = 0x0;

//    voice = (volume << 16) + (value << 8) + 0x94;

//    midiOutShortMsg(handle, voice);
//    Sleep(5000);

//    midiOutClose(handle);
//}

struct ani_item
{
    int x=-1,y=-1;
    int a=-1,b=-1;
    int c=-1,d=-1;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int endm=0;
    QLabel *item[100],*size_label,*key_label;
    QPushButton *albtns[10],*numbtns[5],*test,*turbobtn,*slowbtn,*musicbtn;
    QString alName[10]={"冒泡排序","选择排序","插入排序","堆排序","归并排序"};
    QString numName[5]={"10","20","50","100"};
    QPropertyAnimation *xani,*yani,*aani,*bani,*chani[105],*insani[105];
    myThread *music;
    int abani=0;
    int endch=0,checkcnt=0,endi=0,inscnt=0;
    ani_item s[50000];
    int heads=0,tails=0;
    int nums[5]={10,20,50,100};
    int num=4,a[100];
    int size=-1;
    int cursize=-1;
    void suiji(int max);
    void rec_swap(int x,int y);
    void rec_cmp(int a,int b);
    void swap(int x,int y);
    void cmp(int a,int b);
    void item_generate();
    void ani_start();
    void check();
    void makeSound(int a,int b);
    QTimer *checker;
    int dur=500;
    int xx,yy,cc,dd;
    bool isMusicOn=false;
    bool isAniStarted=false;
	bool isAniing=false;
	bool isChecking=false;
private slots:
    void albtns_clicked();
    void numbtns_clicked();
    void swapFinish();
	void cmpFinish();
    void checkani();
    void checkFinish();
    void tests();
    void slowDown();
    void speedUp();
    void musicOn();
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
