#ifndef MULTIBOOT_HEADER
#include <stdint.h>
#define MULTIBOOT_HEADER 1

/*  How many bytes from the start of the file we search for the header. */
#define MULTIBOOT_SEARCH                        32768
#define MULTIBOOT_HEADER_ALIGN                  8
#define MULTIBOOT2_ARCHITECTURE_I386            0  

/*  The magic field should contain this. */
#define MULTIBOOT2_HEADER_MAGIC                 0xe85250d6

/*  This should be in %eax. */
#define MULTIBOOT2_BOOTLOADER_MAGIC             0x36d76289

/*  Alignment of multiboot modules. */
#define MULTIBOOT_MOD_ALIGN                     0x00001000

/*  Alignment of the multiboot info structure. */
#define MULTIBOOT_INFO_ALIGN                    0x00000008

/*  Flags set in the ’flags’ member of the multiboot header. */

#define MULTIBOOT_TAG_ALIGN                  8
#define MULTIBOOT_TAG_TYPE_END               0
#define MULTIBOOT_TAG_TYPE_CMDLINE           1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME  2
#define MULTIBOOT_TAG_TYPE_MODULE            3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4
#define MULTIBOOT_TAG_TYPE_BOOTDEV           5
#define MULTIBOOT_TAG_TYPE_MMAP              6
#define MULTIBOOT_TAG_TYPE_VBE               7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER       8
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS      9
#define MULTIBOOT_TAG_TYPE_APM               10
#define MULTIBOOT_TAG_TYPE_EFI32             11
#define MULTIBOOT_TAG_TYPE_EFI64             12
#define MULTIBOOT_TAG_TYPE_SMBIOS            13
#define MULTIBOOT_TAG_TYPE_ACPI_OLD          14
#define MULTIBOOT_TAG_TYPE_ACPI_NEW          15
#define MULTIBOOT_TAG_TYPE_NETWORK           16
#define MULTIBOOT_TAG_TYPE_EFI_MMAP          17
#define MULTIBOOT_TAG_TYPE_EFI_BS            18
#define MULTIBOOT_TAG_TYPE_EFI32_IH          19
#define MULTIBOOT_TAG_TYPE_EFI64_IH          20
#define MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR    21

#define MULTIBOOT_HEADER_TAG_END  0
#define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST  1
#define MULTIBOOT_HEADER_TAG_ADDRESS  2
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS  3
#define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS  4
#define MULTIBOOT_HEADER_TAG_FRAMEBUFFER  5
#define MULTIBOOT_HEADER_TAG_MODULE_ALIGN  6
#define MULTIBOOT_HEADER_TAG_EFI_BS        7
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32  8
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64  9
#define MULTIBOOT_HEADER_TAG_RELOCATABLE  10

#define MULTIBOOT_ARCHITECTURE_I386  0
#define MULTIBOOT_ARCHITECTURE_MIPS32  4
#define MULTIBOOT_HEADER_TAG_OPTIONAL 1

#define MULTIBOOT_LOAD_PREFERENCE_NONE 0
#define MULTIBOOT_LOAD_PREFERENCE_LOW 1
#define MULTIBOOT_LOAD_PREFERENCE_HIGH 2

#define MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED 1
#define MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED 2

struct multiboot_tag {
    uint32_t type;
    uint32_t size;
};

struct multiboot_tag_with_data {
    uint32_t type;
    uint32_t size;
    uint8_t data[];
};

struct multiboot_tag_basic_meminfo {
    uint32_t type;
    uint32_t size;
    uint32_t mem_lower;
    uint32_t mem_upper;
};

struct multiboot_tag_bootdev {
    uint32_t type;        // Значение 5 для MULTIBOOT_TAG_TYPE_BOOTDEV
    uint32_t size;        // Размер всей структуры в байтах
    uint32_t biosdev;     // Номер загрузочного устройства BIOS
    uint32_t slice;       // Номер раздела (partition)
    uint32_t part;        // Номер вложенного раздела (sub-partition)
};

