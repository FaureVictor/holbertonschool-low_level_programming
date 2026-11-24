# Memory Maps

## Méthode
j'ai d'abord compilé les programmes avec "make" dans le dossier "programmes/".
Ensuite j'ai lancé "./stack_exemple" et "./aliasing_exemple", et executer valgrinde sur "./aliasing_exemple" pour verifier si il avait des erreur de mémoire.
Pour ce qui est de l'ia j'ai utiliser claude pour faire des cartes mémoires, je lui ai demandé : "peux tu faire une ou des cartes mémoire, fais en sortes qu'elle presente chaque étape du programme avec la pile, le tas, les pointeurs, les alias et leurs durées de vie".
Enfin j'ai verifier par la suite ce que L'IA m'a repondu


## 1. stack_example.c
Aucun `malloc` : le **tas reste vide**. Tout se passe sur la **pile**.

### Au point le plus profond (depth = 3)
| Cadre (sommet en haut) | Variables | Meurt à |
|------------------------|-----------|---------|
| dump_frame | depth=3, local_int=103, local_buf, p_local=&local_int | ligne 17 |
| walk_stack #3 | depth=3, marker=30 | ligne 30 |
| walk_stack #2 | depth=2, marker=20 | ligne 30 |
| walk_stack #1 | depth=1, marker=10 | ligne 30 |
| walk_stack #0 | depth=0, marker=0 | ligne 30 |
| main | — | fin du programme |

- Chaque appel de `walk_stack` a **son propre** `marker`. Les adresses diminuent quand `depth` augmente (la pile grandit vers le bas).
- `p_local` est un **alias** de `local_int` : les deux disparaissent au retour de `dump_frame`.
- Les cadres sont détruits dans l'ordre inverse : 3, 2, 1, 0.


## 2. aliasing_example.c

| Étape | Ligne | Pile (main) | Tas |
|-------|-------|-------------|-----|
| Début | 24-26 | a=NULL, b=NULL, n=5 | vide |
| Après make_numbers | 30 | a=BLOC_A | BLOC_A (20 octets) = [0,11,22,33,44] |
| Alias | 34 | a=BLOC_A, **b=BLOC_A** | même bloc, pas de copie |
| free(a) | 38 | a et b gardent BLOC_A → **pendants** | BLOC_A **libéré** |

### Accès après le free
| Ligne | Code | Erreur Valgrind |
|-------|------|-----------------|
| 42 | `b[2]` | Invalid read of size 4 (8 octets dans un bloc libéré de 20) |
| 44 | `b[3] = 1234` | Invalid write of size 4 (12 octets dans le bloc) |
| 45 | `b[3]` | Invalid read of size 4 |

- Pas de fuite : le bloc est libéré une fois.
- Le bug : utiliser `b` après `free(a)`, car `b` vise le même bloc.


## 3. Erreur de l'IA
première erreur de l'ia sur le nombre de blocs dans le tas
    l'ia demande et affirme : "Combien de blocs dans le tas ? 1 (BLOC_A, 20 octets)" ce qui est faux, valgrind affiche "2 allocs, 2 frees, 1.044 bytes allocated". 1024 = 1044. Le deuxième bloc est le tampon de 1024 octets créé par la bibliothèque C pour "printf" ce qui n'apparait pas dans le code l'ia l'a peut etre oublié.
    la correction est qu'il y'a 2 blocs dans le tas : le BLOC_A (20 octets, crée par "malloc" ligne 12) et le tampon de "printf" (1024 octets). Les deux sont libérés, donc il n'y a pas de fuite.
    pour verifier ça dans la sortie de "valgrind ./aliasing_example", la partie HEAP SUMMARY affiche "total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated".

deuxieme erreur de l'ia sur la valeur lue après le free
    l'ia dit : « La ligne 42 peut encore afficher 22, car l'ancienne valeur peut toujours être présente en mémoire. » là c'est incomplet car Sans Valgrind, le programme a affiché "reading b[2]=-1144611582". Après le "free", la glibc réutilise le début du bloc pour ses propres informations, et la case "[2]" (octets 8 à 11) a été écrasée. Sous Valgrind, on lit 22, parce que Valgrind ne réutilise pas les blocs libérés.
    pour la correction : La valeur lue après un "free" dépend de l'outil qui gère la mémoire, c'est un comportement qui est indéfini (donc que l'on ne peut rien prévoir).
    pour verifier ça, il faut comparer la sortie de "./aliasing_example" avec celle de "valgrind ./aliasing_example".