#pragma once

#include <map>
#include <string>
#include <stdexcept>
#include <memory>

namespace OpenGLEngine {

	class UserPreferences
	{
	private:
		std::map<std::string, float> m_preferencesFloat;

	public:
		UserPreferences();
		float GetPreferenceFloat(std::string preferenceString);
		void Load();
		void Save();

	};

}