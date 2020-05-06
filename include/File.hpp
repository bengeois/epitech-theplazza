/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** File
*/

#ifndef FILE_HPP_
#define FILE_HPP_

#include <string>
#include <fstream>

namespace Plazza
{
    class File {
        public:
            File(const std::string &path, std::ios_base::openmode mode);
            ~File();
            File(const File &file) = delete;
            File &operator=(const File &file) = delete;

            bool getNextLine(std::string &line);

            File &operator<<(const std::string &name);
            File &operator<<(std::ostream& (*os)(std::ostream&));

        private:
            const std::string _path;
            std::fstream _fileStream;
    };
} // namespace arc

#endif /* !FILE_HPP_ */
