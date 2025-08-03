## Part 1. Готовый докер

Скачивание официального докер-образа с nginx при помощи docher pull. \
![1](screenshots/image_1.png)

Проверка наличия докер-образа через docker images. \
![2](screenshots/image_2.png)

Запуск докер-образа через docker run -d [image_id][repository]. \
![3](screenshots/image_3.png)

Проверка, что образ запустился через docker ps: \
![4](screenshots/image_4.png)

Информация о контейнере через docker inspect  [container_id|container_name] и запуск команды для отчета размер контейнера, список запампленных портов и id контейнера. \
![5](screenshots/image_5.png) \
Size and ip: \
![6](screenshots/image_6.png) \
Ports: \
![7](screenshots/image_7.png) 

Остановка и проверка докер образа через docker stop [container_id|container_name] и docker ps. \
![8](screenshots/image_8.png) 

Запусти докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду run. \
![9](screenshots/image_9.png)

Проверка, что в браузере по адресу localhost:80 доступна стартовая страница nginx \
![10](screenshots/image_10.png)

Перезапуск докер контейнера через docker restart [container_id|container_name] и проверка любым способом, что контейнер запустился.
![11](screenshots/image_11.png)

## Part 2. Операции с контейнером
Чтение конфигурационного файла nginx.conf внутри докер контейнера через команду exec. \
![12](screenshots/image_12.png)

- Создаем на локальной машине файл nginx.conf.
- Настройка в нем по пути /status отдачу страницы статуса сервера nginx.\
![13](screenshots/image_13.png)

- Копирования созданного файла nginx.conf внутрь докер-образа через команду docker cp. \
![14](screenshots/image_14.png)

- Перезапуск nginx внутри докер-образа через команду exec. \
![15](screenshots/image_15.png)

- Проверка, что по адресу localhost:80/status отдается страничка со статусом сервера nginx.\
![16](screenshots/image_16.png) \
![17](screenshots/image_17.png)

Экспорт контейнера в файл container.tar через команду export и остановка контейнера \
![18](screenshots/image_18.png) 

Удаление образа через docker rmi [image_id|repository], не удаляя перед этим контейнеры. \
![19](screenshots/image_19.png) 


Удаление остановленного контейнера.\
![20](screenshots/image_20.png) 

Импортирование контейнера обратно через команду import. \
![21](screenshots/image_21.png)

Запуск импортированного контейнер. \
![22](screenshots/image_22.png) \
![23](screenshots/image_23.png) 

Проверка, что по адресу localhost:80/status отдается страничка со статусом сервера nginx. \
![24](screenshots/image_24.png) \
![25](screenshots/image_25.png) 


## Part 3. Мини веб-сервер
- Создание мини-сервера на C и FastCgi, который будет возвращать простейшую страничку с надписью Hello World!. \
![26](screenshots/image_26.png) \
- Запуск написанного мини-сервера через spawn-fcgi на порту 8080 \
![27](screenshots/image_27.png) 

- Пишем nginx.conf, который будет проксировать все запросы с 81 порта на 127.0.0.1:8080. src/mini_server/nginx.conf \
![28](screenshots/image_28.png) 

- Помещаем файл nginx.conf в папку ./nginx/: cp nginx.conf ./nginx/nginx.conf 
- Помещаем docker cp ./nginx.conf temp:/etc/nginx/
- sudo docker exec temp apt-get update
- sudo docker exec temp apt-get install -y gcc spawn-fcgi libfcgi-dev
- sudo docker exec temp gcc /etc/nginx/mini_server.c -o /etc/nginx/webserver -l fcgi
- sudo docker exec temp spawn-fcgi -p 8080 /etc/nginx/webserver
- sudo docker exec temp nginx -s reload
- curl http://localhost:81/


- Открываем браузер и переходим по адресу: http://localhost:81 \
![29](screenshots/image_29.png) \


## Part 4. Свой докер 
Написание своего докер-образа, который:
1) собирает исходники мини сервера на FastCgi из Части 3;
2) запускает его на 8080 порту;
3) копирует внутрь образа написанный ./nginx/nginx.conf;
4) запускает nginx. 

Сборка написанного докер-образа через docker build при этом указав имя и тег.\
![30](screenshots/image_30.png) \

Проверка через docker images, что все собралось корректно. \
![31](screenshots/image_31.png) 

Запуск собранного докер-образа с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а (см. Часть 2).
![32](screenshots/image_32.png) 

Проверка, что по localhost:80 доступна страничка написанного мини сервера.\
![33](screenshots/image_33.png) 


Допиши в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx. \
![34](screenshots/image_34.png) 

Перезапуск докер-образа. Если всё сделано верно, то, после сохранения файла и перезапуска контейнера, конфигурационный файл внутри докер-образа должен обновиться самостоятельно без лишних действий\
![35](screenshots/image_35.png) 

Проверка, что теперь по localhost:80/status отдается страничка со статусом nginx\
![36](screenshots/image_36.png) 


## Part 5. Dockle

- Просканируй образ из предыдущего задания через dockle [image_id|repository]. \
![37](screenshots/image_37.png) 

- Исправвление образа так, чтобы при проверке через dockle не было ошибок и предупреждений.
> FATAL	- CIS-DI-0010 \
> Нужна проверка образа с флагами: \
> -ak NGINX_GPGKEYS \
> -ak NGINX_GPGKEY_PATH \

> FATAL	- DKL-DI-0005 \
> Добавить в Dockerfile строку для очистки кэша пакетов apt-get после установки необходимых пакетов: 
rm -rf /var/lib/apt/lists 

![38](screenshots/image_38.png) 

## Part 6. Базовый Docker Compose

1) Подними докер-контейнер из Части 5 (он должен работать в локальной сети, т.е. не нужно использовать инструкцию EXPOSE и мапить порты на локальную машину).
```
server {
        listen       81;
        server_name  localhost;

        location / {
            fastcgi_pass 127.0.0.1:8080;
        }

        location = /status {
            stub_status;
        }
}
```
2) Подними докер-контейнер с nginx, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера.
```
server {
        listen 8080;
	    location = / {
              proxy_pass http://temp:81;
			}
        location /status {
		           stub_status on;
	    }

    }
```

- Остановка всех запущенных контейнеров. \
![39](screenshots/image_39.png) 

- Сборка и запуск проекта с помощью команд docker-compose build и docker-compose up. \
![40](screenshots/image_40.png) \
![41](screenshots/image_41.png) 

Проверка, что в браузере по localhost:80 отдается написанная тобой страничка, как и ранее.\

![41](screenshots/image_42.png) 