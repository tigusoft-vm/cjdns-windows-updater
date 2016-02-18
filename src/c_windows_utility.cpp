#if defined _WIN32 || defined __CYGWIN__

#include "c_windows_utility.hpp"

#include <windows.h>
#include <winbase.h>

namespace win_utility {

// function from https://msdn.microsoft.com/en-us/library/aa376389%28v=VS.85%29.aspx
bool c_windows_utility::is_user_admin() {
	BOOL b;
	SID_IDENTIFIER_AUTHORITY NtAuthority = {SECURITY_NT_AUTHORITY};
	PSID AdministratorsGroup;
	b = AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&AdministratorsGroup);
	if(b)
	{
		if (!CheckTokenMembership( nullptr, AdministratorsGroup, &b))
		{
			b = false;
		}
		FreeSid(AdministratorsGroup);
	}
	return(b);
}
	

} // namespace

#endif