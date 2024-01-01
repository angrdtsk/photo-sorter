#include <string>
#include <iostream>
#include <filesystem>

#include <cxxopts.hpp>

#include "photo_file.h"

void parse_date_range_string(const std::string &string, std::time_t &time)
{
        std::tm tm{};
        std::istringstream ss(string);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        time = std::mktime(&tm);
}

int main(int argc, char ** argv)
{
    cxxopts::Options cl_options("photo-sorter", "Photo file sorter");
    cl_options.add_options()
        ("source", "Source directory", cxxopts::value<std::string>())
        ("target", "Target directory", cxxopts::value<std::string>())
        ("s,start", "Start date", cxxopts::value<std::string>())
        ("e,end", "End date", cxxopts::value<std::string>())
        ;
    cl_options.parse_positional({"source", "target"});
    cl_options.positional_help("<source> <target>");
    auto cl_parser_result = cl_options.parse(argc, argv);

    if ((cl_parser_result.count("source") == 0) || (cl_parser_result.count("target") == 0))
    {
        std::cout << cl_options.help() << std::endl;
        return 0;
    }

    const std::filesystem::path source_directory_path = cl_parser_result["source"].as<std::string>();
    if (!std::filesystem::exists(source_directory_path))
    {
        std::cout << "Source directory given doesn't exist" << std::endl;
        return 0;
    }

    const std::filesystem::path target_directory_path = cl_parser_result["target"].as<std::string>();
    if (!std::filesystem::exists(target_directory_path))
    {
        std::cout << "Target directory given doesn't exist" << std::endl;
        return 0;
    }

    bool filter_with_date = false;
    std::time_t start_date;
    std::time_t end_date;
    if ((cl_parser_result.count("start") == 1) && (cl_parser_result.count("end") == 1))
    {
        std::string start_date_string = cl_parser_result["start"].as<std::string>();
        std::string end_date_string = cl_parser_result["end"].as<std::string>();

        parse_date_range_string(start_date_string, start_date);
        parse_date_range_string(end_date_string, end_date);

        if ((start_date != -1) && (end_date != -1))
        {
            filter_with_date = true;
        }
    }

    for (const auto &source_entry_it : std::filesystem::recursive_directory_iterator(source_directory_path))
    {
        std::filesystem::path source_entry_path = source_entry_it.path();
 
        std::string source_entry_extension = source_entry_path.extension();

        if (PhotoFile::is_photo_file(source_entry_extension))
        {
            std::cout << "photo" << std::endl;
            try
            {
                PhotoFile photo_file(source_entry_path, target_directory_path);
                if (!filter_with_date)
                {
                    photo_file.copy_file();
                }
                else if (filter_with_date && photo_file.is_within_date_range(start_date, end_date))
                {
                    photo_file.copy_file();
                }
            }
            catch (const std::exception &e)
            {
                std::cout << std::string(e.what()) << std::endl;
            }
        }
        else
        {
            std::cout << "unknown" << std::endl;
        }
    }
}
