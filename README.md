Projet Brigitte Friand
=

Contexte
--

Le dépôt contient une partie du challenge 2020 de cybersécurité de la DGSE : le projet Brigitte Friang. Plus précisément, le dépôt contient une partie de la branche Blaise Pascal du challenge (algorithmique, cracking). Il est codé en C et réalisé par Clément Préaut.
[Lien vers la description du défi](https://www.defense.gouv.fr/dgse/tout-le-site/operation-brigitte-friang-prets-pour-relever-le-defi).

Fonctionnalités
---

Le dépôt comporte trois aspects :

* Un décryptage de l'énoncé crypté présent dans `enonce/code`.
* Une extraction d'informations contenues dans un fichier altéré (`enonce_pascal/txt/intercepte.txt`) à partir du fichier original (`enonce_pascal/txt/original.txt`). Après investigations, les données récoltées correspondent aux données d'une image JPEG, affichée grâce à `enonce_pascal/blaise.html`. Cette image donne une complétion d'adresse web qui permet de continuer le challenge.
* Une résolution de problème d'optimisation dont l'énoncé se trouve dans `stock/IMPORTANT.pdf`. L'éxécutable créé permet de résoudre les 4 instances du problème fournies dans les fichiers `stock/fichier_<lettre>_<adjectif>.in`.

Instructions
---

* `./exec.sh` : Cette commande suffit à lancer l'ensemble des fonctionnalités. D'abord, elle compile l'ensemble du projet. Ensuite, le script affiche à l'écran l'énoncé décodé. Après cela, le script éxcute la deuxième fonctionnalité et affiche l'image résultat grâce à firefox. Enfin, le script éxécute la troisième fonctionnalité en ouvrant une interface permettant de choisir par une lettre dans [a-d] quelle instance du problème l'utilisateur souhaite résoudre.

* `[a-d]` : lors de L'éxécution de `exec.sh`, permet de choisir l'instance du problème à résoudre.

* `stop` : lors de L'éxécution de `exec.sh`, stop permet de terminer le programme.