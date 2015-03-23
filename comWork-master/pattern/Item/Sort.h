#include <iostream>
#include <vector>
#include <string>

using namespace std;

class test
{
public:
	test()
	{
		std::cout<<"test构造"<<endl;
	}
	test(const test& obj)
	{
		std::cout<<"test复制构造"<<endl;
	}
	test& operator=(const test& obj)
	{
		std::cout<<"test复制"<<endl;
		return *this;
	}
};
//字符串
class MyClass
{

public:
	MyClass()
	{
		std::cout<<"MyClass"<<endl;
	}
	MyClass(const MyClass& obj) //:test(obj.test)
	{
		std::cout<<"MyClass复制构造"<<endl;
		test=obj.test;
	}
	test test;
};
class DClass:public MyClass
{
public:
	DClass(){std::cout<<"DClass"<<endl;}
	~DClass(){std::cout<<"~DClass"<<endl;};
};
class Base
{
public:
	Base(){
		std::cout<<"Base"<<endl;
	}
};
void PrintArray(int* a,int N)
{
	for(int i=0;i<N;++i)
	{
		std::cout<<a[i]<<" ";
	}
	std::cout<<endl;
}
void mswap(int* a,int* b)
{
	int t=*a;
	*a=*b;
	*b=t;
}
void BulleSort(int* a,int N)
{
	for(int i=0;i<N-1;++i)
	{
		for(int j=0;j<N-1-i;++j)
		{
			if(a[j]>a[j+1])
			{
				mswap(&a[j],&a[j+1]);
			}
		}
	}
}
void InsertSort(int* a,int N)
{
	for(int i=0;i<N;++i)
	{
		for(int j=i;j<N;++j)
		{
			int key=a[j];
			int m=j-1;
			while(m>0&&a[m]>key)
			{
				a[m]=a[m-1];
				m--;
			}
			a[m]=key;
		}
	}
}
void BinaryInsertSort(int* a,int N)
{
	for(int i=0;i<N;++i)
	{
		for(int j=i;j<N;++j)
		{
			int m=0;
			int n=j-1;
			while(m<=n)
			{
				int mm=(m+n)/2;
				if(a[mm]>a[j])
					n=mm-1;
				else
					m=mm+1;
			}
			int key=a[j];
			for(int p=j;p>m;--p)
				a[p]=a[p-1];
			a[m]=key;
		}
	}
}
int BinarySearch(int* a,int N,int key) 
{
	int i=-1;
	int m=0;
	int n=N-1;
	while(m<=n)
	{
		int middle=(m+n)/2;
		if(key==a[middle])
			return middle;
		else if(key>a[middle])
			m=middle+1;
		else
			n=middle-1;
	}
	return i;
}
void SelectSort(int* a,int N)
{
	for(int i=0;i<N-1;++i)
	{
		for(int j=i+1;j<N;++j)
		{
			if(a[j]>a[i])
				mswap(&a[j],&a[i]);
		}
	}
}
void MergeSort(int* a,int* t,int m,int n,int p,int q)
{
	int i=m;
	int j=p;
	int k=m;
	while(i<=n&&j<=q)
	{
		if(a[i]<=a[j])
		{
			t[k++]=a[i++];
		}
		else
		{
			t[k++]=a[j++];
		}
	}
	while(i<=n)
		t[k++]=a[i++];
	while(j<=q)
		t[k++]=a[j++];
	for(int i=m;i<=q;++i)
		a[i]=t[i];
}
void MergeSort(int* a,int* t,int m,int n)
{
	if(m<n)
	{
		int middle=(m+n)/2;
		MergeSort(a,t,m,middle);
		MergeSort(a,t,middle+1,n);
		MergeSort(a,t,m,middle,middle+1,n);
	}
}
void MergeSort(int* a,int N)
{
	int* t=new int[N];
	MergeSort(a,t,0,N-1);
	delete[]t;
}
void NMergeSort(int* a,int N) //非递归版本
{
	int* t=new int[N];
	int i=1;
	while(i<N)// 
	{
		int m=0,n=m+i-1;
		int p=n+1,q=p+i-1;
		if(q>=N)
			q=N-1;
		while(m<N)
		{
			MergeSort(a,t,m,n,p,q);
			m=q+1;			
			n=m+i-1;			
			p=n+1;
			q=p+i-1;
			if(n>=N||p>=N)
				break; //不够一个步长
			if(q>=N)
				q=N-1; //够一个步长
		}
		i=2*i;
	}
}
void Adjust(int* a,int k,int N) 
{
	int l=2*k+1;
	if(l>=N) 
		return;
	int r=2*k+2;
	if(r<N)
	{
		if(a[l]>a[r])
		{
			if(a[l]>a[k])
			{
				mswap(&a[l],&a[k]);
				Adjust(a,l,N);
			}
		}
		else 
		{
			if(a[r]>a[k])
			{
				mswap(&a[r],&a[k]);
				Adjust(a,r,N);
			}
		}
	}
	else
	{
		if(a[l]>a[k])
		{
			mswap(&a[l],&a[k]);
			Adjust(a,l,N);
		}
	}

}
void MakeHeap(int* a,int N)
{
	for(int i=N/2-1;i>=0;--i)
		Adjust(a,i,N);
}
void HeapSort(int* a,int N)
{
	MakeHeap(a,N);
	int M=N;
	for(int i=0;i<M-1;++i)
	{
		mswap(&a[N-1],&a[0]);
		N=N-1;
		Adjust(a,0,N);
	}
	/*
	int a[]={1,3,7,6,4,5,6,2,4,6};
	size_t N=sizeof(a)/sizeof(int);
	HeapSort(a,N);
	PrintArray(a,N);
	*/
}

//数组 查询 任意数 和 为 http://blog.csdn.net/v_july_v/article/details/6419466
//计数排序
//基数排序
//Hash排序
//捅排序
//二叉查找树
//AVL树
//红黑树
//树状数组
//Treap
//伸展树
//Fibonacci
//关联数组
//eventloop
//深度探索 数组
//http://blog.csdn.net/defonds/article/details/6260604
//树的节点排序？？？
/*
有一个单向循环链表队列，从头开始报数，当报到m或者m的倍数的元素出列，根据出列的先后顺序重新组成单向循环链表。
函数原型： void reorder(Node **head , int m)
*/
//内存对齐 http://blog.chinaunix.net/uid-10995602-id-2918694.html