#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
const int MAXN=1e6+10;
int a[MAXN];
int abs(int x) {return x>0?x:-x;}
struct xxx
{
	int lch[MAXN],rch[MAXN],rt[MAXN],sz[MAXN],l[MAXN],r[MAXN],dis[MAXN],val[MAXN];
	int tot,now;
	int newnode(int x)
	{
		val[++tot]=x;
		lch[tot]=rch[tot]=dis[tot]=0;
		sz[tot]=1;
		return tot;
	}
	int newheap(int pos,int x)
	{
		rt[++now]=newnode(x);
		l[now]=r[now]=pos;
	}
	int _merge(int x,int y)
	{
		if (!x||!y) return x+y;
		if (val[x]<val[y]) swap(x,y);
		rch[x]=_merge(rch[x],y);
		sz[x]=sz[lch[x]]+sz[rch[x]]+1;
		if (dis[lch[x]]<dis[rch[x]]) swap(lch[x],rch[x]);
		dis[x]=dis[rch[x]]+1;
		return x;
	}
	int merge_last() 
	{
		--now;
		rt[now]=_merge(rt[now],rt[now+1]);
		r[now]=r[now+1];
		while (sz[rt[now]]*2>r[now]-l[now]+2)
			del(rt[now]);
	}
	int del(int &x)
	{
		--sz[x];
		x=_merge(lch[x],rch[x]);
	}
	int get_top(int x)
	{
		return val[rt[x]];
	}
	ll calc(int x)
	{
		ll ret=0;
		int top=get_top(x);
		for (int i=l[x];i<=r[x];++i)
			ret+=abs(top-val[i]);
		return ret;
	}
	int check()
	{
		return val[rt[now-1]]<val[rt[now]];
	}
}heap;
int n,m;

int main()
{
	freopen("a.in","r",stdin);

	scanf("%d",&n);
	for (int i=1;i<=n;++i) 
	{
		scanf("%d",a+i);
		heap.newheap(i,a[i]-i);
		while (!heap.check()&&heap.now>1)
			heap.merge_last();
	}
	ll ans=0;
	for (int i=1;i<=heap.now;++i)
		ans+=heap.calc(i);
	printf("%lld\n",ans);
}

//˼·����ʮ�ּ򵥴ֱ���
//���ȿ�������ǲ��½��ļ������
//���˵����a�ǲ��½��ģ����Ž����ȡ���Լ�
//���a�ǲ������ģ����Ž������λ�����š��������������֤��������
//��ô���ھ���һ��̰�ĵ��뷨
//��ԭ���зֳ����ɸ�С�Ĳ��������� 
//��ô��õ��������ÿ������ȡ��λ��
//Ȼ������ֺ������λ����ǰ���С
//��ô���ʱ��ͽ���������ϲ�ȡ��λ����ʹ�ø�����Ľ�����
//Ȼ���������ϸ������Ļ���������С���ɣ�ȫ��ֵ-i�ͺ� 

//����������λ����֤��
//��һ���ܼ򵥵��뷨
//���ȡ�Ĳ�����λ��w�������������Ϊw+k
//��ô��С����λ������Щ���Ĺ��׻�+k��������λ����ÿ�����Ĺ��׻�-k
//�������λ����n/2������С�ڵĸ�����>=���ڵĸ�����
//���Բ�����ţ�������λ������������ 
