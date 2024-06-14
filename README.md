# Gestion des Interventions de Fibres Optiques

Ce projet implémente un programme en C pour gérer les interventions de fibres optiques.

Il permet de gérer des entreprises, de publier des missions, de consulter des missions disponibles,  
d'accepter des missions, de sous-traiter des missions, de créer des rapports de mission et de fournir des récapitulatifs de mission.

## Fonctionnalités

Le programme permet les opérations suivantes via des commandes saisies dans le terminal :

1. **inscription** : Inscription d'une entreprise.
2. **mission** : Publication d'une mission.
3. **consultation** : Consultation des missions disponibles.
4. **detail** : Affichage des détails d'une mission.
5. **acceptation** : Acceptation d'une mission par une entreprise.
6. **sous-traitance** : Sous-traitance d'une mission.
7. **rapport** : Création d'un rapport sur une mission.
8. **recapitulatif** : Affichage du récapitulatif des missions pour une entreprise donnée.
9. **exit** : Quitter le programme.

## Structure des Données

- `t_entreprise` : Structure représentant une entreprise avec un nom et un rôle (Opérateur, Agent, Installateur).
- `t_mission` : Structure représentant une mission avec plusieurs attributs tels que l'ID de l'opérateur, le nom de la mission, la rémunération, le niveau de sous-traitance, etc.
- `t_rapport` : Structure pour stocker les rapports des missions.

## Utilisation

### Commandes Disponibles

- `inscription` : Inscrire une nouvelle entreprise.
  - Saisir le rôle de l'entreprise (`OP`, `AG`, `IN`).
  - Saisir le nom de l'entreprise.
  
- `mission` : Publier une nouvelle mission.
  - Saisir l'ID de l'opérateur.
  - Saisir le nom de la mission.
  - Saisir la rémunération de la mission.

- `consultation` : Afficher toutes les missions disponibles.

- `detail` : Afficher les détails d'une mission.
  - Saisir l'identifiant de la mission.

- `acceptation` : Accepter une mission par une entreprise.
  - Saisir l'ID de l'entreprise acceptant la mission.
  - Saisir l'ID de la mission à accepter.

- `sous-traitance` : Sous-traiter une mission.
  - Saisir l'ID de l'entreprise sous-traitante.
  - Saisir l'ID de la mission à sous-traiter.
  - Saisir la nouvelle rémunération pour la sous-traitance.

- `rapport` : Créer un rapport sur une mission.
  - Saisir l'ID de la mission.
  - Saisir le code de retour (0 pour succès, 1 pour local non accessible, 2 pour pas de signal, 3 pour récepteur défectueux).

- `recapitulatif` : Afficher le récapitulatif des missions pour une entreprise.
  - Saisir l'ID de l'entreprise.

- `exit` : Quitter le programme.

  ## Notes
  Il s'agit du premier projet de développement de l'année, fait dans le cadre de ma première année de BUT Informatique.  
  On notera que tout le projet a été fait dans un seul et même fichier .c, et peut être divisé en plusieurs fichiers.  
  Tout est donc améliorable, il s'agit d'un projet de 1ère année.
  
  Vous pouvez exécuter le programme en utilisant un compilateur comme GCC.


