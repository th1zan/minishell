# Liens

- fichier excel de suivi: https://kdrive.infomaniak.com/app/office/511209/156120
- 
# Structure du dossier

```
my_project/
|-- Makefile
|-- README.md
|-- .gitignore
|
|── src/
│   |── main.c
│   |── minishell.h                             #"main" header file
	|
	|── header                                  #header folder
	|	|- minishel_function_header_1           #header file
	|	|- minishel_function_header_2           #header file
	|	|- ...
	|
	|── minishel_function_folder_1
	|	|── other_source_files.c
	|	|- ...
	|
	|── minishel_function_folder_2
	|	|── other_source_files.c
	|	|- ...
	|
	|──libft/libft_source_files
	|	|- printf                               #folder
	|	|- getnextline                          #folder
	|	|- other libft_fct                      #folders
	|	|- ...
	|	|- Makefile                             #for libft
	|	|- libft.h
|
|
|── obj/
│   |── all_object_files.c
|
|-- ressources                                  #folder 
	|-- eval
	|-- documentation
	|-- ...

```

