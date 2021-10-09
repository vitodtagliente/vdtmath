/// Copyright (c) Vito Domenico Tagliente

#pragma once

#include "matrix4.h"
#include "vector3.h"

namespace math
{
	class transform
	{
	public:

		transform();

		inline const matrix4& matrix() const { return m_matrix; }

		void update();

		vector3 position;
		vector3 rotation;
		vector3 scale;
		bool isStatic;

	private:

		struct State
		{
			vector3 position;
			vector3 rotation;
			vector3 scale;	

			bool update(transform& transform);
		};

		// cached matrix
		matrix4 m_matrix;
		bool m_wasStatic;
		State m_state;
	};
}