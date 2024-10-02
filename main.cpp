#include <iostream>
#include <filesystem>
#include <fstream>
#include <set>
#include <windows.h>

// Используем пространство имен для работы с файловой системой
namespace fs = std::filesystem;

// Функция для логирования изменений в указанной директории
void logChanges(const std::string& dirPath) {
    // Множество для хранения существующих файлов
    std::set<std::string> existingFiles;
    // Открываем файл для логирования изменений в режиме добавления
    std::ofstream logFile("file_log.txt", std::ios::app);

    // Бесконечный цикл для постоянного мониторинга директории
    while (true) {
        // Множество для хранения текущих файлов в директории
        std::set<std::string> currFiles;

        try {
            // Проходим по всем элементам в директории
            for (const auto& entry : fs::directory_iterator(dirPath)) {
                currFiles.insert(entry.path().string()); // Добавляем путь к файлу в текущее множество
            }
        } catch (const fs::filesystem_error& err) {
            // Обработка ошибок доступа к директории
            std::cerr << "Ошибка доступа к вашей директории: " << err.what() << std::endl;
            return; // Выход из функции в случае ошибки
        }

        // Проверяем, есть ли новые файлы или папки
        for (const auto& file : currFiles) {
            if (existingFiles.find(file) == existingFiles.end()) {
                // Логируем новый файл или папку
                logFile << "Новый файл / добавленная папка: " << file << std::endl;
                std::cout << "Новый файл/папка добавлен: " << file << std::endl;
            }
        }

        // Поиск файлов по названию
        std::string searchTerm;
        std::cout << "Введите название файла или папки для поиска (или 'exit' для выхода): ";
        std::cin >> searchTerm; // Считываем название для поиска

        if (searchTerm == "exit") {
            break; // Выход из цикла, если пользователь ввел 'exit'
        }

        // Обновляем множество существующих файлов
        existingFiles = currFiles;
        Sleep(5500); // Задержка перед следующим мониторингом (5500 мс)
    }

    logFile.close(); // Закрываем файл логирования
}

int main() {
    std::string dirPath = "C:\\users"; // Путь к директории для мониторинга
    //std::cout << "Введите путь к директории. Слешы директории должны быть \\" << std::endl;
    //std::cin >> dirPath; // Возможность ввода пути пользователем

    // Убедитесь, что слеши правильные
    logChanges(dirPath); // Запускаем функцию логирования изменений

    return 0; // Завершаем программу
}
