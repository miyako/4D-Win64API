/* --------------------------------------------------------------------------------
#
#	Registry.cpp
#	All of the methods related to registry functions
#	Project : Win32API
#	author : jmiller
#	9/29/2020
#
# --------------------------------------------------------------------------------*/

#include "Registry.h"

void sys_GetRegEnum(PA_PluginParameters params)
{
	DWORD dwSubKeys, i, j;
	DWORD dwMaxSubKeyLength = MAX_KEY_LENGTH;
	HKEY hRootKey, hOpenKey;
	REGSAM regSamFlag;
	WCHAR wcSubKeyName[MAX_KEY_LENGTH];

	PA_long32 lRootKey, lReturnValue;
	PA_Unistring paSubKeyName;
	PA_Unistring* paSubKeyNames;
	PA_Variable paReturnKeyNamesArray;

	// Get the parameters
	lRootKey = PA_GetLongParameter(params, 1);
	paSubKeyNames = PA_GetStringParameter(params, 2);
	paReturnKeyNamesArray = PA_GetVariableParameter(params, 3);

	regSamFlag = KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_WOW64_64KEY;

	lReturnValue = 0;
	dwSubKeys = 0;
	hRootKey = hOpenKey = 0;

	hRootKey = util_getRegRoot(lRootKey);

	if (RegOpenKeyEx(hRootKey, (LPCWSTR)paSubKeyNames->fString, 0, regSamFlag, &hOpenKey) == ERROR_SUCCESS)
	{
		if (RegQueryInfoKey(hOpenKey, NULL, NULL, NULL, &dwSubKeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
		{
			if (dwSubKeys)
			{
				PA_ResizeArray(&paReturnKeyNamesArray, dwSubKeys);

				for (i = 0, j = 0; i < dwSubKeys; i++)
				{
					dwMaxSubKeyLength = MAX_KEY_LENGTH;

					if (RegEnumKeyEx(hOpenKey, i, wcSubKeyName, &dwMaxSubKeyLength, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
					{
						paSubKeyName = PA_CreateUnistring((PA_Unichar*)wcSubKeyName);
						PA_SetStringInArray(paReturnKeyNamesArray, ++j, &paSubKeyName);
					}
				}

				lReturnValue = 1;
			}
		}
	}

	// Close the handle
	RegCloseKey(hOpenKey);

	// Set the return values
	PA_SetVariableParameter(params, 3, paReturnKeyNamesArray, 0);
	PA_ReturnLong(params, lReturnValue);
}

HKEY util_getRegRoot(PA_long32 lKey) {
	HKEY hReturnKey = 0;

	switch (lKey) {
	case (GR_HKEY_CLASSES_ROOT):
		hReturnKey = HKEY_CLASSES_ROOT;
		break;

	case (GR_HKEY_CURRENT_USER):
		hReturnKey = HKEY_CURRENT_USER;
		break;

	case (GR_HKEY_DYN_DATA):
		hReturnKey = HKEY_DYN_DATA;
		break;

	case (GR_HKEY_LOCAL_MACHINE):
		hReturnKey = HKEY_LOCAL_MACHINE;
		break;

	case (GR_HKEY_USERS):
		hReturnKey = HKEY_USERS;
		break;

	case (GR_HKEY_CURRENT_CONFIG):
		hReturnKey = HKEY_CURRENT_CONFIG;
		break;

	case (GR_HKEY_PERFORMANCE_DATA):
		hReturnKey = HKEY_PERFORMANCE_DATA;
		break;

	default:
		hReturnKey = HKEY_LOCAL_MACHINE;
	}

	return hReturnKey;
}
