# Philosopher
[![jaeskim's 42Project Score](https://badge42.herokuapp.com/api/project/asimon/Philosophers)](https://github.com/JaeSeoKim/badge42)

_Voici mon projet Philosopher pour l'école 42 - 2022_




## Idée Global


One or more philosophers sit at a round table:


* Each philosopher should be a thread.

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


1. le nb de philosophe(s) présent(s)

2. Le temps qu'un philosophe peut passer sans manger

3. Le temps que prendra un philosophe pour manger

4. Le temps que prendra un philosophe pour dormir



### (optionnel) Il est aussi possible d'ajouter un dernier argument 


* Le nombre(s) de repas necessaire(s) a un philosophe

```
$ ./philo [nb_philo] [temps_sans_manger] [temps_pour_manger] [temps_repos] (optionnel: [nb_de_repas])
```

#### Idées de tests


* Pour faire mourir un philosophe:
```
$ ./philo 4 310 200 100 
```

* Pour les faires manger indefiniments
```
$ ./philo 4 410 200 200
```

* Pour permettre a un philosophe manger a sa faim
```
$ ./philo 4 410 200 200 5
```

***

## Ressources


Pour verifier les datas races et autres messages d'erreurs:
```
$> valgrind --tool=helgrind ./philo [args]
```

Valgrind ralentit le programme, dans certains cas ou le programme n'aurai pas le temps de tourner assez longtemps (1 tour et le philo meurt), je vous consceil de tester avec:
```
$> clang -Wall -Wextra -Werror -fsanitize=thread -g3
```
L'option 'thread'sur fsanitize est moins precise que valgrind mais le ralentit moins, cela vous permettra une seconde verification de votre programme.

