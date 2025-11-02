#ifndef EXEC_PATH_H
# define EXEC_PATH_H

char    *get_path_from_env(char **envp);
char    *join_path(const char *dir, const char *cmd);

#endif
