/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:27:26 by mlachat           #+#    #+#             */
/*   Updated: 2023/10/03 18:34:51 by tsanglar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_tk *tk)
{
	t_tk	*tmp;
	int		ret;

	tmp = NULL;
	ret = 1;
	if (tk->tk_arg)
		tmp = tk->tk_arg;
	else
		return (-1);
	if (ft_strncmp(tmp->tk_str, "-n", 2) == 0)
	{
		ret = 0;
		tmp = tmp->next;

	}
	while(tmp)
	{
		if (tmp->tk_str)
			printf("%s", tmp->tk_str);
		tmp = tmp->next;
		if (tmp)
			printf(" ");
	}
	if(ret)
		printf("\n");
	return(0);
}

int	export(t_tk *tk)
{
	char	**env;
	int		tab_size;
	char	**new_env;
	int		i;
	
	
	env = tk->env;
	print_strtab(env);
	tab_size = 0;
	while (env[tab_size] != NULL)
		tab_size++;

	if (malloc_strtab(&new_env, tab_size + 2)) // +1 pour la nouvelle entrée et +1 pour NULL
		return (1);
	
	i = 0;
	while (i < tab_size)
	{	
		new_env[i] = env[i];
		i++;
	}

	// TODO: Vérifier l'argument et ajouter à new_env
	if (tk->tk_arg->tk_str /* && is_valid_env_argument(tk->tk_arg->tk_str) */)
	{
		new_env[i] = tk->tk_arg->tk_str;
		i++;
	}
	new_env[i] = NULL;


	tk->env = new_env;
	print_strtab(tk->env);

	return (0);
}



/*
Arguments sans valeurs:
Si vous passez seulement le nom de la variable sans lui affecter une valeur, la variable sera créée sans valeur. Si cette variable existait déjà, sa valeur précédente restera inchangée.

Erreurs possibles:

a. Noms de variables non valides : Les noms de variables d'environnement doivent commencer par une lettre ou un underscore (_), suivi de lettres, chiffres ou underscores. Si un nom de variable est invalide, export doit renvoyer une erreur.

b. Pas d'égal (=) dans l'argument : Si l'argument ne contient pas d'égal et n'est pas un nom de variable valide, cela peut être considéré comme une erreur.

c. Pas de nom avant l'égal (=) : L'argument =value est invalide car il n'y a pas de nom de variable avant le =.

d. Espace autour de l'égal (=) : Dans la plupart des shells, des espaces avant ou après le = ne sont pas autorisés. Ainsi, VAR = value est invalide.

Comportements supplémentaires:

a. Affichage de variables : Si vous utilisez export suivi d'un nom de variable sans =, cela affichera généralement la valeur de cette variable (dans certains shells comme bash).

b. Options : La commande export dans des shells plus complets peut aussi accepter des options (commençant généralement par -). Cependant, pour un minishell, vous pourriez ne pas avoir besoin d'implémenter ces options.

Quand vous implémentez la commande export dans votre minishell, assurez-vous de gérer correctement la validation des arguments et de renvoyer des messages d'erreur appropriés pour les cas d'erreurs mentionnés ci-dessus.

*/

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