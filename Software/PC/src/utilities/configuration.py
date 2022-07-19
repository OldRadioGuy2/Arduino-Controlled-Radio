
import shelve
from pathlib import Path
from os import path
import logging
logger = logging.getLogger(__name__)

config_initial_values = { 
                   "port":"",
                   "baud_rate":"9600"
                }

class ConfigView:
    
    def __new__(cls):
        if not hasattr(cls, 'instance'):
            cls.instance= super(ConfigView, cls).__new__(cls)
        return cls.instance
       
        def __init__(self):
            self.__dict__=config_initial_values

class Configuration(object):
    
    # Make this a singleton instance
    
    def __init__(self):
        self. config_view=ConfigView()
        self.home_path=Path.home()
        self.db_file=path.normpath(str(self.home_path) + "/.arduino_radio")
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
            