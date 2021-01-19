import shotgun_api3


def connect(url,login,passwd):
    sg = shotgun_api3.Shotgun(url,login=login,password=passwd)
    print('OK')
    return sg

def findProjectList(sg):
    result = sg.find("Project", [['archived','is',False],['is_template','is',False],['sg_status','is','Active']], ['name','is_template','sg_status'])
    print(result)
    return result

def findAssetTypeList(sg,project_id):
    assets = sg.find("Asset",[['project','is',{'type':'Project','id':project_id}]],['sg_asset_type'])
    assetTypelist = []
    for asset in assets:
        asset_type = asset['sg_asset_type']
        if asset_type not in assetTypelist:
            assetTypelist.append(asset_type)

    print assetTypelist
    return assetTypelist

def findSequenceList(sg,project_id):
    sequences = sg.find("Sequence",[['project','is',{'type':'Project','id':project_id}]],['code'])
    sequenceList = []
    for sequence in sequences:
        sequence_code = sequence['code']
        if sequence_code not in sequenceList:
            sequenceList.append(sequence_code)

    print sequenceList
    return sequenceList

def findAssetList(sg,project_id,assetType):
    assets = sg.find("Asset",[['project','is',{'type':'Project','id':project_id}],['sg_asset_type','is',assetType]],['code'])
    assetList = []
    for asset in assets:
        asset_code = asset['code']
        if asset_code not in assetList:
            assetList.append(asset_code)

    print assetList
    return assetList

def findShotList(sg,project_id,sequence_ode):
    shots = sg.find("Shot",[['project','is',{'type':'Project','id':project_id}],['sg_sequence.Sequence.code','is',sequence_ode]],['code'])
    shotList = []
    for shot in shots:
        shot_code = shot['code']
        if shot_code not in shotList:
            shotList.append(shot_code)

    print shotList
    return shotList

def findAssetTaskList(sg,project_id,asset_code):
    tasks = sg.find("Task",[['project','is',{'type':'Project','id':project_id}],['entity.Asset.code','is',asset_code]],['content'])
    taskList = []
    for task in tasks:
        task_content = task['content']
        if task_content not in taskList:
            taskList.append(task_content)

    print taskList
    return taskList    

def findShotTaskList(sg,project_id,shot_code):
    tasks = sg.find("Task",[['project','is',{'type':'Project','id':project_id}],['entity.Shot.code','is',shot_code]],['content'])
    taskList = []
    for task in tasks:
        task_content = task['content']
        if task_content not in taskList:
            taskList.append(task_content)

    print taskList
    return taskList    