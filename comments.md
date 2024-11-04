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

