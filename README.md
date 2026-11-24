# M5StickC Plus2 Air Mouse

Bluetooth-мышь с управлением движением для **M5StickC Plus2**. Гироскоп управляет курсором, а кнопки устройства работают как левая и правая кнопки мыши.

**Проект из видео Electronic / @electronicworld12.**

- 🎬 [Видео: Tutor on Air mouse on M5stick Plus2](https://www.tiktok.com/@electronicworld12/video/7625605493150551303)
- 📱 [TikTok — @electronicworld12](https://www.tiktok.com/@electronicworld12)
- 💬 [Telegram — electronicworld12](https://t.me/m5stiksplus2)

## Возможности

- Подключение по Bluetooth LE под именем **M5-Air-Remote**.
- Движение курсора по двум осям гироскопа.
- Сглаживание движения и мёртвая зона для уменьшения дрожания.
- Нажатие и удержание левой и правой кнопок мыши.
- Медленный режим с надписью `25% SPEED MODE` на экране.

## Что понадобится

- M5StickC Plus2 и USB-C кабель с передачей данных.
- Компьютер с Arduino IDE для загрузки скетча.
- Устройство с поддержкой Bluetooth LE HID для подключения мыши.

## Библиотеки и проверенная сборка

Скетч успешно скомпилирован со следующими версиями:

| Компонент | Версия |
| --- | --- |
| esp32 by Espressif Systems | 2.0.14 |
| [M5Unified](https://github.com/m5stack/M5Unified) | 0.2.21 |
| [M5GFX](https://github.com/m5stack/M5GFX) | 0.2.28 |
| [ESP32 BLE Mouse by T-vK](https://github.com/T-vK/ESP32-BLE-Mouse) | 0.3.1 |

Профиль платы для этой сборки: **M5Stick-C** (`esp32:esp32:m5stick-c`), схема разделов **Default**. Это название профиля в указанной версии пакета esp32; целевое устройство проекта — M5StickC Plus2.

## Установка

1. В настройках Arduino IDE добавьте адрес пакета плат Espressif в поле **Additional Boards Manager URLs**:

   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```

2. В **Boards Manager** установите **esp32 by Espressif Systems 2.0.14**.
3. В **Library Manager** установите **M5Unified 0.2.21** и **M5GFX 0.2.28**. Библиотеку **ESP32 BLE Mouse 0.3.1** можно скачать со [страницы релизов](https://github.com/T-vK/ESP32-BLE-Mouse/releases) и установить через **Sketch → Include Library → Add .ZIP Library**.
4. На странице этого репозитория выберите **Code → Download ZIP** и распакуйте архив.
5. Откройте файл [`M5AirMouse/M5AirMouse.ino`](M5AirMouse/M5AirMouse.ino) в Arduino IDE.
6. Выберите плату **M5Stick-C** и USB-порт вашего устройства. Оставьте схему разделов **Default**.
7. Нажмите **Verify**, затем **Upload**. Загрузка заменит текущую программу на устройстве.
8. После запуска откройте настройки Bluetooth компьютера и подключитесь к **M5-Air-Remote**.

## Управление

| Действие | Результат |
| --- | --- |
| Поворот устройства | Перемещение курсора |
| BtnA — передняя кнопка | Левая кнопка мыши |
| BtnB — боковая кнопка | Правая кнопка мыши |
| Удержание BtnA или BtnB | Удержание соответствующей кнопки мыши |

Движения и нажатия передаются только при активном Bluetooth-подключении. Прокрутка колёсиком в этой версии не реализована.

## Настройка чувствительности

В начале скетча находятся три параметра:

```cpp
float sensitivity = 0.87; // Больше значение — быстрее курсор.
float deadzone = 2.0;    // Больше значение — меньше реакция на слабое движение.
float filterK = 0.3;     // Меньше значение — сильнее сглаживание и больше задержка.
```

Оси из исходного кода: `inputX = -gz`, `inputY = -gx`. Перемещение ограничено диапазоном от −20 до +20 за цикл, задержка между циклами — 10 мс. Надпись `25% SPEED MODE` — название режима из исходного проекта, а не настройка скорости мыши в операционной системе.

## Проверка

При подготовке публикации восстановлены строки `#include <M5Unified.h>` и `#include <BleMouse.h>`, убраны символы экранирования и оформлены отступы. Алгоритм движения и значения параметров сохранены.

Сборка Arduino CLI завершилась успешно: **1 247 789 байт программы (95%)**, **41 756 байт глобальных переменных (12%)** для указанного профиля. Повторная проверка Bluetooth, кнопок и движения на физическом устройстве при подготовке публикации не проводилась. Другие версии библиотек и пакетов плат отдельно не проверялись.

---

**English:** Bluetooth LE air mouse for M5StickC Plus2. Gyroscope motion controls the cursor; BtnA is left click and BtnB is right click. Pair with **M5-Air-Remote**. Open `M5AirMouse/M5AirMouse.ino` in Arduino IDE and use the dependency versions listed above.
