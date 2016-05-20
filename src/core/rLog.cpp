#include "rLog.hpp"

#include <vector>

namespace Log {
	struct LogImpl{
		bool enabled;
		std::vector<Target*> targets;

		LogImpl() : enabled(true){}
	};

	LogImpl* _impl;
	
	rString FormatString(const rString format, va_list args);

	void AddTarget(Target* target){
		_impl->targets.push_back(target);
	}

	void RemoveTarget(Target* target){
		auto end = _impl->targets.end();

		for (auto it = _impl->targets.begin(); it != end; ++it){
			if (*it == target){
				_impl->targets.erase(it);
				return;
			}
		}
	}

	void Debug(const rString format, ...){
		if (_impl->enabled){
			va_list args;
			va_start(args, format);

			rString message = FormatString(format, args);

			for (size_t i = 0; i < _impl->targets.size(); i++)
				_impl->targets[i]->Debug(message);

			va_end(args);
		}
	}

	void Warning(const rString format, ...){
		if (_impl->enabled){
			va_list args;
			va_start(args, format);

			rString message = FormatString(format, args);

			for (size_t i = 0; i < _impl->targets.size(); i++)
				_impl->targets[i]->Warning(message);

			va_end(args);
		}
	}

	void Trace(const rString format, ...){
		if (_impl->enabled){
			va_list args;
			va_start(args, format);

			rString message = FormatString(format, args);

			for (size_t i = 0; i < _impl->targets.size(); i++)
				_impl->targets[i]->Trace(message);

			va_end(args);
		}
	}

	void Info(const rString format, ...){
		if (_impl->enabled){
			va_list args;
			va_start(args, format);

			rString message = FormatString(format, args);

			for (size_t i = 0; i < _impl->targets.size(); i++)
				_impl->targets[i]->Info(message);

			va_end(args);
		}
	}

	void Error(const rString format, ...){
		if (_impl->enabled){
			va_list args;
			va_start(args, format);

			rString message = FormatString(format, args);

			for (size_t i = 0; i < _impl->targets.size(); i++)
				_impl->targets[i]->Error(message);

			va_end(args);
		}
	}

	void Shutdown(){
		delete _impl;
	}

	void Init(){
		_impl = new LogImpl();
	}

	void SetEnabled(bool enabled){
		_impl->enabled = enabled;
	}

	void ClearTargets(){
		_impl->targets.clear();
	}

	//note this is a temporary implementation for now
	rString FormatString(const rString format, va_list args) {
		char buffer[2056];
		vsprintf(buffer, format.c_str(), args);

		return rString(buffer);
	}
}