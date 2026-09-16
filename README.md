<div align="center"><h1>calct</h1></div>

Calculadora para operar valores de tiempo (hh:mm:ss) rápida y directamente en consola.

## Uso

Se deben ingresar los tiempos con el siguiente formato: `hh:mm:ss`.

El nivel de detalle máximo aceptado es en horas, y el mínimo en segundos.

### Ejemplos de formato (formato -> equivalencia en lenguaje natural):

- 10:31:27 -> 10 horas, 31 minutos y 27 segundos
- 01:03:07 -> 1 hora, 3 minutos y 7 segundos
- 2:1:0 -> 2 horas, 1 minuto y 0 segundos
- 10:3 -> 10 minutos y 3 segundos
- 5:07 -> 5 minutos y 7 segundos
- 34 -> 34 segundos
- 03 -> 3 segundos
- 9 -> 9 segundos

### Ejemplos de uso:

- Suma de tiempos:

    ```
    calct 23:19 + 56
    24:15
    ```
    ```
    calct 1:3:4 + 2:34:1
    3:37:5
    ```
- Resta de tiempos:
    ```
    calct 4:56:12 - 1:23:09
    3:33:3
    ```
    ```
    calct 57:29 - 19:51
    37:38
    ```

## Instalación

Descargar el ejecutable desde las [releases](https://github.com/KNZodiac24/calct/releases) o compilar manualmente el proyecto; y añadir el ejecutable al PATH.

## Desarrollo y compilación

### Requisitos (Linux/Windows)

- CMake
- [Ninja](https://ninja-build.org/)
- Compilador de C++
> [!NOTE] 
> El compilador que se utiliza por defecto al ejecutar el build es `g++`. Para el caso de Windows, se puede utilizar el ejecutable de `g++` que viene incluido en la suite de herramientas y paquetes `MinGW-W64-builds` de [Mingw-w64](https://www.mingw-w64.org/downloads/).
- Make
> [!NOTE] 
> Para Windows se puede utilizar el ejecutable `mingw32-make` que también viene incluido en la suite de herramientas de Mingw-w64.
- Vcpkg [instalado y configurado](https://learn.microsoft.com/vcpkg/get_started/get-started) (seguir las instrucciones solo hasta el primer literal del paso 2); con la variable de entorno `VCPKG_ROOT` definida.

### Proceso 

1. Clonar el repo y ejecutar en la carpeta raíz:
    - Linux:
        ```
        make setup
        ```
    - Windows:
> [!IMPORTANT] 
> Para Windows se debe ejecutar añadiendo un argumento:
```
mingw32-make setup WIN_ARGS="-DCMAKE_CXX_COMPILER=g++ -DVCPKG_TARGET_TRIPLET=x64-mingw-static -DVCPKG_HOST_TRIPLET=x64-mingw-static"
```
> [!IMPORTANT]
> De esta forma se asegura que el proyecto en Windows sea independiente de MSVC y Visual Studio; sin el argumento adicional, se tendría que trabajar obligatoriamente con dichas herramientas.

Con esto ya se puede realizar el desarrollo.

2. Para compilar el proyecto se ejecuta en la carpeta raíz:
    - Linux:
        ```
        make build
        ```
    - Windows:
        ```
        mingw32-make build
        ```
    Por defecto, el ejecutable resultante se ubicará en la carpeta `build`.
