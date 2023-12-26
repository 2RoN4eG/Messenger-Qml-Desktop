#include "t_fs.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>


namespace {
    using t_entry = std::filesystem::directory_entry;
using t_directory_entries = std::filesystem::recursive_directory_iterator;
}

bool t_fs::does_exist(const t_fs_path& path) const {
    return std::filesystem::exists(path);
}

bool t_fs::is_directory(const t_fs_path& path) const {
    return std::filesystem::is_directory(path);
}

void t_fs::do_create_directories(const t_fs_path& path) const {
    if (does_exist(path)) {
        return;
    }

    if (!std::filesystem::create_directories(path)) {
        throw std::runtime_error { "directories did not create on drive by path " + path.string() };
    }
}

std::set<t_fs_path> t_fs::get_paths_in_directory(const t_fs_path& root) const {
    if (!does_exist(root)) {
        return {};
    }

    std::set<t_fs_path> paths;
    std::ranges::for_each (t_directory_entries { root }, [&paths](const t_entry& entry) {
        if (entry.is_directory()) {
            return;
        }

        paths.emplace(entry.path());
    });

    return paths;
}

std::set<t_fs_meta> t_fs::get_metas_in_directory(const t_fs_path& root) const {
    if (!does_exist(root)) {
        return {};
    }

    std::set<t_fs_meta> metas;
    std::ranges::for_each (t_directory_entries { root }, [&metas](const t_entry& entry) {
        if (entry.is_directory()) {
            return;
        }

        metas.emplace(entry.path(), entry.file_size(), entry.last_write_time());
    });

    return metas;
}

void t_fs::do_directories_remove(const t_fs_path& path) const {
    std::filesystem::remove_all(path);
}

t_fs_size t_fs::get_size(const t_fs_path& path) const {
    return std::filesystem::file_size(path);
}

t_fs_timestamp t_fs::get_timestamp(const t_fs_path& path) const {
    return std::filesystem::last_write_time(path);
}

t_fs_line t_fs::read_as_single_line(const t_fs_path &path) const {
    std::fstream istream { path, std::ios::in };
    if (!istream.is_open()) {
        return {};
    }

    std::stringstream sstream;
    t_fs_line line {};
    while(getline(istream, line)) {
        sstream << line << std::endl;
    }
    istream.close();

    return sstream.str();
}

void t_fs::do_write_to_drive(const t_ui_image& image, const t_fs_path& path) const {
    if (!image.save(QString::fromStdString(path.string()))) {
        throw std::runtime_error { "image did not write on drive by path " + path.string() };
    }
}

t_ui_image t_fs::do_read_from_drive(const t_fs_path& path) const {
    t_ui_image image {};

    if (!image.load(QString::fromStdString(path.string()))) {
        throw std::runtime_error { "image did not read on drive by path " + path.string() };
    }

    return image;
}
