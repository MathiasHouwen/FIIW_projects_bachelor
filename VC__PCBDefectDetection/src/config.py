# Configs
BASE_PATH = './../images'
PROCESS_PARAMS = {
    'test_1': {},
    'test_2': {
        '01': {'min_defect_area': 50, 'thresh': 190},
        '05': {'min_defect_area': 50, 'thresh': 150}
    },
    'test_3': {
        '01': {'min_defect_area': 30, 'thresh': 180},
        '05': {'min_defect_area': 30, 'thresh': 180}
    },
    'test_4': {
        '01': {'notch': (540, 140)},
        '05': {'notch': (450, 220)}
    },
    'test_5': {
        '01': {'filter': False},
        '05': {'filter': False}
    },
    'test_6': {
        '01': {'filter': True, 'thresh': 150},
        '05': {'filter': True}
    }

}