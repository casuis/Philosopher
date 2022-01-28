# Philosopher
***

## This is my Project Philosopher for the 42 school


### Here is the global ideas of th programe:


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


### Execution


Pour compiler:
```
$ make
```

#### L'execution prend 4 arguments obligatoires:

* le nb de philossophe(s) présent(s)

* Le temps qu'un philosophe peut passer sans manger

* Le temps que prendra un philosophe pour manger

* Le temps que prendra un philosophe pour dormir

#### Il est aussi possible d'ajouter un dernier argument (optionnel)

* Le nombre de repas necessaire a un philosophe pour etre repus


L'exectuon ce presente comme ci-dessous:
```
$ ./philo [nb_philo] [temps_sans_manger] [temps_pour_manger] [temps_repos] (optionnel: [nb_de_repas])
```
