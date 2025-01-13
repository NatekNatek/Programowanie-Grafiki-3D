# Assignments 73.0/150.0

## House OK 2.0/2.0

30.10.2024 10:13:55 OK

## Colors OK 5.0/5.0

30.10.2024 10:17:04 OK

## Indices OK 5.0/5.0

30.10.2024 10:17:19 OK

## Uniforms OK 8.0/8.0

30.10.2024 10:19:41 OK
Ale niepotrzebnie woła Pani funkcje `glGetUniformBlockIndex` i  `glUniformBlockBinding`. Wiązanie jest już zrobione w deklaracji layout(std140, binding=x) w szaderach.
No i w CmakeLists.txt ma Pani błąd w nazwie projektu.

## PVM OK 5.0/5.0

6.11.2024 09:00:30
Proszę wnieść poprawki podane w poprzednim zadaniu. 

13.01.2025 10:35:21 OK


## Pyramid OK 3.0/3.0

6.11.2024 09:03:17
Proszę wnieść poprawki podane w poprzednim zadaniu.

13.01.2025 10:36:20 OK


## Resize OK 8.0/8.0

6.11.2024 09:22:18
W funkcji frame tworzenie przesyłanie do bufora uniform  i jego bindowanie powinno się odbywać przed wywołaniem funkcji glDrawElements. 

18.11.2024 16:27:02 OK

## Zoom OK 10.0/10.0

11.11.2024 12:48:44
Nie kompiluje się. W pliku app.h niepotrzebnie podaje Pani nazwę klasy przed nazwą funkcji `scroll_callback`
Podobnie jak poprzenio kolejność wywołań w funkcji frame jest zła. 

12.11.2024 18:51:11 OK

## Camera movement OK 15.0/15.0

11.11.2024 12:53:45
Podobnie jak poprzenio kolejność wywołań w funkcji frame jest zła. 

18.11.2024 16:27:50 OK


## Mesh OK 12.0/12.0

2.12.2024 17:10:49 OK

## Kd material Not OK 0/20.0

17.12.2024 12:53:09
W metodzie `add_primitive` drugi argument powinien być gornym końcem zakresu indeksów dla danej podsiatki, a nie liczbą indeksów,

5.01.2025 19:06:43
Dalej całkowite zamieszanie w wywołaniach metod add_primitive. Piewszy argumenty powinnym być indeksami do tabl,icy indeksów oznaczającymi, poczatek i koniec zakresu indeksów dla tej podsieci. 
Ponadto z niewiadomych powodów w niektórych wywołaniach podaje Pani liczbę bajtów, a nie indeks.

13.01.2025 10:38:21
Nie kompilje się. W pliku texture.cpp zmienna img jest definiowana dwa razy.
Caly czas podaje Pani  indeks w bajtach. 



