Projet OpenGL
=============

Pour ce projet j'ai choisi comme sujet une sonde MALP de l'univers de Stargate.
C'est un objet que j'ai modélisé et texturé moi-même avec 3D Studio Max il y a
quelques années pour un mod Half-Life 2 nommé Garry's Mod.

Format des objets
-----------------

Tous mes objets sont stockés dans des fichiers au format OBJ et les informations des
matériaux et textures sont stockées à part dans des fichiers MTL.

Il y a plus d'information sur la [page Wikipedia du format OBJ](http://fr.wikipedia.org/wiki/Objet\_3D\_\(format\_de\_fichier\)).

J'ai bien sûr codé moi même la partie qui interprète ces fichiers, stocke les informations contenues
à l'intérieur et appelle les instructions OpenGL correspondantes.

Je n'implémente pas toutes les fonctionnalités de ce format. Par exemple pour les objets, je ne tiens
pas compte des groupes (g) et des smoothing groups (s). Pour les matériaux je ne gère que les paramètres
correspondants à ambiant (Ka), diffuse (Kd), specular (Ks), emission (Ke), brillance (Ns) et
le chemin de la texture si il y en a une pour ce matériau (map\_Ka).

Pour les textures, j'ai décidé d'utiliser le format PNG car il est assez répandu. J'utilise un loader nommé LodePNG.
Son avantage est qu'il ne dépend de rien, j'ai juste à inclure deux fichiers dans mon projet. Il charge les fichiers PNG
et me renvoie un tableau de char contenant mon image. Par contre je dois l'inverser moi-même car OpenGL les charge à l'envers.

Description de la scène
-----------------------

Ma scène est divisée en deux "mondes" séparés par une porte des étoiles traversable par le sujet et la caméra.
Ces deux mondes (un désert de jour et une plaine de nuit) ont la même largeur, longueur et hauteur (30 * 30 * 15).

L'un est centré en (0, 0, 0) et l'autre en (0, 0, -30), donc pour tester si un objet ou la caméra se trouve 
d'un coté ou de l'autre je vérifie simplement si sa coordonnées Z est supérieure ou inférieure à -15
(plus ou moins quelques dixièmes en fonction des besoins)

Je gère le "passage" à travers la porte par une simple condition dans la détection de collision du bord de la scène :
X compris entre -2 et 2 et Y compris entre 0 et 3.3, ce qui correspond approximativement à la taille de la porte.

J'ai également modélisé la plupart des autres objets à l'aide de 3D Studio Max. Par contre j'ai créé la plupart
des matériaux moi-même, notamment celui de la porte des étoiles.

Déplacements et contrôles
-------------------------

On peut contrôler la caméra à la manière d'un FPS en maintenant enfoncé le bouton gauche de la souris.
Elle se déplace en utilisant les touches Z Q S D (respectivement avancer, aller à gauche, reculer, aller à droite)

Le sujet est quant à lui contrôlable à l'aide des touches directionnelles. Il dispose également des actions suivante :

* R / Shift+R : plier/déplier la première partie du bras articulé
* T / Shift+T : plier/déplier la deuxième partie du bras
* Y / Shift+R : faire tourner à droite/gauche la deuxième partie du bras
* U / Shift+U : ouvrir/fermer la pince à l'extrémité du bras

Les touches suivantes sont également disponibles :

* L : allumer/éteindre les lumières colorées dans le temple (après la porte des étoiles)
* C : passer la caméra en mode "subjectif" (en réappuyant sur C, la caméra redevient "libre")
* Espace : remettre la caméra au point de départ
* Echap : quitter le programme

Rôle des classes
----------------

* Point, Vector, Angle : Contiennent des méthodes utiles en général
* Application : Instanciée une seule fois par exécution. Met en place GLUT et instancie un objet Scene
* Scene : Contient la boucle de modélisation et la gestion des évènements clavier. C'est elle qui créé et appelle leur méthode de dessin
* Object : Classe abstraite décrivant un objet pouvant être affiché dans la scène
* Mesh : Sous-classe d'Object, elle décrit un objet constitué de sommets et de faces. C'est elle qui charge les fichiers objets
et les affiche
* Face : Décrit une face avec les index des sommets et des normales la constituant dans les tableaux de l'objet Mesh. Contient également
les coordonnées de texture et le matériau qui lui sera appliqué
* Material : Contient les informations sur un matériau (ambiant, diffuse, specular, ...) ainsi que le fichier de texture correspondant
le cas échéant. C'est elle qui charge les textures en mémoire
* Light : Décrit une lumière dans la scène (position, couleur, ...) et contient des méthodes permettant de l'allumer ou de l'éteindre
* MALP et Stargate : Sous-classes de Object qui instancient seulement des objets Mesh et les positionnent correctement dans l'espace
(pour séparer le dessin du MALP et de la porte et rendre le code plus lisible, ainsi que pour pouvoir facilement faire la réplique)