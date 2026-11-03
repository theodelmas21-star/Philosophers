This project has been created as part of the 42 curriculum by <tdelmas2>.
Description

Le projet Philosophers est une introduction à la programmation concurrente en C, basée sur le célèbre problème des philosophes formulé par Edsger Dijkstra.

L’objectif est de simuler plusieurs philosophes assis autour d’une table, alternant entre trois états :

manger
dormir
réfléchir

Chaque philosophe a besoin de deux fourchettes pour manger, ce qui crée des problématiques classiques de concurrence :

race conditions
deadlocks
starvation

Le projet consiste à implémenter une solution robuste utilisant :

les threads POSIX (pthread)
les mutex pour protéger les ressources partagées

Le programme doit garantir :

l’absence de deadlock
une gestion correcte du temps (time_to_die, time_to_eat, time_to_sleep)
la détection de la mort d’un philosophe

Instructions :

Compilation
make
Exécution
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Exemple :
./philo 5 800 200 200

Paramètres :
number_of_philosophers : nombre de philosophes
time_to_die : temps maximum sans manger (en ms)
time_to_eat : durée d’un repas
time_to_sleep : durée du sommeil
[optional] number_of_times_each_philosopher_must_eat : nombre de repas requis

Concepts clés :
Multithreading avec pthread
Mutex pour la synchronisation
Gestion du temps précise (timestamp)
Prévention des deadlocks
Gestion de la starvation (non obligatoire mais observable)

L'intelligence artificielle a ete utilise 
comme aide pour ecrire ce Readme.

Choix techniques :
Un thread par philosophe
Un mutex par fourchette
Un mutex global pour l’écriture (éviter les outputs mélangés)
Surveillance via un thread dédié (monitor)
Horodatage basé sur gettimeofday

Resources :
Documentation & articles
Codequoi - Threads, Mutex et Programmation Concurrente en C
Utilisé pour comprendre :
la création de threads (pthread_create)
l’utilisation des mutex
les bases de la synchronisation
Dining Philosophers in C: From Theory to Practice (Medium)
Utilisé pour :
comprendre l’architecture globale du projet
visualiser différentes stratégies d’implémentation
mieux appréhender les problèmes de starvation