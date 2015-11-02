from datetime import datetime
import pandas as pd

PARAMSPATH = "./parameters"
TABLESPATH = "./tables"
PARAMS = ['stock10','startYear10','stock1000','start300Days',
    'startPeriod','endPeriod','SP500','start6Mo','Russell2000']

# loading query parameters    
def load_params():
    param_dict = {}
    for param in PARAMS:
        path = PARAMSPATH + "/" + param + ".csv"
        file = open(path)
        value = file.readlines()[0].split(",")
        if "." in value[0]:
            value = pd.to_datetime(value[0], format = "%Y.%m.%d")
        param_dict[param] = value
    
    return param_dict


param_values = load_params()
stock10 = param_values.get("stock10")
startYear10 = param_values.get("startYear10")
stock1000 = param_values.get("stock1000")
start300Days = param_values.get("start300Days")
startPeriod = param_values.get("startPeriod")
endPeriod = param_values.get("endPeriod")
SP500 = param_values.get("SP500")
start6Mo = param_values.get("start6Mo")
Russell2000 = param_values.get("Russell2000")

# loading tables
price = pd.read_pickle(TABLESPATH + "/" + "price_pandas")
base = pd.read_pickle(TABLESPATH + "/" + "base_pandas")
split = pd.read_pickle(TABLESPATH + "/" + "split_pandas")


            
        
        
    
    
