/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanglar <tsanglar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 13:27:26 by mlachat           #+#    #+#             */
/*   Updated: 2023/10/04 17:34:36 by tsanglar         ###   ########.fr       */
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
			if (tmp_env[j + 1] && tmp_env[j + 1] == '=' && (var_name[j + 1] == 0 || var_name[j] == '='))
			{
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

	new_var = ft_strdup("");
	while(tk->tk_arg)
	{
		tmp = ft_strjoin(new_var, tk->tk_arg->tk_str);
		free(new_var);
		new_var = tmp;
		tk->tk_arg = tk->tk_arg->next;
	}
	
	return new_var;
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

	env = *(tk->env);
	target_var = concat_args(tk); // Supposons que cette fonction crée la variable à supprimer à partir du token
	index = find_env_var(env, target_var);
	printf("index: %d/n", index);
	// Si la variable n'existe pas, on termine la fonction sans rien faire
	if (index == -1)
	{
		free(target_var); // N'oubliez pas de libérer la mémoire si elle n'est pas utilisée
		return (0);
	}

	// 3) Si elle existe, supprime la variable du tableau
	// free(env[index]);

	i = 0;
	while (env[i] != NULL) i++;

	new_env = malloc(i * sizeof(char*)); // -1 car on supprime une variable, mais pas besoin d'ajouter pour NULL car i compte déjà NULL

	j = 0;
	k = 0;
	while (j < i)
	{
		if (j == index) // si on arrive à l'index de la variable à supprimer, on saute cette entrée
		{
			j++;
			continue;
		}
		new_env[k] = env[j];
		j++;
		k++;
	}
	new_env[k] = NULL;  // termine le tableau avec NULL

	free(env); // libère l'ancien tableau
	*(tk->env) = new_env; // met à jour le pointeur env pour pointer vers le nouveau tableau

	free(target_var); // N'oubliez pas de libérer la mémoire de target_var

	return (1); // Tout s'est bien passé
}


int export(t_tk *tk)
{
	char	**env;
	char	*new_var;
	int		index;
	int		i;
	char	**new_env;

	env = *(tk->env);
	
	// 1) Si pas d'argument, alors appelle la fonction env.
	if (tk->tk_arg == 0)
	{
		env_built_in(tk);
		return (0);
	}

	new_var = concat_args(tk);// Supposons que cette fonction crée la nouvelle variable à partir du token

	// 2) et 3) Vérifie si new_var existe et si existe, donne la ligne du tableau
	index = find_env_var(env, new_var);
	// printf("existe index: %d\n", index);

	// 4) Si existe alors change la string dans le tableau et libère l'ancienne
	if (index != -1)
	{
		free(env[index]); // libère l'ancienne string
		env[index] = new_var; // remplace par la nouvelle string
	}
	else
	{
		// 5) Si non, dimensionne nouveau tableau et ajoute une ligne pour la nouvelle variable
		i = 0;
		while (env[i] != NULL) i++;

		new_env = malloc((i + 2) * sizeof(char*)); // +1 pour la nouvelle variable et +1 pour NULL

		for (int j = 0; j < i; j++)
		{
			new_env[j] = env[j];
		}
		new_env[i] = new_var; // ajoute la nouvelle variable
		new_env[i+1] = NULL;  // termine le tableau avec NULL

		// free(env); // libère l'ancien tableau
		*(tk->env) = new_env; // met à jour le pointeur env pour pointer vers le nouveau tableau
	}

	return (1); // Tout s'est bien passé
}



int	env_built_in(t_tk *tk)
{
	if(*(tk->env) == 0)
		return(1);
	printf("env :: *(tk->env): %p\n" ,*(tk->env));
	print_strtab(*(tk->env));
	return(0);
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