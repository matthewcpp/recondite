#ifndef R_LOG_HPP
#define R_LOG_HPP

#include <cstddef>
#include <stdarg.h>
#include <cstdio>

#include "rBuild.hpp"
#include "rString.hpp"

namespace Log {
	class RECONDITE_API Target{
	public:
		virtual void Debug(const rString& message) = 0;
		virtual void Warning(const rString& message) = 0;
		virtual void Trace(const rString& message) = 0;
		virtual void Info(const rString& message) = 0;
		virtual void Error(const rString& message) = 0;
	};

	RECONDITE_API void Init();
	RECONDITE_API void Shutdown();
	RECONDITE_API void ClearTargets();

	RECONDITE_API void SetEnabled(bool enabled);
	RECONDITE_API bool Enabled();

	RECONDITE_API void AddTarget(Target* target);
	RECONDITE_API void RemoveTarget(Target* target);

	RECONDITE_API void Debug(const rString format, ...);
	RECONDITE_API void Warning(const rString format, ...);
	RECONDITE_API void Trace(const rString format, ...);
	RECONDITE_API void Info(const rString format, ...);
	RECONDITE_API void Error(const rString format, ...);
}

#endif
