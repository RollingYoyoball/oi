#include <cstdio>
#include <cstring>
#include <cstdlib>

#define F(i, a, b) for (register int i = (a); i <= (b); i++)
#define D(i, a, b) for (register int i = (a); i >= (b); i--)

const int N = 200;

char s[N]; int n;
int tot, last; int son[N][26], suf[N], len[N];
char t[N]; int cnt;

inline int Newnode(int L) { return len[++tot] = L, tot; }
void Expand(int c) {
    int p = last, np = Newnode(len[last]+1);
    for (; p > 0 && !son[p][c]; p = suf[p])
        son[p][c] = np;
    if (p == 0) suf[np] = 1;
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

void DFS(int x) {
    printf("%s\n", t+1);
    for (int i = 0; i < 26; i++) if (son[x][i] > 0) {
        t[++cnt] = 'A'+i;
        DFS(son[x][i]);
        t[cnt--] = 0;
    }
}

int main(void) {
    #ifndef ONLINE_JUDGE
        freopen("a.in", "r", stdin);
      //  freopen("sam.out", "w", stdout);
    #endif

    scanf("%s", s+1);
    n = strlen(s+1);

    tot = last = 1;
    F(i, 1, n)
        Expand(s[i]-'A');

    printf("The substrings of S in alphabetical order are: \n");
    DFS(1);

    return 0;
}
