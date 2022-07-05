#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Sorts.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	size_label=new QLabel(this);															//创建固定的几个label和Button
	size_label->setText("还未选择");
	size_label->setGeometry(500,430,100,100);
	QLabel *frame=new QLabel(this);
    frame->setStyleSheet("border:1px solid balck;");
    frame->setGeometry(50,50,700,400);
	QLabel *label1=new QLabel(this);
    label1->setText("数据规模：");
    label1->setGeometry(50,430,100,100);
    this->setFixedSize(900,600);
    test=new QPushButton("test",this);
	test->setGeometry(9000,400,80,40);
    connect(test,&QPushButton::clicked,this,&MainWindow::tests);
	for(int i=0;i<num;i++)//批量创建排序算法按钮
	{
        albtns[i]=new QPushButton(alName[i],this);
        albtns[i]->setGeometry(800,50+50*i,80,40);
        connect(albtns[i],&QPushButton::clicked,this,&MainWindow::albtns_clicked);
    }
	for(int i=0;i<4;i++)//批量创建数据规模按钮
    {
        numbtns[i]=new QPushButton(numName[i],this);
        numbtns[i]->setGeometry(130+100*i,470,40,40);
        connect(numbtns[i],&QPushButton::clicked,this,&MainWindow::numbtns_clicked);
    }
	musicbtn=new QPushButton("来点音乐？",this);								//创建三个固定的速度调节按钮
    musicbtn->setGeometry(630,520,80,40);
    connect(musicbtn,&QPushButton::clicked,this,&MainWindow::musicOn);
    slowbtn=new QPushButton("原速",this);
    slowbtn->setGeometry(630,470,80,40);
    connect(slowbtn,&QPushButton::clicked,this,&MainWindow::slowDown);
    turbobtn=new QPushButton("加速！",this);
    turbobtn->setGeometry(750,470,80,40);
    connect(turbobtn,&QPushButton::clicked,this,&MainWindow::speedUp);
	checker=new QTimer();//创建用于check的计时器
	music=new myThread();//创建播放音乐的子线程
	music->start();
}

void MainWindow::musicOn()//设置动画速度和音乐状态
{
    isMusicOn=true;
	dur=1200;
}


void MainWindow::slowDown()
{
    isMusicOn=false;
    dur=500;
}

void MainWindow::speedUp()
{
    isMusicOn=false;
    dur=100;
}

void MainWindow::tests()
{
    //m[0]=new MidiItem(0,50,400,0);
    cmp(size-2,size-1);
}

void MainWindow::numbtns_clicked()//数据规模按钮槽函数
{
    int idx=-1;
	for(int i=0;i<num;i++)//找到是那个按钮被点击
    {
        if(numbtns[i]->hasFocus())
        {
            idx=i;
            break;
        }
    }
	size=nums[idx];//确定数据规模
	size_label->setText( QString("%1").arg(size) );//显示数据规模
	item_generate();//生成动画item
	heads=0;
	tails=0;
    for(int i=0;i<num;i++)
    {
		connect(albtns[i],&QPushButton::clicked,this,&MainWindow::albtns_clicked);	//连接算法按钮与其槽函数
    }
}

void MainWindow::albtns_clicked()
{
    rec_cmp(-1,-1);
    int idx=-1;
	for(int i=0;i<num;i++)//找到是哪个按钮被点击
    {
        if(albtns[i]->hasFocus())
        {
            idx=i;
            break;
        }
    }
	switch(idx)//执行排序算法
    {
        case 0:
            this->setFixedSize(900,600);
            Bubble(a,size,this);
        break;

        case 1:
        this->setFixedSize(900,600);
            Select(a,size,this);
        break;

        case 2:
            this->setFixedSize(900,600);
            Insert(a,size,this);
        break;

        case 3:
            this->setFixedSize(900,600);
            heap_sort(a,size,this);
        break;
    }
    ani_start();
}

