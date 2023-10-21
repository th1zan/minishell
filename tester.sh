#!/usr/bin/expect -f

# Chemin vers votre application minishell
set minishell "./minishell"

# Fichier contenant les commandes à exécuter
set infile "infile_cmd"

# Fichier où les sorties seront enregistrées
set outfile "output_file"

# Ouvrir le fichier pour lire les commandes
set fp [open $infile r]

# Lancer minishell
spawn $minishell

# Log all the output to a file
log_file -a $outfile; # -a appends instead of overwriting

# Attendre que minishell soit prêt
expect "minishell> "

# Lire et exécuter les commandes ligne par ligne
while {[gets $fp cmd] != -1} {
    # Envoyer la commande à minishell
    send -- "$cmd\r"
    # Attendre que la commande soit exécutée avant de continuer
    expect "minishell> "
}

# Fin de l'envoi des commandes, on envoie EOF (Ctrl+D)
send -- "\004"

# Fermer le fichier de commandes
close $fp

# Attendre que minishell se termine
expect eof
