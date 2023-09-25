/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:27:26 by mlachat           #+#    #+#             */
/*   Updated: 2023/09/25 10:47:00 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_tk *tk)
{
	t_tk	*tmp;

	tmp = NULL;
	if (tk->tk_arg)
		tmp = tk->tk_arg;
	while(tmp)
	{
		if (tmp->tk_str)
			printf("%s", tmp->tk_str);
		tmp = tmp->next;
	}
	return(0);
}

// int	echo(t_tk *cmd, int backslash_n, int i)
// {
// 	if (cmd->tab_options[i])
// 	{
// 		while (cmd->tab_options[i])
// 		{
// 			if (ft_strcmp(cmd->tab_options[i], "-n") == 0)
// 			{
// 				backslash_n = 1;
// 				i++;
// 			}
// 			else
// 				break ;
// 		}
// 		while (cmd->tab_options[i])
// 		{
// 			ft_printf("%s", cmd->tab_options[i]);
// 			i++;
// 			if (cmd->tab_options[i])
// 				ft_printf(" ", cmd->tab_options[i]);
// 		}
// 	}
// 	if (backslash_n == 0)
// 		ft_printf("\n");
// 	error_handle(0, NULL, 0);	
// }

// int	cd(t_tk *cmd)
// {

// }

// int	pwd(t_tk *cmd)
// {
// 	ft_printf("%s\n", cmd->current_folder);
// 	error_handle(0, NULL, 0);
// }

// int	export(t_tk *cmd)
// {

// }

// int	unset(t_tk *cmd, t_tk )
// {

// }

// int	env(t_tk *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		j = 0;
// 		while (cmd[i][j])
// 		{
// 			ft_printf("%c", cmd[i][j]);
// 			j++;
// 		}
// 		ft_printf("\n");
// 		i++;
// 	}
// 	error_handle(0, NULL, 0);
// }

// int	exit(t_tk *cmd)
// {
	
// }




/*
echo : Cette commande imprime ses arguments à l'écran. Elle prend également en charge quelques options, comme -n qui supprime le saut de ligne final.
cd : Change le répertoire courant. Sans argument, il se déplace vers le répertoire spécifié dans la variable d'environnement HOME. Avec un argument, il tente de se déplacer vers le répertoire spécifié.
pwd : Affiche le répertoire de travail actuel.
export : Utilisée pour définir ou modifier les variables d'environnement. Avec aucun argument, elle liste toutes les variables d'environnement.
unset : Supprime une variable d'environnement.
env : Sans arguments, il affiche toutes les variables d'environnement. Avec des arguments, il peut être utilisé pour exécuter une commande dans un environnement modifié.
exit : Termine le shell. Elle accepte un argument optionnel qui spécifie le code de sortie.
*/