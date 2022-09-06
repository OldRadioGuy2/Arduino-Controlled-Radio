
import shelve
from pathlib import Path
from os import path
from os import makedirs
from enum import Enum
from platformdirs import user_config_dir
from utilities.singleton import singleton
import logging
logger = logging.getLogger(__name__)

#Units=ENUM('Units', 'KHz MHz' )
#Mode=ENUM('Mode', 'AM FM SSB')

class Band:
    """ A class used to represent a frequency band
    
    Attributes
    ----------
    f_min: float
        The lowest frequency for the band
    f_max: float
        The highest frequency for the band
    scale: int
        Scale factor multiplier to use when displaying frequencies
    units: str
        KHz or MHz
    mode: str
        AM, FM, or SSB
    label: str
        The visible label for the band
        
    Methods
    -------
    format_frequency_range
        returns a string containg the frequency range with units
    format_frequency
        returns a string wit ha frequency and units
    """
    
    
    def __init__(self, f_min:float, f_max:float, scale:int, units:str, mode:str='AM', label:str='' ):
        """
        Parameters
        ----------
        f_min: float
            The lowest frequency for the band
        f_max: float
            The highest frequency for the band
        scale: int
            Scale factor multiplier to use when displaying frequencies
        units: str
            KHz or MHz
        mode: str
            AM, FM, or SSB
        label: str
            The visible label for the band
        """
        self.label:str = label
        self.f_min:float() = float(f_min)
        self.f_max:float = float(f_max)
        self.scale:int = scale
        self.units:str = units
        self.mode:str = mode
        self.current_frequency:float=f_max-f_min
    
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
                    "enable_tuning":False,
                    "enable_volume_control":False,
                    "enable_band_switch":False
                    
                }

class DbView:
    """
    Implements the database data as attributes. Initially
    contains the contents of db_initial_values
    """
    def __init__(self):
        self.__dict__=db_initial_values

@singleton
class Db(object):
    """
    Impements the configuration database and store/recall. Contains
    the DbView representation of the current data
    
    Attributes
    ----------
    db_view: DbView
        The current configuration database
    
    Methods
    -------
        update_db
            Updates the 'Shelve' storage file
    
    """
    
    # Make this a singleton instance
    
    def __init__(self):
        """
        Loads the 'Shelve' file or creates it if it doesn't exist
        then updates it with any new items from db_initial_values
        and finally fills the DbView with data
        """
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
        """ Updates the Shelve file with the current configuration data"""
        with shelve.open(self.db_file, writeback=True) as db:
            db['values']=self.db_view.__dict__
            db.sync()
            