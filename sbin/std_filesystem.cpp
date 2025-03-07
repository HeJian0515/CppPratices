#include <filesystem>
#include <iostream>
#include <format>

namespace fs = std::filesystem;

void path_use()
{
	fs::path currentPath = fs::current_path();
	std::cout << "root_name = " << currentPath.root_name() << std::endl;

	fs::path makefilePath = currentPath / "Makefile.Debug";
	std::cout << "makefile path = " << makefilePath.string() << std::endl;

	std::cout << "root_directory = " << currentPath.root_directory() << std::endl;

	std::cout << "root_path = " << currentPath.root_path() << std::endl;

	std::cout << "relative_path = " << currentPath.relative_path() << std::endl;

	std::cout << "parent_path = " << currentPath.parent_path() << std::endl;

	std::cout << "filename = " << currentPath.filename() << std::endl;

	std::cout << "stem = " << currentPath.stem() << std::endl;

	std::cout << "extension = " << currentPath.extension() << std::endl;
	std::cout << "extension = " << makefilePath.extension() << std::endl;


	std::cout << "empty = " << currentPath.empty() << std::endl;

	std::cout << std::format("empty = {}\n", currentPath.empty());
	std::cout << std::format("has_root_path = {}\n", currentPath.has_root_path());
	std::cout << std::format("has_root_name = {}\n", currentPath.has_root_name());
	std::cout << std::format("has_root_directory = {}\n", currentPath.has_root_directory());
	std::cout << std::format("has_relative_path = {}\n", currentPath.has_relative_path());
	std::cout << std::format("has_parent_path = {}\n", currentPath.has_parent_path());
	std::cout << std::format("has_filename = {}\n", currentPath.has_filename());
	std::cout << std::format("has_stem = {}\n", currentPath.has_stem());
	std::cout << std::format("has_extension = {}\n", currentPath.has_extension());

	std::cout << std::format("is_absolute = {}\n", currentPath.is_absolute());
	std::cout << std::format("is_relative = {}\n", currentPath.is_relative());

	std::cout << std::endl;
}

void directiry_entry()
{
	fs::path currentPath = fs::current_path();

	fs::path makefilePath = currentPath / "Makefile.Debug";
	std::cout << std::format("Makefile path = {}\n", makefilePath.string());

	fs::directory_entry dirEntry(currentPath);
	std::cout << std::format("exists = {}\n", dirEntry.exists());

	std::cout << std::format("is_block_file = {}\n", dirEntry.is_block_file());

	std::cout << std::format("is_character_file = {}\n", dirEntry.is_character_file());

	std::cout << std::format("is_directory = {}\n", dirEntry.is_directory());

	std::cout << std::format("is_fifo = {}\n", dirEntry.is_fifo());

	std::cout << std::format("is_other = {}\n", dirEntry.is_other());

	std::cout << std::format("is_regular_file = {}\n", dirEntry.is_regular_file());

	std::cout << std::format("is_socket = {}\n", dirEntry.is_socket());

	std::cout << std::format("is_symlink = {}\n", dirEntry.is_symlink());

	std::cout << std::format("file_size = {}\n", dirEntry.file_size());

	std::cout << std::format("hard_link_count = ", dirEntry.hard_link_count());

	std::cout << std::endl;
}

void sapce_info_use()
{
	fs::path currentPath = fs::current_path();
	std::cout << std::format("Current path is {}\n", currentPath.string());

	fs::path parentPath = currentPath.parent_path();
	std::cout << std::format("Parent path is {} \n", parentPath.string());

	fs::space_info devi = fs::space(currentPath);
	fs::space_info tmpi = fs::space(parentPath);

	std::cout << ".                 Capacity       Free        Available\n"
              << "current path:   " << devi.capacity << "   "
              << devi.free << "   " << devi.available  << '\n'
              << "parent  path:   " << tmpi.capacity << "   "
              << tmpi.free << "   " << tmpi.available  << '\n';

	std::cout << std::endl;

}


int main()
{
	// path_use();

	// directiry_entry();

	sapce_info_use();
}