struct multiboot_mmap_entry {
    uint64_t addr;    // Начальный физический адрес региона
    uint64_t len;     // Длина региона в байтах
    uint32_t type;    // Тип региона (см. ниже)
    uint32_t zero;    // Зарезервировано, всегда 0
};

struct multiboot_tag_mmap {
    uint32_t type;      // Тип тега, равен 6 (MULTIBOOT_TAG_TYPE_MMAP)
    uint32_t size;      // Общий размер тега в байтах
    uint32_t entry_size;// Размер одной записи в таблице карты памяти
    uint32_t entry_version; // Версия формата записей (обычно 0)
    struct multiboot_mmap_entry entries[0]; // Массив записей карты памяти
};

struct vbe_info_block {
    char signature[4];           // "VESA"
    uint16_t version;  // Версия VBE (например, 0x0200 для 2.0)
    uint32_t oem_string_ptr;  // Указатель на строку OEM (FAR-поинтер)
    uint32_t capabilities;    // Возможности контроллера
    uint32_t video_mode_ptr;  // Указатель на список поддерживаемых режимов
    uint16_t total_memory;    // Общий объём видеопамяти в 64-КБ блоках
    // Дополнительные поля для VBE 3.0 и выше
    uint8_t reserved[492];
};

struct vbe_mode_info_block {
    uint16_t mode_attributes; // Атрибуты режима (например, доступен ли LFB)
    uint8_t win_a_attributes; // Атрибуты окна A
    uint8_t win_b_attributes; // Атрибуты окна B
    uint16_t win_granularity; // Гранулярность окна (КБ)
    uint16_t win_size;        // Размер окна (КБ)
    uint16_t win_a_segment;   // Сегмент окна A
    uint16_t win_b_segment;   // Сегмент окна B
    uint32_t win_func_ptr;    // Указатель на функцию переключения окон
    uint16_t pitch;           // Байт на строку (байтов на линию)
    uint16_t x_res;           // Разрешение по X (ширина)
    uint16_t y_res;           // Разрешение по Y (высота)
    uint8_t x_char_size;      // Ширина символа в текстовом режиме
    uint8_t y_char_size;      // Высота символа в текстовом режиме
    uint8_t number_of_planes; // Количество плоскостей
    uint8_t bits_per_pixel;   // Бит на пиксель (глубина цвета)
    uint8_t number_of_banks;  // Количество банков
    uint8_t memory_model;     // Модель памяти (например, 4 = packed pixel)
    uint8_t bank_size;        // Размер банка (КБ)
    uint8_t number_of_image_pages; // Количество страниц изображения
    uint8_t reserved1;
    uint8_t red_mask_size;    // Размер маски красного цвета
    uint8_t red_field_position; // Позиция красного цвета
    uint8_t green_mask_size;  // Размер маски зелёного цвета
    uint8_t green_field_position; // Позиция зелёного цвета
    uint8_t blue_mask_size;   // Размер маски синего цвета
    uint8_t blue_field_position; // Позиция синего цвета
    uint8_t reserved_mask_size; // Размер резервной маски
    uint8_t reserved_field_position; // Позиция резервной маски
    uint8_t direct_color_mode_info; // Информация о прямом цвете
    uint32_t phys_base_ptr;   // Физический адрес линейного фреймбуфера (LFB)
    uint32_t reserved2[6];
};

struct multiboot_tag_vbe {
    uint32_t type;            // Тип тега, равен 7 (MULTIBOOT_TAG_TYPE_VBE)
    uint32_t size;            // Общий размер тега в байтах
    uint16_t vbe_mode;        // Номер текущего VBE-режима
    uint16_t vbe_interface_seg; // Сегмент интерфейса VBE (устаревшее)
    uint16_t vbe_interface_off; // Смещение интерфейса VBE (устаревшее)
    uint16_t vbe_interface_len; // Длина интерфейса VBE (устаревшее)
    uint8_t vbe_control_info[512]; // Блок VBE Controller Information (VBE 2.0+)
    uint8_t vbe_mode_info[256];    // Блок VBE Mode Information для текущего режима
};

