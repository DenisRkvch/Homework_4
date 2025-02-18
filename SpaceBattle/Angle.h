#ifndef ANGLE_H
#define ANGLE_H

class Angle
{
public:
	Angle(int dir, int num);
	~Angle();

	void add(const Angle &ang);
	void add(int dir);
	bool isEqual(const Angle &ang) const;

	double radians(void) const;
	double degrees(void) const;

	static Angle* plus(const Angle &ang1, const Angle &ang2);
	static Angle* plus(const Angle &ang1, int dir);
	static bool isEqual(const Angle &ang1, const Angle &ang2);

	bool operator==(const Angle &other) const;

	const double PI = 3.141592653589793;

private:
	int d, n;
	
};
#endif


