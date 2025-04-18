typedef long long ll;
ll euclid(ll a, ll b, ll &x, ll &y)
{
   if (!b)
      return x = 1, y = 0, a;
   ll d = euclid(b, a % b, y, x);
   return y -= a / b * x, d;
}
const ll mod = 17;
struct Mod
{
   ll x;
   Mod(ll xx) : x(xx) {}
   Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
   Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
   Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
   Mod operator/(Mod b) { return *this * invert(b); }
   Mod invert(Mod a)
   {
      ll x, y, g = euclid(a.x, mod, x, y);
      assert(g == 1);
      return Mod((x + mod) % mod);
   }
   Mod operator^(ll e)
   {
      if (!e)
         return Mod(1);
      Mod r = *this ^ (e / 2);
      r = r * r;
      return e & 1 ? *this * r : r;
   }
};
