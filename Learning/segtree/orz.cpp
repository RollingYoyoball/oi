#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <functional>
#include <queue>
#include <utility>
using namespace std;

#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define P(i,a,b) for (int i=(a);i>=(b);i--)

#define PID pair<int, pair<int,int> >

#define Make(a,b,c) make_pair(a,make_pair(b,c))
#define X first
#define Y second

#define tree1(x) (x)
#define tree2(x) ((x)+(1<<(d+1))-1)

const int INF=~0u>>2;

int T; int n,m,K;

int d; int ind;
struct Edge { int v,d,nx; inline Edge(int _v=0,int _d=0,int _nx=0):v(_v),d(_d),nx(_nx) {} }mp[1500000];
int tot,hd[300000];

int dis[15][300000];
priority_queue<PID,vector<PID>, greater<PID> > q;

inline int rd(void) {
    int x=0,f=1; char c; for (c=getchar();!isdigit(c);c=getchar()) if (c=='-') f=-1;
    for (;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
}

inline void Ins(int u,int v,int w) { mp[++tot]=Edge(v,w,hd[u]); hd[u]=tot; }
void Link(int l,int r,int sign,int w=0) {
    for (l--,r++,l+=(1<<d),r+=(1<<d);l^r^1;l>>=1,r>>=1) {
        if (!(l&1)) sign==+1?Ins(tree1(l^1),ind,w):Ins(ind,tree2(l^1),0);
        if (r&1) sign==+1?Ins(tree1(r^1),ind,w):Ins(ind,tree2(r^1),0);
    }
}

int Solve(int fs,int ft) {
    F(i,0,K) F(j,1,ind) dis[i][j]=INF; F(i,0,K) q.push(Make(0,i,fs));
    while (!q.empty() && dis[K][ft]==INF) {
        PID now=q.top(); q.pop();
        if (dis[now.Y.X][now.Y.Y]!=INF) continue;
        dis[now.Y.X][now.Y.Y]=now.X;
        for (int k=hd[now.Y.Y];k>0;k=mp[k].nx) {
            if (dis[now.Y.X][mp[k].v]==INF)
                q.push(Make(now.X+mp[k].d,now.Y.X,mp[k].v));
            if (now.Y.X+1<=K && dis[now.Y.X+1][mp[k].v]==INF)
                q.push(Make(now.X,now.Y.X+1,mp[k].v));
        }
    }
    return dis[K][ft];
}

int main(void) {
    #ifndef ONLINE_JUDGE
        freopen("a.in","r",stdin);
        freopen("a1.out","w",stdout);
    #endif

    T=rd();
    F(t,1,T) {
        n=rd(),m=rd(),K=rd(); for (d=0;(1<<d)-1<n+1;d++); ind=2*((1<<(d+1))-1);
        F(i,1,(1<<d)-1) {
            Ins(tree1(i<<1),tree1(i),0);
            Ins(tree1(i<<1|1),tree1(i),0);
            Ins(tree2(i),tree2(i<<1),0);
            Ins(tree2(i),tree2(i<<1|1),0);
        }
        F(i,1,(1<<(d+1))-1)
            Ins(tree2(i),tree1(i),0);
        F(i,1,m) {
            int x=rd(),y=rd(),l=rd(),r=rd(),w=rd();

            ind++;
            Link(x,y,+1,w);
            Link(l,r,-1);

            ind++;
            Link(l,r,+1,w);
            Link(x,y,-1);
        }
    }

    int ans=Solve(tree1(1+(1<<d)),tree2(n+(1<<d)));
    if (ans==INF) printf("Yww is our red sun!\n"); else printf("%d\n",ans);

    return 0;
}
