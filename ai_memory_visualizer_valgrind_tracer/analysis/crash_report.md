# Crash Report — crash_example

## 1. Description du crash
J'ai compilé avec "make" puis lancé "./crash_example". Le programme affiche ses deux premières lignes, puis "Segmentation fault (core dumped)". La commande "echo $?" affiche 139, c'est-à-dire 128 + 11 : le programme a été tué par le signal 11 (SIGSEGV).
Valgrind affiche "Invalid write of size 4" à la ligne 32 ("nums[0] = 42"), à l'adresse 0x0, avec le message "Address 0x0 is not stack'd, malloc'd or (recently) free'd".

## 2. Cause racine
La cause n'est pas le segfault lui-même : le segfault est seulement la conséquence finale.
La vraie cause est que `main` utilise la valeur de retour de `allocate_numbers` sans vérifier si elle vaut NULL.

## 3. Chaîne complète
1. Ligne 25 : `n` vaut 0.
2. Ligne 30 : `main` appelle `allocate_numbers(0)`.
3. Ligne 9 : le test `n <= 0` est vrai, la fonction renvoie NULL à la ligne 10. Le `malloc` de la ligne 12 n'est jamais exécuté, donc aucun bloc n'est créé dans le tas.
4. Ligne 30 : `nums` reçoit NULL.
5. Ligne 32 : `nums[0] = 42` écrit 4 octets (un int) à l'adresse NULL + 0 = 0x0.
6. L'adresse 0x0 n'appartient pas au programme : le processeur bloque l'accès et le système envoie SIGSEGV. La ligne 34 n'est jamais exécutée.

## 4. Pourquoi l'accès est invalide
Pile ou tas : ni l'un ni l'autre. La variable `nums` est sur la pile (cadre de `main`), mais l'adresse qu'elle contient (0x0) ne correspond à aucun bloc du tas et à aucune variable de la pile.
L'adresse 0 n'est jamais attribuée à un programme : c'est volontaire, pour que les accès par un pointeur NULL plantent tout de suite.
Catégorie de comportement indéfini : **déréférencement d'un pointeur NULL** (règle CERT EXP34-C).
Remarque : Valgrind affiche aussi "still reachable: 1,024 bytes". Ce n'est pas le tableau du programme (aucun malloc n'a eu lieu), c'est le tampon de `printf`, jamais libéré parce que le programme a été tué avant la fin.

## 5. Critique des propositions de l'IA
J'ai demandé à Claude les causes et les corrections possibles du crash.

cause proposée par l'ia : "le malloc a échoué par manque de mémoire"
    c'est faux, car avec n = 0, la fonction allocate_numbers s'arrête à la ligne 10 (return NULL), avant le malloc de la ligne 12.
    pour vérifier ça, Valgrind affiche "total heap usage: 1 allocs", et ce seul bloc est le tampon de 1024 octets de printf. Le malloc de la ligne 12 n'a donc jamais été appelé.

## 6. Correction suggérée (optionnelle)
Vérifier la valeur de retour dans `main` avant la ligne 32 : si `nums` vaut NULL, afficher une erreur et quitter le programme au lieu d'écrire dedans.