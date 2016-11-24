#pragma once

#include "rBuild.hpp"
#include "rVector3.hpp"

namespace recondite {
	class Camera {
	public:
		Camera() :
			m_position(rVector3::ZeroVector), m_target(rVector3::ForwardVector), m_up(rVector3::UpVector) {}

		inline void SetPosition(const rVector3& position);
		inline rVector3 GetPosition() const;

		inline void SetTarget(const rVector3& target);
		inline rVector3 GetTarget() const;

		inline void SetUp(const rVector3& up);
		inline rVector3 GetUp() const;

	private:
		rVector3 m_position;
		rVector3 m_target;
		rVector3 m_up;
	};

	inline void Camera::SetPosition(const rVector3& position) {
		m_position = position;
	}

	inline rVector3 Camera::GetPosition() const {
		return m_position;
	}

	inline void Camera::SetTarget(const rVector3& target) {
		m_target = target;
	}

	inline rVector3 Camera::GetTarget() const {
		return m_target;
	}

	inline void Camera::SetUp(const rVector3& up) {
		m_up = up;
	}

	inline rVector3 Camera::GetUp() const {
		return m_up;
	}
}