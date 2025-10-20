<h1 align="center">Math Gadalka Telegram Bot</h1>

[![English version](https://img.shields.io/badge/English%20version-blue)](README.md)

<h2>Обзор</h2>

Телеграм-бот на C++, выполняющий вычисление математических выражений, в том числе в inline-режиме.
Поддерживаются базовые и продвинутые функции из следующих категорий:

* Арифметические операции
* Тригонометрические функции
* Логарифмы
* Степени

Вычисления выполняются при помощи собственной библиотеки и движка функций.

<h2>Технологии</h2>

Стандарт компиляции: **C++23**

Зависимости:
* [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp) — Telegram Bot API для C++
* [nlohmann-json](https://github.com/nlohmann/json) — работа с JSON
* [sqlite3](https://sqlite.org/download.html) — встраиваемая база данных SQL
* [MathWorker](https://github.com/Igorantivirus/MathWorker) — C++ библиотека для обработки математических выражений

<h2>План и идеи</h2>

* Настройки бота: кнопки и меню
* Расширение набора предопределённых функций и примеров
* Режим систем/многострочных выражений

<h2>Сборка</h2>

1. <b>Клонирование репозитория</b>
   
   ```sh
   git clone https://github.com/Igorantivirus/MathTgBot
   ```
2. <b>Генерация CMake</b>
   
   ```sh
   cmake -B build
   ```
3. <b>Сборка</b>
   
   ```sh
   cmake --build build --config Release
   ```
4. <b>Настройка конфигов</b>
   
   Отредактируйте файл `assets/mainConfig.json`. Минимальные шаги:
   - Укажите токен API бота
   - Убедитесь, что указан путь к файлу ответов `assets/responseConfig.json`
5. <b>Запуск</b>
   
   Перейдите в папку `build` и запустите исполняемый файл `MathBot`,
   передав путь к конфигу `assets/mainConfig.json`:
   
   ```sh
   ./MathBot "path/assets/mainConfig.json"
   ```

<h2>Лицензия</h2>

**MIT License**

