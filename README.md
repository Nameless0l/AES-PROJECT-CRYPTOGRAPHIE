
![](https://www.titanhq.fr/wp-content/uploads/2020/05/sensibilisation-securite-informatique-crise-covid-19.png)

#              Science de l'information
## Theme du projet : AES
## Superviseur
-👤 **`Dr TALE Hervé KALACHI`**
## Authors

- 👤  [@Nameless[Mbassi Ewolo Loic Aron]](https://github.com/Nameless0l)
- 👤 [@[Ngoupaye THiery]](https://github.com/)
- 👤 [@[Vuide Ouendeu Franck Jordan]](https://github.com/whitecodename)
- 👤 [@[Wotchoko Ngatcheu Yohan]](https://github.com/Yohanpy2004)
- 👤 [@[WANDJI EMANUEL]](https://github.com/)
### 💡Description du Projet


![](https://nevonprojects.com/wp-content/uploads/2015/06/aes-image.png)


Ce projet a été développé dans le cadre du cours [SI] pour implementer l'algorithme de chiffrement avancé (AES) en langage C. L'objectif principal était de comprendre et de mettre en œuvre les étapes de l'algorithme AES, y compris le chiffrement et le déchiffrement. Dans notre travail nous implementons AES 128 bits
Pour le faire nous avons eu besoin de la structure suivante pour le code source

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
├── 📁 include/
│   ├──📄 common.h
│   ├──📄 data.h
│   ├──📄 decrypt.h
│   └──📄 encrypt.h
│
├── 📁 bin/
│   └──📄 aes               : Exécutable AES
│
└── 📁 notes/
    ├── 📁 Rapport_AES_Project/
    │   ├──📄 rapport.md     : Notes sur Rapport en md
    │   └──📄 rapport.md     : Notes sur pdf
    │
    └── 📁 exercices/
        ├──📄 exercice 1.md   : Le makdown
        └──📄 exercice 1.docx   : 

```
- **`src/`** : Dossier contenant les fichiers source.
  - **`main.c`** : Le fichier source principal permettant de tester le code de l'AES.
  - **`common.c`** : Le fichier source contenant les fonctions utilitaires.
  - **`decrypt.c`** : Le fichier source contenant les fontions necesaires au dechiffrement.
  - **`encrypt.c`** : Le fichier source contenant des fonctions de chiffrement.

- **`include/`** : Dossier contenant les fichiers d'en-tête.
  - **`common.h`** 
  - **`decrypt.h`**  
  - **`encrypt.h`** 
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
./bin/aes
```
Resultat
===
![Resultat](https://github.com/Nameless0l/AES-PROJECT-CRYPTOGRAPHIE/blob/main/aes_encryption_and_decryption.png?raw=true)