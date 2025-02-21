# PROJET IA
*Dernier push est fonctionnel*

En collaboration avec Antoine Cossardeaux, Nathan Lamarre, Adrien Moreau

## Objectif du projet

Le but du projet était de créer une ou plusieurs IA, quelles soient ennemis ou alliés, avec comme contrainte d'utiliser des méthodes différentes qui sont :
- FSM
- BEHAVIOR TREE
- GOAP
- Et un PATHFINDING

## Répartition des méthodes :

Antoine Cossardeaux a utilisé le GOAP.
Tandis que Nahan Lamarre a utilisé le FSM.
Et pour Adrien Moreau qui a utilisé le FSM, un petit Behavior Tree et le Pathfinding.

## Description des ennemis

Chaque ennemis ont un comportement qui leurs sont propres.

L'IA d'Antoine utilisant le GOAP est un ennemi qui tir mais qui dispose d'un nombre de munition limitée et qui doit les recharger à un point spécifique.

L'IA de Nathan avec le FSM est un ennmi qui court partout et qui pose des ennemis. Qui est censé fuir le joueur une fois qu'il se trouve trop proche.

Et pour terminer, les IA d'Adrien dans un premier temps: FSM est une IA de patrouille. Inspiré de Metal Gear Solid.  Elle patrouille à des endroits prédéfinis. Peut entendre le joueur, l'apercevoir, le voir et repérer ses traces de pas. L'autre IA
utilisant le Behavior Tree est une caméra de sécurité très simpliste qui envoie une alerte aux autres ennemis si le joueur est détecté.

