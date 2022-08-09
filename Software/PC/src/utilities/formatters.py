from utilities.configuration import FrequencyRange

def format_frequency_range(band:FrequencyRange) -> str:
    if band.units == 'KHz':
        return '{:s}: {:.0f}-{:.0f}{:s}'.format(band.label, 
                                                band.f_min,
                                                band.f_max,
                                                band.units)
    else:
        return '{:s}: {:.2f}-{:.2f}{:s}'.format(band.label, 
                                                band.f_min,
                                                band.f_max,
                                                band.units)