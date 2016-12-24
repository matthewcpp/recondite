#pragma once

#include "rBuild.hpp"
#include "rVector3.hpp"

namespace recondite {
	class Camera {
	public:
		Camera() :
			m_position(rVector3::ZeroVector), m_target(rVector3::ForwardVector), m_up(rVector3::UpVector) {}

		inline void SetPosition(const rVector3& position);
		inline void SetPosition(float x, float y, float z);
		inline rVector3 GetPosition() const;

		inline void SetTarget(const rVector3& target);
		inline void SetTarget(float x, float y, float z);
		inline rVector3 GetTarget() const;

		inline void SetUp(const rVector3& up);
		inline void SetUp(float x, float y, float z);
		inline rVector3 GetUp() const;

	private:
		rVector3 m_position;
		rVector3 m_target;
		rVector3 m_up;
	};

	inline void Camera::SetPosition(const rVector3& position) {
		m_position = position;
	}

	inline void Camera::SetPosition(float x, float y, float z) {
		m_position.Set(x, y, z);
	}

	inline rVector3 Camera::GetPosition() const {
		return m_position;
	}

	inline void Camera::SetTarget(const rVector3& target) {
		m_target = target;
	}

	inline void Camera::SetTarget(float x, float y, float z) {
		m_target.Set(x, y, z);
	}

	inline rVector3 Camera::GetTarget() const {
		return m_target;
	}

	inline void Camera::SetUp(const rVector3& up) {
		m_up = up;
	}

	inline void Camera::SetUp(float x, float y, float z) {
		m_up.Set(x, y, z);
	}

	inline rVector3 Camera::GetUp() const {
		return m_up;
	}
}