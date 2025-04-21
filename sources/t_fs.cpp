#include "t_fs.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>


namespace
{
    using t_entry = std::filesystem::directory_entry;

    using t_directory_entries = std::filesystem::recursive_directory_iterator;
}

bool t_fs::does_path_exist(const t_fs_path& path) const
{
    return std::filesystem::exists(path);
}

bool t_fs::is_directory(const t_fs_path& path) const
{
    return std::filesystem::is_directory(path);
}

void t_fs::create_directories(const t_fs_path& path) const
{
    if (does_path_exist(path))
    {
        return;
    }

    if (!std::filesystem::create_directories(path))
    {
        throw std::runtime_error { "directories did not create on drive by path " + path.string() };
    }
}

std::set<t_fs_path> t_fs::get_directory_file_paths(const t_fs_path& root) const
{
    if (!does_path_exist(root))
    {
        return {};
    }

    std::set<t_fs_path> paths {};
    std::ranges::for_each (t_directory_entries { root }, [&paths](const t_entry& entry)
    {
        if (entry.is_directory())
        {
            return;
        }

        const t_fs_path path = entry.path();

        paths.emplace(path);

        std::cout << " [] path is " << path << std::endl;
    });

    return paths;
}

t_fs_metas t_fs::get_metas_in_directory(const t_fs_path& root) const
{
    if (!does_path_exist(root))
    {
        return {};
    }

    t_fs_metas metas {};
    std::ranges::for_each (t_directory_entries { root }, [&metas](const t_entry& entry)
    {
        if (entry.is_directory())
        {
            return;
        }

        metas.emplace(entry.path(), entry.file_size(), entry.last_write_time());
    });

    return metas;
}

void t_fs::do_directories_remove(const t_fs_path& path) const
{
    std::filesystem::remove_all(path);
}

t_fs_size t_fs::get_size(const t_fs_path& path) const
{
    return std::filesystem::file_size(path);
}

t_fs_timestamp t_fs::get_timestamp(const t_fs_path& path) const
{
    return std::filesystem::last_write_time(path);
}

t_fs_line t_fs::read_as_single_line(const t_fs_path &path) const
{
    std::fstream input_stream { path, std::ios::in };
    if (!input_stream.is_open())
    {
        return {};
    }

    std::stringstream string_stream;
    for (t_fs_line line {}; getline(input_stream, line); )
    {
        string_stream << line << std::endl;
    }
    input_stream.close();

    return string_stream.str();
}

void t_fs::do_write_image_to_drive(const t_fs_path& path, const t_ui_image& image) const
{
    if (!image.save(path.c_str()))
    {
        throw std::runtime_error { "image did not write to drive, path is " + path.string() };
    }
}

t_ui_image t_fs::do_read_image_from_drive(const t_fs_path& path) const
{
    t_ui_image image {};
    if (!image.load(path.c_str()))
    {
        throw std::runtime_error { "image did not read from drive, path " + path.string() };
    }

    return image;
}
