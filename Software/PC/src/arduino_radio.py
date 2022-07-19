import wx
from gui.ArduinoRadioMainWindow import ArduinoRadioMainWindow
import logging
logger = logging.getLogger(__name__)


   
app = wx.App(False)
frame = ArduinoRadioMainWindow(None)
frame.Show()
app.MainLoop()