void MainWindow::item_generate()
{
    int width=700/size,height=400/size;
	for(int i=0;i<cursize;i++)//清除以往的items
    {
        delete item[i];
    }
	suiji(size);//随机数据
	for(int j=0;j<size;j++)//依照数据生成动画item
    {
        int i=a[j]-1;
        item[j]=new QLabel(this);
        item[j]->setGeometry(50+width*j,50+(400*(size-i-1)/size),width,height*(i+1));
        if(size<=20)
            item[j]->setText(QString("%1").arg(i+1));
        item[j]->setStyleSheet("background-color: rgba(50,100,255,"+QString("%1").arg((1.0*i/size)/3*2+0.2)+")");
        item[j]->show();
    }
    cursize=size;
}


void MainWindow::rec_swap(int x,int y)//记录x与y的交换动作
{
    if(isAniStarted)
        return;
    //qDebug()<<x<<y<<a<<b;
	ani_item t;
    t.x=x;
    t.y=y;
    s[tails++]=t;
    tails%=99999;
    qDebug()<<tails<<"swap";
}

void MainWindow::rec_cmp(int a,int b)//记录a与b的比较动作
{
    if(isAniStarted)
        return;
    //qDebug()<<x<<y<<a<<b;
    ani_item t;
    t.a=a;
    t.b=b;
    s[tails++]=t;
    tails%=99999;
    qDebug()<<tails<<"cmp";
}

void MainWindow::ani_start()//开始动画
{
	if(isAniing)
		return;
    isAniStarted=true;
    qDebug()<<heads<<tails;
    qDebug()<<s[heads].x<<s[heads].y;
    qDebug()<<s[heads].a<<s[heads].b;
    if(heads!=tails)
    {
        if(s[heads].x!=-1)
		{
            swap(s[heads].x,s[heads].y);
			isAniing=true;
		}
        if(s[heads].a!=-1)
		{
            cmp(s[heads].a,s[heads].b);
			isAniing=true;
		}
        heads++;
		heads%=99999;
    }
    else
    {
        check();
        isAniStarted=false;
    }
}

void MainWindow::check()//开始排序成功动画
{
	checker->setInterval(150);
    connect(checker,&QTimer::timeout,this,&MainWindow::checkani);
    endch=0;
    checkcnt=0;
    checker->start();
}

void MainWindow::checkani()//排序成功动画
{

    chani[endch]=new QPropertyAnimation();
    chani[endch]->setTargetObject(item[endch]);
    chani[endch]->setEasingCurve(QEasingCurve::OutInQuad);
    chani[endch]->setPropertyName("pos");
    chani[endch]->setDuration(300);
    QPoint mida(item[endch]->pos().x(),item[endch]->pos().y()-(400-item[endch]->height()+50)/3);
    chani[endch]->setKeyValueAt(0,item[endch]->pos());
    chani[endch]->setKeyValueAt(0.5,mida);
    chani[endch]->setKeyValueAt(1,item[endch]->pos());
    chani[endch]->start();
    connect(chani[endch],&QPropertyAnimation::finished,this,&MainWindow::checkFinish);
    endch++;
    if(endch==size)
    {
		checker->stop();
    }
}


void MainWindow::checkFinish()//排序成功动画结束，释放内存
{
    delete chani[checkcnt++];
}

