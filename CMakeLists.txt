cmake_minimum_required(VERSION 3.10)

# Nom de votre projet
project(BMP VERSION 0.1.0)

# Ajoutez les fichiers source de votre projet
set(SOURCES src/main.c src/common.c src/data.c src/decrypt.c src/encrypt.c)

# Ajoutez les fichiers d'en-tête de votre projet
set(HEADERS include/common.h include/data.h include/decrypt.h include/encrypt.h)
 
# Créez l'exécutable en utilisant les fichiers source
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})