# StreamBeat

StreamBeat es un prototipo de interfaz de usuario que corre directamente
sobre la consola de Windows. El programa presenta unas pantallas de
inicio de sesión y registro utilizando la API de Win32 y widgets propios.

## Compilación

1. Abre `StreamBeat.sln` con Visual Studio (se recomienda VS 2022).
2. Selecciona la configuración (**Debug** o **Release**) y la plataforma
   deseada (**x86** o **x64**).
3. Compila el proyecto desde el IDE.

El ejecutable se generará en `StreamBeat/bin/<Plataform>/<Configuration>/StreamBeat.exe`.

## Ejecución

Desde una consola de comandos navega a la carpeta de salida y ejecuta:

```cmd
StreamBeat.exe
```

Al iniciar se mostrará la pantalla de inicio de sesión.

## Estructura de carpetas

- `StreamBeat/` - código fuente y archivos del proyecto Visual Studio.
  - `Source/` - módulos de la aplicación:
    - `Application/` - ciclo de vida principal.
    - `Console/` - utilidades para la consola de Windows.
    - `Screens/` - pantallas de la interfaz (login, register).
    - `UI/` - controles básicos como botones y cajas de texto.
    - `Manager/` - gestión de pantallas y foco.
    - `Utils/`, `Structures/`, `HashTable/`, `Drawing/`, `Input/` - utilidades varias.
  - `Resource/` - recursos del proyecto, como iconos.
  - `main.cpp` - punto de entrada de la aplicación.

## Dependencias

Se utilizan exclusivamente la STL de C++ y la API de Win32 (`Windows.h`),
por lo que el proyecto solo es compatible con Windows y requiere
Visual Studio para compilar.

## Licencia

Distribuido bajo la licencia MIT. Consulta `LICENSE.txt` para más detalles.
