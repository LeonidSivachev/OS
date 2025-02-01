#!/bin/zsh

# Проверяем, что файл boot.s существует
if [[ ! -f src/boot.s ]]; then
  echo "Файл boot.s не найден!"
  exit 1
fi
mkdir build
# Запускаем ассемблер
../opt/cross/bin/i686-elf-as src/boot.s -o build/boot.o
# Проверяем, что команда выполнена успешно
if [[ $? -eq 0 ]]; then
  echo "Компиляция boot.s прошла успешно!"
else
  echo "Ошибка компиляции boot.s."
  exit 1
fi

# Проверяем, что файл kernel.c существует
if [[ ! -f src/kernel.c ]]; then
  echo "Файл kernel.c не найден!"
  exit 1
fi
../opt/cross/bin/i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
# Проверяем, что команда выполнена успешно
if [[ $? -eq 0 ]]; then
  echo "Компиляция kernel.c прошла успешно!"
else
  echo "Ошибка компиляции kernel.c."
  exit 1
fi

# Проверяем, что файл kernel.c существует
if [[ ! -f src/linker.ld ]]; then
  echo "Файл linker.ld не найден!"
  exit 1
fi
mkdir bin
../opt/cross/bin/i686-elf-gcc -T src/linker.ld -o bin/myos.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o -lgcc
# Проверяем, что команда выполнена успешно
if [[ $? -eq 0 ]]; then
  echo "Линковка прошла успешно!"
else
  echo "Ошибка линковки."
  exit 1
fi
echo "Проверка корректности myos.bin. Программа зависнет, если файл некорректен"
grub-file --is-x86-multiboot bin/myos.bin
echo "Преобразование бинарника к iso."

mkdir -p isodir/boot/grub
cp bin/myos.bin isodir/boot/myos.bin
touch isodir/boot/grub/grub.cfg
echo -e 'menuentry "myos" {\n  multiboot /boot/myos.bin\n}' > isodir/boot/grub/grub.cfg
mkdir iso_result
grub-mkrescue -o iso_result/myos.iso isodir
rm -r isodir/