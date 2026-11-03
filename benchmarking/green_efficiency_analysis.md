## methodologie :
|
|	Pour mesurer les temps de ses programmes il a d'abord fallu importer la bibliotheque " <time.h> "
|	Premierment dans le programme " baseline_loop " on a mesurer 3 fois le temps que mets un fichier a s'executer et donner un reponse afin d'avoir une idee de base sur la maniere d'utiliser le chronometrage et comprendre comment ca fonctionne
|	on a vu que " clock_t " viens en quelques sortes cree la variable du temps ensuite " start = clock() " commence a partir d'un moment donne©un timer et " end = clock() " y mets fin et renvoie la valeur du temps mesurer en ticks 
|	c'est pour ca que l'on utilise juste apres " CLOCKS_PER_SEC " qui convertis les ticks par seconde en seconde.

## Observations parformances et differences :
|
|	Au cours du projet on a pu comparer deux vitesse de deux programmes programmes differents : une mesure sur une la methode Naive (avec 3 lancements) et une autre mesure sur la methode Single-pass (avec 3 lancements)
|	sans s'Ã©taller sur les dÃ©tails et valeurs exacte, en moyenne la methode Naive mets 2.9 secondes a s'executer tandis que le methode Single-pass mets elle 0.0001 seconde a s'executer, elle est environ 26 500x plus rapide.

## Relations entre duree d'execution et consommation d'energie :
|
|	Ici le principe c'est que plus un ordi (ou plus directement le CPU) vas travailler, plus il vas consommer de ressources et donc en gaspiller, c'est pourquoi si il arrive a faire la meme chose mais de maniere plus rapide et efficace il est possible
|	d'economiser de l'energie et meme du temps.

## Limite des exercices :
|
|	Le probleme qui me vient le plus en tete et qui viens freiner un peu ces experimentations c'est que j'ai effectuer ses mesures dans la sandbox, donc dans un environement qui fait tourner pas que sur une machine dediee, c'est un environement qui est 
|	partagee il ne serait alors pas surprenant que il y ait de la latences dans les reponses et donne des resultats qui differerait des vrais en temps normal sur une machine singuliere 

## Enseignement pratique en ingenierie :
|
|	Le plus intelligent pour un ingenieur est donc de faire le programme le plus rapide et efficace possible afin que l'ordinateur ai le moins de chose a calculer et qui pourrait s'acumuler, un code plus rapide occupe moins le processeur.
