# tarea2_JosueHuaiquil

# SPOTIFIND

## Descripción

Spotifind permite cargar una base de datos de canciones y buscarlas rápida y eficientemente, ya sea por denero, artista o tempo. 

## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack** de Microsoft. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

### Requisitos previos:

- Tener instalado [Visual Studio Code](https://code.visualstudio.com/).
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como **gcc**). Si estás en Windows, se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar el entorno [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

### Pasos para compilar y ejecutar:

1. **Descarga y descomprime el** archivo `.zip` en una carpeta de tu elección.
2. **Abre el proyecto en Visual Studio Code**
    - Inicia Visual Studio Code.
    - Selecciona `Archivo > Abrir carpeta...` y elige la carpeta donde descomprimiste el proyecto.
    3. **Compila el código**
    - Abre el archivo principal (por ejemplo, `main.c`).
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando (ajusta el nombre si el archivo principal tiene otro nombre):
        
        ```bash
        gcc main.c tdas/*.c -o test
        ```
        
4. **Ejecuta el programa**
    - Una vez compilado, puedes ejecutar la aplicación con:
        
        ```
        ./test
        ```
        

## Funcionalidades

### Funcionando correctamente:

- Cargar las canciones en sus distintas categorias (Genero, Artista, Tempo) 
- Mostrar un menu interactivo amigable.
- Buscar las canciones según las distintas categorias y mostrarlas por pantalla.
- Finalizar el programa.

### Problemas conocidos:

- El primer dato no se muestra correctamente.

### A mejorar:

- Implementar una interfaz de usuario más amigable.
- Permitir la edición de los datos de los pacientes.

## Ejemplo de uso

Para el uso del programa existen varias opciones para selecionar, lascuales se mmuestran en el siguiente menu:

```
========================================
       BASE DE DATOS DE CANCIONES
========================================
1) CARGAR CANCIONES
2) BUSCAR POR GENERO
3) BUSCAR POR ARTISTA
4) BUSCAR POR TEMPO
5) SALIR
========================================
INGRESE SU OPCION: 
```

**Opción 1: Cargar canciones**

Se comienza cargando los datos de las canciones.

```
INGRESE SU OPCION: 1) CARGAR CANCIONES
```

Se cargan las canciones y se registran por generos, artistas y tempo.

**Opción 2: Buscar por genero**

Se buscan las canciones por genero, al selecionar un genero se escribe en la consola y luego de una busqueda se imprimen en la pantalla.

Ejemplo:
```
Opción seleccionada: 2) BUSCAR POR GENERO
=======================================
          BUSQUEDA POR GENERO
=======================================
INGRESE EL GENERO DE LA CANCION: acoustic
```

Dentro de las canciones cargadas se buscan todas las que tengan un genero especifico, en el caso del ejemplo se buscan todas aquellas que sean de genero acoustic, y luego en la consola se muestran todas las canciones que sean del mismo genero.

Ejemplo de salida en la consola:
```
CANCION: Waves of Panic
ALBUM: The Shreds
TEMPO: 166
ARTISTAS: Corporate Hearts
------------------------
```

**Opción 3: Buscar por artista**

Se buscan las canciones por artista, al selecionar un artista se escribe en la consola el nombre del artista y luego de una busqueda se muestra en la consola las canciones en las que participo ese artista.

Ejemplo:
```
Opción seleccionada: 3) BUSCAR POR ARTISTA
========================================
          BUSQUEDA POR ARTISTA
========================================
INGRESE EL NOMBRE DEL ARTISTA: SA
```

Dentro de las canciones cargadas se buscan todas las que tengan al artista buscado, en el caso del ejemplo se buscan todas las canciones en las que el artista "SA" haya participado, y luego en la consola se muestran todas sus canciones.

Ejemplo de salida en la consola:
```
CANCION: Oora
ALBUM: Oora
TEMPO: 140
ARTISTA BUSCADO: SA
------------------------
```

**Opción 4: Buscar por tempo**

Se busca una canción según su tempo, ya sean "Lentas", "Moderadas" o "Rapidas", se escribre en la consola el tempo deseado, y luego de una busqueda se muestran en la consola todas las canciones que tengan el tempo buscado.

Ejemplo:
```
Opción seleccionada: 4) BUSCAR POR TEMPO
========================================
           BUSQUEDA POR TEMPO
========================================
INGRESE EL TEMPO DE LA CANCION (Lentas, Moderadas, Rapidas): Lentas
```

Dentro de las canciones cargadas se buscan todas las que tengan el tempo buscado, en el caso del ejemplo se buscan todas las canciones en las que el tempo sea lento ("Lentas"), y luego en la consola se muestran todas las canciones en el que el tempo sea lento.

Ejemplo de salida en la consola:
```
CANCION: Jesus Lover of My Soul - Live
ALBUM: Shout to the Lord (Live)
TEMPO: 72
ARTISTAS: Hillsong Worship, Integrity's Hosanna! Music, Darlene Zschech
------------------------
```

**Opción 5: Salir**

Al seleccionar la opción 5 se finaliza la ejecución del programa.

Ejemplo:
```
Opción seleccionada: 5) SALIR
```