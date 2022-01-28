# Philosopher

_Voici mon projet "Philosopher" pour l'école 42_




## Idée Global:


One or more philosophers sit at a round table:


* The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.

* There are also forks on the table. There are as many forks as philosophers.

* Philosopher takes their right and their left forks to eat, one in each hand.

* The simulation stops when a philosopher dies of starvation.

* Every philosopher needs to eat and should never starve.

* Philosophers don’t speak with each other.

* Philosophers don’t know if another philosopher is about to die.

* Philosophers should avoid dying



## Execution


### Compilation:

```
$ make
```


### L'execution prend 4 arguments obligatoires:


1. le nb de philossophe(s) présent(s)

2. Le temps qu'un philosophe peut passer sans manger

3. Le temps que prendra un philosophe pour manger

4. Le temps que prendra un philosophe pour dormir



### (optionnel) Il est aussi possible d'ajouter un dernier argument 


* Le nombre de repas necessaire a un philosophe pour etre repus

```
$ ./philo [nb_philo] [temps_sans_manger] [temps_pour_manger] [temps_repos] (optionnel: [nb_de_repas])
```

***
