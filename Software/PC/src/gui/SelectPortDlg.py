"""Subclass of SelectPortDlg, which is generated by wxFormBuilder."""

import wx
from gui import MainWindow
import serial
import serial.tools.list_ports

from utilities import configuration

# Implementing SelectPortDlg
class SelectPortDlg( MainWindow.SelectPortDlg ):
	def __init__( self, parent ):
		MainWindow.SelectPortDlg.__init__( self, parent )
		self.ports=serial.tools.list_ports.comports()

	def get_port(self):
		return self.port_chooser.GetString(self.port_chooser.GetSelection())

	def get_baud_rate(self):
		return self.baud_rate_chooser.GetString(self.baud_rate_chooser.GetSelection())

	# Handlers for SelectPortDlg events.
	def SelectPortDlgOnInitDialog( self, event ):
		for port in self.ports:
			self.port_chooser.Append(port.device)

		config=configuration.Configuration().config_view
		current_port = config.port
		idx=self.port_chooser.FindString(current_port)
		if idx != wx.NOT_FOUND:
			self.port_chooser.SetSelection(idx)
		else:
			self.port_chooser.SetSelection(0)
		current_baud_rate = config.baud_rate
		idx = self.baud_rate_chooser.FindString(current_baud_rate)
		if idx != wx.NOT_FOUND:
			self.baud_rate_chooser.SetSelection(idx)
		pass

	def port_chooserOnChoice( self, event ):
		# TODO: Implement port_chooserOnChoice
		pass

	def on_ok_button_click(self, event):
		self.EndModal(wx.OK)

	def on_cancel_button_click(self, event):
		self.EndModal(wx.CANCEL)

