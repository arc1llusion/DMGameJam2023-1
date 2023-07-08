#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## IMPORTS
#####
import unreal
import sys

#ignore my bad structure and code pls. ty sorry.

######## EXIT IF VISAI NOT INSTALLED
#####
if not unreal.Paths.directory_exists(unreal.Paths.project_content_dir()+"Vis/AI"):
    print('visai not found. exiting...')
    sys.exit(101)

print('vis.py has started')

######## BUILT IN
#####
import os


######## VIS
#####
#import ai_test

try:
    import ai_backups
except Exception as e:
    print(str(e) + " | This is most likely due to first time start")




print('vis.py - modules imported')






#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## VARIABLES
#####






#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## FUNCTIONS
#####








#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## THE APP
#####






print('vis.py has initialized')
