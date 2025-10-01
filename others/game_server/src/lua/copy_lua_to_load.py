import os
import shutil

def copy_lua_files(src_dir, dest_dir):
    if not os.path.exists(dest_dir):
        raise FileNotFoundError(f"Destination directory '{dest_dir}' does not exist.")

    for root, dirs, files in os.walk(src_dir):
        for file in files:
            if file.endswith('.lua'):
                src_file_path = os.path.join(root, file)
                relative_path = os.path.relpath(root, src_dir)
                dest_subdir = os.path.join(dest_dir, relative_path)

                if not os.path.exists(dest_subdir):
                    os.makedirs(dest_subdir)

                dest_file_path = os.path.join(dest_subdir, file)
                shutil.copy2(src_file_path, dest_file_path)
                print(f'Copy2: {src_file_path} to {dest_file_path}')

if __name__ == "__main__":
    # python脚本路径
    source_directory = os.path.dirname(os.path.abspath(__file__))
    destination_directory = os.path.join(source_directory, "../../cmake-build-debug/bin/")  # 目标目录

    try:
        copy_lua_files(source_directory, destination_directory)
        print("All .lua files have been copied successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")