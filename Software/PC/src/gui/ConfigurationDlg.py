"""Subclass of ConfigurationDlg, which is generated by wxFormBuilder."""

import wx
from gui.ArduinoRadioMainWindow import MainWindow
from utilities.db import Db, DbView, Band
from gui.EditBandDlg import EditBandDlg

# Implementing ConfigurationDlg


class ConfigurationDlg(MainWindow.ConfigurationDlg):
    def __init__(self, parent):
        MainWindow.ConfigurationDlg.__init__(self, parent)
        self.database = Db()
        self.db: DbView() = self.database.db_view
        self.bands=list(self.db.bands)
        self.band_index: int = 0

    # Handlers for ConfigurationDlg events.
    def ConfigurationDlgOnInitDialog(self, event):

        self.enable_tuning_cb.SetValue(self.db.enable_tuning) 
        self.enable_volume_cb.SetValue(self.db.enable_volume_control)  
        self.enable_band_switch_cb.SetValue(self.db.enable_band_switch)
        for heading in ('label', 'Min Freq.', 'Max Freq.', 'Unit', 'Mode'):
            self.band_list_ctrl.AppendColumn(heading,
                                            format=wx.LIST_FORMAT_CENTRE,
                                            width=wx.LIST_AUTOSIZE)
        self.update_list_control()
        pass

    def configuration_pageOnNotebookPageChanged(self, event):
        # TODO: Implement configuration_pageOnNotebookPageChanged
        pass

    def band_list_ctrlOnListItemActivated(self, event):
        self.band_index = event.GetIndex()
        dlg = EditBandDlg(self, self.db.bands[self.band_index])
        result = dlg.ShowModal()
        if result == wx.OK:
            self.db.bands[self.band_index] = dlg.band_info
        pass

    def band_list_ctrlOnListItemSelected(self, event):
        self.band_index = event.GetIndex()
        pass

    def add_band_btnOnButtonClick(self, event):
        dlg = EditBandDlg(self, None)
        result = dlg.ShowModal()
        if result == wx.OK:
            self.bands.append(Band(dlg.band_info.f_min,
                                   dlg.band_info.f_max,
                                   dlg.band_info.scale,
                                   dlg.band_info.units,
                                   dlg.band_info.mode))
        self.update_list_control()
        pass

    def remove_band_btnOnButtonClick(self, event):
        selected = self.band_list_ctrl.GetFirstSelected()
        if selected != -1:
            self.bands.pop(selected)
            self.update_list_control()
        pass

    def move_band_up_btnOnButtonClick(self, event):
        self.band_index = self.band_list_ctrl.GetFirstSelected()
        if self.band_index > 0:
            band = self.bands.pop(self.band_index)
            self.band_index -= 1
            self.bands.insert(self.band_index, band)
            self.update_list_control()
        pass

    def move_band_down_btnOnButtonClick(self, event):
        self.band_index = self.band_list_ctrl.GetFirstSelected()
        if self.band_index != -1 and self.band_index < len(self.bands)-2:
            band = self.bands.pop(self.band_index)
            self.band_index +=1
            self.bands.insert(self.band_index, band)
            self.update_list_control()
        pass

    def ok_btnOnButtonClick(self, event):
        self.db.enable_tuning = self.enable_tuning_cb.IsChecked()
        self.db.enable_volume_cb = self.enable_volume_cb.IsChecked()
        self.db.enable_band_switch = self.enable_band_switch_cb.IsChecked()
        self.db.bands=self.bands
        self.database.update_db()
        self.EndModal(wx.OK)

    def cancel_btnOnButtonClick(self, event):
        self.EndModal(wx.CANCEL)
        
    def update_list_control(self):
        """Redraws the list control"""
        self.band_list_ctrl.DeleteAllItems()
        for band in self.bands:
            self.band_list_ctrl.Append((band.label,
                                        band.format_frequency(band.f_min),
                                        band.format_frequency(band.f_max),
                                        band.units,
                                        band.mode))
        self.band_list_ctrl.SetColumnWidth(0, width=wx.LIST_AUTOSIZE)
        self.band_list_ctrl.Select(self.band_index)
