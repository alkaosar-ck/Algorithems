
typedef unsigned long long ull;
typedef long long ll;
ull modmul(ull a, ull b, ull m)
{
    ll ret = a * b - m * ull(1.L / m * a * b);
    return ret + m * (ret < 0) - m * (ret >= (ll)m);
}

ull modpow(ull b, ull e, ull mod)
{
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1)
            ans = modmul(ans, b, mod);
    return ans;
}

bool is_Prime(ull n)
{
    if (n < 2 || n % 6 % 4 != 1)
        return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;

    for (ull a : A)
    {
        ull p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n - 1 && i != s)
            return 0;
    }
    return 1;
}

ull pollard(ull n)
{
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    auto f = [&](ull x)
    {
        return modmul(x, x, n) + i;
    };

    while (t++ % 40 || __gcd(prd, n) == 1)
    {
        if (x == y)
            x = ++i, y = f(x);
        if ((q = modmul(prd, max(x, y) - min(x, y), n)))
            prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

vector<ull> factor(ull n)
{
    if (n == 1)
        return {};
    if (is_Prime(n))
        return {n};
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}