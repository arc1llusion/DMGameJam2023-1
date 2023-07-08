

#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## IMPORTS
#####
import unreal

print('starting ai_updates.py')


######## THING
#####



#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## VARIABLES
#####

######## THING
#####



#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## FUNCTIONS
#####

######## THING
#####


# ######## RETRIEVE UPDATE DATA
# #####
# def retrieve_update_data(packname='visai'):
#     if packname=="visai":
#         dataURL = 'https://ai.vis-foundation.com/data/renames.html'         # Get Data
#     elif packname=="visgm":
#         dataURL = 'https://gm.vis-foundation.com/data/renames.html'         # Get Data
#     else:
#         return "pack not recognized. use all lowercase, no spaces"

#     # Cleanup
#     thePage = str(urllib2.urlopen(dataURL).read())                          # Format to a string
#     parsedReq = thePage.split("#")                                          # Split String Data
#     del parsedReq[0]                                                        # Remove Null Data
#     del parsedReq[-1]                                                       # Remove Null Data
#     return parsedReq




# ######## CLEAN UPDATE DATA
# #####
# def clean_update_data(listToClean):
#     versionUpdateDataList = []
#     for i in listToClean:
#         j = i.replace(' ','')
#         k = j.replace('\\n','')
#         versionUpdateDataList.append(k)
#     return versionUpdateDataList




#!-!-!-!-!-!-!-!-!-!-!-!-!-!-#
#####
######## THE APP
#####

######## THING
#####



print('ai_updates.py has been initialized')
