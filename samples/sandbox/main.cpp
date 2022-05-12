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

		assert(a * vec2(1.f, 2.f) == vec2(9.f, -13.f));

		assert(a.transpose() == matrix2(
			5.f, -7.f,
			2.f, -3.f
		));
		assert(a.determinant() == -1.f);
		assert(a.inverse(canInvert) == matrix2(
			3.f, 2.f,
			-7.f, -5.f
		));

		// matrix multiplication
		assert(a * a.inverse(canInvert) == matrix2::identity);
	}

	// unit testing matrix3
	{
		const matrix3 a(
			1.f, 2.f, 3.f,
			0.f, 1.f, 4.f,
			5.f, 6.f, 0.f
		);

		assert(a * vec3(1.f, 2.f, 3.f) == vec3(14.f, 14.f, 17.f));

		assert(a.transpose() == matrix3(
			1.f, 0.f, 5.f,
			2.f, 1.f, 6.f,
			3.f, 4.f, 0.f
		));
		assert(a.determinant() == 1.f);
		assert(a.inverse(canInvert) == matrix3(
			-24.f, 18.f, 5.f,
			20.f, -15.f, -4.f,
			-5.f, 4.f, 1.f
		));

		// matrix multiplication
		assert(a * a.inverse(canInvert) == matrix3::identity);
	}

	// unit testing matrix4
	{
		const matrix4 a(
			1.f, 1.f, 1.f, -1.f,
			1.f, 1.f, -1.f, 1.f,
			1.f, -1.f, 1.f, 1.f,
			-1.f, 1.f, 1.f, 1.f
		);

		assert(a * vec4(1.f, 2.f, 3.f, 1.f) == vec4(5.f, 1.f, 3.f, 5.f));

		assert(a.transpose() == matrix4(
			1.f, 1.f, 1.f, -1.f,
			1.f, 1.f, -1.f, 1.f,
			1.f, -1.f, 1.f, 1.f,
			-1.f, 1.f, 1.f, 1.f
		));
		assert(a.determinant() == -16.f);
		assert(a.inverse(canInvert) == matrix4(
			.25f, .25f, .25f, -.25f,
			.25f, .25f, -.25f, .25f,
			.25f, -.25f, .25f, .25f,
			-.25f, .25f, .25f, .25f
		));

		// matrix multiplication
		assert(a * a.inverse(canInvert) == matrix4::identity);
	}

	// tests 
	{
		const matrix2 a(
			8.f, 9.f,
			5.f, -1.f
		);
		const matrix2 b(
			-2.f, 3.f,
			4.f, 0.f
		);
		assert(a * b == matrix2(
			20.f, 24.f,
			-14.f, 15.f
		));
	}

	// tests 
	{
		const matrix4 a(
			5.f, 7.f, 9.f, 10.f,
			2.f, 3.f, 3.f, 8.f,
			8.f, 10.f, 2.f, 3.f,
			3.f, 3.f, 4.f, 8.f
		);
		const matrix4 b(
			3.f, 10.f, 12.f, 18.f,
			12.f, 1.f, 4.f, 9.f,
			9.f, 10.f, 12.f, 2.f,
			3.f, 12.f, 4.f, 10.f
		);
		assert(a * b == matrix4(
			210.f, 267.f, 236.f, 271.f,
			93.f, 149.f, 104.f, 149.f,
			171.f, 146.f, 172.f, 268.f,
			105.f, 169.f, 128.f, 169.f
		));
	}

	// orthographic test
	{

	}
}