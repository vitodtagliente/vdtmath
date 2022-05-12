#include <cassert>
#include <iostream>
#include <vdtmath/math.h>

using namespace std;
using namespace math;

int main()
{
	bool canInvert = false;

	// unit testing matrix2
	{
		const matrix2 a(
			5.f, 2.f,
			-7.f, -3.f
		);
		const matrix2 inverse = a.inverse(canInvert);

		assert(a.determinant() == -1.f);
		assert(inverse == matrix2(
			3.f, 2.f,
			-7.f, -5.f
		));
	}

	// unit testing matrix2
	{
		const matrix3 a(
			1.f, 2.f, -1.f,
			2.f, 1.f, 2.0,
			-1.f, 2.f, 1.f
		);
		const matrix3 inverse = a.inverse(canInvert);

		assert(a.determinant() == -16.f);
		assert(inverse == matrix3(
			3.f / 16.f, 1.f / 4.f, -5.f / 16.f,
			1.f / 4.0f, 0.0f, 1.f / 4.f,
			5.0f / 16.f, 1.f / 4.f, 3.f / 16.f
		));
	}
}