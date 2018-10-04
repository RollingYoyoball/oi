#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 100005;

char s[N]; int nS;
int tot, last; int suf[N], son[N][30]; int len[N];

int Find(int n, int cur) {
    while (s[n-len[cur]-1] != s[n])
        cur = suf[cur];
    return cur;
}
void Expand(int n, int c) {
    int cur = Find(n, last);
    if (!son[cur][c]) {
        int now = ++tot;
        len[now] = len[cur]+2;
        suf[now] = son[Find(n, suf[cur])][c];
        son[cur][c] = now;
    }
    last = son[cur][c];
}

int main(void) {
    #ifndef ONLINE_JUDGE
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
    #endif

    scanf("%s", s+1); nS = strlen(s+1);

	int pre=0;
    tot = 1, last = 0; suf[0] = 1; len[0] = 0, len[1] = -1;
    for (int i = 1; i <= nS; i++)
        pre=tot,Expand(i, s[i]-'a');
   // printf("%d\n", tot-1);

    return 0;
}
