#ifndef SORTS_H
#define SORTS_H
// Sorts.h
#include <iostream>
#include<mainwindow.h>
#include<QDebug>
using namespace std;

double gettime(int restart=0);

template <typename T> void ReSet(T *data, const T *data0, int n)	// 用于恢复"原始数据"，以保证不同的排序算法处理完全相同的数据
{
    for(int i=0; i<n; i++)
        data[i] = data0[i];
}

template <typename T> bool Check(const T *a, int size)				// 仅检验数组元素是否满足升序（并未进行严格的正确性检查）
{
    for(int i=1; i<size; i++)
        if(a[i-1] > a[i])
            return false;
    return true;
}

// 三种基本的（没有优化的）排序算法
template <typename T> void Bubble(T *a, int size, MainWindow *w)	// 冒泡排序
{
    T temp;											// 定义一个局部变量，数据类型与形式数据类型相同
    int i, j;
    bool flag=true;
    for(i=0; i<size&&flag; i++)							// 共进行 size-1 轮比较和交换
    {
        flag=false;
        for(j=size-1; j>i; j--)
        {
            w->rec_cmp(j-1,j);
            if(a[j-1] > a[j])						// 相邻元素之间比较，必要时
            {
                temp = a[j-1];						// 交换 a[j] 与 a[j+1]
                a[j-1] = a[j];
                a[j] = temp;
                qDebug()<<j;
                w->rec_swap(j-1,j);
                flag=true;
            }
        }
    }
}

template <typename T> void Select(T *a, int size, MainWindow *w)	// 选择排序
{
    T temp;
    int i, j, k=0;
    for(i=1; i<size; i++)							// 循环size-1次
    {
        for(j=i; j<size; j++)
        {
            w->rec_cmp(j,k);
            if(a[j] < a[k])
            {
                k = j;                              // 找出当前范围内"最小"元素的下标
            }
        }
        if(k!=i-1)									// 若"最小"元素不是a[i-1]，则交换之
        {
            w->rec_swap(i-1,k);
            temp = a[k];
            a[k] = a[i-1];
            a[i-1] = temp;
        }
        k = i;
    }
}



template<typename T>
void quickSort(T *s, int l, int r, MainWindow *w)
{
    if (l< r)
    {
        int i = l, j = r,  m;
        T x;
        if ((r - l) >= 2)
        {
            if ((r - l) % 2 == 1)
            {
                m = (r - l - 1) / 2 + l;
            }
            else
            {
                m = (r - l) / 2 + l;
            }
            w->rec_cmp(m,l);
            if(s[m] > s[l])
            {
                w->rec_cmp(l,r);
                if(s[l] > s[r])
                {
                    x = s[l];
                }
                else
                {
                    w->rec_cmp(m,r);
                    if(s[m] > s[r])
                    {
                        x = s[r];
                        w->rec_swap(r,l);
                        swap(s[r], s[l]);
                    }
                    else
                    {
                        x = s[m];
                        w->rec_swap(m,l);
                        swap(s[m], s[l]);
                    }
                }
            }
            else
            {
                w->rec_cmp(m,r);
                if(s[m] > s[r])
                {
                    x = s[m];
                    w->rec_swap(m,l);
                    swap(s[m], s[l]);
                }
                else
                {
                    w->rec_cmp(l,r);
                    if(s[l] > s[r])
                    {
                        x = s[r];
                        w->rec_swap(r,l);
                        swap(s[r], s[l]);
                    }
                    else
                    {
                        x = s[l];
                    }
                }
            }
        }
        else
        {
            x = s[l];
        }
        while (i < j)
        {

            while(i < j && s[j]>= x) //从右向左找第一个小于x的数
            {
                j--;
            }
            if(i < j)
            {
                s[i++] = s[j];
            }
            while(i < j && s[i]< x) //从左向右找第一个大于等于x的数
            {
                i++;
            }
            if(i < j)
            {
                s[j--] = s[i];
            }
       }
    s[i] = x;
    quickSort(s, l, i - 1); //递归调用
    quickSort(s, i + 1, r);
    }
}


void quick_sort(int *num,int l,int r, MainWindow *w)
{
    //如果小于等于1个数据元素·直接返回结束快排函数 r为数组元素总个数
    if(l+1>=r){
        return ;
    }
    int first=l,last=r-1,key=num[first];
    while(first<last){
        while(first<last&&num[last]>=key){
            --last;
        }
        //如果值小于 key分界值 交换
        num[first]=num[last];
        while(first<last&&num[first]<key){
            ++first;
        }
        //如果值大于key分界值 交换
        num[last]=num[first];
    }
    num[first]=key;
    //递归左右部分进行快排
    quick_sort(num,l,first,w);
    quick_sort(num,first+1,r,w);
}


