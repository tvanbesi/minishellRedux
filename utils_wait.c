#include "minishell.h"

void
	setexitstatus(int stat_loc)
{
	if (WIFEXITED(stat_loc))
		g_exitstatus = WEXITSTATUS(stat_loc);
	else if (WIFSIGNALED(stat_loc))
		g_exitstatus = 128 + WTERMSIG(stat_loc);
}
