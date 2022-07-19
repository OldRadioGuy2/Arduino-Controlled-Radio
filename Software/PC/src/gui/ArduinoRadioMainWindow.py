"""Subclass of MainWindow, which is generated by wxFormBuilder."""

import wx
import wx.lib.newevent
from gui import MainWindow
from gui.SelectPortDlg import SelectPortDlg
from utilities import configuration
from utilities import serial

import logging
logger = logging.getLogger(__name__)

SerialRxEvent, EVT_SERIALRX = wx.lib.newevent.NewEvent()
SERIALRX = wx.NewEventType()

class FrequencyRange:
    def __init__(self, f_min:int, f_max:int, scale:str):
        self.f_min = f_min
        self.f_max = f_max
        self.scale = scale
        self.port = ""
        

# Implementing MainWindow
class ArduinoRadioMainWindow( MainWindow.MainWindow ):
	def __init__( self, parent ):
		MainWindow.MainWindow.__init__( self, parent )
		self.configuration= configuration.Configuration()
		self.config = self.configuration.config_view
		self.tuning_slider.Bind(wx.EVT_SLIDER, self.tuning_sliderOnSlider)
		#self.volume_ctrl._minvalue = 0		
		self.current_frequency = int(1030)
		self.current_range= FrequencyRange(540,1620,'kHz')
		self.set_frequency_range(self.current_range)
		self.set_frequency(self.current_frequency, self.current_range)
		self.status_bar.SetStatusText("Disconnected", 0)
		self.status_bar.SetStatusText("Port: {0}".format(self.config.port),1)
		self.status_bar.SetStatusText("Baud Rate: {0}".format(self.config.baud_rate))
		self.Bind(EVT_SERIALRX, self.serial_receive)
		self.serial_port=serial.SerialIO(self, SerialRxEvent)
  
    
	# Utilities
	def resize_slider(self) -> None:
		window_size=self.GetSize()
		control_size=self.tuning_slider.GetSize()
		self.tuning_slider.SetSize(wx.Size(window_size.width-20,control_size.height))
  
	def set_frequency(self, freq:int, update_slider:bool=False) -> None:
		self.current_frequency= freq
		if freq < self.current_range.f_min or freq > self.current_range.f_max:
			logger.error("set_frequency: Value out of range: {0}".format(freq))
		if update_slider:
			self.tuning_slider.SetValue(freq)
		self.static_current_frequency.SetLabel("{0}".format(self.tuning_slider.GetValue()))
		# ToDo: insert board command

 	
	def set_frequency_range(self, range:FrequencyRange) -> None:
		if range.f_min >= range.f_max:
			logger.error("set_frequency_range: range min ({0}) >= max ({1})".format(range.f_min, range.f_max))
			return
		self.current_range=range
		self.tuning_slider.SetRange(range.f_min, range.f_max)
		self.static_min_frequency.SetLabel("{0}{1}".format(range.f_min,range.scale))
		self.static_max_frequency.SetLabel("{0}{1}".format(range.f_max,range.scale))
		self.set_frequency( int((range.f_max-range.f_min)), update_slider=True )
		
		# ToDo: insert board command
  
     
	# Handlers for MainWindow events.
	def MainWindowOnShow( self, event ):
		self.resize_slider()
		self.serial_port.open(self.config.port, self.config.baud_rate)
		pass

	def MainWindowOnSize(self, event):
		self.resize_slider()
  
	def MainWindowOnClose(self, event):
		self.serial_port.close()
		self.Destroy()
  
	def tuning_sliderOnSlider(self,event):
		self.current_frequency=self.tuning_slider.GetValue()
		self.set_frequency(self.current_frequency)

	def volume_controlOnSpinCtrl(self, event):
		pass

	def band_switchOnChoice(self, event):
		pass

	def command_entryOnTextEnter(self,event):
		to_send=self.command_entry.GetValue()+'\n'
		self.terminal_text_ctrl.AppendText(to_send)
		x=self.serial_port.write_string(to_send)
		self.command_entry.Clear()
		pass

	# Menu Events
	def file_select_portOnMenuSelection(self, event):
		dlg=SelectPortDlg(self)
		if dlg.ShowModal() == wx.OK:
			self.config.port = dlg.get_port()
			self.config.baud_rate = dlg.get_baud_rate()
			self.configuration.update_configuration()
			self.serial_port.close()
			self.serial_port.open(self.config.port, self.config.baud_rate)
			self.status_bar.SetStatusText("Port: {0}".format(self.config.port),1)
		pass

	# Bound Events
	def serial_receive(self,event):
		default_style=self.terminal_text_ctrl.GetDefaultStyle()
		self.terminal_text_ctrl.SetDefaultStyle(wx.TextAttr(wx.ColourDatabase().Find('MEDIUM FOREST GREEN')))
		self.terminal_text_ctrl.AppendText(event.data.decode('UTF-8', 'replace'))
		self.terminal_text_ctrl.SetDefaultStyle(default_style)
		pass