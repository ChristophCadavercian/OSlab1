# OSlabs
MIEM 4th year Operating Systems labs
## Задание:
Сервер. Создать гнездо домена UNIX типа virtual circuit. Присвоить ему имя. Принять сообщение от клиентского гнезда. Распечатать имена файлов модифицированных в течение последних суток принадлежащих 1-му по порядку пользователю, имя которого упоминается в ответе клиента.

Клиент. Создать гнездо домена UNIX типа virtual circuit. Передать в серверное гнездо информацию (имена) обо всех пользователях, зарегистрированных в системе.
### Usage:
  ```git clone https://github.com/ChristophCadavercian/OSlab1
  cd OSlab1
  gcc ./socket/server/server.c -o server && ./server SOCKET_PATH
  gcc ./socket/client/client.c -o client && ./client SOCKET_PATH
  ```
