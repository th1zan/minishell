/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:27:26 by mlachat           #+#    #+#             */
/*   Updated: 2023/10/18 21:55:50 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_tk *tk)
{
	t_tk	*tmp;
	int		ret;

	tmp = NULL;
	ret = 1;
	// fprintf(stderr, "echo:: fd_out: %d\n", tk->fd_out);
	if (tk->tk_arg)
		tmp = tk->tk_arg;
	else
	{	
		ft_putstr_fd("\n", tk->fd_out);
		return (0);
	}
	if (ft_strncmp(tmp->tk_str, "-n", 2) == 0)
	{
		ret = 0;
		tmp = tmp->next;

	}
	while(tmp)
	{
		if (!is_blank_str(tmp->tk_str))
		{	
			ft_putstr_fd(tmp->tk_str, tk->fd_out);
			// fprintf(stderr, "%s", tmp->tk_str);
			// printf("--%d--", tmp->is_var_type_with_space_before);
		}
		tmp = tmp->next;
		if (tmp && tmp->is_var_type_with_space_before)
			ft_putstr_fd(" ", tk->fd_out);
	}
	if(ret)
		ft_putstr_fd("\n", tk->fd_out);
	return(0);
}


int	find_env_var(char **env, char *var_name)
{
	int		i;
	int		j;
	char	*tmp_env;

	if (!var_name || !*var_name)
		return (-1);

	i = 0;
	tmp_env = NULL;
	while (env[i] != NULL)
	{
		// printf("var_name:%s\n", var_name);
		// printf("env[%d]:%s\n", i, env[i]);
		tmp_env = env[i];
		j = 0;
		// Ajouter une condition supplémentaire pour vérifier la fin de la chaîne
		while (tmp_env[j] && var_name[j] && tmp_env[j] == var_name[j])
		{
			// printf("tmp_env[%d] : %c && var_name[%d] : %c\n",  j,tmp_env[j],j, var_name[j] );
			if (tmp_env[j + 1] && tmp_env[j + 1] == '=' && (var_name[j + 1] == 0 || var_name[j + 1] == '='))
			{
				// printf("variable env trouvée\n");
				return (i); // trouvé
			}
			j++;
			
		}		
		i++;
	}

	return (-1); // non trouvé
}

char	*concat_args(t_tk *tk)
{
	char	*new_var;
	char	*tmp;
	t_tk	*next_arg;

	new_var = ft_strdup("");
	while(tk->tk_arg)
	{
		tmp = ft_strjoin(new_var, tk->tk_arg->tk_str);
		// printf("tmp: %s, %p\n", tmp, tmp);
		if (tmp)
		{
			free(new_var);
			new_var = tmp;
		}
		else
		{
			free(new_var);
			while (tk->tk_arg) {
				next_arg = tk->tk_arg->next;
				free(tk->tk_arg->tk_str);
				free(tk->tk_arg);
				tk->tk_arg = next_arg;
			}
			return (NULL);
		}
		next_arg = tk->tk_arg->next;
		free(tk->tk_arg->tk_str);
		free(tk->tk_arg);
		tk->tk_arg = next_arg;
	}
	return (new_var);
}


int	unset(t_tk *tk)
{
	char **env;
	char *target_var;
	int index;
	int i;
	int j;
	int k;
	char **new_env;

	env = global_env->env_main;
	target_var = concat_args(tk); 
	index = find_env_var(env, target_var);
	// printf("index: %d/n", index);
	if (index == -1)
	{
		free(target_var);
		return (0);
	}

	// 3) Si elle existe, supprime la variable du tableau
	free(env[index]);
	i = 0;
	while (env[i] != NULL)
	i++;

	new_env = malloc(i * sizeof(char*)); // -1 car on supprime une variable, mais pas besoin d'ajouter pour NULL car i compte déjà NULL
	if(!new_env)
		return(1);
	// printf("new_env %p\n", new_env);
	j = 0;
	k = 0;
	while (j < i)
	{
		if (j == index)
		{
			j++;
			continue;
		}
		new_env[k] = env[j];
		j++;
		k++;
	}
	new_env[k] = NULL;  // termine le tableau avec NULL
	free(env);
	// print_strtab(env);
	// if (env)
	// 	free(env); // libère l'ancien tableau
	global_env->env_main = new_env; // met à jour le pointeur env pour pointer vers le nouveau tableau
	// printf("global_env->env_main:%p\n", global_env->env_main);
	if(ft_strncmp(target_var, "PATH", 4) == 0)
	{
		// printf("AVANT, path_tab: %p\n", global_env->path_tab);
		// print_strtab(global_env->path_tab);
		// free_strtab(global_env->path_tab);
		// free(global_env->path_tab);
		global_env->path_tab = NULL;
		global_env->path_tab = get_path_tab(global_env->env_main);
		// printf("APRES, path_tab: %p\n", global_env->path_tab);
		// if (global_env->path_tab)
		// 	print_strtab(global_env->path_tab);
	}
	free(target_var); // N'oubliez pas de libérer la mémoire de target_var

	
	return (0); // Tout s'est bien passé
}

int	is_valid_env_argument(char *arg)
{
	int		i;
	int		equals_found;  // 0 pour false, 1 pour true

	// printf("is_valid_env_argument:: arg: %s\n", arg);
	equals_found = 0;
	// Check if the argument is not empty
	if (!arg || arg[0] == '\0')
		return (-1);  // -1 pour empty

	// Check for a valid starting character: either a letter or an underscore
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (-2);  // 0 pour non-valide

	i = 1;

	// Check subsequent characters for validity or the presence of an equals sign
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			equals_found = 1;  // 1 pour true
			if (arg[i + 1] == 0)
				return (1);
			break;
		}
		else if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (-2);  // -2 pour non-valide
		i++;
	}

	// Check for presence of '='. If '=' is found, there should be valid characters before it.
	if (!equals_found || i == 0)
	{
		// printf("minishell:  export: not a valid identifier\n");
		return (0);  // 0 pour false
	}
		

	return (1);  // 1 pour true
}

int	export(t_tk *tk)
{
	char	**env;
	char	*new_var;
	int		index;
	int		i;
	char	**new_env;

	env = global_env->env_main;
	if (tk->tk_arg == 0)
	{
		env_built_in(tk);
		return (0);
	}
	new_var = concat_args(tk);
	if (is_valid_env_argument(new_var) == -2)
	{
		printf("minishell:  export: '%s' : not a valid identifier\n", new_var);
		free(new_var);	
		return (1);
	}
	else if (!is_valid_env_argument(new_var))
	{
		// printf("minishell:  export: %s : not a valid identifier\n", new_var);
		free(new_var);	
		return (0);
	}
	index = find_env_var(env, new_var);
	if (index != -1)
	{
		free(env[index]);
		env[index] = new_var;
	}
	else
	{
		i = 0;
		while (env[i])
			i++;
		new_env = malloc((i + 2) * sizeof(char *));
		if(!new_env)
			return(0);
		i = -1;
		while (env[++i])
			new_env[i] = env[i];
		new_env[i] = new_var;
		new_env[i + 1] = NULL;
		free(global_env->env_main);
		global_env->env_main = new_env;
	}
	if(ft_strncmp(new_var, "PATH", 4) == 0)
	{
		// printf("AVANT, path_tab: %p\n", global_env->path_tab);
		// if (global_env->path_tab)
		// 	print_strtab(global_env->path_tab);
		global_env->path_tab = get_path_tab(global_env->env_main);
		// printf("APRES, path_tab: %p\n", global_env->path_tab);
		// if (global_env->path_tab)
		// 	print_strtab(global_env->path_tab);
	}
	return (0);
}



int	env_built_in(t_tk *tk)
{
	int	fd_out;
	// printf("env_built_in:: tk: %s\n", tk->tk_str);
	// printf("env_built_in:: tk->env: %p\n", tk->env);
	// printf("global env_built_in:: global_env->env_main: %p\n", global_env->env_main);
	// printf("global env_built_in:: global_env->env_main[3]:%s %p\n", global_env->env_main[3], global_env->env_main[3]);
	if(*(tk->env) == 0)
		return(1);
	fd_out = tk->fd_out;
	print_strtab(global_env->env_main, fd_out);
	return(0);
}

int pwd(t_tk *tk)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr_fd(cwd, tk->fd_out);
	ft_putstr_fd("\n", tk->fd_out);
	return(0);
}

int update_oldpwd(char *current_directory)
{
	
	char	**env;
	// char	*new_var;
	int		index;
	int		i;
	char	**new_env;

	env = global_env->env_main;
	// new_var = ft_strdup(current_directory);
	// if (!is_valid_env_argument(new_var))
	// {
	// 	free(new_var);	
	// 	return (1);
	// }
	index = find_env_var(env, "OLDPWD");
	if (index != -1)
	{
		free(env[index]);
		env[index] = ft_strjoin("OLDPWD=", current_directory);
	}
	else
	{
		i = 0;
		while (env[i])
			i++;
		new_env = malloc((i + 2) * sizeof(char *));
		if(!new_env)
			return(1);
		i = -1;
		while (env[++i])
			new_env[i] = env[i];
		new_env[i] = ft_strjoin("OLDPWD=", current_directory);
		new_env[i + 1] = NULL;
		free(global_env->env_main);
		global_env->env_main = new_env;
	}
	return (0);
}


int	cd(t_tk *tk) 
{
	char *path;
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	update_oldpwd(cwd);

	if (tk == NULL)
	{
		return (1);
	}
	if (tk->tk_arg == NULL || tk->tk_arg->tk_str == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else
		path = tk->tk_arg->tk_str;
	if (chdir(path) != 0) 
	{
		// perror("chdir failed");
		printf("minishell: cd: %s: parsing path: No such file or directory\n", path);
		return (1);
	}
	return (0);
}

int	exit_builtin(t_tk *cmd)
{
	int status = 0;

	status = 0;
	ft_putstr_fd("exit\n", 2);

	if (cmd->tk_arg)
	{
		if (cmd->tk_arg->next)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			status = 1;
		}
		else
		{
			if (is_str_with_alpha(cmd->tk_arg->tk_str) || !is_all_digit(cmd->tk_arg->tk_str))
			{
				ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
				status = 255;
			}
			else
			{
				status = ft_atoi(cmd->tk_arg->tk_str);
				if (status < 0)
					status = 256 + (status % 256);
				else
					status = status % 256;
			}
		}
	}
	return (status);
}

int	is_str_with_alpha(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (ft_isalpha(*str))
			return (1);
		str++;
	}
	return (0);
}

int	is_all_digit(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

/*
echo : Cette commande imprime ses arguments à l'écran. Elle prend également en charge quelques options, comme -n qui supprime le saut de ligne final.
cd : Change le répertoire courant. Sans argument, il se déplace vers le répertoire spécifié dans la variable d'environnement HOME. Avec un argument, il tente de se déplacer vers le répertoire spécifié.
pwd : Affiche le répertoire de travail actuel.
export : Utilisée pour définir ou modifier les variables d'environnement. Avec aucun argument, elle liste toutes les variables d'environnement.
unset : Supprime une variable d'environnement.
env : Sans arguments, il affiche toutes les variables d'environnement. Avec des arguments, il peut être utilisé pour exécuter une commande dans un environnement modifié.
exit : Termine le shell. Elle accepte un argument optionnel qui spécifie le code de sortie.
*/