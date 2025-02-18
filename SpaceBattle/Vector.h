#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector
{
public:
	Vector(int x, int y);
	Vector(int x, int y, int z);
	Vector(int _coords[], int len);
	Vector(const Vector& p);
	~Vector();

	void add(const Vector& vec);
	bool isEqual(const Vector &vec) const;

	//int getValue(int coord_ind) const;//

	bool operator==(const Vector& other) const;
	class Vector& operator=(const class Vector& counter);

	static Vector* plus(const Vector& vec1, const Vector& vec2);
	static bool isEqual(const Vector& vec1, const Vector& vec2);
	static double calcMagnitude(const Vector& vec);

private:

	int* coords;
	int dim;
};


#endif
