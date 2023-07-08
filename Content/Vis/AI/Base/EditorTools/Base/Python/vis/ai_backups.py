


# If you've somehow found this in your ai journey, don't judge my bad code! I worked 18h straight to get this ready for an update lol...
# Clean will happen later!
#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## IMPORTS
#####
import unreal
import os
import sys
import shutil


print('ai_backups.py has started')

# copy_tree might be used instead of shutil.copytree at some point.
from distutils.dir_util import copy_tree

#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## VARIABLES
#####



######## PATHS
#####

paths_unreal_content_dir = unreal.Paths.convert_relative_path_to_full(unreal.Paths.engine_content_dir())
paths_unreal_plugins_dir = unreal.Paths.convert_relative_path_to_full(unreal.Paths.engine_plugins_dir())



paths_vis_main_contents_dir = paths_unreal_content_dir + "Python"
paths_vis_ai_dir = paths_vis_main_contents_dir + "/ai"
paths_vis_ai_savedata_dir = paths_vis_ai_dir + '/saved'


paths_vis_ai_template_live_dir = unreal.Paths.project_content_dir() + "Vis/AI/Base/Template"
paths_vis_ai_template_test_file = "/VisAI_HealthAndDamage_Temp_C.uasset"
paths_vis_ai_template_test_file_full = paths_vis_ai_template_live_dir + "/Base" + paths_vis_ai_template_test_file
paths_vis_ai_template_backup_dir = paths_unreal_plugins_dir + "vis/Template/"
paths_vis_ai_subsystem_savedata_file = paths_vis_ai_savedata_dir + "/subsystemdata.ai"
paths_vis_ai_original_subsystem_savedata_file = unreal.Paths.project_content_dir() + "Vis/AI/Base/EditorTools/Base/Python/vis/ai/saved/subsystemdata.ai"
paths_vis_ai_new_version_indicator_file = paths_vis_ai_savedata_dir + "/new_version_indicator.ai"


######## FILE NAMES
#####




#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## FUNCTIONS
#####
######## COPYTREE THAT WORKS BETTER
#####
def vis_copytree(src, dst, symlinks=False, ignore=None):
    for item in os.listdir(src):
        s = os.path.join(src, item)
        d = os.path.join(dst, item)
        if os.path.isdir(s):
            shutil.copytree(s, d, symlinks, ignore)
        else:
            shutil.copy(s, d)


######## ADD NEW SUBSYSTEM TO DATA
#####
def add_new_subsystem_to_data(subsystemName, subsystemNamingConvention):

    # If file doesn't exist
    if not os.path.isfile(paths_vis_ai_subsystem_savedata_file):
        # Create new file, write subsystem data to file
        anstd_local_subsystem_data_file = open(paths_vis_ai_subsystem_savedata_file, "w+")
        anstd_local_subsystem_data_file.write(subsystemName + "," + subsystemNamingConvention + "\n")
        anstd_local_subsystem_data_file.close()
    else:
        # Append to current subsystem data
        anstd_local_subsystem_data_file = open(paths_vis_ai_subsystem_savedata_file, "a+")
        anstd_local_subsystem_data_file.write(subsystemName + "," + subsystemNamingConvention + "\n")
        anstd_local_subsystem_data_file.close()





######## READ SUBSYSTEM DATA FILE
#####
def read_subsystem_data_file():
    rsdf_local_contents = ""
    # Read and return contents
    if os.path.isfile(paths_vis_ai_subsystem_savedata_file):
        rsdf_local_subsystem_data_file = open(paths_vis_ai_subsystem_savedata_file, "r")
        rsdf_local_contents = rsdf_local_subsystem_data_file.read()
        rsdf_local_subsystem_data_file.close()
        return rsdf_local_contents
    else:
        return rsdf_local_contents



######## READ ALL SUBSYSTEM NAMES
#####
def read_all_subsystem_names():
    # Data
    rasn_names_list = ['']
    rasn_subsystemdata = read_subsystem_data_file()
    rasn_subsystemsdata_parsed = rasn_subsystemdata.split("\n")

    # Loop through and get all names, add to a list
    for i in rasn_subsystemsdata_parsed: 
        rasn_x = i.split(',')
        rasn_name = rasn_x[0]
        rasn_names_list.append(rasn_name)
    
    # Clean up data
    del rasn_names_list[0]
    del rasn_names_list[-1] 

    # Return Data
    return rasn_names_list



######## READ ALL NAMING CONVENTIONS
#####
def read_all_subsystem_naming_conventions():
    # Data
    rasn_names_list = ['']
    rasn_subsystemdata = read_subsystem_data_file()
    rasn_subsystemsdata_parsed = rasn_subsystemdata.split("\n")

    # Loop through and get all names, add to a list
    for i in rasn_subsystemsdata_parsed: 
        rasn_x = i.split(',')
        rasn_name = rasn_x[-1]
        rasn_names_list.append(rasn_name)
    
    # Clean up data
    del rasn_names_list[0]
    del rasn_names_list[-1] 

    # Return Data
    return rasn_names_list



######## READ SUBSYSTEM NAMING CONVENTION
##### 
def read_subsystem_naming_convention(subsystemName = ""):
    rsnc_subsystem_name_index = read_all_subsystem_names().index(subsystemName)
    rsnc_subsystem_name = read_all_subsystem_naming_conventions()[rsnc_subsystem_name_index]
    return rsnc_subsystem_name



######## BACKUP VISAI TEMPLATE FILES
#####
def backup_visai_template():
    if os.path.isdir(paths_vis_ai_template_live_dir):
        #If current backup template exists, remove it (for updates). This should be changed to a version check instead.
        if os.path.isdir(paths_vis_ai_template_backup_dir):
            shutil.rmtree(paths_vis_ai_template_backup_dir)
        # Copy live files to backup
        shutil.copytree(paths_vis_ai_template_live_dir, paths_vis_ai_template_backup_dir)
    if os.path.isdir(paths_vis_ai_template_backup_dir):
        return True
    else:
        return False



######## BACKUP VISAI TEMPLATE FILES
#####
def restore_visai_template():
    #need to make this a try
    #shutil.rmtree(paths_vis_ai_template_live_dir)
    shutil.copytree(paths_vis_ai_template_backup_dir, paths_vis_ai_template_live_dir)
    if os.path.isdir(paths_vis_ai_template_live_dir):
        return True
    else:
        return False



#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## THE APP
#####



######## BACKUP VISAI TEMPLATE FILES
#####

#backup_visai_template()

# this is borken
# need to make it check if template *asset* doesn't exist in the folder, and verify there's a current template ready. ,
# before that, need to have a way to properly deal with references.
# if not os.path.isfile(paths_vis_ai_template_test_file_full):
#     if unreal.Paths.directory_exists(paths_vis_ai_template_backup_dir):
#         restore_visai_template()



print('ai_backups.py has initialized')


# - EOF - #
# print(read_subsystem_naming_convention("Subsystem Name"))

# to use this in unreal, do; 
# to read a naming convention;
# unreal.log(read_subsystem_naming_convention("Subsystem Name"))
# to add a subsystem; 
# add_new_subsystem_to_data("ThisTest", "TST")

