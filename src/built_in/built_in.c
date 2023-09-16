/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlachat <mlachat@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:27:26 by mlachat           #+#    #+#             */
/*   Updated: 2023/09/13 17:25:39 by mlachat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_tk *cmd, int backslash_n, int i)
{
	if (cmd->tab_options[i])
	{
		while (cmd->tab_options[i])
		{
			if (ft_strcmp(cmd->tab_options[i], "-n") == 0)
			{
				backslash_n = 1;
				i++;
			}
			else
				break ;
		}
		while (cmd->tab_options[i])
		{
			ft_printf("%s", cmd->tab_options[i]);
			i++;
			if (cmd->tab_options[i])
				ft_printf(" ", cmd->tab_options[i]);
		}
	}
	if (backslash_n == 0)
		ft_printf("\n");
	error_handle(0, NULL, 0);	
}

int	cd(t_tk *cmd)
{

}

int	pwd(t_tk *cmd)
{
	ft_printf("%s\n", cmd->current_folder);
	error_handle(0, NULL, 0);
}

int	export(t_tk *cmd)
{

}

int	unset(t_tk *cmd, t_tk )
{

}

int	env(t_tk *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			ft_printf("%c", cmd[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	error_handle(0, NULL, 0);
}

int	exit(t_tk *cmd)
{
	
}

int	builtin_exec(t_tk *cmd)
{
	int	status;

	status = -1;
	if (is_echo(cmd))
		status = echo(cmd);
	else if (is_cd(cmd))
		status = cd(cmd);
    else if (is_pwd(cmd))
		status = pwd(cmd);
	else if (is_export(cmd))
		status = export(cmd);
	else if (is_unset(cmd))
		status = unset(cmd);
	else if (is_env(cmd))
		status = env(cmd);
	else if (is_exit(cmd))
	{
		status = 0;
		exit(cmd);
	}
	return (status);
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