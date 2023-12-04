# Obfuscated CrackMe

<!-- TODO: Rajouter les techniques d'obfuscation que vous avez implémentées dans la présentation -->

## Table of contents

- [Obfuscated CrackMe](#obfuscated-crackme)
  - [Table of contents](#table-of-contents)
  - [Presentation](#presentation)
  - [Control Flow obfuscation](#control-flow-obfuscation)
  - [Plan fonctions raph adds](#plan-fonctions-raph-adds)
  - [Deadcode](#deadcode)
  - [Encrypted Obfuscation](#encrypted-obfuscation)
  - [Time Based Password](#time-based-password)
  - [pTrace](#ptrace)
  - [Options gcc](#options-gcc)
  - [Pistes d'amélioration](#pistes-damélioration)
  - [Resolution BASH command](#resolution-bash-command)

## Presentation

Élaboration un "crackme" éducatif, un défi de reverse engineering, où l'exécutable affiche "OK\n" sur STDOUT et retourne zéro lorsque le bon mot de passe est entré.

- Exigences de l'exécutable
  - Livrable :  un exécutable ELF pour Linux x64, avec une taille maximale de 16KB.
  - Le fichier binaire doit un script ./BUILD.sh doit le compiler indépendamment.
- Spécification du CrackMe
  - Le mot de passe doit être passé via `argv[1]` OU `argv[2]` OU `argv[1] et argv[2]`.
  - L'exécutable doit afficher "OK\n" sur STDOUT et retourner zéro si le mot de passe est correct.
  - Doit fonctionner sur toute distribution Linux moderne AMD64
- Techniques d'obfuscation (objectif 4) :
  - [Control Flow obfuscation](#Method1)
  - [Encrypted Obfuscation](#Method2)
  - [Time Based Password](#time-based-password)
  - [pTrace](#ptrace)
  - fonction and variable name randomised
- Ethique
  - Aucun comportements malveillants dans l'exécutable.

## Control Flow obfuscation

L'objectif de cette méthode d'obfuscation est de générer des comportements perturbateurs dans le code.
[Présentaion de la méthode](./Control_Flow_Obfucation.c)

## Plan fonctions raph adds

- [function001](./fonctionsASM/my_func001.s) -> inutile
- [function002](./fonctionsASM/my_func002.s) -> chaine de caractère "crack_en"
- [function003](./fonctionsASM/my_func003.s) -> inutile
- [function004](./fonctionsASM/my_func004.s) -> chaine de caractère "$ε₳₹¢hHι̇d€η₭e¥₣or₮he₩i₦" -> search hiden key for the win . Arg1 contient la clé et arg2 contient une fausse clé
- [function005](./fonctionsASM/my_func005.s) -> caractère changeant chaque minute (offset 0x20)
- [function006](./fonctionsASM/my_func006.s) -> inutile
- [function007](./fonctionsASM/my_func007.s) -> Xor encrypt
- [function008](./fonctionsASM/my_func008.s) -> inutile
- [function009](./fonctionsASM/my_func009.s) -> récupération du répertoire HOME
- [function011](./fonctionsASM/my_func011.s) -> caractère changeant chaque minute (offset 0x43)
- [function012](./fonctionsASM/my_func012.s) -> my_strcmp
- [test_bloc1](./fonctionsASM/test_blk1.s) -> my_strcmp
- [test_bloc2](./fonctionsASM/test_blk2.s) -> my_strcmp
- [test_bloc3](./fonctionsASM/test_blk3.s) -> my_strcmp



## Deadcode

[function015](./enzo_adds/my_func015.s) -> fonction strcmp avec deadcode


## Encrypted Obfuscation

Pour réussir le CrackMe, les utilisateurs devront retrouver le code crypté et sa méthode de cryptage pour valider le challenge.
[Présentaion de la méthode](./Encrypted_Obfuscation.c)

## Time Based Password

Cette méthode permet de changer le mot de passe en fonction de l'heure d'execution.
[Présentaion de la méthode](./Time_changing_password.c)

## pTrace

Cet appel système est utilisé par tous les debugger sous Linux. 
Pour vérifier si un debugger est en train d'être utilisé sur notre CrackMe, il suffit de faire un appel à ce dernier au début de notre programme : 
  - S'il renvoi une erreur (-1), alors il y a un debugger (exemple: gdb) qui est utilisé et le programme devra s'interrompre
  - S'il renvoi autre chose, le porgramme n'est pas en cours de debuggage et peut donc être utilisé normalement

## Options gcc

Pour dissimuler des techniques d'obfuscation, on pourrait utiliser les options d'optimisation -02 et -03 : 

```powershell
gcc -O2 -o votre_programme votre_source.c
```
et
```powershell
gcc -O3 -o votre_programme votre_source.c
```

## Pistes d'amélioration

- Obfuscation de Contrôle de Flux: Modifiez la structure de contrôle du programme pour la rendre moins linéaire et plus difficile à suivre. Par exemple, l'utilisation de sauts indirects, de tables de sauts, ou l'insertion de code mort. (A améliorer)

- Obfuscation des Données: Changez la façon dont les données sont stockées et utilisées. Par exemple, utiliser des encodages personnalisés pour les chaînes de caractères ou diviser des variables en plusieurs morceaux stockés séparément.

- Cryptage de Chaînes: Les chaînes de caractères peuvent être cryptées dans le code binaire et déchiffrées en temps réel lors de l'exécution. Cela rend difficile la compréhension du but de certaines parties du code sans exécuter le programme. (A améliorer)

- Incorporation de Code Auto-Modifiant: Le code qui modifie son propre comportement en cours d'exécution peut semer la confusion et compliquer le reverse engineering.

- Utilisation de Macros et de Fonctions Inline Complexes: L'utilisation intensive de macros et de fonctions inline peut rendre le code source visuellement complexe et difficile à suivre.

- Anti-Debugging et Anti-Tampering: Des techniques telles que la vérification de l'intégrité du code ou l'introduction de routines de détection de débogage peuvent rendre l'analyse plus compliquée.

- Packers et Compresseurs: Utiliser des packers ou des compresseurs pour réduire la lisibilité du code binaire. Cependant, des outils comme Ghidra sont souvent capables de décompresser ou de déballer ces programmes.


## Resolution BASH command

```bash
./your_program $(minute=$(date +"%M") && hex1=$(printf "%x\n" "$((${minute#0} + 0x20))") && hex2=$(printf "%x\n" "$((${minute#0} + 0x43))") && echo -e "crack_en\x$hex1$HOME\x$hex2"
```