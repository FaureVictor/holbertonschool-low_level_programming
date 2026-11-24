# Valgrind Analysis

## 1. Méthode
J'ai d'abord compilé les programmes avec "make" dans le dossier "programs/".
Ensuite, j'ai lancé Valgrind sur "./heap_example" et "./aliasing_example" avec les options "--leak-check=full --show-leak-kinds=all --track-origins=yes", pour trouver les fuites, les lectures ou écritures interdites et l'utilisation de mémoire non initialisée.
Pour ce qui est de l'IA, j'ai utilisé Claude pour une première lecture des sorties de Valgrind. Je lui ai demandé : « Peux-tu m'expliquer chaque erreur de cette sortie Valgrind : son type, le bloc mémoire concerné et sa cause ? »
Enfin, j'ai vérifié chaque explication de l'IA avec le code et avec mes cartes mémoire du fichier "memory_maps.md".


## 2. heap_example

### Sortie Valgrind (extrait)
```
6 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at malloc
   by person_new (heap_example.c:21)
   by main (heap_example.c:51)
total heap usage: 5 allocs, 4 frees, 1,066 bytes allocated
```

### Analyse
| Point | Réponse |
|---|---|
| Type d'erreur | Fuite mémoire, **definitely lost** |
| Objet concerné | Le nom `"Alice"` : bloc de 6 octets dans le tas, créé ligne 21 pendant `person_new("Alice", 30)` (ligne 51) |
| Cause | `person_free_partial` (ligne 41) libère la structure `Person` sans libérer `p->name` avant |
| Terme précis | **Fuite par perte de propriété** (*leak due to lost ownership*) |

Le seul pointeur vers le nom était `alice->name`, rangé **dans** la structure.
Quand la structure est libérée, ce pointeur disparaît.
Plus aucun pointeur ne connaît le bloc de 6 octets : il ne peut plus être libéré.
Bob n'a pas de fuite : son nom et sa structure sont libérés (lignes 66 et 67).

Bilan des 5 blocs : 16 + 6 (Alice) + 16 + 4 (Bob) + 1024 (tampon de `printf`) = 1066 octets. 4 sont libérés, il manque le nom d'Alice.


## 3. aliasing_example

### Sortie Valgrind (extrait)
```
Invalid read of size 4   at main (aliasing_example.c:42)
Invalid write of size 4  at main (aliasing_example.c:44)
Invalid read of size 4   at main (aliasing_example.c:45)
Address ... is 8 / 12 bytes inside a block of size 20 free'd
Block was freed at main (aliasing_example.c:38)
Block was alloc'd at make_numbers (aliasing_example.c:12)
```

### Analyse
| Ligne | Type | Objet | Cause |
|---|---|---|---|
| 42 | Invalid read (4 octets) | case `[2]` du bloc de 20 octets | lecture par `b` après `free(a)` |
| 44 | Invalid write (4 octets) | case `[3]` du même bloc | écriture par `b` après `free(a)` |
| 45 | Invalid read (4 octets) | case `[3]` du même bloc | lecture par `b` après `free(a)` |

Terme précis : **use-after-free** par un **pointeur pendant**.
`b = a` (ligne 34) copie seulement l'adresse : `a` et `b` visent le même bloc.
`free(a)` (ligne 38) termine la vie du bloc, donc `b` devient pendant lui aussi.
Pas de fuite : `All heap blocks were freed`.

---

## 4. Mémoire non initialisée
Aucun message `uninitialised value` dans les deux sorties, malgré `--track-origins=yes`.
Ces programmes ne lisent aucune variable sans valeur.

---

## 5. Erreur de l'IA
erreur de l'ia sur la mémoire non initialisée
    l'ia affirme : "Ces programmes ne lisent aucune variable sans valeur." ce qui est trop fort, car Valgrind ne vérifie que le chemin que le programme a vraiment suivi. Par exemple, les lignes 54 à 61 de "heap_example.c" (le cas où un "malloc" échoue) n'ont jamais été exécutées, donc Valgrind ne peut rien dire sur elles. En plus, Valgrind ne signale une valeur non initialisée que lorsqu'elle change le comportement du programme (une condition, un affichage ou un appel système). Copier une valeur non initialisée dans une autre variable ne déclenche aucun message.
    la correction est : "Pendant cette exécution, Valgrind n'a détecté aucune utilisation de valeur non initialisée." L'absence de message n'est pas une preuve absolue.
    pour vérifier ça, il faut lire la partie "Use of uninitialised values" du manuel de Memcheck (Valgrind), et regarder dans le code que les lignes 54 à 61 ne sont jamais atteintes quand les "malloc" réussissent.