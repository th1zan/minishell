https://projects.intra.42.fr/projects/42cursus-minishell

## Liens bon exemple
https://github.com/widium/Minishell
https://github.com/widium/pipex

## Lien théorie

- language shell: https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
- cours sur création d'un minishell: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- manuel de bash sur les pipes:https://www.gnu.org/software/bash/manual/bash.html#Pipelines "https://www.gnu.org/software/bash/manual/bash.html#Pipelines
- manuel de bash sur le Here document: https://www.gnu.org/software/bash/manual/bash.html#Here-Documents "https://www.gnu.org/software/bash/manual/bash.html#Here-Documents
- redirection characters in C: https://www.ibm.com/docs/en/aix/7.2?topic=shell-input-output-redirection-in-c


## Tips depuis le discord 42 (bronx)

- readline ? [https://tiswww.case.edu/php/chet/readline/readline.html](https://tiswww.case.edu/php/chet/readline/readline.html "https://tiswww.case.edu/php/chet/readline/readline.html") `#include <readline/readline.h>`
- `valgrind --leak-check=full --track-origins=yes ./minishell` ,  autrement `-fsanitize=address` sous linux et/ou dans un container linux
- [https://github.com/theo-grivel/42-minishell/blob/main/doc/parsing.md](https://github.com/theo-grivel/42-minishell/blob/main/doc/parsing.md "https://github.com/theo-grivel/42-minishell/blob/main/doc/parsing.md")
- [https://man7.org/linux/man-pages/man3/cfsetspeed.3.html](https://man7.org/linux/man-pages/man3/cfsetspeed.3.html "https://man7.org/linux/man-pages/man3/cfsetspeed.3.html")
- un bon tuto pour comprendre comment ça se passe en interne quand on manipule les fichiers/pipes [http://tzimmermann.org/2017/09/01/the-internals-of-unix-pipes-and-fifos/](http://tzimmermann.org/2017/09/01/the-internals-of-unix-pipes-and-fifos/ "http://tzimmermann.org/2017/09/01/the-internals-of-unix-pipes-and-fifos/")
 a lire avant: 1 - [http://tzimmermann.org/2017/07/28/data-structures-of-unix-file-io/](http://tzimmermann.org/2017/07/28/data-structures-of-unix-file-io/ "http://tzimmermann.org/2017/07/28/data-structures-of-unix-file-io/") 2 - [http://tzimmermann.org/2017/08/04/unix-hard-links-soft-links-and-files/](http://tzimmermann.org/2017/08/04/unix-hard-links-soft-links-and-files/ "http://tzimmermann.org/2017/08/04/unix-hard-links-soft-links-and-files/") 3 - [http://tzimmermann.org/2017/08/17/file-descriptors-during-fork-and-exec/](http://tzimmermann.org/2017/08/17/file-descriptors-during-fork-and-exec/ "http://tzimmermann.org/2017/08/17/file-descriptors-during-fork-and-exec/")
- [http://www.zeitoun.net/articles/communication-par-tuyau/start](http://www.zeitoun.net/articles/communication-par-tuyau/start "http://www.zeitoun.net/articles/communication-par-tuyau/start")
- `tcsetattr, tcgetattr` permettent d'interagir avec les structures termios -> On les a utilisé pour un cas: afficher ou non les caractères de contrôles (quand tu appuies sur Ctrl + C par exemple).
- Si jamais instruments (app installe sur les macs) est aussi pratique pour trouver d'ou viennent les leaks
- man de `export` . `Export` est un subsection de POSIX specification, je crois pas que ce soit dispo sur les ordis, tu peux regarder ici [https://www.man7.org/linux/man-pages/man1/export.1p.html](https://www.man7.org/linux/man-pages/man1/export.1p.html "https://www.man7.org/linux/man-pages/man1/export.1p.html")
- Voici un article qui m'a bien aidé à commencer le projet et à identifier les différentes parties à implémenter: [https://medium.com/@mohammedisam2000/lets-build-a-linux-shell-part-i-954c95911501](https://medium.com/@mohammedisam2000/lets-build-a-linux-shell-part-i-954c95911501 "https://medium.com/@mohammedisam2000/lets-build-a-linux-shell-part-i-954c95911501")
- [https://github.com/baku00/42_minishell](https://github.com/baku00/42_minishell "https://github.com/baku00/42_minishell")
-  Oui, la version de readline installée sur nos sessions n'est pas à jour. Tu peux installer une nouvelle version avec `brew install readline`. Dans ton Makefile, tu spécifies avec le flag -I le dossier où se trouvent les headers de readline et avec -L le dossier où se trouve la librairie. Brew te dit où il installe readline. (modifié)
-  Le sujet dit qu'en cas de doute il faut se référer à bash. Il est quasi impossible de reproduire exactement tous les comportements, mais l'idée c'est de s'en rapprocher le plus possible. Je te conseille de bien étudier les messages d'erreurs de bash justement, pour mieux comprendre comment bash fonctionne. A mon avis, les choses qu'il faut gérer sont:
    
    - une commande ou un fichier n'est pas trouvé
    - une commande ou un fichier n'est pas accessible pour une autre raison (par exemple: _Permission denied_ ou _Too many levels of symbolic links_)
    - erreurs de syntaxe
    - erreurs dans les builtins (par exemple: donner trop d'arguments à exit ou essayer d'exporter des noms de variable invalides)
    
    Les choses qu'il serait mieux de gérer:
    
    - Protéger tous les appels tels que `fork()` ou `pipe()` ou `dup()` et absolument tous les `malloc()`
    - Redirections ambigües (`< *` ou `>> $VAR` si VAR est vide ou composé de plusieurs mots))
    - ...
    
    Après, minishell est un projet tellement complexe que la plupart des évaluateurs ne compteraient pas faux s'il y a une ou deux imprécisions dans les messages d'erreurs, mais plutôt l'accumulation des erreurs. (modifié)
    

## Videos 42
https://elearning.intra.42.fr/notions/66/subnotions/261/videos/208
https://elearning.intra.42.fr/notions/27/subnotions/929/videos/1020
https://elearning.intra.42.fr/notions/57/subnotions/245/videos/203