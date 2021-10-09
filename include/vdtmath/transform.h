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

		inline bool getIsStatic() const { return m_isStatic; }
		void setIsStatic(bool value);

		vector3 position;
		vector3 rotation;
		vector3 scale;

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
		bool m_isStatic;
		State m_state;
	};
}