struct Angle
{
	int x, y;
	int t;
	Angle(int x, int y, int t = 0) : x(x), y(y), t(t) {}
	Angle operator-(Angle b) const { return {x - b.x, y - b.y, t}; }
	int half() const
	{
		assert(x || y);
		return y < 0 || (y == 0 && x < 0);
	}
	Angle t90() const { return {-y, x, t + (half() && x >= 0)}; }
	Angle t180() const { return {-x, -y, t + half()}; }
	Angle t360() const { return {x, y, t + 1}; }
};
bool operator<(Angle a, Angle b)
{
	// adda.dist2() and b.dist2() to also compare distances
	return make_tuple(a.t, a.half(), a.y * (ll)b.x) <
			 make_tuple(b.t, b.half(), a.x * (ll)b.y);
}
// Given two points, this calculates the smallest angle between
//  them, i.e., the angle that covers the defined line segment.
pair<Angle, Angle> segmentAngles(Anglea, Angleb)
{
	if (b < a)
		swap(a, b);
	return (b < a.t180() ? make_pair(a, b) : make_pair(b, a.t360()));
}
Angle operator+(Angle a, Angle b)
{ // point a+vector b
	Angle r(a.x + b.x, a.y + b.y, a.t);
	if (a.t180() < r)
		r.t--;
	return r.t180() < a ? r.t360() : r;
}
Angle angleDiff(Anglea, Angleb)
{ // angle b-	angle a
	int tu = b.t - a.t;
	a.t = b.t;
	return {a.x * b.x + a.y * b.y, a.x * b.y - a.y * b.x, tu - (b < a)};
}