#include <vdtmath/transform.h>

namespace math
{
	transform::transform()
		: position()
		, rotation()
		, scale(1.0f, 1.0f, 1.0f)
		, isStatic(false)
		, m_matrix(matrix4::identity)
		, m_wasStatic(isStatic)
		, m_state()
	{

	}
	
	void transform::update()
	{
		if (isStatic && m_wasStatic) return;

		if (bool isChanged = m_state.update(*this))
		{
			//m_matrix = matrix4::scale(scale) * rotation.matrix() * matrix4::translate(position);
			m_matrix = matrix4::scale(scale) * matrix4::rotate_z(rotation.z) * matrix4::translate(position);
		}
		m_wasStatic = isStatic;
	}
	
	bool transform::State::update(transform& transform)
	{
		if (position != transform.position
			|| rotation != transform.rotation
			|| scale != transform.scale)
		{
			position = transform.position;
			rotation = transform.rotation;
			scale = transform.scale;
			return true;
		}
		return false;
	}
}