# 42-Madrid — alfsanch

Repositorio con los proyectos desarrollados durante el programa de **42 Madrid**, ordenados por dificultad creciente. Abarca desde utilidades en C hasta un servidor IRC completo en C++.

---

## Proyectos

### - Libft
Biblioteca estándar personalizada en C. Reimplementación de funciones de `libc` (manipulación de strings, memoria, listas enlazadas) que sirve de base para el resto de proyectos.

### - GNL — Get Next Line
Función que lee una línea de cualquier descriptor de archivo de forma eficiente, manejando múltiples fds simultáneos con buffers de tamaño configurable.

### - ft_printf
Reimplementación de `printf` con soporte para los especificadores de formato más comunes: `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, `%X`, `%p` y `%%`.

### - minitalk
Sistema de comunicación cliente-servidor entre procesos usando únicamente señales UNIX (`SIGUSR1` / `SIGUSR2`). Transmite mensajes bit a bit de forma fiable.

### - so_long
Juego 2D sencillo con MiniLibX. El jugador recorre un mapa leyendo un archivo `.ber`, recoge objetos y alcanza la salida, con detección de camino válido incluida.

### - push_swap
Algoritmo de ordenación sobre dos pilas con un conjunto restringido de operaciones. El objetivo es ordenar una lista de enteros usando el menor número de movimientos posible.

### - philo — Philosophers
Implementación del problema clásico de los filósofos comensales. Usa **pthreads** y **mutexes** para sincronizar el acceso a los tenedores sin deadlocks ni data races.

### - minishell
Shell funcional que replica el comportamiento básico de bash: ejecución de comandos, pipes, redirecciones, variables de entorno, expansión de `$?`, señales y builtins (`cd`, `echo`, `export`, `unset`, `env`, `exit`).

### - cub3d
Motor de raycasting en C inspirado en Wolfenstein 3D, construido con MiniLibX. Renderiza un mundo 3D a partir de un mapa 2D con texturas para paredes, suelo y techo.

### - ft_irc — Internet Relay Chat Server
Servidor IRC completo escrito en **C++98**. Maneja múltiples clientes simultáneos con un único `poll()` (sin fork). Compatible con clientes reales como HexChat o WeeChat.

Comandos implementados: `PASS`, `NICK`, `USER`, `JOIN`, `PART`, `PRIVMSG`, `KICK`, `INVITE`, `TOPIC`, `MODE`, `QUIT`, `PING`/`PONG`.

Modos de canal soportados: `i` (invite-only), `t` (topic restringido), `k` (contraseña), `o` (operador), `l` (límite de usuarios).

```bash
# Compilar y arrancar
make
./ircserv 6667 mypassword

# Test rápido con netcat
nc -C 127.0.0.1 6667
PASS mypassword
NICK testnick
USER testuser 0 * :Real Name
JOIN #general
PRIVMSG #general :Hello world!
```

### - CPP Modules (00 → 05)
Serie de módulos introductorios a **C++**: clases, herencia, polimorfismo, sobrecarga de operadores, templates, excepciones y STL. Cada módulo profundiza sobre el anterior.

### - Exam 02
Ejercicios de práctica para el examen de nivel 2 (ft_printf, get_next_line, etc.). Usados como material de estudio; no todos están al 100 %.

---

## Instalación

```bash
git clone https://github.com/alfonso7199/42-Madrid-alfsanch.git
cd 42-Madrid-alfsanch
```

Cada proyecto tiene su propio `Makefile`. Entra en la carpeta correspondiente y ejecuta `make`.

---

## Autor

**alfsanch** · 42 Madrid