void MainWindow::cmp(int a,int b) //a与b的比较动画
{
	abani=0;
	qDebug()<<"cmp!"<<a<<b<<dur;
	aani=new QPropertyAnimation();			//构造动画对象
	aani->setTargetObject(item[a]);			//设置动画object
	aani->setEasingCurve(QEasingCurve::OutInQuad);//设置动画曲线
	aani->setPropertyName("pos");			//设置动画的property
	aani->setDuration(dur);					//设置动画时长
	QPoint mida(item[a]->pos().x(),item[a]->pos().y()-(400-item[a]->height()+50)/3);//算出动画中点
	aani->setKeyValueAt(0,item[a]->pos());	//设置三个关键帧
    aani->setKeyValueAt(0.5,mida);
	aani->setKeyValueAt(1,item[a]->pos());
	aani->start();							//动画开始，下同不再重复
    bani=new QPropertyAnimation();
    bani->setTargetObject(item[b]);
    bani->setEasingCurve(QEasingCurve::OutInQuad);
    bani->setPropertyName("pos");
    bani->setDuration(dur);
    QPoint midb(item[b]->pos().x(),item[b]->pos().y()-(400-item[b]->height()+50)/3);
    bani->setKeyValueAt(0,item[b]->pos());
    bani->setKeyValueAt(0.5,midb);
    bani->setKeyValueAt(1,item[b]->pos());
    bani->start();
    connect(aani,&QPropertyAnimation::finished,this,&MainWindow::cmpFinish);
    connect(bani,&QPropertyAnimation::finished,this,&MainWindow::cmpFinish);
    if(isMusicOn)
    {
		int ha=1.0*item[a]->height()/16+50;
		int hb=1.0*item[b]->height()/16+50;
		music->makeSound(ha);
		music->makeSound(hb);
    }
}

void MainWindow::swap(int x,int y)//x与y的交换动画
{
    qDebug()<<"swap!"<<x<<y;
    xx=x;
    yy=y;
    xani=new QPropertyAnimation();
    yani=new QPropertyAnimation();
    xani->setTargetObject(item[x]);
    yani->setTargetObject(item[y]);
    xani->setEasingCurve(QEasingCurve::InOutQuad);
    yani->setEasingCurve(QEasingCurve::InOutQuad);
    xani->setPropertyName("pos");
    yani->setPropertyName("pos");
	if(isMusicOn)
	{
		xani->setDuration(dur/2);
		yani->setDuration(dur/2);
	}
	else
	{
		xani->setDuration(dur);
		yani->setDuration(dur);
	}
    xani->setStartValue(item[x]->pos());
    yani->setStartValue(item[y]->pos());
    QPoint endx(item[y]->pos().x(),item[x]->pos().y());
    QPoint endy(item[x]->pos().x(),item[y]->pos().y());
    xani->setEndValue(endx);
    yani->setEndValue(endy);
    xani->start();
    yani->start();
    connect(yani,&QPropertyAnimation::finished,this,&MainWindow::swapFinish);
//    if(isMusicOn)
//    {
//        int ha=1.0*item[y]->height()/16+50;
//        int hb=1.0*item[x]->height()/16+50;
//        music->makeSound(ha);
//        music->makeSound(hb);
//    }
}

void MainWindow::swapFinish()
{
    QLabel *temp;
    temp=item[xx];
    item[xx]=item[yy];
    item[yy]=temp;
	isAniing=false;
    ani_start();
}

void MainWindow::cmpFinish()
{
    abani++;
    if(abani==2)
    {
		disconnect(aani,&QPropertyAnimation::finished,this,&MainWindow::cmpFinish);
		disconnect(bani,&QPropertyAnimation::finished,this,&MainWindow::cmpFinish);
        abani=0;
		isAniing=false;
        ani_start();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::suiji(int  max)
{
    int min=1;
    int  num=max-min+1;  //要随机数的个数
    int  index;         //随机下标
    int aa[100];
    for(int  i=0;i<num;i++)        //准备要被随机的数
        aa[i]=i+min;
    srand((int)time(0));            //随机种子
    for(int  i=0;i<num;i++)
    {
        index=(int)((float)(num-i)*rand()/(RAND_MAX+1.0));          //产生随机下标
        a[i]=aa[index];                    //把不重复的随机数下标保存到数组中
        aa[index]=aa[num-1-i];        //用随机范围内的最后一个随机下标对应的值,去替换己用过的值.这样就不重复了.（即把上面用过的a[index]丢掉。）
    };
}
