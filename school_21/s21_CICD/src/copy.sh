#!/bin/bash

# Переменные
SOURCE_DIR="./cat/s21_cat ./grep/s21_grep"  # Директория с артефактами на текущей машине
TARGET_DIR="/usr/local/bin"                  # Директория на целевой машине
TARGET_USER="production"                            # Пользователь на целевой машине
TARGET_HOST="192.168.56.104"                   # IP или имя хоста целевой машины
TARGET_PORT="22"                             # Порт SSH (по умолчанию 22)
SUDO_PASSWORD="123"            # Пароль для sudo на целевой машине

# Копирование файлов на целевую машину
scp -r -P $TARGET_PORT $SOURCE_DIR $TARGET_USER@$TARGET_HOST:/tmp/

# Проверка успешности копирования
if [ $? -eq 0 ]; then
  echo "Файлы успешно скопированы в временную директорию на $TARGET_HOST"
else
  echo "Ошибка при копировании файлов"
  exit 1
fi

# Перемещение файлов в целевую директорию с использованием sudo
echo $SUDO_PASSWORD | ssh -p $TARGET_PORT $TARGET_USER@$TARGET_HOST "sudo -S mv /tmp/s21_cat /tmp/s21_grep $TARGET_DIR"

# Проверка успешности перемещения
if [ $? -eq 0 ]; then
  echo "Файлы успешно перемещены в $TARGET_DIR на $TARGET_HOST"
else
  echo "Ошибка при перемещении файлов"
  exit 1
fi
