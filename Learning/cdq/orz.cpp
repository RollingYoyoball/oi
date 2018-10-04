#include <cstdio>
#include <cstring>
#include <algorithm>
#define lowbit(x) (x&-x)

using namespace std;

int sumv[200005];

void add(int x,int num) {
	for(;x<=200005;x+=lowbit(x)) sumv[x]+=num;
}

int sum(int x) {
	int s=0;
	for(;x;x-=lowbit(x)) s+=sumv[x];
	return s;
}

struct Data {
	int x,y,z,id;
	Data() {}
	Data(int a,int b,int c,int d):x(a),y(b),z(c),id(d) {}
	bool operator < (const Data & b) const {
		if (x!=b.x) return x<b.x;
		if (y!=b.y) return y<b.y;
		if (z!=b.z) return z<b.z;
		return id<b.id;
	}
};

Data a[100005],b[100005];
int f[100005];

void solve(int l,int r) {
	if (l==r) return;
	int m=((l+r)>>1);
	solve(l,m);
	solve(m+1,r);
	int lx=l,tot=l;
	for(int i=m+1;i<=r;i++) {
		while (lx<=m&&a[lx].y<=a[i].y) {
			b[tot++]=a[lx];
			add(a[lx].z,1);
			lx++;
		}
		b[tot++]=a[i];
		f[a[i].id]+=sum(a[i].z);
	}
	for(int i=l;i<lx;i++) add(a[i].z,-1);
	for(int i=lx;i<=m;i++) b[tot++]=a[i];
	for(int i=l;i<=r;i++) a[i]=b[i];
}

int ans[200005];

int main() {
	freopen("a.in","r",stdin);
	
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) {
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[i]=Data(x,y,z,i);
	}
	sort(a+1,a+n+1);
	solve(1,n);
	sort(a+1,a+n+1);
	for(int i=n-1;i>0;i--)
		if (a[i+1].x==a[i].x&&a[i+1].y==a[i].y&&a[i+1].z==a[i].z) f[a[i].id]=f[a[i+1].id];
	for(int i=1;i<=n;i++) ans[f[i]]++;
	for(int i=0;i<n;i++) printf("%d\n",ans[i]);
	return 0;
}
