#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
#define F(i, a, b) for (register int i = (a); i <= (b); i++)
#define D(i, a, b) for (register int i = (a); i >= (b); i--)
 
const int N = 5000;
 
char A[N]; int nA;
char B[N]; int nB;
 
namespace SAM {
    int tot, last, son[N][30], suf[N], len[N];
    inline int Newnode(int L) { return len[++tot] = L, tot; }
    void Expand(int c) {
        int np = Newnode(len[last]+1), p = last;
        for (; p > 0 && !son[p][c]; p = suf[p])
            son[p][c] = np;
        if (!p) suf[np] = 1;
        else {
            int q = son[p][c];
            if (len[p]+1 == len[q]) suf[np] = q;
            else {
                int nq = Newnode(len[p]+1);
                memcpy(son[nq], son[q], sizeof son[q]);
                suf[nq] = suf[q], suf[q] = suf[np] = nq;
                for (; p > 0 && son[p][c] == q; p = suf[p])
                    son[p][c] = nq;
            }
        }
        last = np;
    }
    void Init(void) {
        tot = last = 1;
        F(i, 1, nB)
            Expand(B[i] - 'a');
    }
}
 
namespace LAM {
    int son[N][30];
    void Init(void) {
        D(i, nB, 1) {
            memcpy(son[i], son[i+1], sizeof son[i+1]);
            son[i][B[i] - 'a'] = i+1;
        }
    }
}
 
inline void gmin(int &x,int y) { x = min(x, y); }
void Work1(void) {
    using namespace SAM;
    int res = nA+1;
    F(L, 1, nA) {
        int R = L-1, x = 1;
        while (R+1 <= nA && son[x][A[R+1] - 'a'] > 0)
            x = son[x][A[++R] - 'a'];
        if (R != nA) gmin(res, (R+1)-L+1);
    }
    printf("%d\n", res == nA+1 ? -1 : res);
}
void Work2(void) {
    using namespace LAM;
    int res = nA+1;
    F(L, 1, nA) {
        int R = L-1, x = 1;
        while (R+1 <= nA && son[x][A[R+1] - 'a'] > 0)
            x = son[x][A[++R] - 'a'];
        if (R != nA) gmin(res, (R+1)-L+1);
    }
    printf("%d\n", res == nA+1 ? -1 : res);
}
void Work3(void) {
    using namespace SAM;
    static int f[N]; F(i, 0, tot) f[i] = nA+1; f[1] = 0;
    F(i, 1, nA)
        D(j, tot, 1)
            gmin(f[son[j][A[i] - 'a']], f[j]+1);
    printf("%d\n", f[0] == nA+1 ? -1 : f[0]);
}
void Work4(void) {
    using namespace LAM;
    static int f[N]; F(i, 0, nB+1) f[i] = nA+1; f[1] = 0;
    F(i, 1, nA)
        D(j, nB+1, 1)
            gmin(f[son[j][A[i] - 'a']], f[j]+1);
    printf("%d\n", f[0] == nA+1 ? -1 : f[0]);
}
 
int main(void) {
    #ifndef ONLINE_JUDGE
        freopen("a.in", "r", stdin);
       // freopen("a.out", "w", stdout);
    #endif
 
    scanf("%s", A+1); nA = strlen(A+1);
    scanf("%s", B+1); nB = strlen(B+1);
 
    SAM::Init();
    LAM::Init();
 
    Work1();
    Work2();
    Work3();
    Work4();
 
    return 0;
}
