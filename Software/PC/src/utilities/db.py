
import shelve
from pathlib import Path
from os import path
from os import makedirs
from platformdirs import user_config_dir
from utilities.singleton import singleton
import logging
logger = logging.getLogger(__name__)


class Band:
    def __init__(self, f_min:float, f_max:float, scale:int, units:str, mode='AM', label='' ):
        self.label = label
        self.f_min = f_min
        self.f_max = f_max
        self.scale = scale
        self.units = units
        self.mode = mode
        self.current_frequency=f_max-f_min
    
    def format_frequency_range(self) -> str:
        if self.units == 'KHz':
            return '{:s}: {:.0f}-{:.0f}{:s}'.format(self.label, 
                                                    self.f_min,
                                                    self.f_max,
                                                    self.units)
        else:
            return '{:s}: {:.2f}-{:.2f}{:s}'.format(self.label, 
                                                    self.f_min,
                                                    self.f_max,
                                                    self.units)

    def format_frequency(self, frequency:float) -> str:
        if self.units == 'KHz':
            return '{:.0f}'.format(frequency)
        else:
            return '{:.2f}'.format(frequency)


db_initial_values = { 
                   "port":"",
                   "baud_rate":"9600",
                   "bands":[Band(550, 1600, 1, 'KHz', label='AM Broadcast'),
                            Band(1600, 4000, 1, 'KHz', label= 'Short Wave 1'),
                            Band(88, 106, 1, 'MHz', mode='FM', label='FM Broadcast')],
                    "current_band_index":0,
                    "current_volume":32,
                    
                }

class DbView:
    
    def __init__(self):
        self.__dict__=db_initial_values

@singleton
class Db(object):
    
    # Make this a singleton instance
    
    def __init__(self):
        self.db_view=DbView()
        self.home_path=Path.home()
        self.db_dir=user_config_dir("arduino_radio")
        try:
            makedirs(self.db_dir)
        except FileExistsError:
            pass

        self.db_file=path.normpath(self.db_dir + "/.arduino_radio")
        with shelve.open(self.db_file, writeback=True) as db:
            if 'values' not in db:
                db['values']=self.db_view.__dict__
            else:
                self.db_view.__dict__ = db['values']
            #if there are new values, merge them into the db
            for key in db_initial_values.keys():
                if key not in self.db_view.__dict__:
                    self.db_view.__dict__[key] = db_initial_values[key]
            db.sync()
    
    def update_db(self):
        with shelve.open(self.db_file, writeback=True) as db:
            db['values']=self.db_view.__dict__
            db.sync()
            