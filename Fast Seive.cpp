#define rep(i, a, b) for (int i = a; i < b; i++)
typedef pair<int, int> pii;
typedef vector<int> vi;

const int Lim = 2e5;
bitset<Lim> isPrime;

vi eratosthenes()
{
    const int S = (int)round(sqrt(Lim)), R = Lim / 2;
    vi pr = {2}, sieve(S + 1);
    pr.reserve(int(Lim / log(Lim) * 1.1));
    vector<pii> cp;

    for (int i = 3; i <= S; i += 2)
        if (!sieve[i])
        {
            cp.push_back({i, i * i / 2});
            for (int j = i * i; j <= S; j += 2 * i)
                sieve[j] = 1;
        }

    for (int L = 1; L <= R; L += S)
    {
        array<bool, S> block{};
        for (auto &[p, idx] : cp)
            for (int i = idx; i < S + L; idx = (i += p))
                block[i - L] = 1;

        rep(i, 0, min(S, R - L)) if (!block[i]) pr.push_back((L + i) * 2 + 1);
    }

    for (int i : pr)
        isPrime[i] = 1;
    return pr;
}
