/// Copyright (c) Vito Domenico Tagliente

#pragma once
#pragma warning(disable : 4201)

#include <cassert>
#include <cmath>
#include <cstring>

#include "matrix2.h"
#include "vector3.h"

namespace math
{
	template <typename T>
	struct matrix3_t
	{
		static const matrix3_t zero;
		static const matrix3_t identity;

		// num of rows
		const std::size_t rows = 3;
		// num of columns
		const std::size_t columns = 3;
		// matrix size
		const std::size_t length = 3 * 3;

		// matrix data
		union
		{
			struct
			{
				T m00, m01, m02;
				T m10, m11, m12;
				T m20, m21, m22;
			};

			T data[3 * 3];
		};

		matrix3_t()
			: data()
		{
			for (unsigned int j = 0; j < rows; j++)
			{
				for (unsigned int i = 0; i < columns; i++)
				{
					(*this)(i, j) = static_cast<T>(0.0);
				}
			}
		}

		matrix3_t(const T value)
			: data()
		{
			for (unsigned int j = 0; j < rows; j++)
			{
				for (unsigned int i = 0; i < columns; i++)
				{
					(*this)(i, j) = value;
				}
			}
		}

		matrix3_t(
			const T m00, const T m01, const T m02,
			const T m10, const T m11, const T m12,
			const T m20, const T m21, const T m22
		) :
			m00(m00), m01(m01), m02(m02),
			m10(m10), m11(m11), m12(m12),
			m20(m20), m21(m21), m22(m22)
		{

		}

		matrix3_t(const matrix3_t& matrix)
			: data()
		{
			std::memcpy(data, matrix.data, length * sizeof(T));
		}

		std::size_t size() const
		{
			return length;
		}

		// get (i,j) element
		T& operator() (const unsigned int i, const unsigned int j)
		{
			// row major implementation
			return data[i + j * columns];
		}

		T operator() (const unsigned int i, const unsigned int j) const
		{
			return data[i + j * columns];
		}

		// transpose matrix
		matrix3_t transpose() const
		{
			matrix3_t MT;
			for (unsigned int j = 0; j < rows; j++)
			{
				for (unsigned int i = 0; i < columns; i++)
				{
					MT(i, j) = (*this)(j, i);
				}
			}
			return MT;
		}

		// sub matrix
		matrix2_t<T> minor(const unsigned int i, const unsigned int j) const
		{
			assert(i < columns
				&& j < rows);
			matrix2_t<T> result;

			for (unsigned int _j = 0, __j = 0; _j < rows; ++_j)
			{
				if (_j == j) continue;
				for (unsigned int _i = 0, __i = 0; _i < columns; ++_i)
				{
					if (_i == i) continue;
					result(__i, __j) = (*this)(_i, _j);
					++__i;
				}
				++__j;
			}
			return result;
		}

		matrix3_t inverse(bool& is_invertible) const
		{
			is_invertible = false;
			const T d = determinant();
			if (d != static_cast<T>(0.0)) {
				is_invertible = true;
				return adjugate() / d;
			}
			return *this;
		}

		// adjugate matrix
		matrix3_t adjugate() const
		{
			matrix3_t result;
			const matrix3_t MT = transpose();
			for (unsigned int j = 0; j < rows; ++j)
			{
				for (unsigned int i = 0; i < columns; ++i)
				{
					matrix2_t<T> currentMinor = MT.minor(i, j);
					result(i, j) = static_cast<T>(std::pow(-1, i + j)) * currentMinor.determinant();
				}
			}
			return result;
		}

		// determinant 
		T determinant() const
		{
			// Sarrus law
			return (m00 * m11 * m22) + (m01 * m12 * m20) + (m02 * m10 * m21)
				- (m20 * m11 * m02) - (m21 * m12 * m00) - (m22 * m10 * m01);
		}

		/* Operators overloading */

		matrix3_t& operator= (const matrix3_t& matrix)
		{
			// check for self-assignment
			if (this == &matrix)
				return *this;

			std::memcpy(data, matrix.data, length * sizeof(T));
			return *this;
		}

		bool operator== (const matrix3_t& matrix) const
		{
			return m00 == matrix.m00 && m01 == matrix.m01 && m02 == matrix.m02
				&& m10 == matrix.m10 && m11 == matrix.m11 && m12 == matrix.m12
				&& m20 == matrix.m20 && m21 == matrix.m21 && m22 == matrix.m22;
		}

		bool operator!= (const matrix3_t& matrix) const
		{
			return m00 != matrix.m00 || m01 != matrix.m01 || m02 != matrix.m02
				|| m10 != matrix.m10 || m11 != matrix.m11 || m12 != matrix.m12
				|| m20 != matrix.m20 || m21 != matrix.m21 || m22 != matrix.m22;
		}

		matrix3_t& operator+= (const matrix3_t& matrix)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] += matrix.data[i];
			return *this;
		}

		matrix3_t& operator-= (const matrix3_t& matrix)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] -= matrix.data[i];
			return *this;
		}

		matrix3_t& operator*= (const T scalar)
		{
			for (unsigned int i = 0; i < length; i++)
				data[i] *= scalar;
			return *this;
		}

		matrix3_t& operator/= (const T scalar)
		{
			assert(scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / scalar;
			return (*this) *= f;
		}

		matrix3_t operator- () const
		{
			matrix3_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = -data[i];
			return result;
		}

		matrix3_t operator+ (const matrix3_t& matrix) const
		{
			matrix3_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] + matrix.data[i];
			return result;
		}

		matrix3_t operator- (const matrix3_t& matrix) const
		{
			matrix3_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] - matrix.data[i];
			return result;
		}

		matrix3_t operator* (const T scalar) const
		{
			matrix3_t result;
			for (unsigned int i = 0; i < length; i++)
				result.data[i] = data[i] * scalar;
			return result;
		}

		matrix3_t operator/ (const T scalar) const
		{
			assert(scalar != static_cast<T>(0.0));
			T f = static_cast<T>(1.0) / scalar;
			return (*this) * f;
		}

		matrix3_t operator* (const matrix3_t& matrix) const
		{
			matrix3_t result;
			for (unsigned int j = 0; j < rows; ++j)
			{
				for (unsigned int y = 0; y < columns; ++y)
				{
					for (unsigned int i = 0; i < rows; ++i)
					{
						result(y, j) += (*this)(i, j) * matrix(y, i);
					}
				}
			}
			return result;
		}

		vector3_t<T> operator* (const vector3_t<T>& vector) const
		{
			vector3_t<T> result;
			for (unsigned int j = 0; j < rows; ++j)
			{
				T value{};
				for (unsigned int i = 0; i < columns; ++i)
				{
					value += (*this)(i, j) * vector[i];
				}
				result[j] = value;
			}
			return result;
		}
	};

	template<typename T> const matrix3_t<T> matrix3_t<T>::zero = matrix3_t<T>(0.0);
	template<typename T> const matrix3_t<T> matrix3_t<T>::identity = matrix3_t<T>(
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
		);

	// matrix types

	typedef matrix3_t<float> matrix3;
	typedef matrix3 mat3;
}