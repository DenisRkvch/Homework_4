#include "Vector.h"
#include <stdexcept>

Vector::Vector(int x, int y) : dim(2)
{
	coords = new int[dim] {x, y};
}

Vector::Vector(int x, int y, int z) : dim(3)
{
	coords = new int[dim] {x, y, z};
}

Vector::Vector(int _coords[], int len): dim(len)
{
	
	if (len <= 0)
	{
		throw std::invalid_argument("length can't be less or equar to 0");
	}

	coords = new int[dim];
	for (int i = 0; i < len;i++)
	{
		coords[i] = _coords[i];
	}
}

Vector::Vector(const Vector& p)
{
	dim = p.dim;
	coords = new int[dim];
	for (int i = 0; i < dim;i++)
	{
		coords[i] = p.coords[i];
	}
}

Vector::~Vector()
{
	delete[] coords;	
}

void Vector::add(const Vector& vec)
{
	if (vec.dim > dim)
	{
		throw std::invalid_argument("dimension of the added vector can't be greater than of the first one");
	}

	for (int i = 0; i < vec.dim; i++)
	{
		coords[i] += vec.coords[i];
	}
}

bool Vector::isEqual(const Vector &vec) const
{
	int dim_min = (dim <= vec.dim) ? dim : vec.dim;

	/* ��������� ��������� � ����������� ���������� */
	for (int i = 0; i < dim_min; i++)
	{
		if (coords[i] != vec.coords[i])
		{
			return false;
		}
	}
	
	if (dim != vec.dim)
	{
		/* �������� ��� ���������� � ��������� ���������� ����� 0 */
		const Vector * vec_max = (dim > vec.dim) ? this : &vec;
		
		for (int i = dim_min; i < vec_max->dim;i++)
		{
			if (vec_max->coords[i] != 0)
			{
				return false;
			}
		}
	}
	
	return true;
}

//������� �������� �������� ����������
//int Vector::getValue(int coord_ind) const
//{
//	if (coord_ind+1 > dim)
//	{
//		throw std::invalid_argument("the vector doesn't have a coordinate with the passed index ");
//	}
//	if (coord_ind < 0)
//	{
//		throw std::invalid_argument("passing index can't be negative");
//	}
//	return coords[coord_ind];
//}

// statics
bool Vector::isEqual(const Vector &vec1, const Vector &vec2)
{
	return vec1.isEqual(vec2);
}

Vector* Vector::plus(const Vector &vec1, const Vector &vec2)
{	
	Vector* returnVec;
	const Vector* vec_max;	// ��������� �� ������ ������� �����������
	const Vector* vec_min;	// ��������� �� ������ ������� �����������

	if (vec1.dim >= vec2.dim)
	{
		vec_max = &vec1;
		vec_min = &vec2;
	}
	else
	{
		vec_max = &vec2;
		vec_min = &vec1;

	}

	returnVec = new Vector{ *vec_max };
	
	/* ����� ��������� */
	for (int i = 0; i < vec_min->dim;i++)
	{
		returnVec->coords[i] += vec_min->coords[i];
	}

	return returnVec;
}

double Vector::calcMagnitude(const Vector& vec)
{
	unsigned long sqr_summ = 0;

	for (int i = 0; i < vec.dim; i++)
	{
		sqr_summ += vec.coords[i] * vec.coords[i];
	}
	return sqrt(sqr_summ);
}

bool Vector::operator==(const Vector& other) const
{
	return isEqual(other);

}

Vector& Vector::operator=(const Vector& p)
{

	delete coords;

	dim = p.dim;
	coords = new int[dim];

	for (int i = 0; i < dim;i++)
	{
		coords[i] = p.coords[i];
	}

	return *this;
}




