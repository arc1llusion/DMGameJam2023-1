#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## IMPORTS
#####

print('updater.py has started')
import sys
import os
import shutil
import unreal


# For keeping a backup of the template files so users dont' have to reimport it everytime.
from distutils.dir_util import copy_tree



#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## VARIABLES
#####


paths_vis_main_original_dir = unreal.Paths.project_content_dir() + "Vis/AI/Base/EditorTools/Base/Python"
paths_vis_python_original_dir = paths_vis_main_original_dir + "/vis"

paths_engine_content_dir = unreal.Paths.convert_relative_path_to_full(unreal.Paths.engine_content_dir())
paths_unreal_plugins_dir = unreal.Paths.convert_relative_path_to_full(unreal.Paths.engine_plugins_dir())
paths_vis_python_desired_dir = paths_engine_content_dir + "Python"
paths_vis_ai_template_backups_dir = paths_unreal_plugins_dir + "vis/"


paths_updater_py_file = paths_vis_main_original_dir + "updater.py"


paths_local_vis_py_file = "/vis.py"
paths_local_vis_ai_dir = "/ai"
paths_local_vis_ai_saved_dir = paths_local_vis_ai_dir + "/saved"
paths_local_vis_ai_backups_file = "/ai_backups.py"
paths_local_vis_ai_test_file = "/ai_test.py"
paths_local_vis_ai_updates_file = "/ai_updates.py"
paths_local_vis_ai_subsystems_data_file = paths_local_vis_ai_saved_dir + "/subsystemdata.ai"
paths_visai_new_version_indicator_file = paths_local_vis_ai_saved_dir + "/new_version_indicator.ai"


paths_vis_py_file_original = paths_vis_python_original_dir + paths_local_vis_py_file
paths_vis_ai_backups_file_original = paths_vis_python_original_dir + paths_local_vis_ai_backups_file
paths_vis_ai_test_file_original = paths_vis_python_original_dir + paths_local_vis_ai_test_file
paths_vis_ai_updates_file_original = paths_vis_python_original_dir + paths_local_vis_ai_updates_file
paths_vis_ai_subsystems_data_file_original = paths_vis_python_original_dir + paths_local_vis_ai_subsystems_data_file

paths_visai_new_version_indicator_file_full = paths_vis_python_original_dir + paths_visai_new_version_indicator_file



paths_vis_py_file = paths_vis_python_desired_dir + paths_local_vis_py_file
paths_vis_ai_backups_file = paths_vis_python_desired_dir + paths_local_vis_ai_backups_file
paths_vis_ai_test_file = paths_vis_python_desired_dir + paths_local_vis_ai_test_file
paths_vis_ai_updates_file = paths_vis_python_desired_dir + paths_local_vis_ai_updates_file
paths_vis_ai_subsystems_data_file = paths_vis_python_desired_dir + paths_local_vis_ai_subsystems_data_file




# these need to be moved.
paths_unreal_content_dir_updater = unreal.Paths.convert_relative_path_to_full(unreal.Paths.engine_content_dir())
paths_unreal_plugins_dir_updater = unreal.Paths.convert_relative_path_to_full(unreal.Paths.engine_plugins_dir())
paths_vis_ai_template_backup_dir_updater = paths_unreal_plugins_dir + "vis/Template/"
paths_vis_ai_template_live_dir_updater = unreal.Paths.project_content_dir() + "Vis/AI/Base/Template"


# Core File List
vis_core_files_list = [
    paths_local_vis_py_file,
    paths_local_vis_ai_backups_file,
    paths_local_vis_ai_test_file,
    paths_local_vis_ai_updates_file,

]

vis_user_files_list = [
    paths_local_vis_ai_subsystems_data_file,

]

vis_core_desired_directory_list = [
    paths_vis_python_desired_dir,
    paths_vis_python_desired_dir + paths_local_vis_ai_dir,
    paths_vis_python_desired_dir + paths_local_vis_ai_saved_dir,
    paths_vis_ai_template_backups_dir,
    paths_vis_ai_template_backups_dir+"Template/"

]



