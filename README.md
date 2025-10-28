# UdeATunes

proyecto Desafío II - informática II (2025-2): simulación de una plataforma de streaming musical UdeATunes en C++

enlace al video en YouTube: https://youtu.be/U2jXtpQ34Cg



Descripción del proyecto



UdeATunes es un simulador de una plataforma de streaming musical desarrollado completamente en C++, como parte del desafío final de la materia Informática II.



El objetivo principal fue implementar un sistema que represente de forma estructurada cómo funciona un servicio de música, aplicando programación orientada a objetos, uso de plantillas, manejo de memoria dinámica y modularidad.

Además, se exigía no usar estructuras de datos de la STL, por lo que se diseñó un contenedor genérico propio: MiLista<T>.





Clases principales



Clase	        Descripción



UdeATunes	Clase central del sistema. Contiene y administra los usuarios y artistas.

Usuario	        Representa a cada persona dentro del sistema. Puede ser estándar o VIP.

Artista	        Contiene los álbumes publicados y sus seguidores.

Álbum	        Agrupa canciones y calcula su duración total.

Canción	        Contiene datos como duración, nombre, rutas de audio (128 kbps / 320 kbps) y créditos.

Créditos	Registra información de productores, disqueras y patrocinadores.

Publicidad	Módulo que gestiona los anuncios aleatorios con ponderación.

MiLista<T>	Clase genérica que reemplaza estructuras STL como vector o list.


Santiago Gallón Restrepo
Estudiante de Ingeniería – Universidad de Antioquia
Santiago.gallon1@udea.edu.co
2025-2


