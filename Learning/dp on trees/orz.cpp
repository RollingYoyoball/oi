#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
  
namespace output
{
    const int BufferSize = 800005;
  
    char buffer[BufferSize];
    char *out_tail = buffer;
  
    inline void putint(int x)
    {
        if (x == 0)
            *out_tail++ = '0';
        else
        {
            char s[11], *t = s;
            while (x > 0)
                *t++ = x % 10 + '0', x /= 10;
            while (t-- != s)
                *out_tail++ = *t;
        }
        *out_tail++ = ' ';
    }
  
    inline void flush()
    {
        fwrite(buffer, 1, out_tail - buffer, stdout);
        out_tail = buffer;
    }
}
using output::putint;
  
namespace input
{
    const int BufferSize = 1 << 16 | 1;
  
    char buffer[BufferSize];
    char *head = buffer + BufferSize;
    const char *tail = head;
  
    inline char nextChar()
    {
        if (head == tail)
        {
            fread(buffer, 1, BufferSize, stdin);
            head = buffer;
        }
        return *head++;
    }
  
    inline int getint()
    {
        static char c;
        while ((c = nextChar()) < '0' || c > '9');
  
        int res = c - '0';
        while ((c = nextChar()) >= '0' && c <= '9')
            res = res * 10 + c - '0';
        return res;
    }
}
using input::getint;
  
const int MaxN = 100005;
const int MaxM = 100005;
const int INF = 0x3f3f3f3f;
  
int n, m;
int cap[MaxN], pos[MaxN];
int dep[MaxN];
  
inline int get_lca(int u, int v)
{
    while (u != v)
        (u > v ? u : v) >>= 1;
    return u;
}
  
int cost[MaxN];
  
struct item
{
    int l, v;
    item() {}
    item(const int &_l, const int &_v)
        : l(_l), v(_v) {}
  
    inline void update(item r, int delta)
    {
        r.l += delta;
        if (r.l < l)
            l = r.l, v = r.v;
    }
};
item f[MaxN];
  
inline void update(const int &x)
{
    if (cap[x] > 0)
        f[x] = item(0, x);
    else
        f[x] = item(INF, 0);
  
    int lc = x << 1, rc = lc | 1;
    if (lc <= n)
        f[x].update(f[lc], cost[lc] < 0 ? -1 : 1);
    if (rc <= n)
        f[x].update(f[rc], cost[rc] < 0 ? -1 : 1);
}
  
inline item query(int u)
{
    int now = 0;
    item res(INF, 0);
    while (u > 0)
    {
        res.update(f[u], now);
        now += cost[u] > 0 ? -1 : 1;
        u >>= 1;
    }
    return res;
}
  
inline void path_add(int u, int v, int d)
{
    while (u != v)
    {
        cost[u] += d;
        update(u);
        u >>= 1;
    }
}
  
int main()
{
    n = getint(), m = getint();
    for (int u = 1; u <= n; ++u)
        cap[u] = getint(), dep[u] = dep[u >> 1] + 1;
    for (int i = 1; i <= m; ++i)
        pos[i] = getint();
  
    for (int u = n; u >= 1; --u)
        update(u);
  
    int res = 0;
    for (int i = 1; i <= m; ++i)
    {
        item k = query(pos[i]);
        res += k.l, --cap[k.v];
  
        int u = pos[i], v = k.v;
        int lca = get_lca(u, v);
        path_add(u, lca, -1);
        path_add(v, lca, 1);
        while (v > 0)
            update(v), v >>= 1;
  
        putint(res);
    }
  
    output::flush();
    return 0;
}
