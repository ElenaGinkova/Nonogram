#pragma once
bool found(const char* playersName, const char* name)
{
	while (*name != '\0' && *playersName != '\0')
	{
		if (*name != *playersName)
		{
			return false;
		}
		name++;
		playersName++;
	}
	return (*playersName == '\0' && *name == '\0');
}