#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## FUNCTIONS
#####


######## VALIDATE NEW VIS FILES
#####
def validate_new_vis_files():
    # if there are new files;
    if os.path.isfile(paths_vis_py_file_original):
        return True
    else: 
        return False


def validate_vis_core_files():
    for file in vis_core_files_list:
        if os.path.isfile(file):
            continue
        else:
            return False
    return True

def validate_vis_user_files():
    for file in vis_core_files_list:
        if os.path.isfile(file):
            continue
        else:
            return False
    return True

######## CREATE DIRECTORIES
#####
def create_vis_dirs():
    for visdir in vis_core_desired_directory_list:
        if not os.path.isdir(visdir):
            os.mkdir(visdir + "/")


######## REMOVE VIS FILES
#####
def remove_vis_files():
    for file in vis_core_files_list:
        if os.path.isfile(paths_vis_python_desired_dir + file):
            os.remove(paths_vis_python_desired_dir + file)


######## UPDATE VIS CORE FILES
##### always update's core files
def update_vis_core_files():
    for file in vis_core_files_list:
        if os.path.isfile(paths_vis_python_original_dir + file):
            shutil.copy(paths_vis_python_original_dir + file, paths_vis_python_desired_dir + file)


######## UPDATE VIS USER FILES
##### only update if not valid
def update_vis_user_files():
    for file in vis_user_files_list:
        if not os.path.isfile(paths_vis_python_desired_dir + file):
            shutil.copy(paths_vis_python_original_dir + file, paths_vis_python_desired_dir + file)


######## UPDATE VIS FILES
#####
def update_vis_files():

    # Remove old files if they exist
    remove_vis_files()

    # Create new directories if they don't exist
    create_vis_dirs()

    # Transfer new core-files
    update_vis_core_files()

    # Transfer new user-files if they don't exist
    update_vis_user_files()

    # Return True if the files are still there
    if validate_vis_user_files() and validate_vis_core_files():
        return True
    else:
        return False


######## NEW VERSION CHECK
#####
def visai_new_version_check():
    print('vis.py - checking for new version')
    if os.path.isfile(paths_visai_new_version_indicator_file_full):
        print('vis.py - new VisAI import detected.')
        return True
    else:
        return False



######## BACKUP VISAI TEMPLATE FILES
#####
def updater_backup_visai_template():
    if os.path.isdir(paths_vis_ai_template_live_dir_updater):
        #If current backup template exists, remove it (for updates). This should be changed to a version check instead.
        if os.path.isdir(paths_vis_ai_template_backup_dir_updater):
            shutil.rmtree(paths_vis_ai_template_backup_dir_updater)
        # Copy live files to backup
        shutil.copytree(paths_vis_ai_template_live_dir_updater, paths_vis_ai_template_backup_dir_updater)
    if os.path.isdir(paths_vis_ai_template_backup_dir_updater):
        return True
    else:
        return False


######## RESTORE SUBSYSTEM DATA FILE
#####

def restore_subsystem_data_file():
    if os.path.isfile(paths_vis_ai_subsystems_data_file_original):
        os.remove(paths_vis_ai_subsystems_data_file)
        shutil.copy(paths_vis_ai_subsystems_data_file_original, paths_vis_ai_subsystems_data_file)


#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## THE APP
#####



# If there's a new version, move python files, backup template assets.
if visai_new_version_check():

    # Backup Template
    updater_backup_visai_template()

    # Copy Python Files Over.
    update_vis_files()

    # Remove New Version Indicator.
    os.remove(paths_visai_new_version_indicator_file_full)


#update_vis_files() #use in unreal to update files
print('updater.py has initialized')





### The code that didn't make it... :'(

# copy_tree(paths_vis_python_original_dir + "/", paths_vis_python_desired_dir + "/")
# shutil.copytree(paths_vis_python_original_dir + "/", paths_vis_python_desired_dir + "/")