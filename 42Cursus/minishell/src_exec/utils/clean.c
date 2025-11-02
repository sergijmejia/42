
#include "minishell_exec.h"

/* Frees executor dynamic list */
void	free_tmp_var_exec(t_temp_lst_exec *lst)
{
	t_temp_lst_exec	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->name);
		free(lst->value);
		free(lst);
		lst = tmp;
	}
}