template <typename T> void Qsort(T *a, int size, MainWindow *w)	// 快速排序
{
    quickSort(a,0,size-1,w);

//	T pivot, temp;
//	int left=0, right=size-1;						// 下标（整数）
//
//	if(size<=1) return;
//
//	pivot = a[right];								// 选择最后一个值为分界值
//	do
//	{
//		while(left<right && a[left]<=pivot) left++;	// 此处 "<=" 是让与分界值相等的元素暂时留在原地
//		while(left<right && a[right]>=pivot)right--;// 此处 ">=" 是让与分界值相等的元素暂时留在原地
//		if(left < right)
//		{
//			temp=a[left]; a[left]=a[right]; a[right]=temp;
//		}
//	}while(left < right);
//	a[size-1] = a[left]; a[left] = pivot;			// 找到分界点 left
//	Qsort(a, left);									// 递归调用(左侧部分)
//	Qsort(a+left+1, size-left-1);					// 递归调用(右侧部分)
}

template <typename T>void Insert(T *a, int size, MainWindow *w) {
    for (int i = 1; i < size; ++i)
    {
        for(int j=i;j>0;j--)
        {
            w->rec_cmp(j-1,j);
            if(a[j-1]>a[j])
            {
                w->rec_swap(j-1,j);
                swap(a[j-1],a[j]);
            }
            else
                break;
        }
    }
}



template<typename T>
void max_heapify(T *tree, int start, int end, MainWindow *w) {
    //堆处理函数
    int parent = start;         //父节点
    int child = parent * 2 + 1; //子节点
    qDebug()<<parent<<child;
    while (child <= end) {
        if (child + 1 <= end )
        {
            w->rec_cmp(child,child+1);
            if(tree[child] < tree[child + 1])
                child++;
        }
        //当子节点不越界的情况下，比较两子节点，并取大的子节点

        w->rec_cmp(parent,child);
        if (tree[parent] > tree[child])
        {
            return;
        }
        //当父节点大于子节点时，改堆调整已完成，直接return

        else {
            w->rec_swap(parent,child);
            swap(tree[parent], tree[child]);
            parent = child;
            child = parent * 2 + 1;
        }
        //否则，调整该堆
    }
}

template<typename T>
void heap_sort(T *tree, int size,MainWindow *w) {
    for (int i = size / 2 - 1; i >= 0; i--)
        max_heapify(tree, i, size - 1,w);
    //构建堆
    for (int i = size - 1; i > 0; i--) {
        w->rec_swap(0,i);
        swap(tree[0], tree[i]);
        max_heapify(tree, 0, i - 1,w);
    }
    //堆排序
}

template<typename T>
void merge_Sort(T *a,int l,int r,MainWindow *w)
{
    qDebug()<<l<<r;
    if(l==r)
        return;
    int mid=(l+r)/2;
    merge_Sort(a,l,mid,w);
    merge_Sort(a,mid+1,r,w);
    int i=l,j=mid+1;
    T *temp=new T[r-l+2];
    int endd=0;
    while(i<=mid||j<=r)
    {
        if(a[i]<=a[j])
        {
            temp[endd++]=a[i++];
        }
        else
        {
            temp[endd++]=a[j++];
        }
    }
    for(;i<=mid;i++)
    {
        temp[endd++]=a[i];
    }
    for(;j<=r;j++)
    {
        temp[endd++]=a[j];
    }
    for(int k=0;k<r-l+1;k++)
    {
        a[k+l]=temp[k];
    }
    delete[] temp;
}
template<typename T>
void merge_sort(T *a,int size,MainWindow *w)
{
    merge_Sort(a,0,size-1,w);
}
template<typename T>
void merge_sort1(T *a,int size)
{
    if(size<=1)
    {
        return;
    }
    int mid=size/2;							//找到中间点
    merge_sort(a,mid);						//排序前半段
    merge_sort(a+mid,size-mid);				//排序后半段
    T *temp=new T[size+1];
    int endd=0;
    int l=0,r=mid;
    while(l<mid&&r<size)					//两段有序数组合并
    {
        if(a[l]<=a[r])
            temp[endd++]=a[l++];
        else
            temp[endd++]=a[r++];
    }
    while(l<mid) temp[endd++]=a[l++];
    while(r<size) temp[endd++]=a[r++];
    for(int i=0;i<size;i++)					//合并完成后放回原数组
    {
        a[i]=temp[i];
    }
    delete[] temp;							//清理内存
}

#endif // SORTS_H