struct multiboot_tag_framebuffer {
    uint32_t type;          // Тип тега, равен 8 (MULTIBOOT_TAG_TYPE_FRAMEBUFFER)
    uint32_t size;          // Общий размер тега в байтах
    uint64_t framebuffer_addr; // Физический адрес фреймбуфера
    uint32_t framebuffer_pitch; // Количество байт на строку
    uint32_t framebuffer_width; // Ширина экрана в пикселях (или символах)
    uint32_t framebuffer_height; // Высота экрана в пикселях (или символах)
    uint8_t framebuffer_bpp;    // Бит на пиксель (глубина цвета)
    uint8_t framebuffer_type;   // Тип фреймбуфера (см. ниже)
    uint8_t reserved;           // Зарезервировано, обычно 0
    union {
        struct {
            uint8_t framebuffer_red_field_position;   // Позиция красного цвета
            uint8_t framebuffer_red_mask_size;        // Размер маски красного
            uint8_t framebuffer_green_field_position; // Позиция зелёного цвета
            uint8_t framebuffer_green_mask_size;      // Размер маски зелёного
            uint8_t framebuffer_blue_field_position;  // Позиция синего цвета
            uint8_t framebuffer_blue_mask_size;       // Размер маски синего
        } framebuffer_rgb; // Для RGB-режима
        struct {
            uint16_t framebuffer_palette_num_colors; // Количество цветов в палитре
            struct multiboot_color *framebuffer_palette;       // Указатель на палитру
        } framebuffer_palette; // Для палитрового режима (устаревшее)
    } u;
};

struct multiboot_tag_elf_sections {
    uint32_t type;       // Тип тега, равен 9 (MULTIBOOT_TAG_TYPE_ELF_SECTIONS)
    uint32_t size;       // Общий размер тега в байтах
    uint32_t num;        // Количество секций в таблице
    uint32_t entsize;    // Размер одной записи о секции (обычно 40 или 64 байта)
    uint32_t shndx;      // Индекс секции строк (string table), содержащей имена секций
    uint8_t sections[0]; // Массив записей о секциях (переменной длины)
};

struct multiboot_tag_apm {
    uint32_t type;    // Тип тега, равен 10 (MULTIBOOT_TAG_TYPE_APM)
    uint32_t size;    // Общий размер тега в байтах (обычно 20)
    uint16_t version; // Версия APM (например, 0x0101 для 1.1)
    uint16_t cseg;    // 16-битный сегмент кода APM (реальный режим)
    uint32_t offset;  // 32-битное смещение точки входа APM
    uint16_t cseg_16; // 16-битный сегмент кода для 16-битного защищённого режима
    uint16_t dseg;    // 16-битный сегмент данных
    uint16_t flags;   // Флаги состояния APM
    uint16_t cseg_len;// Длина сегмента кода (в байтах)
    uint16_t cseg_16_len; // Длина 16-битного сегмента кода
    uint16_t dseg_len;// Длина сегмента данных
};

struct multiboot_tag_efi32 {
    uint32_t type;       // Тип тега, равен 11 (MULTIBOOT_TAG_TYPE_EFI32)
    uint32_t size;       // Общий размер тега в байтах (обычно 12)
    uint32_t pointer;    // Указатель на EFI System Table (32-битный адрес)
};

struct multiboot_tag_efi64 {
    uint32_t type;       // Тип тега, равен 12 (MULTIBOOT_TAG_TYPE_EFI64)
    uint32_t size;       // Общий размер тега в байтах (обычно 16)
    uint64_t pointer;    // Указатель на EFI System Table (64-битный адрес)
};

struct multiboot_tag_smbios {
    uint32_t type;       // Тип тега, равен 13 (MULTIBOOT_TAG_TYPE_SMBIOS)
    uint32_t size;       // Общий размер тега в байтах
    uint8_t major;       // Мажорная версия SMBIOS
    uint8_t minor;       // Минорная версия SMBIOS
    uint8_t reserved[6]; // Зарезервировано (заполняется нулями)
    uint8_t tables[0];   // Начало данных таблиц SMBIOS (переменной длины)
};
#endif