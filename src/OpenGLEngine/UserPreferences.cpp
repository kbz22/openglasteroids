#include <OpenGLEngine/UserPreferences.h>

OpenGLEngine::UserPreferences::UserPreferences()
{
	if (m_preferencesFloat.empty()) {
		 m_preferencesFloat = {
			{ "sensitivity", 0.1f },
			{ "movementSpeed", 3.0f },
			{ "fov", 45.0f }
		};
	}
}

void OpenGLEngine::UserPreferences::Load()
{

}

float OpenGLEngine::UserPreferences::GetPreferenceFloat(std::string preferenceString)
{
	if (m_preferencesFloat.find(preferenceString) != m_preferencesFloat.end()) {
		return m_preferencesFloat[preferenceString];
	}

	throw new std::invalid_argument("preference string \""+preferenceString+"\" was not found");	
}
