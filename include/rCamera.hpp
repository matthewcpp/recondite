#pragma once

#include <cstdint>

#include "rBuild.hpp"
#include "rVector3.hpp"

namespace recondite {
	class Camera {
	public:
		Camera() :
			m_position(rVector3::ZeroVector), m_target(rVector3::ForwardVector), m_up(rVector3::UpVector), 
			m_width(10), m_height(10), m_renderingMask(1U) {}

		inline void SetPosition(const rVector3& position);
		inline void SetPosition(float x, float y, float z);
		inline rVector3 GetPosition() const;

		inline void SetTarget(const rVector3& target);
		inline void SetTarget(float x, float y, float z);
		inline rVector3 GetTarget() const;

		inline void SetUp(const rVector3& up);
		inline void SetUp(float x, float y, float z);
		inline rVector3 GetUp() const;

		inline void SetWidth(float width);
		inline float GetWidth() const;

		inline void SetHeight(float height);
		inline float GetHeight() const;

		inline uint16_t GetRenderingMask() const;
		inline void SetRenderingMask(uint16_t renderingMask);

	private:
		rVector3 m_position;
		rVector3 m_target;
		rVector3 m_up;

		float m_width;
		float m_height;

		uint16_t m_renderingMask;
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

	inline void Camera::SetWidth(float width) {
		m_width = width;
	}

	inline float Camera::GetWidth() const {
		return m_width;
	}

	inline void Camera::SetHeight(float height) {
		m_height = height;
	}

	inline float Camera::GetHeight() const {
		return m_height;
	}

	inline uint16_t Camera::GetRenderingMask() const {
		return m_renderingMask;
	}
	inline void Camera::SetRenderingMask(uint16_t renderingMask) {
		m_renderingMask = renderingMask;
	}
}