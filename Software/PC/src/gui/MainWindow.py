# -*- coding: utf-8 -*-

###########################################################################
## Python code generated with wxFormBuilder (version Oct 26 2018)
## http://www.wxformbuilder.org/
##
## PLEASE DO *NOT* EDIT THIS FILE!
###########################################################################

import wx
import wx.xrc

###########################################################################
## Class MainWindow
###########################################################################

class MainWindow ( wx.Frame ):

	def __init__( self, parent ):
		wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = u"Arduino Radio", pos = wx.DefaultPosition, size = wx.Size( 729,700 ), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL )

		self.SetSizeHints( wx.DefaultSize, wx.DefaultSize )

		self.m_menubar1 = wx.MenuBar( 0 )
		self.m_menu1 = wx.Menu()
		self.file_select_port = wx.MenuItem( self.m_menu1, wx.ID_ANY, u"Select Serial Port", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu1.Append( self.file_select_port )

		self.file_load_config = wx.MenuItem( self.m_menu1, wx.ID_ANY, u"Load Configuration", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu1.Append( self.file_load_config )

		self.file_save_config = wx.MenuItem( self.m_menu1, wx.ID_ANY, u"Save Configuration", wx.EmptyString, wx.ITEM_NORMAL )
		self.m_menu1.Append( self.file_save_config )

		self.m_menubar1.Append( self.m_menu1, u"File" )

		self.m_menu4 = wx.Menu()
		self.m_menubar1.Append( self.m_menu4, u"Configure" )

		self.m_menu2 = wx.Menu()
		self.m_menubar1.Append( self.m_menu2, u"Calibrate" )

		self.m_menu3 = wx.Menu()
		self.m_menubar1.Append( self.m_menu3, u"Help" )

		self.SetMenuBar( self.m_menubar1 )

		self.status_bar = self.CreateStatusBar( 4, 0, wx.ID_ANY )
		bSizer1 = wx.BoxSizer( wx.VERTICAL )

		self.m_staticText1 = wx.StaticText( self, wx.ID_ANY, u"Tuning", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText1.Wrap( -1 )

		bSizer1.Add( self.m_staticText1, 0, wx.ALL, 5 )

		bSizer2 = wx.BoxSizer( wx.HORIZONTAL )


		bSizer2.Add( ( 10, 0), 0, wx.EXPAND, 5 )

		self.static_min_frequency = wx.StaticText( self, wx.ID_ANY, u"540", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.static_min_frequency.Wrap( -1 )

		bSizer2.Add( self.static_min_frequency, 0, wx.ALL, 5 )


		bSizer2.Add( ( 0, 0), 1, wx.EXPAND, 5 )

		self.static_current_frequency = wx.StaticText( self, wx.ID_ANY, u"1030", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.static_current_frequency.Wrap( -1 )

		bSizer2.Add( self.static_current_frequency, 0, wx.ALL, 5 )


		bSizer2.Add( ( 0, 0), 1, wx.EXPAND, 5 )

		self.static_max_frequency = wx.StaticText( self, wx.ID_ANY, u"1620", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.static_max_frequency.Wrap( -1 )

		bSizer2.Add( self.static_max_frequency, 0, wx.ALL, 5 )


		bSizer2.Add( ( 20, 0), 0, wx.EXPAND, 5 )


		bSizer1.Add( bSizer2, 0, wx.EXPAND, 5 )

		bSizer3 = wx.BoxSizer( wx.HORIZONTAL )

		self.tuning_slider=wx.Slider(self, size=wx.DefaultSize)
		bSizer3.Add( self.tuning_slider, 0, wx.ALL, 5 )


		bSizer1.Add( bSizer3, 0, wx.EXPAND, 5 )

		bSizer5 = wx.BoxSizer( wx.HORIZONTAL )


		bSizer5.Add( ( 150, 0), 0, wx.EXPAND, 5 )

		self.scan_down_button = wx.BitmapButton( self, wx.ID_ANY, wx.NullBitmap, wx.DefaultPosition, wx.DefaultSize, wx.BU_AUTODRAW|0 )

		self.scan_down_button.SetBitmap( wx.ArtProvider.GetBitmap( wx.ART_GO_BACK,  ) )
		bSizer5.Add( self.scan_down_button, 0, wx.ALL, 5 )


		bSizer5.Add( ( 50, 0), 1, wx.EXPAND, 5 )

		self.scan_up_button = wx.BitmapButton( self, wx.ID_ANY, wx.NullBitmap, wx.DefaultPosition, wx.DefaultSize, wx.BU_AUTODRAW|0 )

		self.scan_up_button.SetBitmap( wx.ArtProvider.GetBitmap( wx.ART_GO_FORWARD,  ) )
		bSizer5.Add( self.scan_up_button, 0, wx.ALL, 5 )


		bSizer5.Add( ( 150, 0), 0, wx.EXPAND, 5 )


		bSizer1.Add( bSizer5, 0, wx.EXPAND, 5 )

		self.m_staticline1 = wx.StaticLine( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.LI_HORIZONTAL )
		bSizer1.Add( self.m_staticline1, 0, wx.EXPAND |wx.ALL, 5 )

		bSizer4 = wx.BoxSizer( wx.HORIZONTAL )


		bSizer4.Add( ( 40, 0), 0, wx.EXPAND, 5 )

		self.m_staticText5 = wx.StaticText( self, wx.ID_ANY, u"Volume", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText5.Wrap( -1 )

		bSizer4.Add( self.m_staticText5, 0, wx.ALIGN_CENTER_VERTICAL|wx.ALL, 5 )

		self.volume_control = wx.SpinCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, wx.SP_ARROW_KEYS, 0, 64, 33 )
		bSizer4.Add( self.volume_control, 0, wx.ALL, 5 )


		bSizer4.Add( ( 0, 0), 1, wx.EXPAND, 5 )

		self.m_staticText6 = wx.StaticText( self, wx.ID_ANY, u"Band", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText6.Wrap( -1 )

		bSizer4.Add( self.m_staticText6, 0, wx.ALIGN_CENTER_VERTICAL|wx.ALL, 5 )

		band_switchChoices = [ u"AM:  540-1620kHz", u"SW1: 1.7-4.0MHz", u"80M Ham: 3.5-4.0MHz", u"FM: 88-108MHz", wx.EmptyString ]
		self.band_switch = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, band_switchChoices, 0 )
		self.band_switch.SetSelection( 0 )
		bSizer4.Add( self.band_switch, 0, wx.ALL, 5 )


		bSizer4.Add( ( 0, 0), 1, wx.EXPAND, 5 )


		bSizer1.Add( bSizer4, 0, wx.EXPAND, 5 )

		self.m_staticline2 = wx.StaticLine( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.LI_HORIZONTAL )
		bSizer1.Add( self.m_staticline2, 0, wx.EXPAND |wx.ALL, 5 )

		bSizer6 = wx.BoxSizer( wx.HORIZONTAL )


		bSizer6.Add( ( 20, 0), 0, wx.EXPAND, 5 )

		self.m_staticText7 = wx.StaticText( self, wx.ID_ANY, u"Signal Level", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText7.Wrap( -1 )

		bSizer6.Add( self.m_staticText7, 0, wx.ALIGN_TOP|wx.ALL, 5 )

		self.signal_level_guage = wx.Gauge( self, wx.ID_ANY, 255, wx.DefaultPosition, wx.DefaultSize, wx.GA_HORIZONTAL|wx.GA_SMOOTH )
		self.signal_level_guage.SetValue( 128 )
		bSizer6.Add( self.signal_level_guage, 0, wx.ALL, 5 )


		bSizer6.Add( ( 0, 0), 1, wx.EXPAND, 5 )

		self.m_staticText8 = wx.StaticText( self, wx.ID_ANY, u"S/N Ratio", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText8.Wrap( -1 )

		bSizer6.Add( self.m_staticText8, 0, wx.ALIGN_CENTER_VERTICAL|wx.ALL, 5 )

		self.m_gauge2 = wx.Gauge( self, wx.ID_ANY, 256, wx.DefaultPosition, wx.DefaultSize, wx.GA_HORIZONTAL|wx.GA_SMOOTH )
		self.m_gauge2.SetValue( 128 )
		bSizer6.Add( self.m_gauge2, 0, wx.ALIGN_TOP|wx.ALL, 5 )


		bSizer6.Add( ( 20, 0), 1, wx.EXPAND, 5 )


		bSizer1.Add( bSizer6, 0, wx.EXPAND, 5 )

		bSizer7 = wx.BoxSizer( wx.VERTICAL )

		self.terminal_text_ctrl = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, wx.TE_MULTILINE|wx.TE_READONLY )
		bSizer7.Add( self.terminal_text_ctrl, 1, wx.ALL|wx.EXPAND, 5 )

		self.m_staticText9 = wx.StaticText( self, wx.ID_ANY, u"Enter Command", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText9.Wrap( -1 )

		bSizer7.Add( self.m_staticText9, 0, wx.ALL, 5 )

		self.command_entry = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.Size( -1,-1 ), wx.TE_PROCESS_ENTER )
		self.command_entry.SetMinSize( wx.Size( -1,50 ) )

		bSizer7.Add( self.command_entry, 0, wx.ALL|wx.EXPAND, 5 )


		bSizer1.Add( bSizer7, 1, wx.EXPAND, 5 )


		self.SetSizer( bSizer1 )
		self.Layout()

		self.Centre( wx.BOTH )

		# Connect Events
		self.Bind( wx.EVT_CLOSE, self.MainWindowOnClose )
		self.Bind( wx.EVT_SHOW, self.MainWindowOnShow )
		self.Bind( wx.EVT_SIZE, self.MainWindowOnSize )
		self.Bind( wx.EVT_MENU, self.file_select_portOnMenuSelection, id = self.file_select_port.GetId() )
		self.volume_control.Bind( wx.EVT_SPINCTRL, self.volume_controlOnSpinCtrl )
		self.band_switch.Bind( wx.EVT_CHOICE, self.band_switchOnChoice )
		self.command_entry.Bind( wx.EVT_TEXT_ENTER, self.command_entryOnTextEnter )

	def __del__( self ):
		pass


	# Virtual event handlers, overide them in your derived class
	def MainWindowOnClose( self, event ):
		event.Skip()

	def MainWindowOnShow( self, event ):
		event.Skip()

	def MainWindowOnSize( self, event ):
		event.Skip()

	def file_select_portOnMenuSelection( self, event ):
		event.Skip()

	def volume_controlOnSpinCtrl( self, event ):
		event.Skip()

	def band_switchOnChoice( self, event ):
		event.Skip()

	def command_entryOnTextEnter( self, event ):
		event.Skip()


###########################################################################
## Class SelectPortDlg
###########################################################################

class SelectPortDlg ( wx.Dialog ):

	def __init__( self, parent ):
		wx.Dialog.__init__ ( self, parent, id = wx.ID_ANY, title = u"Select Serial Port", pos = wx.DefaultPosition, size = wx.Size( 336,261 ), style = wx.DEFAULT_DIALOG_STYLE )

		self.SetSizeHints( wx.DefaultSize, wx.DefaultSize )

		bSizer8 = wx.BoxSizer( wx.VERTICAL )


		bSizer8.Add( ( 0, 40), 0, wx.EXPAND, 5 )

		bSizer9 = wx.BoxSizer( wx.HORIZONTAL )

		gSizer1 = wx.GridSizer( 2, 2, 0, 0 )

		self.m_staticText10 = wx.StaticText( self, wx.ID_ANY, u"Port:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText10.Wrap( -1 )

		gSizer1.Add( self.m_staticText10, 0, wx.LEFT, 5 )

		self.m_staticText11 = wx.StaticText( self, wx.ID_ANY, u"Baud Rate:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText11.Wrap( -1 )

		gSizer1.Add( self.m_staticText11, 0, wx.LEFT, 5 )

		port_chooserChoices = []
		self.port_chooser = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, port_chooserChoices, 0 )
		self.port_chooser.SetSelection( 0 )
		gSizer1.Add( self.port_chooser, 0, wx.LEFT, 5 )

		baud_rate_chooserChoices = [ u"1200", u"9600", u"19200", u"115200", wx.EmptyString, wx.EmptyString ]
		self.baud_rate_chooser = wx.Choice( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, baud_rate_chooserChoices, 0 )
		self.baud_rate_chooser.SetSelection( 1 )
		gSizer1.Add( self.baud_rate_chooser, 0, wx.LEFT, 5 )


		bSizer9.Add( gSizer1, 1, wx.EXPAND, 5 )


		bSizer8.Add( bSizer9, 0, wx.EXPAND, 5 )


		bSizer8.Add( ( 0, 0), 1, wx.EXPAND, 5 )

		m_sdbSizer1 = wx.StdDialogButtonSizer()
		self.m_sdbSizer1OK = wx.Button( self, wx.ID_OK )
		m_sdbSizer1.AddButton( self.m_sdbSizer1OK )
		self.m_sdbSizer1Cancel = wx.Button( self, wx.ID_CANCEL )
		m_sdbSizer1.AddButton( self.m_sdbSizer1Cancel )
		m_sdbSizer1.Realize();

		bSizer8.Add( m_sdbSizer1, 0, wx.BOTTOM|wx.EXPAND, 5 )


		self.SetSizer( bSizer8 )
		self.Layout()

		self.Centre( wx.BOTH )

		# Connect Events
		self.Bind( wx.EVT_INIT_DIALOG, self.SelectPortDlgOnInitDialog )
		self.port_chooser.Bind( wx.EVT_CHOICE, self.port_chooserOnChoice )
		self.m_sdbSizer1Cancel.Bind( wx.EVT_BUTTON, self.on_cancel_button_click )
		self.m_sdbSizer1OK.Bind( wx.EVT_BUTTON, self.on_ok_button_click )

	def __del__( self ):
		pass


	# Virtual event handlers, overide them in your derived class
	def SelectPortDlgOnInitDialog( self, event ):
		event.Skip()

	def port_chooserOnChoice( self, event ):
		event.Skip()

	def on_cancel_button_click( self, event ):
		event.Skip()

	def on_ok_button_click( self, event ):
		event.Skip()


