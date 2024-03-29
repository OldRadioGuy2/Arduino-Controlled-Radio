"""Subclass of MainWindow, which is generated by wxFormBuilder."""

import wx
import wx.lib.newevent
from gui import MainWindow
from gui.SelectPortDlg import SelectPortDlg
from gui.ConfigurationDlg import ConfigurationDlg
from utilities import db
from utilities.db import Band
from utilities import serial

import logging
logger = logging.getLogger(__name__)

SerialRxEvent, EVT_SERIALRX = wx.lib.newevent.NewEvent()
SERIALRX = wx.NewEventType()

# Implementing MainWindow


class ArduinoRadioMainWindow(MainWindow.MainWindow):
    def __init__(self, parent):
        MainWindow.MainWindow.__init__(self, parent)
        self.db = db.Db()
        self.db_view = self.db.db_view
        self.serial_port = serial.SerialIO(self, SerialRxEvent)

        self.tuning_slider.Bind(wx.EVT_SLIDER, self.tuning_sliderOnSlider)
        self.set_band(self.db_view.current_band_index)
        self.set_volume(self.db_view.current_volume, update_control=True)

        self.populate_band_chooser()
        self.band_switch.SetSelection(self.db_view.current_band_index)

        self.status_bar.SetStatusText("Disconnected", 0)
        self.status_bar.SetStatusText("Port: {0}".format(self.db_view.port), 1)
        self.status_bar.SetStatusText(
            "Baud Rate: {0}".format(self.db_view.baud_rate))
        self.Bind(EVT_SERIALRX, self.serial_receive)

    # Utilities
    def resize_slider(self) -> None:
        window_size = self.GetSize()
        control_size = self.tuning_slider.GetSize()
        self.tuning_slider.SetSize(
            wx.Size(window_size.width-20, control_size.height))

    def set_band(self, band_index: int) -> None:
        self.db_view.current_band_index = band_index
        band = self.db_view.bands[band_index]
        f_min = int(band.f_min*band.scale)
        f_max = int(band.f_max*band.scale)
        self.tuning_slider.SetRange(f_min, f_max)
        self.static_min_frequency.SetLabel(
            "{0}{1}".format(band.f_min, band.units))
        self.static_max_frequency.SetLabel(
            "{0}{1}".format(band.f_max, band.units))
        self.serial_send("SB,{0},{1},{2},{3},{4},{5}".format(f_min,
                                                             f_max,
                                                             band.scale,
                                                             band.units,
                                                             band.mode,
                                                             band.label
                                                             ))
        self.set_frequency(band.current_frequency, update_control=True)

    def set_frequency(self, freq: int, update_control: bool = False) -> None:
        current_band = self.db_view.bands[self.db_view.current_band_index]
        current_band.current_frequency = freq
        if update_control:
            self.tuning_slider.SetValue(freq)
        self.static_current_frequency.SetLabel("{0}".format(freq))
        x = self.serial_send("SF,{:d}".format(freq))
        # ToDo: insert board command

    def set_volume(self, volume: int, update_control: bool = False) -> None:
        self.db_view.current_volume = volume
        if update_control:
            self.volume_control.SetValue(volume)
        self.serial_send('sv,{:d}'.format(volume))

    def populate_band_chooser(self) -> None:
        self.band_switch.Clear()
        for band in self.db_view.bands:
            self.band_switch.Append(band.format_frequency_range())

    def serial_send(self, cmd: str) -> None:
        self.terminal_text_ctrl.AppendText(cmd + '\n')
        self.serial_port.write_string(cmd + '\n')

    # Handlers for MainWindow events.
    def MainWindowOnShow(self, event):
        self.resize_slider()
        self.serial_port.open(self.db_view.port, self.db_view.baud_rate)
        pass

    def MainWindowOnSize(self, event):
        self.resize_slider()

    def MainWindowOnClose(self, event):
        self.serial_port.close()
        self.db.update_db()
        self.Destroy()

    def tuning_sliderOnSlider(self, event):
        self.tuning_slider.GetValue()
        self.set_frequency(self.tuning_slider.GetValue())

    def volume_controlOnSpinCtrl(self, event):
        volume = self.volume_control.GetValue()
        self.set_volume(volume)
        pass

    def band_switchOnChoice(self, event):
        band_index = self.band_switch.GetSelection()
        if band_index != wx.NOT_FOUND:
            self.set_band(band_index)
        pass

    def command_entryOnTextEnter(self, event):
        to_send = self.command_entry.GetValue()+'\n'
        self.terminal_text_ctrl.AppendText(to_send)
        self.serial_port.write_string(to_send)
        self.command_entry.Clear()
        pass

    # Menu Events
    def file_select_portOnMenuSelection(self, event):
        dlg = SelectPortDlg(self)
        if dlg.ShowModal() == wx.OK:
            self.db_view.port = dlg.get_port()
            self.db_view.baud_rate = dlg.get_baud_rate()
            self.db.update_db()
            self.serial_port.close()
            self.serial_port.open(self.db_view.port, self.db_view.baud_rate)
            self.status_bar.SetStatusText(
                "Port: {0}".format(self.db_view.port), 1)
        pass

    def file_exitOnMenuSelection(self, event):
        self.MainWindowOnClose(event)

    def configure_configureOnMenuSelection(self, event):
        dlg = ConfigurationDlg(self)
        result = dlg.ShowModal()
        if result == wx.ID_OK:
            pass

    # Bound Events
    def serial_receive(self, event):
        default_style = self.terminal_text_ctrl.GetDefaultStyle()
        self.terminal_text_ctrl.SetDefaultStyle(wx.TextAttr(
            wx.ColourDatabase().Find('MEDIUM FOREST GREEN')))
        self.terminal_text_ctrl.AppendText(
            event.data.decode('UTF-8', 'replace'))
        self.terminal_text_ctrl.SetDefaultStyle(default_style)
        pass
