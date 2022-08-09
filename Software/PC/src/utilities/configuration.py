
import shelve
from pathlib import Path
from os import path
from os import makedirs
from platformdirs import user_config_dir
from utilities.singleton import singleton
import logging
logger = logging.getLogger(__name__)


class FrequencyRange:
    def __init__(self, f_min:float, f_max:float, scale:int, units:str, format='AM', label='' ):
        self.label = label
        self.f_min = f_min
        self.f_max = f_max
        self.scale = scale
        self.units = units
        self.format = format
        self.current_frequency=f_max-f_min


config_initial_values = { 
                   "port":"",
                   "baud_rate":"9600",
                   "bands":[FrequencyRange(550, 1600, 1, 'KHz', label='AM Broadcast'),
                            FrequencyRange(1600, 4000, 1, 'KHz', label= 'Short Wave 1'),
                            FrequencyRange(88, 106, 1, 'MHz', format='FM', label='FM Broadcast')],
                    "current_band_index":0,
                    "current_volume":32,
                    
                }

class ConfigView:
    
    def __init__(self):
        self.__dict__=config_initial_values

@singleton
class Configuration(object):
    
    # Make this a singleton instance
    
    def __init__(self):
        self.config_view=ConfigView()
        self.home_path=Path.home()
        self.db_dir=user_config_dir("arduino_radio")
        try:
            makedirs(self.db_dir)
        except FileExistsError:
            pass

        self.db_file=path.normpath(self.db_dir + "/.arduino_radio")
        with shelve.open(self.db_file, writeback=True) as db:
            if 'values' not in db:
                db['values']=self.config_view.__dict__
            else:
                self.config_view.__dict__ = db['values']
            #if there are new values, merge them into the db
            for key in config_initial_values.keys():
                if key not in self.config_view.__dict__:
                    self.config_view.__dict__[key] = config_initial_values[key]
            db.sync()
    
    def update_configuration(self):
        with shelve.open(self.db_file, writeback=True) as db:
            db['values']=self.config_view.__dict__
            db.sync()
            