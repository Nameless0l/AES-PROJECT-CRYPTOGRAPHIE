
![](https://www.titanhq.fr/wp-content/uploads/2020/05/sensibilisation-securite-informatique-crise-covid-19.png)

Science de l'information
===
## Theme du projet : AES
## Superviseur
 - 👤 **`Dr TALE Hervé KALACHI`**
## Authors

- 👤  [@Nameless[Mbassi Ewolo Loic Aron]](https://github.com/Nameless0l)
- 👤 [@[Ngoupaye THiery]](https://github.com/)
- 👤 [@[Vuide]](https://github.com/)
- 👤 [@[WO]](https://github.com/)
- 👤 [@[WANDJI EMANUEL]](https://github.com/)
### 💡Description du Projet




Ce projet a été développé dans le cadre du cours [SI] pour implementer l'algorithme de chiffrement avancé (AES) en langage C. L'objectif principal était de comprendre et de mettre en œuvre les étapes de l'algorithme AES, y compris le chiffrement et le déchiffrement.
Pour le faire nous avons eu besoin de la structure suivante pour le code source
## Resume 
![Image](https://nevonprojects.com/wp-content/uploads/2015/06/aes-image.png)


## 🛠️ Contenu du Projet

Le projet est organisé de la manière suivante :
```
📁 project_root/
│
├──📄 CMakeLists.txt
│
├── 📁 src/
│   ├──📄 main.c
│   ├──📄 common.c
│   ├──📄 data.c
│   ├──📄 decrypt.c
│   └──📄 encrypt.c
│
└──📁  include/
    ├──📄 common.h
    ├──📄 data.h
    ├──📄 decrypt.h
    └──📄 encrypt.h
```
- **`src/`** : Dossier contenant les fichiers source.
  - **`main.c`** : Le fichier source principal permettant de tester le code de l'AES.
  - **`common.c`** : Le fichier source contenant les fonctions utilitaires.
  - **`decrypt.c`** : Le fichier source pour la génération des clés de ronde.
  - **`encrypt.c`** : Le fichier source contenant des fonctions .
  - **`main.c`** : Le fichier source contenant la fonction principale.

- **`include/`** : Dossier contenant les fichiers d'en-tête.
  - **`common.h`** 
  - **`decrypt.h`**  
  - **`encrypt.h`** 
  - **`main.h`** 
- **`CMakeLists.txt`** : Fichier CMake pour la configuration du projet.

- **`build/`** : Dossier où les fichiers binaires seront générés par Cmake.
- **`bin/`** : Dossier contenant egalement les fichiers de lorsqu'on compile le code sans utiliser Cmake.
## 📖 Compilation et Exécution
Pour compiler le projet, vous pouvez utiliser la commande suivante :
## 📖 En utilisant Cmake
  
## 📖 Compilation habituelle
Creer le fichier binaire en executant :

```
gcc -o bin/aes src/main.c src/common.c src/data.c src/decrypt.c src/encrypt.c
```
Lancer l'executable avec la commande suivante :
```
bin/aes
```


## Resultats

![App Screenshot](https://raw.githubusercontent.com/Nameless0l/AES-PROJECT-CRYPTOGRAPHIE/9d4636d19384e98024fd94cb783f03d9ea716564/aes_encryption_and_decryption.png)

