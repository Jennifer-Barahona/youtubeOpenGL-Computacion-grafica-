# Proyecto OpenGL - Escena 3D

## 1. Descripción general

Este proyecto consiste en el desarrollo de una escena tridimensional utilizando C++ y OpenGL. Su propósito es aplicar diferentes conceptos de programación gráfica mediante la importación, visualización, transformación e iluminación de modelos 3D.

Durante el desarrollo se trabaja con diferentes librerías que permiten gestionar los elementos necesarios para construir una escena interactiva, desde la carga de modelos y texturas hasta el manejo de la cámara y el desplazamiento de objetos en el espacio tridimensional.

Como modelo principal se utiliza **DamagedHelmet.glb**, el cual se importa mediante Assimp y conserva sus colores y texturas originales.

El proyecto se encuentra en desarrollo y busca integrar progresivamente diferentes elementos de gráficos por computador.

---

## 2. Objetivos del proyecto

### Objetivo general

Desarrollar una escena tridimensional mediante C++ y OpenGL, aplicando conceptos de programación gráfica, transformación de objetos, iluminación y movimiento en un entorno 3D.

### Objetivos específicos

- Implementar la carga e importación de modelos tridimensionales.
- Aplicar texturas para conservar la apariencia visual de los modelos.
- Incorporar iluminación para mejorar la visualización de los objetos.
- Implementar una cámara interactiva que permita explorar la escena.
- Aplicar transformaciones geométricas para modificar la posición de los objetos.
- Implementar una curva de Bézier para controlar el desplazamiento de un modelo en el espacio tridimensional.

---

## 3. Características implementadas

### Carga de modelos 3D

Se utiliza la librería Assimp para importar modelos tridimensionales en diferentes formatos.

El modelo principal utilizado es `DamagedHelmet.glb`, que se procesa para obtener sus mallas, vértices, índices y materiales.

### Aplicación de texturas

Se implementó la carga de imágenes mediante la librería stb_image, permitiendo aplicar las texturas correspondientes al modelo.

De esta manera, el objeto conserva sus colores y detalles visuales en lugar de mostrarse únicamente con un color uniforme.

### Iluminación

Se implementó un sistema básico de iluminación mediante shaders de OpenGL.

Este sistema utiliza componentes de iluminación ambiental y difusa para generar diferencias de intensidad en la superficie del modelo dependiendo de la dirección de la luz.

### Cámara interactiva

Se incorporó una cámara que permite modificar la perspectiva desde la cual se observa la escena tridimensional.

El movimiento se controla mediante el teclado y el mouse, facilitando la exploración del entorno.

### Movimiento mediante curvas de Bézier

Se implementó una curva de Bézier cúbica para controlar el desplazamiento del modelo 3D.

La trayectoria se define mediante cuatro puntos de control:

- **P0:** punto inicial de la curva.
- **P1:** primer punto de control.
- **P2:** segundo punto de control.
- **P3:** punto final de la curva.

Mediante una función matemática se calcula la posición del objeto a lo largo de la trayectoria. El parámetro de tiempo permite actualizar su posición continuamente y generar un movimiento repetitivo.

---

## 4. Tecnologías y herramientas utilizadas

| Tecnología | Función dentro del proyecto |
|---|---|
| C++ | Lenguaje principal de programación. |
| OpenGL | Renderizado de gráficos tridimensionales. |
| GLFW | Creación de ventanas y gestión de entradas. |
| GLAD | Carga de funciones de OpenGL. |
| GLM | Operaciones matemáticas y transformaciones 3D. |
| Assimp | Importación y procesamiento de modelos 3D. |
| stb_image | Carga de imágenes y texturas. |
| Visual Studio 2022 | Entorno de desarrollo. |

---

## 5. Organización de los archivos

El proyecto se encuentra organizado en diferentes archivos para separar las responsabilidades de cada componente.

```text
youtubeOpenGL/
│
├── Main.cpp
│
├── Camera.h
├── Camera.cpp
│
├── Mesh.h
├── Mesh.cpp
│
├── Model.h
├── Model.cpp
│
├── Shader.h
├── Shader.cpp
│
├── Texture.h
├── Texture.cpp
│
├── Bezier.h
├── stb_image.h
│
└── models/
    └── DamagedHelmet.glb
```

### Descripción de los archivos principales

- **Main.cpp:** contiene la inicialización de OpenGL, la configuración de la escena y el ciclo principal de renderizado.
- **Camera:** gestiona la posición, orientación y movimiento de la cámara.
- **Mesh:** almacena y procesa la información geométrica necesaria para representar las mallas.
- **Model:** permite importar y organizar los modelos 3D mediante Assimp.
- **Shader:** administra los shaders utilizados durante el proceso de renderizado.
- **Texture:** se encarga de cargar y administrar las texturas.
- **Bezier.h:** contiene la función matemática utilizada para calcular los puntos de la curva de Bézier.
- **stb_image.h:** permite cargar imágenes utilizadas como texturas.
- **models:** contiene los archivos correspondientes a los modelos tridimensionales.

---

## 6. Modelo utilizado

**DamagedHelmet.glb**

El modelo utilizado como elemento principal de la escena es un casco tridimensional que cuenta con materiales y texturas.

Su importación se realiza mediante Assimp, permitiendo procesar la geometría y los recursos visuales del archivo GLB.

---

## 7. Controles de la escena

La cámara puede controlarse mediante las siguientes entradas:

| Tecla o entrada | Acción |
|---|---|
| W | Avanzar. |
| S | Retroceder. |
| A | Desplazarse hacia la izquierda. |
| D | Desplazarse hacia la derecha. |
| Mouse | Modificar la orientación de la cámara. |

---

## 8. Instalación y ejecución

El proyecto fue desarrollado en Visual Studio 2022 utilizando C++ y OpenGL.

Para ejecutarlo se requiere:

1. Contar con Visual Studio 2022.
2. Configurar un entorno compatible con OpenGL.
3. Instalar y configurar las librerías necesarias: GLFW, GLAD, GLM y Assimp.
4. Incluir los archivos correspondientes a stb_image.
5. Mantener el modelo `DamagedHelmet.glb` dentro de la carpeta `models`.
6. Compilar y ejecutar el proyecto desde Visual Studio.

Es importante conservar la estructura de carpetas y verificar que la ruta del modelo coincida con la utilizada en el código.

---

## 9. Estado actual del proyecto

El proyecto se encuentra en desarrollo.

Hasta el momento se han implementado los siguientes elementos:

- Importación y visualización del modelo 3D.
- Carga de sus texturas originales.
- Iluminación básica.
- Cámara interactiva.
- Movimiento del modelo mediante una curva de Bézier cúbica.

Se continuará trabajando en la integración y mejora de los diferentes componentes de la escena.

---

## 10. Autoría

Proyecto académico desarrollado como práctica de programación gráfica utilizando C++ y OpenGL.

**Entorno de desarrollo:** Visual Studio 2022.

