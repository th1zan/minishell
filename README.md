# Liens

- fichier excel de suivi: https://kdrive.infomaniak.com/app/office/511209/156120

# Ajout d'une fonctionnalité
1) Créer un nouveau répertoire `ma_fonction`sous `/src` et créer les fichiers `ma_fonction.c` nécessaires
2) Inscrire le nom et le chemin des nouveaux fichiers `ma_fonction.c` dans le Makefile
3) Créer un header `header_de_ma_fonction.h`dans `/header` et y inscrire les prototypes des fonctions
4) Ajouter le nom du header  `header_de_ma_fonction.h` dans le header principal `minishell.h`
# Structure du dossier

```
my_project/
|-- Makefile
|-- README.md
|-- .gitignore
|
|── src/
│   |── minishell.c                             #file with the main
│   |── minishell.h                             #"main" header file
│	|
│	|── header                                  #header folder
│	|	|- my_header_for_my_function.h          #header file
│	|	|- ...
│	|
│	|── my_function_folder
│	|	|── my_function.c
│	|	|- ...
│	|
│	|── other_function_folder_2
│	|	|── other_source_files.c
│	|	|- ...
│	|
│	|──libft/libft_source_files
│	|	|- printf                               #folder
│	|	|- getnextline                          #folder
│	|	|- other libft_fct                      #folders
│	|	|- ...
│	|	|- Makefile                             #makefile for libft
│	|	|- libft.h
│	|	|- libft.a
|
|
|-- ressources                                  #folder "dropbox"
	|-- eval
	|-- documentation
	|-- ...

```

